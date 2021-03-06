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
  HttpSession(net::tcp::socket sock) : sock_(std::move(sock)) {
    //
  }
  HttpSession(const HttpSession &) = delete;
  HttpSession &operator=(const HttpSession &) = delete;
  void run();
  void Dispatch();
  // Copy Request body to other socket pipe, file ...
  void WriteTo();

  // Read socket and pipe write to response body.
  void ReadFrom();

private:
  net::tcp::socket sock_;
  net::flat_buffer buffer;
  net::http::request<net::http::buffer_body> req;
};

} // namespace blase

#endif
