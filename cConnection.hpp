#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <array>
#include "cRequestHandler.hpp"

#include "reply.hpp"
#include "request.hpp"
#include "request_parser.hpp"

namespace httpservice{

class cConnManager;

/// Represents a single connection from a client.
class cConnection
  : public std::enable_shared_from_this<cConnection>
{
public:

  explicit cConnection(boost::asio::ip::tcp::socket sock, cConnManager& manager, cRequestHandler& handler);

  void run();
  void stop();
  cConnection(const cConnection&) = delete;
  cConnection& operator=(const cConnection&) = delete;


private:
  void do_read();
  void do_write();
  void finish_writting(const boost::system::error_code &errcod);


  boost::asio::ip::tcp::socket m_socket;
  cConnManager & m_ConnManager;


  std::array<char, 16384> m_buffer;


  cRequestHandler & m_ReqHandler;
  request request_;
  request_parser request_parser_;
  reply reply_;
};

using cConnection_Ptr = std::shared_ptr<cConnection>;

}

