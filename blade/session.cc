///
#include "session.hpp"

namespace ssh {
void SshSession::run() {
  // send_session_identification TODO our versions.
  // https://github.com/mkj/dropbear/blob/master/svr-session.c#L133
  // set no delay
}

void SshSession::kexfirstinitialise() {
  // initialize kex
}

// Key Exchange.
// https://github.com/mkj/dropbear/blob/d740dc548924f2faf0934e5f9a4b83d2b5d6902d/common-kex.c#L54
void SshSession::send_msg_kexinit() {
  //
}

} // namespace ssh