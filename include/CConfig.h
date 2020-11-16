#pragma once
#include <map>
#include <string>
#include <fstream>

class CConfig
{
public:
	CConfig(const char* pCfgFile);
	~CConfig();
	bool Initialize();
	std::string GetOneCfg(const char* pCfg);
	void PrintAll();
public:
	static CConfig& Instance()
	{
		static CConfig cConfig("iris.cfg");
		cConfig.Initialize();
		return cConfig;
	}
private:
	std::string								m_strCfgFile;
	std::map<std::string, std::string>		m_mapCfg;
};