#pragma once
#include "common.h"
#include "ThreadPool.h"
#include "ProtocolDefine.h"
#include "muduo/net/TcpServer.h"
#include "muduo/base/Timestamp.h"

//tcp·þÎñÀà
class CTcpServer
{
public:
	CTcpServer();
	~CTcpServer();
	bool Init(const char* pchIpAddr, u16 wPort, muduo::net::EventLoop* pLoop);
	void Start();
private:
	void OnConnection(const muduo::net::TcpConnectionPtr& conn);
	void OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* pBuf, muduo::Timestamp time);
private:
	u32											m_dwCount;
	std::unique_ptr<muduo::net::TcpServer>		m_pServer;
	std::unique_ptr<CThreadManager>				m_pThreadPool;
};