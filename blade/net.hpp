#ifndef BLADE_NET_HPP
#define BLADE_NET_HPP

/// FIX ASIO Compiler failed under MSVC 15.6 or Later
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING 1
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#include <memory>
#include <boost/asio.hpp>

namespace ssh {
using error_code = boost::system::error_code;
using io_context_t = boost::asio::io_context;
using socket_t = boost::asio::ip::tcp::socket;
using io_work_t = boost::asio::executor_work_guard<io_context_t::executor_type>;
using acceptor_t = boost::asio::ip::tcp::acceptor;
using endpoint_t = boost::asio::ip::tcp::endpoint;
#ifndef _WIN32
using signal_set = boost::asio::signal_set;
#endif
} // namespace ssh

#endif
