///
#include "session.hpp"

namespace blase {
void HttpSession::run() {
  /// begin to parse request.
  auto self(shared_from_this());
  net::http::async_read(sock_, buffer, req,
                        [this, self](net::error_code ec, std::size_t bytes) {
                          if (ec) {
                            /// disconnect
                            return;
                          }
                          // TODO resolve header.
                        });
  // net::http::async_read_header(sock_,)

}
void HttpSession::Dispatch() {
  //
}
void HttpSession::WriteTo() {
  //
  // net::http::async_read_some(sock_,,,[this]())
}
void HttpSession::ReadFrom() {
  //
}
} // namespace blase