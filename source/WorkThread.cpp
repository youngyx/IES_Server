#include "WorkThread.h"

CWorkThread::CWorkThread()
{
	m_shpThread.reset(new std::thread(std::bind(&CWorkThread::threadProc, this)));
}


CWorkThread::~CWorkThread()
{}


//线程处理函数，所以任务都在这里处理
void CWorkThread::threadProc()
{
	int nRet = 0;
	TNetProtocol tNetPro;
	
	while (!m_bQuit)
	{
		CTask task;
		{
			std::unique_lock<std::mutex> lck(m_cMutex);
			while (m_cTaskQue.empty())
			{
				m_cCond.wait(lck);
			}
			task = m_cTaskQue.front();
			m_cTaskQue.pop();
		}

		if (nullptr == task.m_pCon)
		{
			LOG_INFO << "thread quit !";
			continue;;
		}

		//处理语义理解系列函数
		if (task.m_strCmd == "ssb")
		{
			nRet = task.m_pInst->onCreate(task.m_strParam);
			if (0 != nRet)
			{

			}
			strcpy(tNetPro.m_tBody.m_achCmd, "ssb");
			strcpy(tNetPro.m_tBody.m_achSid, task.m_strSid.c_str());
			std::cout << "threadProc " << tNetPro.m_tBody.m_achSid << std::endl;
		}
		else if (task.m_strCmd == "ipt")
		{
			std::string strResult;
			task.m_pInst->onInterpret(task.m_strText, task.m_strParam, strResult);
			strcpy(tNetPro.m_tBody.m_achCmd, "ipt");
			strcpy(tNetPro.m_tBody.m_achTxt, strResult.c_str());
			strcpy(tNetPro.m_tBody.m_achSid, task.m_strSid.c_str());
		}
		else if (task.m_strCmd == "prc")
		{
			
		}
		else if(task.m_strCmd == "rst")
		{
			
		}
		else if (task.m_strCmd == "sse")
		{
			task.m_pInst->onDestroy();
			strcpy(tNetPro.m_tBody.m_achCmd, "sse");
			strcpy(tNetPro.m_tBody.m_achSid, task.m_strSid.c_str());
			
		}
		else
		{
			LOG_ERROR << "unknow cmd";
			task.m_pCon->forceClose();
		}
		task.m_pCon->send(&tNetPro, sizeof(TNetProtocol));
		tNetPro.clear();
	}
	std::cout << std::this_thread::get_id() << "quit\n";
}

void CWorkThread::pushTask(const CTask& cTask)
{
	m_cTaskQue.push(cTask);
}

void CWorkThread::setQuit(bool bQuit /* = true */)
{
	m_bQuit = bQuit;
}

void CWorkThread::threadJoin()
{
	m_shpThread->join();
}