#include "cConnection.hpp"
#include "cConnManager.hpp"
#include <vector>
#include <utility>
#include "cRequestHandler.hpp"
#include <boost/bind.hpp>
namespace httpservice {

cConnection::cConnection(boost::asio::ip::tcp::socket socket, cConnManager& manager, cRequestHandler& handler)
  : m_socket(std::move(socket)),  m_ConnManager(manager), m_ReqHandler(handler)
{
}

void cConnection::run()
{
  //init reading
  do_read();
}

void cConnection::stop()
{
  m_socket.close();
}

void cConnection::do_read()
{
  auto self(shared_from_this());
  m_socket.async_read_some(boost::asio::buffer(m_buffer),
      [this, self](boost::system::error_code ec, std::size_t bytes_transferred)
      {
        if (!ec)
        {

	  //	std::cout << "Request: " << m_buffer << std::endl;
          request_parser::result_type result;
          std::tie(result, std::ignore) = request_parser_.parse(
          request_, m_buffer.data(), m_buffer.data() + bytes_transferred);

          if (result == request_parser::good)
          {
           m_ReqHandler.handle_request(request_, reply_);
           do_write();
          }
          else if (result == request_parser::bad)
          {
            reply_ = reply::stock_reply(reply::bad_request);
            do_write();
          }
          else
          {
          do_read();
          }
        }
        else if (ec != boost::asio::error::operation_aborted)
        {
          m_ConnManager.stop(shared_from_this());
        }
      });
}

void cConnection::finish_writting(const boost::system::error_code &errcod)
{
        if (!errcod)
        {
          // Initiate graceful connection closure.
         boost::system::error_code ignored_ec;
          m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
            ignored_ec);
        }

        if (errcod != boost::asio::error::operation_aborted)
        {
          m_ConnManager.stop(shared_from_this());
        }
 
}

void cConnection::do_write()
{
  boost::asio::async_write(m_socket, reply_.to_buffers(),
			   boost::bind(&cConnection::finish_writting, shared_from_this(), 
			   boost::asio::placeholders::error));
}

}
