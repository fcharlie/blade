#ifndef BLASE_SESSION_HPP
#define BLASE_SESSION_HPP
#pragma once
#include "net.hpp"
//
#include <memory>
#include "blase.hpp"

namespace blase {

class HttpSession : public std::enable_shared_from_this<HttpSession> {
public:
  HttpSession(net::tcp::socket sock, const ServerContext &scontex)
      : sock_(std::move(sock)), scontex_(scontex) {
    //
  }
  HttpSession(const HttpSession &) = delete;
  HttpSession &operator=(const HttpSession &) = delete;
  void run();
  void HeaderCompleted();
  // Copy Request body to other socket pipe, file ...
  void WriteTo();

  // Read socket and pipe write to response body.
  void ReadFrom();

private:
  net::tcp::socket sock_;
  const ServerContext &scontex_;
};

} // namespace blase

#endif
