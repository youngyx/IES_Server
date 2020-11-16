#include <iostream>
#include "CConfig.h"
#include "CLibLoader.h"



int main(int argc, char** argv)
{
	std::cout << CConfig::Instance().GetOneCfg("cfg.path") << std::endl;
	return 0;
}
