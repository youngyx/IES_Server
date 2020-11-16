#pragma once
#include <vector>
#include <string>
#include <string.h>

class CStringUtils
{
private:
	static void TrimBeginEnd(std::string& strStr)
	{
		strStr.erase(0, strStr.find_first_not_of(" "));
		strStr.erase(strStr.find_last_not_of(" ") + 1, std::string::npos);
	}

	static void TrimTab(std::string& strStr)
	{
		size_t dwPos = 0;
		const std::string strDelim = "\t";
		dwPos = strStr.find_first_of(strDelim);
		if (dwPos == std::string::npos)
		{
			return;
		}
		strStr.erase(dwPos, strStr.find_last_not_of(strDelim) - dwPos);
	}
public:
	static void SplitStr(const std::string& str, std::vector<std::string>& vec, const char* splite)
	{
		size_t dwPos = 0;
		std::string strSubstr;
		std::string strTemp = str;
		size_t spLen = strlen(splite);

		while (true)
		{
			dwPos = strTemp.find(splite);
			if (dwPos != std::string::npos)
			{
				strSubstr = strTemp.substr(0, dwPos);
				
				TrimBeginEnd(strSubstr);
				TrimTab(strSubstr);

				vec.push_back(strSubstr);
				strTemp = strTemp.substr(dwPos + spLen, strTemp.length());
			}
			else
			{
				TrimBeginEnd(strTemp);
				TrimTab(strTemp);

				vec.push_back(strTemp);
				break;
			}
		}
	}
};
