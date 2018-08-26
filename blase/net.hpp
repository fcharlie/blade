#ifndef BLASE_NET_HPP
#define BLASE_NET_HPP
#pragma once
#define _SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING 1
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/bind_executor.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/steady_timer.hpp>

namespace net {
using tcp = boost::asio::ip::tcp;        // from <boost/asio/ip/tcp.hpp>
using timer = boost::asio::steady_timer; // timer
using strand = boost::asio::strand<boost::asio::io_context::executor_type>;
namespace http = boost::beast::http; // from <boost/beast/http.hpp>
using error_code = boost::system::error_code;
using io_context_t = boost::asio::io_context;
using socket_t = boost::asio::ip::tcp::socket;
using io_work_t = boost::asio::executor_work_guard<io_context_t::executor_type>;
using acceptor_t = boost::asio::ip::tcp::acceptor;
using endpoint_t = boost::asio::ip::tcp::endpoint;
#ifndef _WIN32
using signal_set = boost::asio::signal_set;
#endif
} // namespace net

#endif
