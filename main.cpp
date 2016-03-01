//
// main.cpp
// ~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at <a href="http://www.boost.org/LICENSE_1_0.txt">http://www.boost.org/LICENSE_1_0.txt</a>)
//

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "server.hpp"

#include <unistd.h>
#include <getopt.h>

struct t_hostparams 
{

std::string host;
std::string port;
std::string doc_root;

bool notconfigured(){
	if (host.empty() || port.empty() || doc_root.empty())
		return true;
	else
		return false;
	}
};


void getoptions(int argc, char *argv[], t_hostparams &p)
{
 auto result = 0;

 while( (result = getopt(argc, argv, "h:p:d:"))!= -1){
	switch(result){
	case 'h': std::cout << "host : " << optarg << std::endl; p.host = optarg; break;
	case 'p': std::cout << "port : " << optarg << std::endl; p.port = optarg; break;
	case 'd': std::cout << "dir  : " << optarg << std::endl; p.doc_root = optarg; break;
	}
 } 
}


int main(int argc, char* argv[])
{
  try
  {
   	


    struct t_hostparams params;
    getoptions(argc, argv, params);
	
    

	// Check command line arguments.
    if (params.notconfigured())
    {
      std::cerr << "Usage: http_server -h <address> -p <port> -d <doc_root>\n";
      std::cerr << "  For IPv4, try:\n";
      std::cerr << "    receiver 0.0.0.0 80 .\n";
      return 1;
    }

    // Initialise the server.
    http::server::server s(params.host, params.port, params.doc_root);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}
