#pragma once
#include "IES.h"
#include <dlfcn.h>
#include "muduo/base/Logging.h"

#define DECLARE_FUNC_MEMBER(NAME)	Proc_##NAME func_##NAME = nullptr;

#define GET_PROC_ADDRESS(NAME)	func_##NAME = (Proc_##NAME)dlsym(m_pHandle, #NAME);


class CLibLoader
{
public:
	DECLARE_FUNC_MEMBER(IESInit)
	DECLARE_FUNC_MEMBER(IESFini)
	DECLARE_FUNC_MEMBER(IESCreate)
	DECLARE_FUNC_MEMBER(IESReset)
	DECLARE_FUNC_MEMBER(IESInterpret)
	DECLARE_FUNC_MEMBER(IESProcess)
	DECLARE_FUNC_MEMBER(IESDestroy)

public:
	static CLibLoader& Instance()
	{
		static CLibLoader loader;
		return loader;
	}

	~CLibLoader();
public:
	int Initialize(std::string strFile);
	int Uninitialize();
	void SetCfg(const std::string strCfg)
	{
		m_strCfg = strCfg;
	}
private:
	CLibLoader();
private:
	std::string	m_strCfg;
	void		*m_pHandle = nullptr;
};
