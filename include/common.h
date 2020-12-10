#pragma once
#include <map>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <string>
#include <errno.h>
#include <string.h>
#include <iostream>
#include <functional>
#include <condition_variable>
#include "muduo/base/Logging.h"


using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using s8 = signed char;
using s16 = signed short;
using s32 = signed int;
using s64 = signed long long;