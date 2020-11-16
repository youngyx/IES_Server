#include "CLibLoader.h"


CLibLoader::CLibLoader()
{}

CLibLoader::~CLibLoader()
{}


int CLibLoader::Initialize(std::string strFile)
{

	if (m_pHandle)
	{
		LOG_ERROR << "m_pHandle not null";
		return 1;
	}
	m_pHandle = dlopen(strFile.c_str(), RTLD_LAZY);
	if (nullptr == m_pHandle)
	{
		LOG_ERROR << "open " << strFile << " failed " << dlerror();
		exit(1);
		return 1;
	}

	
	GET_PROC_ADDRESS(IESInit)
	GET_PROC_ADDRESS(IESFini)
	GET_PROC_ADDRESS(IESCreate)
	GET_PROC_ADDRESS(IESReset)
	GET_PROC_ADDRESS(IESInterpret)
	GET_PROC_ADDRESS(IESProcess)
	GET_PROC_ADDRESS(IESDestroy)

	if (func_IESInit)
	{
		int nRet = func_IESInit("/home/xuyan2/robocall/ROBOCALL_Build1039/iris/IES_Server/config_linux/sc.cfu");
		if (0 != nRet)
		{
			LOG_ERROR << "func_IESInit failed";
			return 1;
		}
	}
	return 0;
}


int CLibLoader::Uninitialize()
{
	if (func_IESFini)
	{
		int nRet = func_IESFini();
		if (0 != nRet)
		{
			LOG_ERROR << "func_IESFini failed\n";
			return 1;
		}
	}

	if (m_pHandle)
	{
		int nRet = dlclose(m_pHandle);
	}
	return 0;
}
