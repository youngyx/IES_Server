#include "CInstImp.h"
#include "CLibLoader.h"
#include "msp_errors.h"

CInstImp::CInstImp()
{}

CInstImp::~CInstImp()
{

}

int CInstImp::onCreate(const std::string& strParam)
{
	int nRet = 0;
	nRet = CLibLoader::Instance().func_IESCreate(&m_pInst, strParam.c_str());
	if (nRet != 0)
	{
		LOG_ERROR << "[CInstImp::onCreate] IESCreate failed :" << nRet;
	}
	return nRet;
}

int CInstImp::onDestroy()
{
	if (m_pInst)
	{
		int nRet = 0;
		nRet = CLibLoader::Instance().func_IESDestroy(m_pInst);
		if (0 != nRet)
		{
			LOG_ERROR << "[CInstImp::onDestroy] IESDestroy failed " << nRet;
		}
		return nRet;
	}
	return MSP_ERROR_INVALID_HANDLE;

}

int CInstImp::onReset(const std::string& strParam)
{
	if (m_pInst)
	{
		int nRet = 0;
		nRet = CLibLoader::Instance().func_IESReset(m_pInst, strParam.c_str());
		if (nRet != 0)
		{
			LOG_ERROR << "[CInstImp::onReset] IESRest failed " << nRet;
		}
		return nRet;
	}
	return MSP_ERROR_INVALID_HANDLE;
}

int CInstImp::onInterpret(const std::string& strSent, const std::string& strParam, std::string& strRst)
{
	if (m_pInst)
	{
		int nRet = 0;
		const char* pResult = nullptr;
		nRet = CLibLoader::Instance().func_IESInterpret(m_pInst, strSent.c_str(), &pResult, strParam.c_str());
		if (nRet != 0 || nullptr == pResult)
		{
			LOG_ERROR << "[CInstImp::onInterpret] IESInterpret failed " << nRet;
			return MSP_ERROR_INVALID_HANDLE;
		}
		strRst.assign(pResult);
		return nRet;
	}
	return MSP_ERROR_INVALID_HANDLE;
}

int CInstImp::onProcess(const std::string& strSent, const std::string& strParam, std::string& strRst)
{
	if (m_pInst)
	{
		int nRet = 0;
		const char* pResult = nullptr;
		nRet = CLibLoader::Instance().func_IESProcess(m_pInst, strSent.c_str(), &pResult, strParam.c_str());
		if (nRet != 0 || nullptr == pResult)
		{
			LOG_ERROR << "[CInstImp::onProcess] IESProcess failed " << nRet;
			return MSP_ERROR_INVALID_HANDLE;
		}
		strRst.assign(pResult);
		return nRet;
	}
	return MSP_ERROR_INVALID_HANDLE;
}