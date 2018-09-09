#ifndef SERVER_HPP
#define SERVER_HPP
#pragma once
#include <string>

namespace ssh {
//
#ifdef _WIN32
typedef std::wstring string_t;
#else
typedef std::string string_t;
#endif

// Host keys path.
/*
WINDOWS
Administrator Require.
C:\ProgramData\ssh\
C:\ProgramData\ssh\ssh_host_rsa_key
C:\ProgramData\ssh\ssh_host_dsa_key
C:\ProgramData\ssh\ssh_host_ecdsa_key
C:\ProgramData\ssh\ssh_host_ed25519_key

LINUX
Root Require.
/etc/ssh/ssh_host_rsa_key
/etc/ssh/ssh_host_dsa_key
/etc/ssh/ssh_host_ecdsa_key
/etc/ssh/ssh_host_ed25519_key
*/
struct HostKeys {
  string_t RSA;
  string_t DSA;
  string_t ECDSA;
  string_t ED25519;
};
struct ServerContext {
  std::string banner;
};
} // namespace ssh

#endif
