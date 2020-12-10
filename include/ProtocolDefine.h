#pragma once
#include "common.h"
#include "CInstImp.h"
#include "muduo/net/TcpServer.h"

//协议包头
typedef struct tNetHeader
{
	u8			m_byVer;	//版本号
	u16			m_wLen;		//包长度
} TNetHeader;

//协议包体
typedef struct tNetBody
{
	char m_achCmd[12];	//命令
	char m_achParam[512];	//参数
	char m_achSid[32];	//sessionId
	char m_achSvc[12];	//能力类型
	char m_achTxt[2048];	//文本

	void clear()
	{
		memset(m_achCmd, 0, sizeof(m_achCmd));
		memset(m_achTxt, 0, sizeof(m_achTxt));
		memset(m_achSvc, 0, sizeof(m_achSvc));
		memset(m_achSid, 0, sizeof(m_achSid));
		memset(m_achParam, 0, sizeof(m_achParam));
	}
} TNetBody;

//自定义通信协议
typedef struct tNetProtocol
{
	TNetHeader	m_tHeader;	//包头
	TNetBody	m_tBody;

	void clear()
	{
		m_tBody.clear();
	}
} TNetProtocol;



struct CTask
{
	std::string m_strCmd;
	std::string m_strParam;
	std::string m_strText;
	std::string m_strSid;
	CInstImp*	m_pInst = nullptr;
	muduo::net::TcpConnectionPtr m_pCon = nullptr;

	CTask() { clear(); }

	CTask(const TNetProtocol& tNetPro, muduo::net::TcpConnectionPtr pCon)
	{
		m_strCmd = tNetPro.m_tBody.m_achCmd;
		m_strParam = tNetPro.m_tBody.m_achParam;
		m_strText = tNetPro.m_tBody.m_achTxt;
		m_strSid = tNetPro.m_tBody.m_achSid;
		m_pCon = pCon;
	}

	void clear()
	{
		m_strCmd.clear();
		m_strParam.clear();
		m_strText.clear();
	}
};