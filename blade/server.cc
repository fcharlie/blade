///
#include <memory>
#include "net.hpp"
#include "blade.hpp"
#include "server.hpp"


class ServeContext {
public:
  ServeContext(const ServeContext &) = delete;
  ServeContext &operator=(const ServeContext &) = delete;
  explicit ServeContext(std::size_t n = std::thread::hardware_concurrency()) {
    for (std::size_t i = 0; i < n; i++) {
      auto ctx = std::make_shared<io_context_t>();
      auto work =
          std::make_shared<io_work_t>(boost::asio::make_work_guard(*ctx));
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

  io_context_t &Next() {
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
  using context_t = std::shared_ptr<io_context_t>;
  using work_t = std::shared_ptr<io_work_t>;
  std::vector<context_t> contexts_;
  std::vector<work_t> works_;
  std::size_t next_{0};
};

class SshServer {
public:
  SshServer() = default;
  SshServer(const SshServer &) = delete;
  SshServer &operator=(const SshServer &) = delete;
  ~SshServer() {}
  int ListenAndServe(const std::string &addr, int port) {
    //
    return 0;
  }

private:
  void Accept() {
    // Accept Loop todo
  }
};