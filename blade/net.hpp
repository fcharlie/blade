#ifndef BLADE_NET_HPP
#define BLADE_NET_HPP
#pragma once
#ifdef _MSC_VER
#define  _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING 1
#endif
#include <boost/asio.hpp>

using io_context_t = boost::asio::io_context;
using socket_t = boost::asio::ip::tcp::socket;
using io_work_t = boost::asio::executor_work_guard<io_context_t::executor_type>;
using acceptor_t = boost::asio::ip::tcp::acceptor;

#ifndef _WIN32
using signal_set = boost::asio::signal_set;
#endif

#endif
