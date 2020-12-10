#pragma once
#include "common.h"
#include "ProtocolDefine.h"

class CInstImp;
class CWorkThread;

//œﬂ≥Ã≥ÿ¿‡
class CThreadManager
{
public:
	CThreadManager(int nNums = 10);
	~CThreadManager();

	std::string createSid(const muduo::net::TcpConnectionPtr& conn);

	void dispatch(const TNetProtocol& tNetPro, const muduo::net::TcpConnectionPtr& pConn);
	
	void start();

	void stop();
private:
	u32															m_dwSidCount = 0;
	u32         												m_dwCount = 0;
	int															m_nThreadNum;
	bool														m_bQuit = false;
	std::vector<std::shared_ptr<CWorkThread>>					m_vecThreads;
	std::map<std::string, std::shared_ptr<CInstImp>>			m_mapSees;
};

