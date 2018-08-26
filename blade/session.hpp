#ifndef SSH_SESSION_HPP
#define SSH_SESSION_HPP
#pragma once
#include "net.hpp"
//
#include "server.hpp"

namespace ssh {
class SshSession : public std::enable_shared_from_this<SshSession> {
public:
  SshSession(const SshSession &) = delete;
  SshSession &operator=(const SshSession &) = delete;
  explicit SshSession(socket_t sock, const ServerContext &scontext)
      : sock_(std::move(sock)), scontext_(scontext) {
    //
  }
  void run();
  void send_msg_kexinit();
private:
  socket_t sock_;
  const ServerContext &scontext_;
};
} // namespace ssh

#endif