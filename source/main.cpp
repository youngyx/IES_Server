#include <iostream>
#include "CConfig.h"
#include "CLibLoader.h"
#include "CTcpServer.h"
#include "muduo/net/EventLoop.h"


int main(int argc, char** argv)
{
	//≈‰÷√ƒ£øÈ
	CConfig cfg("iris.cfg");
	cfg.Initialize();
	CLibLoader::Instance().SetCfg(cfg.GetOneCfg("Config.Path"));
	CLibLoader::Instance().Initialize(cfg.GetOneCfg("IESlibName"));

	muduo::net::EventLoop loop;
	std::unique_ptr<CTcpServer> pServer;
	pServer.reset(new CTcpServer());
	pServer->Init(cfg.GetOneCfg("ipAddr").c_str(), atoi(cfg.GetOneCfg("port").c_str()), &loop);
	pServer->Start();
	loop.loop();

	CLibLoader::Instance().Uninitialize();
	return 0;
}
