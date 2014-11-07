#ifndef PROXYDB_HPP
#define PROXYDB_HPP

#define _GNU_SOURCE 1
#include <stdio.h>
#include <dlfcn.h>

#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <dlfcn.h>
#include <csignal>
#include <vector>
#include <memory>
#include <cassert>
#include <map>
#include <wchar.h>
#include <sys/mman.h>
#include <time.h>
#include <fstream>
#include <complex>

#include "globals.hpp"
#include "irrlicht/irrlicht.h"
#include "enet/enet.h"
#include "lua/lua.hpp"
#include "lua/lauxlib.h"

typedef irr::core::stringw WideString;
typedef irr::core::stringc String;

#include "PluginManager.hpp"
#include "PlayerManager.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#include "leveldb/db.h"

class ProxyDB
{
public:
	static int Open(const char*);
};

#endif