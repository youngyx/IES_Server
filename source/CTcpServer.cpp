#include "CTcpServer.h"

using std::placeholders::_1;
using std::placeholders::_2;
using std::placeholders::_3;

CTcpServer::CTcpServer()
{}


CTcpServer::~CTcpServer()
{}

bool CTcpServer::Init(const char* pchIpAddr, u16 wPort, muduo::net::EventLoop* pLoop)
{
	muduo::net::InetAddress listnAddr(pchIpAddr, wPort);

	m_pThreadPool.reset(new CThreadManager());
	m_pThreadPool->start();
	m_pServer.reset(new muduo::net::TcpServer(pLoop, listnAddr, "Iris Server"));
	m_pServer->setConnectionCallback(std::bind(&CTcpServer::OnConnection, this, _1));
	m_pServer->setMessageCallback(std::bind(&CTcpServer::OnMessage, this, _1, _2, _3));
}

//��ʼ����
void CTcpServer::Start()
{
	m_pServer->start();
}

void CTcpServer::OnConnection(const muduo::net::TcpConnectionPtr& conn)
{}


//socket���ݰ��ص�����
void CTcpServer::OnMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* pBuf, muduo::Timestamp time)
{
	TNetProtocol tNetPro;
	//socket �ɶ�����С�ڰ�ͷ �´ζ�ȡ
	if (pBuf->readableBytes() < sizeof(TNetHeader))
	{
		LOG_INFO << "readable bytes smaller than msg head";
		return;
	}
	//��ȡЭ���ͷ
	memcpy(&tNetPro.m_tHeader, pBuf->peek(), sizeof(TNetHeader));
	pBuf->retrieve(sizeof(TNetHeader));
	
	if (pBuf->readableBytes() > sizeof(TNetBody))
	{
		LOG_ERROR << "msg body too big";
		//�Ƿ��ͻ��� �ر�
		conn->forceClose();
		return;
	}
	else if (pBuf->readableBytes() < sizeof(TNetBody))
	{
		LOG_INFO << "msg packet not complete";
		return;
	}
	//��ȡЭ�����
	memcpy(&tNetPro.m_tBody, pBuf->peek(), sizeof(TNetBody));
	pBuf->retrieve(sizeof(TNetBody));
	//�ַ�����
	m_pThreadPool->dispatch(tNetPro, conn);
}