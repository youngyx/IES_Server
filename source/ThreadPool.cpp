#include <stdio.h>
#include "CInstImp.h"
#include "ThreadPool.h"
#include "WorkThread.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>


CThreadManager::CThreadManager(int nNums )
	:m_nThreadNum(nNums)
{}


CThreadManager::~CThreadManager()
{
	for (int nIndex = 0; nIndex < m_nThreadNum; ++nIndex)
	{
		m_vecThreads[nIndex]->threadJoin();
	}
}

void CThreadManager::start()
{
	for (int nIndex = 0; nIndex < m_nThreadNum; ++nIndex)
	{
		std::shared_ptr<CWorkThread> ptr(new CWorkThread());
		m_vecThreads.push_back(ptr);
	}
}

//停止线程池
void CThreadManager::stop()
{
	TNetProtocol pro;
	CTask task(pro, nullptr);
	m_bQuit = true;

	for (int nIndex = 0; nIndex < m_nThreadNum; ++nIndex)
	{
		std::unique_lock<std::mutex> lck(m_vecThreads[nIndex]->m_cMutex);
		m_vecThreads[nIndex]->pushTask(task);
		m_vecThreads[nIndex]->setQuit();
		m_vecThreads[nIndex]->m_cCond.notify_one();
	}
}

//任务分发
void CThreadManager::dispatch(const TNetProtocol& tNetPro, const muduo::net::TcpConnectionPtr& pConn)
{
	CTask task(tNetPro, pConn);

	if (0 == strlen(tNetPro.m_tBody.m_achSid) && 0 == strcmp(tNetPro.m_tBody.m_achCmd, "ssb"))
	{
		std::string strSessionId = createSid(pConn);
		std::shared_ptr<CInstImp> pInst;
		pInst.reset(new CInstImp());
		if (nullptr == pInst.get())
		{
			LOG_ERROR << "[CThreadManager::dispatch] new failed";
			exit(1);
		}
		m_mapSees.insert(std::make_pair(strSessionId, pInst));
		task.m_pInst = pInst.get();
		task.m_strSid = strSessionId;
		std::cout << "dispatch " << tNetPro.m_tBody.m_achCmd << std::endl;
	}
	else
	{
		std::map<std::string, std::shared_ptr<CInstImp>>::iterator itr = m_mapSees.find(task.m_strSid);
		if (itr == m_mapSees.end())
		{
			LOG_ERROR << "[CThreadManager::dispatch] not find";
			pConn->forceClose();
		}
		task.m_pInst = itr->second.get();
	}

	std::cout << "dispatch " << m_vecThreads.size() << std::endl;

	{
		m_dwCount %= m_nThreadNum;
		std::unique_lock<std::mutex> lck(m_vecThreads[m_dwCount]->m_cMutex);
		m_vecThreads[m_dwCount]->pushTask(task);
		m_vecThreads[m_dwCount]->m_cCond.notify_one();
		++m_dwCount;
	}
}

//IP+Port+Time+Counter
std::string CThreadManager::createSid(const muduo::net::TcpConnectionPtr& conn)
{
	char achSid[32] = { 0 };
	std::string strIpAddr = conn->peerAddress().toIp();
	u16 wPort = conn->peerAddress().toPort();
	struct timeval tv;
	struct timezone tZone;
	int nRet = gettimeofday(&tv, &tZone);
	if (nRet < 0)
	{
		LOG_ERROR << "[CThreadManager::createSid] " << strerror(errno);
		return "";
	}
	u32 dwTick = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	sprintf(achSid, "%5x%5x%5x%5x", inet_addr(strIpAddr.c_str()), wPort, dwTick, m_dwSidCount++);
	std::string strSid = achSid;
	return strSid;
}

