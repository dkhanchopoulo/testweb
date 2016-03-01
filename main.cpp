#include <iostream>
#include <boost/asio.hpp>
#include "server.hpp"
#include <string>
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
      std::cerr << " To run final usage:  -h <address> -p <port> -d <doc_root>\n";
      std::cerr << " try:\n";
      std::cerr << " ./final -h 0.0.0.0 -p 80 -d .\n";
      return 1;
    }

    httpservice::server myserver(params.host, params.port, params.doc_root);

    
    myserver.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "std::exception: " << e.what() << "\n";
  }

  return 0;
}
