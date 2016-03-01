#include "cConnManager.hpp"

namespace httpservice {

void cConnManager::start(cConnection_Ptr c)
{
  m_connections.insert(c);
  c->run();
}

void cConnManager::stop(cConnection_Ptr c)
{
  m_connections.erase(c);
  c->stop();
}

void cConnManager::stop_all()
{
  for (auto c: m_connections)
    c->stop();
  m_connections.clear();
}

} //
