#include "CTcpServer.h"

CTcpServer::CTcpServer(muduo::net::EventLoop* pLoop, const muduo::net::InetAddress& listenAdr)
{
	m_pServer.reset(new muduo::net::TcpServer(pLoop, listenAdr, "Iris_Server"));
}

CTcpServer::~CTcpServer()
{

}

void CTcpServer::Start()
{
	m_pServer->start();
}

void CTcpServer::OnConnection(const muduo::net::TcpConnectionPtr& conn)
{

}


void CTcpServer::OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* pBuf, muduo::Timestamp time)
{


}