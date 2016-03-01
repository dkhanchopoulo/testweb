#pragma once 
#include "cConnection.hpp"
#include <set>

namespace httpservice {

class cConnManager
{
  std::set<cConnection_Ptr> m_connections;

public:
  cConnManager(const cConnManager&) = delete;
  cConnManager& operator=(const cConnManager&) = delete;

  cConnManager() {};
  ~cConnManager(){};
  void start(cConnection_Ptr c);
  void stop(cConnection_Ptr c);
  void stop_all();
};

} 

