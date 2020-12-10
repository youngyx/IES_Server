#pragma once
#include "common.h"
#include "ProtocolDefine.h"

class CWorkThread
{
public:
	CWorkThread();
	~CWorkThread();
	void threadProc();
	void setQuit(bool bQuit = true);
	void pushTask(const CTask& cTask);
	void threadJoin();
private:
	bool										m_bQuit = false;
	std::queue<CTask>							m_cTaskQue;
	std::shared_ptr<std::thread>				m_shpThread;
public:
	std::mutex									m_cMutex;
	std::condition_variable						m_cCond;
};

