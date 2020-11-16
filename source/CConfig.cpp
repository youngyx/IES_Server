#include "CConfig.h"
#include "CStringUtil.h"

CConfig::CConfig(const char* pCfgFile)
	:m_strCfgFile(pCfgFile)
{
}


CConfig::~CConfig()
{

}

bool CConfig::Initialize()
{
	std::ifstream in;
	std::string strLine;
	in.open(m_strCfgFile.c_str(), std::ios::binary);
	m_strCfgFile.clear();

	while (getline(in, strLine))
	{
		if (strLine.find("#") != std::string::npos)
		{
			continue;
		}

		std::vector<std::string> vecEle;
		CStringUtils::SplitStr(strLine, vecEle, "=");
		if (2 == vecEle.size())
		{
			m_mapCfg.insert(make_pair(vecEle[0], vecEle[1]));
		}
	}
	in.close();
	return true;
}

std::string CConfig::GetOneCfg(const char* pCfg)
{
	std::map<std::string, std::string>::iterator itr;
	itr = m_mapCfg.find(pCfg);
	if (itr != m_mapCfg.end())
	{
		return itr->second;
	}
	return "";
}

void CConfig::PrintAll()
{
	std::map<std::string, std::string>::iterator itr = m_mapCfg.begin();
	while (itr != m_mapCfg.end())
	{
		printf("Key:%s, Value:%s\n", itr->first.c_str(), itr->second.c_str());
		++itr;
	}
}