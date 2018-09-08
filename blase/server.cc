////////
#include "net.hpp"
//
#include <thread>
#include "session.hpp"
#include "blase.hpp"

namespace blase{
class IODevice {
public:
  IODevice(const IODevice &) = delete;
  IODevice &operator=(const IODevice &) = delete;
  explicit IODevice(std::size_t n = std::thread::hardware_concurrency()) {
    for (std::size_t i = 0; i < n; i++) {
		auto ctx = std::make_shared < net::io_context_t > ();
      auto work =
          std::make_shared<net::io_work_t>(boost::asio::make_work_guard(*ctx));
      contexts_.push_back(ctx);
      works_.push_back(work);
    }
  }
  void Execute() {
    std::vector<std::shared_ptr<std::thread>> threads;
    for (auto &ctx : contexts_) {
      std::shared_ptr<std::thread> thread(new std::thread([ctx]() {
        /// run
        ctx->run();
      }));
      threads.push_back(thread);
    }
    for (auto &t : threads) {
      t->join();
    }
  }
  void Exit() {
    for (auto &ioc : contexts_) {
      ioc->stop();
    }
  }

  net::io_context_t &Next() {
    auto &ioc = *contexts_[next_];
    ++next_;
    if (next_ == contexts_.size()) {
      next_ = 0;
    }
    return ioc;
  }
  void Clear() {
    /// clear worker
    works_.clear();
  }

private:
  using context_t = std::shared_ptr<net::io_context_t>;
  using work_t = std::shared_ptr<net::io_work_t>;
  std::vector<context_t> contexts_;
  std::vector<work_t> works_;
  std::size_t next_{0};
};

class HttpServer {
public:
#ifdef _WIN32
  HttpServer(std::size_t n) : iodevice_(n), acceptor_(iodevice_.Next()){};
#else
  HttpServer(std::size_t n)
      : iodevice_(n), acceptor_(iodevice_.Next()), sigs_(iodevice_.Next()){};
#endif
  HttpServer(const HttpServer &) = delete;
  HttpServer &operator=(const HttpServer &) = delete;
  ~HttpServer() {}

  void DelayExit() {
    net::error_code ec;
    acceptor_.close(ec);
    iodevice_.Clear();
  }
  void Acceptorclose(net::error_code &ec) {
    /// close acceptor
    acceptor_.close(ec);
  }
  void Exit() {
    net::error_code ec;
    acceptor_.close(ec);
    iodevice_.Exit();
  }
  int ListenAndServe(const std::string &addr, int port) {
    //
    net::error_code ec;
    net::endpoint_t ep(boost::asio::ip::make_address(addr, ec),
                  static_cast<unsigned int>(port));
    if (ec) {
      fprintf(stderr, "make_address: %s\n", ec.message().c_str());
      return -1;
    }
    acceptor_.open(ep.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    for (int i = 0;;) {
      acceptor_.bind(ep, ec);
      if (!ec) {
        break;
      }
      fprintf(stderr, "bind() %s:%d %s ", addr.c_str(), port,
              ec.message().c_str());
      i++;
      if (boost::asio::error::address_in_use != ec || i >= 10) {
        fprintf(stderr, "ERROR: blade exit: %s\n", ec.message().c_str());
        exit(127);
      }
#ifndef _WIN32
      usleep(10);
#else
      Sleep(100);
#endif
    }
    acceptor_.listen();
    // NOTE: When fork and exec a new process, should close acceptor FD !!!
    // Otherwise git-srv restart may not bind acceptor
#ifndef _WIN32
    auto acceptorFd = acceptor_.native_handle();
    fcntl(acceptorFd, F_SETFD, FD_CLOEXEC);
    sigs_.add(SIGUSR1, ec);
    sigs_.add(SIGUSR1, ec);
    sigs_.async_wait([this](error_code e, int sig) {
      if (!e) {
        if (sig == SIGUSR1) {
          Exit();
        } else if (sig == SIGUSR2) {
          DelayExit();
        }
      }
    });
#endif
    Accept();
    iodevice_.Execute();
    return 0;
  }

private:
  IODevice iodevice_;
  net::acceptor_t acceptor_;
#ifndef _WIN32
  signal_set sigs_;
#endif
  ServerContext scontext_;
  void Accept() {
    acceptor_.async_accept(
        iodevice_.Next(), [this](std::error_code ec, net::socket_t sock_) {
          if (ec) {
            if (sock_.is_open()) {
              fprintf(stderr, "acceptor is closed !\n");
            }
            return;
          }
      /// TO
#ifndef _WIN32
          ::fcntl(sock_.native_handle(), F_SETFD, FD_CLOEXEC);
#endif
          std::make_shared<HttpSession>(std::move(sock_), scontext_)->start();
          Accept();
        });
  }
};
}