#ifndef SSH_KEYS_HPP
#define SSH_KEYS_HPP
#pragma once

#define RSA_HEADER_BEGIN "-----BEGIN RSA PRIVATE KEY-----"
#define RSA_HEADER_END "-----END RSA PRIVATE KEY-----"
#define DSA_HEADER_BEGIN "-----BEGIN DSA PRIVATE KEY-----"
#define DSA_HEADER_END "-----END DSA PRIVATE KEY-----"
#define ECDSA_HEADER_BEGIN "-----BEGIN EC PRIVATE KEY-----"
#define ECDSA_HEADER_END "-----END EC PRIVATE KEY-----"
#define OPENSSH_HEADER_BEGIN "-----BEGIN OPENSSH PRIVATE KEY-----"
#define OPENSSH_HEADER_END "-----END OPENSSH PRIVATE KEY-----"
/* Magic defined in OpenSSH/PROTOCOL.key */
#define OPENSSH_AUTH_MAGIC "openssh-key-v1"

#endif
