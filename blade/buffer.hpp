#ifndef SSH_BUFFER_HPP
#define SSH_BUFFER_HPP
#pragma once
#include <cstdlib>
#include <cstddef>
#include <stdexcept>
#include <string_view>
// modern buffer

#define BUF_MAX_INCR 1000000000
#define BUF_MAX_SIZE 1000000000

namespace ssh {
template <typename IntegerA, typename IntegerB>
constexpr IntegerA Minimum(IntegerA n, IntegerB m) {
  static_assert(std::is_integral<IntegerA>::value, "Must Integer");
  static_assert(std::is_integral<IntegerB>::value, "Must Integer");
  return n > m ? static_cast<IntegerA>(m) : n;
}

template <typename T> T *Malloc(std::size_t n) {
  return reinterpret_cast<T *>(malloc(sizeof(T) * n));
}

template <typename T> T *Realloc(T *old, std::size_t n) {
  return reinterpret_cast<T *>(realloc(old, sizeof(T) * n));
}

struct Buffer {
  using Byte = unsigned char;
  Byte *data{nullptr};
  std::size_t len;
  std::size_t pos{0};
  std::size_t size;
  Buffer(std::size_t asize = 8192) {
    if (asize > BUF_MAX_SIZE) {
      /// ERROR
      throw std::runtime_error("ssh::Buffer out memory");
    }
    data = Malloc<Byte>(asize);
    size = asize;
  }
  ~Buffer() {
    if (data != nullptr) {
      free(data);
    }
  }
  Buffer &Resize(std::size_t newsize) {
    if (newsize > BUF_MAX_SIZE) {
      /// ERROR
      throw std::runtime_error("ssh::Buffer out memory");
    }
    data = Realloc(data, newsize);
    size = newsize;
    len = Minimum(newsize, len);
    pos = Minimum(newsize, pos);
    return *this;
  }
  Buffer &AddByte(std::byte b) {
    //
    return *this;
  }
  Buffer &AddInt(std::uint32_t val) {
    //
    return *this;
  }
  Buffer &AddBytes(const Byte *bytes, std::size_t num) {
    //
    return *this;
  }
  Buffer &AddString(std::string_view str) {
    //
    return *this;
  }
};
} // namespace ssh

#endif
