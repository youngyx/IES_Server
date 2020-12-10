#pragma once
#include "IES.h"
#include "common.h"


class CInstImp
{
public:
	CInstImp();
	~CInstImp();
	int onCreate(const std::string& strParam);
	int onDestroy();
	int onReset(const std::string &strParam);
	int onInterpret(const std::string &strSent, const std::string &strParam, std::string& strRst);
	int onProcess(const std::string& strSent, const std::string& strParam, std::string& strRst);
private:
	HMRLSESSION		m_pInst = nullptr;
};

