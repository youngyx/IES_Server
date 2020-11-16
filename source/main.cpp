#include <iostream>
#include "CConfig.h"
#include "CLibLoader.h"



int main(int argc, char** argv)
{
	FILE *fp = nullptr;
	fp = fopen("file", "w+");
	std::string strSo = "/home/xuyan2/robocall/ROBOCALL_Build1039/iris/IES_Server/lib_linux/libOutBound.so";
	CLibLoader::Instance().Initialize(strSo.c_str());

	HMRLSESSION hSessionId = nullptr;
	CLibLoader::Instance().func_IESCreate(&hSessionId, "{}");
	if(!hSessionId)
	{
		fwrite("hSessionId nullptr", 1, 18, fp);
		return 1;
	}
	std::string sent = "高高压一百一十八";
	char params[200] = "{\"nbest\" : 1, \"type\" : \"semantic|intent\", \"resType\" : \"bloodPressure\", \"encode\" : \"utf-8\"}";
	const char* rst = nullptr;
	int nRet = CLibLoader::Instance().func_IESInterpret(hSessionId, sent.c_str(), &rst, params);
	if (0 != nRet)
	{
		fwrite("ipt error", 1, 9, fp);
	}
	else
	{
		fwrite(rst, 1, strlen(rst), fp);
		std::cout << rst << std::endl;
	}
	fclose(fp);

	CLibLoader::Instance().Uninitialize();
	return 0;
}
