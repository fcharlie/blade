#ifndef BLADE_HPP
#define BLADE_HPP
#pragma once

#ifndef BLADE_VERSION
#define BLADE_VERSION "2018.09"
#endif


#define BLADE_IDENT "SSH-2.0-Blade-" BLADE_VERSION

/* Spec recommends after one hour or 1 gigabyte of data. One hour
 * is a bit too verbose, so we try 8 hours */
#ifndef KEX_REKEY_TIMEOUT
#define KEX_REKEY_TIMEOUT (3600 * 8)
#endif
#ifndef KEX_REKEY_DATA
#define KEX_REKEY_DATA (1 << 30) /* 2^30 == 1GB, this value must be < INT_MAX  \
                                  */
#endif
/* Close connections to clients which haven't authorised after AUTH_TIMEOUT */
#ifndef AUTH_TIMEOUT
#define AUTH_TIMEOUT 300 /* we choose 5 minutes */
#endif

#endif
