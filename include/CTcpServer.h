#pragma once
#include "common.h"
#include "muduo/net/TcpServer.h"
#include "muduo/base/Timestamp.h"

class CTcpServer
{
public:
	CTcpServer();
	CTcpServer(muduo::net::EventLoop *pLoop, const muduo::net::InetAddress &listenAdr);
	~CTcpServer();
	void Start();
private:
	void OnConnection(const muduo::net::TcpConnectionPtr& conn);
	void OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* pBuf, muduo::Timestamp time);
private:
	std::unique_ptr<muduo::net::TcpServer>		m_pServer;
};