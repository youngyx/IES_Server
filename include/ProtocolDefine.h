#pragma once
#include "common.h"
#include "CInstImp.h"
#include "muduo/net/TcpServer.h"

//Э���ͷ
typedef struct tNetHeader
{
	u8			m_byVer;	//�汾��
	u16			m_wLen;		//������
} TNetHeader;

//Э�����
typedef struct tNetBody
{
	char m_achCmd[12];	//����
	char m_achParam[512];	//����
	char m_achSid[32];	//sessionId
	char m_achSvc[12];	//��������
	char m_achTxt[2048];	//�ı�

	void clear()
	{
		memset(m_achCmd, 0, sizeof(m_achCmd));
		memset(m_achTxt, 0, sizeof(m_achTxt));
		memset(m_achSvc, 0, sizeof(m_achSvc));
		memset(m_achSid, 0, sizeof(m_achSid));
		memset(m_achParam, 0, sizeof(m_achParam));
	}
} TNetBody;

//�Զ���ͨ��Э��
typedef struct tNetProtocol
{
	TNetHeader	m_tHeader;	//��ͷ
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