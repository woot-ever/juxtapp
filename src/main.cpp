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
#include <unistd.h>

#include "TheHTTP.hpp"

#include "globals.hpp"
#include "irrlicht/irrlicht.h"
//#include "enet/enet.h"
#include "lua/lua.hpp"
#include "lua/lauxlib.h"

typedef irr::core::stringw WideString;
typedef irr::core::stringc String;

struct APIPlayer {
    std::string username;
    bool banned;
    bool active;
    bool gold;
    bool termsAccepted;
    bool receiveEmails;
    std::string banReason;
    std::string banExpiration;
    short role;
  public:
    APIPlayer(void);
};

#include "kage/Singleton.hpp"
#include "kage/CBadassPtr.hpp"
#include "kage/Vec2f.hpp"
#include "kage/CRunner.hpp"
#include "kage/CWorldTask.hpp"
#include "kage/CInventoryActor.hpp"
#include "kage/CActor.hpp"

////////////////////////////////////////////
#include "PluginManager.hpp"
#include "PlayerManager.hpp"
////////////////////////////////////////////

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#include <sys/stat.h> // for mkdir
#include <sys/types.h> // for mkdir

const int CURRENT_VERSION = 4;

bool currdirinbase = false;

void UpdateFile(const char* path, const char* webpath, const char* filename, bool forceUpdate)
{
	std::string filepath = std::string(currdirinbase ? "../" : "./") + std::string(path) + std::string(filename);
	std::ifstream f(filepath);
    if (!f.good() || forceUpdate) {
		f.close();
		std::cout << "Downloading " << filename << " to " << filepath << " ..." << std::endl;
		if (DownloadBinary("update.juxta.cf", std::string(std::string(webpath) + std::string(filename)).c_str(), filepath))
		{
			std::cout << "Downloaded " << filename << std::endl;
		}
    }
	else
	{
		f.close();
	}
}

void UpdateLibraries(bool forceUpdate)
{
	UpdateFile("Plugins/__libs/", "files/libs/", "mathutils.lua", forceUpdate);
	UpdateFile("Plugins/__libs/", "files/libs/", "stringutils.lua", forceUpdate);
	UpdateFile("Plugins/__libs/", "files/libs/", "tableutils.lua", forceUpdate);
	UpdateFile("Plugins/__libs/", "files/libs/", "db.lua", forceUpdate);
}

bool CheckForUpdates()
{
	int new_version = DownloadText("update.juxta.cf","version.txt");
	if (new_version==-1)
	{
		std::cout << std::endl << "ERROR! CANNOT CHECK FOR JUXTA++ UPDATES!" << std::endl << std::endl;
		return false;
	}

	std::string rel = currdirinbase ? "../" : "./";
	mkdir(std::string(rel + std::string("Plugins")).c_str(), 0755);
	mkdir(std::string(rel + std::string("Plugins/__libs")).c_str(), 0755);
	UpdateLibraries(false);
	
	if (new_version>CURRENT_VERSION)
	{
		std::cout << std::endl << "New Juxta++ version found! Updating..." << std::endl << std::endl;
		std::string thesoname = currdirinbase ? "../juxtapp.so" : "juxtapp.so";
		if (DownloadBinary("update.juxta.cf","files/linux/juxtapp.so",thesoname))
		{
			UpdateLibraries(true);
			std::cout << std::endl << "New version of Juxta++ is ready!" << std::endl << std::endl;
			return true;
		}
		else
		{
			std::cout << std::endl << "ERROR! CANNOT DOWNLOAD NEW JUXTA++ LIBRARY, PLEASE UPDATE IT ON YOUR OWN!" << std::endl << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << std::endl << "No update avaliable :-(" << std::endl << std::endl;
	}
	return false;
}

static void* (*o_dlsym) ( void *handle, const char *name ) = 0;

void find_dlsym(){
	char buf[32];
	int maxver = 40;
	for(int a=0;a<maxver;a++) {
		sprintf(buf, "GLIBC_2.%d", a);
		o_dlsym = (void*(*)(void *handle, const char *name)) dlvsym(RTLD_NEXT,"dlsym", buf);
		if(o_dlsym){
			return;
		}
	}
	for(int a=0;a<maxver;a++){	
		for(int b=0;b<maxver;b++){
			sprintf(buf, "GLIBC_2.%d.%d", a, b);
			o_dlsym = (void*(*)(void *handle, const char *name)) dlvsym(RTLD_NEXT,"dlsym", buf);
			if(o_dlsym){
				return;
			}
		}
	}
}

static void* (*o_CRunnerBuild)(void *, Vec2f, unsigned char) = 0;
static String (*o_CActorGetName)(void *) = 0;
static int (*o_ZN4CNet20ReadPacketInSnapshotEbP10CStatePumpR10CBitStream)(void*, bool, void*, void*) = 0;
static int (*o_ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer)(void*, void*, void*) = 0;
static int (*o_ZN14CPlayerManager12RemovePlayerEP7CPlayer)(void*, void*) = 0;
static int (*o_ZN4CMap11recdMapTileER10CBitStream)(void*,void*) = 0;
static void* (*o_ZN9CSecurityC1Ev)(void*) = 0;
static int (*o_ZN7CRunner6DoTickEv) (CRunner*) = 0;
static void* (*o_ZN7CRunner5ThinkEv) (CRunner*) = 0;
static void* (*o_ZN4CNetC1Ev)(void*) = 0;
static void* (*o_ZN7CScriptC1Ev)(void*) = 0;
static void* (*o_ZN4CNet15ServerSendToAllER10CBitStream) (void*,DWORD) = 0;
static void* (*o_ZN10IC_ConsoleC2Ev) (void*) = 0;
static int (*o_ZN14CPlayerManager14MakeUniqueName) (int,int,int,int,int) = 0;
static bool (*o_ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc) (void*, CRunner*, const char*) = 0;
static void* (*o_ZN4CNet10RecdDeltasER10CBitStreamP10CStatePump) (void*, void*, void*) = 0;
static void* (*o_ZN10CWorldTask5StartEv) (void*) = 0;
static void* (*o_ZN6CRules5ThinkEv) (void*) = 0;
static void* (*o_ZN4CMap7LoadMapEPKcb) (void*, char*) = 0;
static void* (*o_ZN4CMap7InitMapEv) (void*) = 0;
static void* (*o_ZN4CNet23server_ProcessAPIPlayerEP9APIPlayerP13CSecurityData18APIRequestStatus_t) (void*, APIPlayer*, void*, int) = 0;
static void* (*o_ZN7CRunner9ThrowSackEiRhfi) (CRunner*, int, unsigned char &, float, int) = 0;
static void* (*o_ZN10CWorldTask7DropEggEi5Vec2fii) (void*, int, Vec2f, int, int) = 0;
static bool (*o_ZN7CRunner10recdStrikeER10CBitStreamPS_) (CRunner*, CBitStream&, CRunner*) = 0;
static int (*o_accept) (int, struct sockaddr*, socklen_t*) = 0;

// detour xD
typedef void* (*o_CNetCreateServer_) (void *);
o_CNetCreateServer_ o_CNetCreateServer = NULL;

typedef int (*o_CPlayer__Send_Delta_) (void*, void*, void*, void*);
o_CPlayer__Send_Delta_ o_CPlayer__Send_Delta = NULL;

typedef int (*o_CRunner__Send_Delta_) (void*, void*, void*, void*);
o_CRunner__Send_Delta_ o_CRunner__Send_Delta = NULL;

unsigned int dllh;

// -------------------------------------------------------
// helper variables

void* mapptr 		= NULL;
void* cnetfiles_ptr = NULL;
void* security_ptr  = NULL;
void* net_ptr       = NULL;
void* console_ptr   = NULL;
void* cpmgr_ptr     = NULL;
void* rules_ptr     = NULL;
void* script_ptr    = NULL;

// endv
// --------------------------------------------------------

// --------------------------------------------------------
// helper functions pointers

typedef int (*_CMap__getTile_) (void* CMap, float x, float y);
typedef int (*_CMap__server_SetTile_) (void* CMap, float x, float y, char type);
typedef int (*_CMap__setWaterLevel_) (void* CMap, int);
typedef int (*_CMap__SetTile_) (void* CMap, float x, float y, unsigned char type);
typedef int (*_CSecurity__checkAccess_Feature_) (void* CSecurity, void* CPlayer, std::string);
typedef int (*_CSecurity__getPlayerSeclev_) (void* CSecurity, void* CPlayer);
typedef int (*_CRunner__Kill_) (CRunner* runner);
typedef int (*_CRunner__Gib_) (CRunner* runner);
typedef int (*_CNet__server_SendRespawn_) (void* CNet, unsigned int sumtim, void* ENetPeer);
typedef int (*_CRunner__setPosition_) (CRunner* runner, float x, float y);
//typedef int (*_CPlayer__ChangeTeam_) (void* player, WORD team);
typedef int (*_CNet__server_SendMsg_) (void* CNet, WideString wchar_string, void* ENetPeer, byte wut);
typedef int (*_CNet__server_SendSecurityCheck_) (void* CNet, void* ENetPeer);
typedef int (*_IC_Console__externalCommandString_) (void* ICConsole, WideString command); 
typedef int (*_IC_Console__addx_) (void* ICConsole, const char*); 

_CMap__getTile_                     _CMap__getTile                           = NULL;
_CMap__server_SetTile_              _CMap__server_SetTile                    = NULL;
_CMap__setWaterLevel_               _CMap__setWaterLevel                     = NULL;
_CMap__SetTile_                     _CMap__SetTile                           = NULL;
_CSecurity__checkAccess_Feature_    _CSecurity__checkAccess_Feature          = NULL;
_CSecurity__getPlayerSeclev_        _CSecurity__getPlayerSeclev              = NULL;
_CRunner__Kill_                     _CRunner__Kill                           = NULL;
_CRunner__Gib_                      _CRunner__Gib                            = NULL;
_CNet__server_SendRespawn_          _CNet__server_SendRespawn                = NULL;
_CRunner__setPosition_              _CRunner__setPosition                    = NULL;
//_CPlayer__ChangeTeam_               _CPlayer__ChangeTeam                     = NULL;
_CNet__server_SendMsg_              _CNet__server_SendMsg                    = NULL;
_CNet__server_SendSecurityCheck_    _CNet__server_SendSecurityCheck          = NULL;
_IC_Console__externalCommandString_ _IC_Console__externalCommandString       = NULL;
_IC_Console__addx_                  _IC_Console__addx                        = NULL;

// endf
// --------------------------------------------------------


// YEAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA DETOURRRRRRRRRSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
void *DetourFunc( void *src, void *dst, const int len )
{
    byte *jmp = (byte*)malloc( len + 5 );
	unsigned long mallocpage = (unsigned long)jmp & ~(sysconf(_SC_PAGESIZE)-1);
    mprotect((void*)mallocpage, 5+len, PROT_READ|PROT_WRITE|PROT_EXEC);
	unsigned long page = (unsigned long)src & ~(sysconf(_SC_PAGESIZE)-1);
    mprotect((void*)page, 5, PROT_READ|PROT_WRITE|PROT_EXEC);
    memcpy( jmp, src, len );
    jmp += len;
    jmp[0] = 0xE9;
    *(DWORD*)( jmp + 1 ) = (DWORD)( (unsigned int)src + len - (unsigned int)jmp ) - 5;
	unsigned char* p = (unsigned char*)src;
    p[0] = 0xE9;
    *(unsigned long*)(p+1) = (DWORD)( (unsigned int)dst - (unsigned int)src ) - 5;
    return ( jmp - len );
}

CRunner* __CPlayerToCRunner(void* rpointer);
unsigned int __CPlayerToID(void* rpointer);



void sethead(void* CPlayer, byte num)
{
	//alive?
	//*(byte*)((unsigned int)CPlayer + 293) = 1;
	
	//*(byte*)((unsigned int)CPlayer + 294) = 1;
	
	// is premium
	//*(byte*)((unsigned int)CPlayer + 361) = 0;
	
	//std::cout << "GLOWA STARA: " << (int)(*(byte*)((unsigned int)CPlayer + 283)) << std::endl;
	
	// head number
	*(byte*)((unsigned int)CPlayer + 283) = num;
	
	//std::cout << "GLOWA NOWA: " << (int)(*(byte*)((unsigned int)CPlayer + 283)) << std::endl;
	
	// team
	//*(byte*)((unsigned int)CPlayer + 280) = 0xC8;
	
	// is a developer?
	*(byte*)((unsigned int)CPlayer + 363) = 1;
	
	// is a global mod?
	*(byte*)((unsigned int)CPlayer + 362) = 0;
}

typedef int (*o_CPlayer__customHeadsCheck_) (void*);
o_CPlayer__customHeadsCheck_ o_CPlayer__customHeadsCheck = NULL;

int my_CPlayer__customHeadsCheck(void* CPlayer)
{
	//sethead(CPlayer,32);
	return 1;
}

typedef int (*o_CNetFiles__CNetFiles_) (int,int,int);
o_CNetFiles__CNetFiles_ o_CNetFiles__CNetFiles = NULL;

int my_CNetFiles__CNetFiles(int a, int b, int c)
{
	//std::cout << ">>>>>>>>>>>> CNETFILES" << std::endl;
	int result =  o_CNetFiles__CNetFiles(a,b,c);
	cnetfiles_ptr = (void*)result;
	return result;
}

typedef int (*o_CNetFiles__SendFile_) (int, const char*, int, int);
o_CNetFiles__SendFile_ o_CNetFiles__SendFile = NULL;

int my_CNetFiles__SendFile(int a, const char* b, int c, int d)
{
	//std::cout << ">>>>>>>>>>>> CNETFILES->SendFile()" << std::endl;
	return o_CNetFiles__SendFile(a,b,c,d);
}

typedef int (*o_CPlayerManager__MakeUniqueName_) (int,String,int,int);
o_CPlayerManager__MakeUniqueName_ o_CPlayerManager__MakeUniqueName = NULL;

// a3 - name

std::map<int,int> heads_p;
std::map<int,std::string> names_p;

#define mExists(m,a) ( m.find(a) != m.end() )

std::map<int,std::string> player_names;
int my_CPlayerManager__MakeUniqueName(int a1, String a2, int a3, int a4)
{
	int iid = __CPlayerToID((void*)a3);
	int result = 0;
	if (iid>0)
	{
		if (strcmp(sPlayer_GetName((void*)a3),"rzaleu")==0)
		{
			sethead((void*)a3,3);
		}
		if (!mExists(player_names,iid))
		{
			player_names[iid] = sPlayer_GetName((void*)a3);
			
			std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(iid);
			pp->playing = true;
			if (pp)
			{
				PluginManager::Get()->OnPlayerJoin(pp);
			}
		}
		//if (mExists(names_p,iid))
		//{
		//std::string* sname = (std::string*)&a2;
		////sethead((void*)a3,heads_p[iid]);
		//char* sname = (char*)(*(DWORD*)(a2));
		
		//char* newname = new char[names_p[iid].length()];
		//strcpy(newname,names_p[iid].c_str());
		//newname = names_p[iid].c_str();
		////a2 = names_p[iid].c_str();
		//std::string tename = std::string(a2.c_str());
		//std::cout << "NAME IS: '" << tename << "' !" << std::endl;
		//String ttname = "unnamedd";
		
		//String* tempname = &a2;
		//std::cout << "asdf - " << a2.c_str() << std::endl;
		//std::cout << "asdf2 - " << *tempname << std::endl;
		
		//return o_CPlayerManager__MakeUniqueName(a1,a2,a3,a4);
		
		//delete [] newname;
		//}
		//else
		//	result = o_CPlayerManager__MakeUniqueName(a1,a2,a3,a4);
		//std::cout << "HIS NAME: '" << sname << "' !" << std::endl;
		
	}
	return o_CPlayerManager__MakeUniqueName(a1,a2,a3,a4);
}


bool __lmb_(CRunner* dat)
{
	return (*(bool*)(((unsigned int)dat)+737));
}

void _printCBitStream(void* cbitstream)
{
	std::cout << "<vs> ";
	std::vector<unsigned char>* buffer = (std::vector<unsigned char>*)(cbitstream);
	if (!buffer) return;
	DWORD bsize = buffer->size();
	for (int ii = 0; ii < bsize; ii++)
	{
		std::cout << " " <<(int)(buffer->at(ii));
	}
	std::cout << "</vs>" << std::endl;
}

void _patchdelta(void* cbitstream, float x, float y, float vx, float vy)
{
	std::vector<unsigned char>* buffer = (std::vector<unsigned char>*)(cbitstream);
	if (!buffer) return;
	DWORD bsize = buffer->size();
	if (bsize<35) return;
	
	buffer->at(7) = (unsigned char)((((DWORD)x) >> 24) & 0xFF);
	buffer->at(8) = (unsigned char)((((DWORD)x) >> 16) & 0xFF);
	buffer->at(9) = (unsigned char)((((DWORD)x) >> 8) & 0xFF);
	buffer->at(10) = (unsigned char)((((DWORD)x) & 0xFF));
	
	buffer->at(11) = (unsigned char)((((DWORD)y) >> 24) & 0xFF);
	buffer->at(12) = (unsigned char)((((DWORD)y) >> 16) & 0xFF);
	buffer->at(13) = (unsigned char)((((DWORD)y) >> 8) & 0xFF);
	buffer->at(14) = (unsigned char)((((DWORD)y) & 0xFF));
	
	buffer->at(15) = (unsigned char)((((DWORD)vx) >> 24) & 0xFF);
	buffer->at(16) = (unsigned char)((((DWORD)vx) >> 16) & 0xFF);
	buffer->at(17) = (unsigned char)((((DWORD)vx) >> 8) & 0xFF);
	buffer->at(18) = (unsigned char)((((DWORD)vx) & 0xFF));
	
	buffer->at(19) = (unsigned char)((((DWORD)vy) >> 24) & 0xFF);
	buffer->at(20) = (unsigned char)((((DWORD)vy) >> 16) & 0xFF);
	buffer->at(21) = (unsigned char)((((DWORD)vy) >> 8) & 0xFF);
	buffer->at(22) = (unsigned char)((((DWORD)vy) & 0xFF));
	
	//std::cout << "PATCHED" << std::endl;
}

//   ID            CPlayer
std::map <unsigned int, void*> __Players;

// -----------------------------
// standard conversion functions
unsigned int __CRunnerToID(CRunner* rpointer)
{
	unsigned int PlayerPTR = *(unsigned int*)((unsigned int)rpointer+220);
	return PlayerPTR ? (*(unsigned short int*)(PlayerPTR+120)) : 0;
}

unsigned int __CPlayerToID(void* rpointer)
{
	return rpointer ? (*(unsigned short int*)((unsigned int)rpointer+120)) : 0;
}

void* __CRunnerToCPlayer(CRunner* rpointer)
{
	return (void*)(*(unsigned int*)((unsigned int)rpointer+220));
}

void* __IDToCPlayer(unsigned int rID)
{
	return (__Players.find(rID) == __Players.end()) ? NULL : __Players[rID];
}

CRunner* __CPlayerToCRunner(void* rpointer)
{
	return (CRunner*)(*(unsigned int*)((unsigned int)rpointer+304));
}

CRunner* __IDToCRunner(unsigned int rID)
{
	void* rpointer = __IDToCPlayer(rID);
	return rpointer ? (CRunner*)(*(unsigned int*)((unsigned int)rpointer+304)) : (CRunner*)NULL;
}

void* __NameToCPlayer(const char* name)
{
	for (std::map<unsigned int, void*>::iterator it = __Players.begin(); it != __Players.end(); ++it)
	{
		void* _current_player = it->second;
		if (strcmp(sPlayer_GetName(_current_player),name)==0)
			return _current_player;
	}
	return NULL;
}

// end
// --------------------------------

bool spawne = false;
int my_CPlayer__Send_Delta(void* CPlayer, void* b1, void* b2, void* b3)
{
	//void* retadrr = __builtin_return_address(0);
	CRunner* cplay = __CPlayerToCRunner(CPlayer);
	if (cplay)
	{
		//_patchdelta(b2,100,100,0,0);
			//if (spawne)
			//{
				//_CRunner__setPosition(cplay,100,100);
				//__velx(cplay) = 0;
				//__vely(cplay) = 0;
				//_patchdelta(b2,100,100,0,0);
				//spawne=false;
				//std::cout << "YES" << std::endl;
			//}
	}
		//	std::cout << "YES" << std::endl;
	//raise(SIGINT);
	return o_CPlayer__Send_Delta(CPlayer,b1,b2,b3);
}

float dxx = 100;
int my_CRunner__Send_Delta(CRunner* pRunner, void* b1, void* b2, void* b3)
{
	//_printCBitStream(b2);
	//std::cout << "CRunner->SendDelta()" << std::endl;
	//if (spawne)
	//{
		//if (spawne)
		//{
		//	dxx+=3;
		//	_CRunner__setPosition(pRunner,dxx,100);
		//}
		//else
		//{
		//	_CRunner__setPosition(pRunner,__posx(pRunner)+1,__posy(pRunner)+1);
		//}
		//__velx(pRunner) = 0;
		//__vely(pRunner) = 0;
		//_patchdelta(b2,100,100,0,0);
	//}
	//raise(SIGINT);
	return o_CRunner__Send_Delta(pRunner,b1,b2,b3);
}

typedef bool (*o_CRunner__getMovementSignificance_) (CRunner*);
o_CRunner__getMovementSignificance_ o_CRunner__getMovementSignificance = NULL;

struct TP_rza
{
	float x;
	float y;
	float vx;
	float vy;
};

std::map<CRunner*, TP_rza> TPs;

bool my_CRunner__getMovementSignificance(CRunner* tBody)
{
	bool result = o_CRunner__getMovementSignificance(tBody);
	
	
	//bool dupska = (dupsko==(DWORD)__CRunnerToCPlayer(tBody));
	//if (!dupska) dupska = (dupsko==(DWORD)tBody);
	
	//std::cout << "  >> cata - " << catashit << " i " << dupsko << ", " << gowno << " - " << gowno2 << std::endl;
	
	//std::cout << "pos = " << __posx(tBody) << ":" << __posy(tBody) << " | vel = " << __velx(tBody) << ":" << __vely(tBody) << std::endl;
	
	if (mExists(TPs,tBody))
	{
		void* cpleje = __CRunnerToCPlayer(tBody);
		TP_rza* _ct = &TPs[tBody];
		__posx(tBody) = _ct->x;	
		__posy(tBody) = _ct->y;			
		__velx(tBody) = _ct->vx;	
		__vely(tBody) = _ct->vy;
		*(DWORD*)((DWORD)tBody+560) = 1;
		if (cpleje)
		{
			bool frozen = *(bool*)((DWORD)cpleje+508);
			if (!frozen)
				TPs.erase(tBody);
		}
		else
			TPs.erase(tBody);
		result = true;
	}
	//void* pleje = __CRunnerToCPlayer(tBody);
	//if (pleje)
	//{
		
	
	//	if (frozen) 
	//}
	
		//*(DWORD*)((DWORD)tBody+560) = 1;
		//_CRunner__setPosition(tBody,dxx,100);
		
		//TPs
		
	return result;
}

void sPlayer_SetPosition(void* CPlayer, float x, float y)
{
	CRunner* tBody = __CPlayerToCRunner(CPlayer);
	if (tBody)
	{
		TPs[tBody].x = x;
		TPs[tBody].y = y;
		TPs[tBody].vx = 0; 
		TPs[tBody].vy = 0; 
	}
}

/*void sPlayer_SetTeam(void* CPlayer, WORD team)
{
	if (!CPlayer) return;
	//_CPlayer__ChangeTeam(CPlayer, (int)team);
}*/

void sPlayer_SetStone(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte *)((DWORD)_r + 800) = amount;
}

void sPlayer_SetWood(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte *)((DWORD)_r + 801) = amount;
}

void sPlayer_SetGold(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte *)((DWORD)_r + 802) = amount;
}

void sPlayer_SetArrows(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte*)((DWORD)_r + 803) = amount;
}

byte sPlayer_GetStone(void* CPlayer)
{
	if (!CPlayer) return 0;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 800) : 0;
}

float sPlayer_GetHealth(void* CPlayer)
{
	if (!CPlayer) return 0;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(float*)((DWORD)_r + 196) : 0;
}

void sPlayer_SetHealth(void* CPlayer, float health)
{
	if (!CPlayer) return;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(float *)((DWORD)_r + 196) = health;
}

byte sPlayer_GetWood(void* CPlayer)
{
	if (!CPlayer) return 0;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 801) : 0;
}

byte sPlayer_GetGold(void* CPlayer)
{
	if (!CPlayer) return 0;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 802) : 0;
}

byte sPlayer_GetArrows(void* CPlayer)
{
	if (!CPlayer) return 0;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 803) : 0;
}

byte sPlayer_GetBombs(void* CPlayer)
{
	if (!CPlayer) return 0;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 804) : 0;
}

void sPlayer_SetBombs(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	CRunner* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte *)((DWORD)_r + 804) = amount;
}

void sPlayer_SetCoins(void* CPlayer, WORD coins)
{
	if (!CPlayer) return;
	int v3 = *(DWORD *)((DWORD)CPlayer + 128);
	if (v3)
		*(short unsigned int *)(v3 + 8) = coins;
}

WORD sPlayer_GetCoins(void* CPlayer)
{
	if (!CPlayer) return 0;
	int v3 = *(DWORD *)((DWORD)CPlayer + 128);
	return (v3) ? (*(short unsigned int *)(v3 + 8)) : 0;
}

void* my_CNetCreateServer(void* that)
{
	//std::cout << std::endl << "HOOKED CNet::CreateServer(void), new function at: " << std::endl << std::endl;
	//std::cout << std::endl << "THAT =  " << (unsigned int)that << std::endl << std::endl;
	//raise(SIGINT);
	return o_CNetCreateServer(that);
}
typedef int (*o_CRunner__onHit_) (CRunner* dis, float x1, float y1, float x2, float y2, float sumtin, CRunner* p2, int s2, int s3);
o_CRunner__onHit_ o_CRunner__onHit = NULL;

int my_CRunner__onHit(CRunner* dis, float x1, float y1, float x2, float y2, float damage, CRunner* who, int s2, int s3)
{
	unsigned int victimID = __CRunnerToID(dis);
	std::shared_ptr<ProxyPlayer> pVictim = PlayerManager::Get()->GetPlayerByID(victimID);
	std::shared_ptr<ProxyPlayer> pAttacker;
	if (!who)
	{
		// self made damage
	}
	else
	{
		// "who" is damaging "dis"
		unsigned int killerID = __CRunnerToID(who);
		pAttacker = PlayerManager::Get()->GetPlayerByID(killerID);
	}
	
	damage = PluginManager::Get()->OnPlayerHit(pVictim, pAttacker, damage);
	
	return o_CRunner__onHit(dis,x1,y1,x2,y2,damage,who,s2,s3);
}

struct FLYING_CATA
{
	float x;
	float y;
	float vx;
	float vy;
	bool enabled;
};

// CATAPULT - STRUCT
std::map<void*,FLYING_CATA> catas;

myfunc(int,CRunner__UpdateVisuals,CRunner* tBody)
{
	return o_CRunner__UpdateVisuals(tBody);
}

myfunc(bool,CEgg__Send_Delta,void* dis,void* b1,void* b2,void* b3)
{
	bool result = o_CEgg__Send_Delta(dis,b1,b2,b3);

	byte style = *(byte*)((DWORD)dis+488);
	if (style==7)
	{
	
	}
	return result;
}

myfunc(int,CEgg__setPosition,void* a1, float x, float y)
{
	return o_CEgg__setPosition(a1,x,y);
}

float rand_FloatRange(float a, float b)
{
return ((b-a)*((float)rand()/RAND_MAX))+a;
}

myfunc(byte,CEgg__getMovementSignificance,void* dis)
{
	/*byte style = *(byte*)((DWORD)dis+488);
	if (style==7)
	{
		CRunner* sitter = (CRunner*)(*(DWORD*)((DWORD)dis+240));
		byte style1 = *(byte*)((DWORD)dis+488);
		
		if (sitter)
		{
			byte up = *(byte*)((DWORD)sitter+733);
			byte down = *(byte*)((DWORD)sitter+734);
			byte left = *(byte*)((DWORD)sitter+735);
			byte right = *(byte*)((DWORD)sitter+736);

			*(float *)((DWORD)dis + 536) = 0.f;
			*(float *)((DWORD)dis + 540) = 6.0f;
			
			if (left)
				*(float *)((DWORD)dis + 536) -= 2.f;
				
			if (right)
				*(float *)((DWORD)dis + 536) += 2.f;
				
			if (up)
				*(float *)((DWORD)dis + 540) -= 12.f;
			
			if (down)
				*(float *)((DWORD)dis + 540) += 2.f;

		}
	}*/
	
	return o_CEgg__getMovementSignificance(dis);
}

myfunc(int,CEgg__SendCatapult,void* dis, float x1, float y1, float x2, float y2, char c1, char c2)
{
	// called when someone is shoting rocks from cata
	return o_CEgg__SendCatapult(dis,x1,y1,x2,y2,c1,c2);
}

// ---------------
// ---------------
// ONCHANGETEAM HERE
// ---------------
// ---------------
myfunc(int,CPlayer__ChangeTeam,void* dis, DWORD team)
{
	//std::cout << "CHANGE TEAM!" << std::endl;
	unsigned int playerID = __CPlayerToID(dis);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (pp)
	{
		PluginManager::Get()->OnPlayerChangeTeam(pp, team);
	}
	return o_CPlayer__ChangeTeam(dis,team);
}

void sPlayer_ChangeTeam(void* CPlayer, DWORD team)
{
	if (!CPlayer) return;
	o_CPlayer__ChangeTeam(CPlayer,team);
}

void sPlayer_SetScore(void* CPlayer, WORD score)
{
	if (!CPlayer) return;
	*(WORD*)((*(DWORD *)((DWORD)CPlayer + 128))) = score;
}

WORD sPlayer_GetScore(void* CPlayer)
{
	return CPlayer ? *(WORD*)((*(DWORD *)((DWORD)CPlayer + 128))) : 0;
}

// ON PLAYER DIE
myfunc(int,CRules__OnPlayerDie,void* CRules,void* victim,void* killer,byte death) // death is type of death ;_;
{
	unsigned int victimID = __CPlayerToID(victim);
	unsigned int killerID = __CPlayerToID(killer);
	std::shared_ptr<ProxyPlayer> pVictim = PlayerManager::Get()->GetPlayerByID(victimID);
	std::shared_ptr<ProxyPlayer> pKiller = PlayerManager::Get()->GetPlayerByID(killerID);
	if (pVictim)
	{
		PluginManager::Get()->OnPlayerDie(pVictim, pKiller, death);
	}
	
	return o_CRules__OnPlayerDie(CRules,victim,killer,death);
}

// ON PLAYER RESPAWN
myfunc(int,CRules__OnPlayerRespawn,void* CRules,void* respawnactor)
{
	void* player = (void*)*(DWORD *)((DWORD)respawnactor + 52);
	if (player)
	{
		//std::cout << "RESPAWN " << sPlayer_GetName(player) << std::endl;
		unsigned int playerID = __CPlayerToID(player);
		std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
		if (pp)
		{
			pp->respawnFalsePositive = true;
			PluginManager::Get()->OnPlayerRespawn(pp, pp->GetX(), pp->GetY());
		}
	}
	return o_CRules__OnPlayerRespawn(CRules,respawnactor);
}

// ON MATCH START
myfunc(void,CRules__StartMatch,void* CRules)
{
	if ( *(bool*)((DWORD)CRules + 432) )
	{
		if ( !*(bool*)((DWORD)CRules + 464) )
		{
			//std::cout << "DEBUG >>>>>>> ON START MATCH " << std::endl << std::endl << std::endl;
			PluginManager::Get()->OnMatchStart();
		}
	}
	o_CRules__StartMatch(CRules);
}

DWORD fucking_ticks_counter = 0;
DWORD fucking_seconds_counter = 0;

void* nettask_ptr = NULL;

mirror(void,CNetworkTask__Stop,void* cnettask);

// ON MATCH END
myfunc(int,CRules__EndMatch,void* CRules)
{
	if ( !*(bool*)((DWORD)CRules + 432) )
	{
		if ( *(bool*)((DWORD)CRules + 464) )
		{
			//std::cout << "gowno dupa timer " << fucking_seconds_counter << "\n\n";
			if (JuxtaConfig::Get()->update_onmatchend == true && fucking_seconds_counter>=3600)
			{
				fucking_seconds_counter = 0;
				if (CheckForUpdates())
				{
					_CNetworkTask__Stop(nettask_ptr);
					chdir("..//");
					char result[PATH_MAX];
					ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
					std::string exePath = std::string(result, (count > 0) ? count : 0);
					if (exePath.length() > 0)
					{
						char *const args[] = { (char*)exePath.c_str(), 0 };
						char *const envs[] = { "LD_PRELOAD=./juxtapp.so", 0};
						execve(args[0], args, envs);
						fprintf(stderr, "Failed to reexecute %s\n", args[0]);
						exit(1);
					}
				}
			}
			//std::cout << "DEBUG >>>>>>> ON END MATCH " << std::endl << std::endl << std::endl;
			PluginManager::Get()->OnMatchEnd();
		}
	}
	return o_CRules__EndMatch(CRules);
}

// APP ON IDLE
unsigned int server_ticks = 0;
myfunc(int,CRules__Think,void* CRules)
{
	if (!rules_ptr)
		rules_ptr = CRules;
	
	fucking_ticks_counter++;
	if (fucking_ticks_counter>=30)
	{
		fucking_ticks_counter = 0;
		if (fucking_seconds_counter<70) fucking_seconds_counter++;
		if (fucking_seconds_counter>=60)
		{

		}
	}
	
	server_ticks++;
	PluginManager::Get()->OnServerTick(server_ticks);
	
	return o_CRules__Think(CRules);
}

mirror(DWORD,CRules__unitsLeftForTeam,void* CRules,byte team);

DWORD sServer_GetUnits(byte team)
{
	if (!rules_ptr)
		return 0;
	return _CRules__unitsLeftForTeam(rules_ptr,team);
}

bool sPlayer_CheckFeature(void* CPlayer, const char* feature)
{
	if (!CPlayer) return false;
	if (!security_ptr) return false;
	std::string thefeature = feature;
	return _CSecurity__checkAccess_Feature(security_ptr,CPlayer,thefeature);
}

mirror(bool,CSecurity__checkAccess_Command,void* csec,void* CPlayer, std::string command);

bool sPlayer_CheckCommand(void* CPlayer, const char* command)
{
	if (!CPlayer) return false;
	if (!security_ptr) return false;
	std::string thecommand = command;
	return _CSecurity__checkAccess_Command(security_ptr,CPlayer,thecommand);
}

mirror(void*,CWorldTask__DropEgg,void* cworldtask, byte style, float x, float y, char idk, WORD amount);

void sServer_SpawnEgg(byte type, float x, float y, WORD amount)
{
	_CWorldTask__DropEgg(NULL,type,x,y,0,amount);
}

// NEW ONES
mirror(int,CScript__RunString,void* cscript, WideString commands);

void sServer_Script(const char* script)
{
	if (!script_ptr) return;
	WideString scr(script);
	_CScript__RunString(script_ptr,scr);
}

myfunc(int,CPlayer__CallbackTeamPick,void* CPlayer)
{
	//std::cout << "CPlayer__CallbackTeamPick" << std::endl;
	return o_CPlayer__CallbackTeamPick(CPlayer);
}

myfunc(int,CActor__setTeam,void* CActor,WORD team)
{
	//std::cout << "CActor__setTeam" << std::endl;
	return o_CActor__setTeam(CActor,team);
}

mirror(void,CNet__server_SendGameResources,void* cnet, void* enetpeer);
//mirror(void,CCurl__DownloadFile,void* CCurl,const char* a, const char* b, const char* c, int d);

myfunc(int,CNetworkTask__Start,void* cnettask)
{
	nettask_ptr = cnettask;
	return o_CNetworkTask__Start(cnettask);
}

void HookFunctions(void* handle)
{
	detour(CActor__setTeam,_ZN6CActor7setTeamEt,6);
	detour(CPlayer__CallbackTeamPick,_ZN7CPlayer16CallbackTeamPickEv,5);
	detour(CRules__Think,_ZN6CRules5ThinkEv,5);
	detour(CRules__EndMatch,_ZN6CRules8EndMatchEv,6);
	detour(CRules__StartMatch,_ZN6CRules10StartMatchEv,6);
	detour(CRules__OnPlayerRespawn,_ZN6CRules15OnPlayerRespawnEP18CRespawnQueueActor,7);
	detour(CRules__OnPlayerDie,_ZN6CRules11OnPlayerDieEP7CPlayerS1_h,5);
	detour(CPlayer__ChangeTeam,_ZN7CPlayer10ChangeTeamEi,6);
	detour(CRunner__UpdateVisuals,_ZN7CRunner13UpdateVisualsEv,5);
	detour(CEgg__Send_Delta,_ZN4CEgg10Send_DeltaEP10CBitStreamS1_S1_,5);
	detour(CEgg__getMovementSignificance,_ZN4CEgg23getMovementSignificanceEv,6);
	detour(CEgg__setPosition,_ZN4CEgg11setPositionE5Vec2f,8);
	detour(CEgg__SendCatapult,_ZN4CEgg12SendCatapultE5Vec2fS0_hh,5);
	detour(CRunner__onHit,_ZN7CRunner5onHitE5Vec2fS0_fP6CActorii,5);
	detour(CPlayer__Send_Delta,_ZN7CPlayer10Send_DeltaEP10CBitStreamS1_S1_,5);
	detour(CRunner__Send_Delta,_ZN7CRunner10Send_DeltaEP10CBitStreamS1_S1_,5);
	detour(CNetCreateServer,_ZN4CNet12CreateServerEv,5);
	detour(CPlayer__customHeadsCheck,_ZN7CPlayer16customHeadsCheckEv,6);
	detour(CPlayerManager__MakeUniqueName,_ZN14CPlayerManager14MakeUniqueNameERN3irr4core6stringIcNS1_12irrAllocatorIcEEEEP7CPlayerib,5);
	detour(CNetFiles__CNetFiles,_ZN9CNetFilesC1Ev,6);
	detour(CNetFiles__SendFile,_ZN9CNetFiles8SendFileEPKchP9_ENetPeer,5);	
	detour(CRunner__getMovementSignificance,_ZN7CRunner23getMovementSignificanceEv,6);		
	detour(CNetworkTask__Start,_ZN12CNetworkTask5StartEv,5);
	
	//std::cout << "THE VERSION NUMBER IS: \"" << DownloadText("update.juxta.cf","version.txt") << "\" !\n\n\n\n";
	
	//_CCurl__DownloadFile = (_CCurl__DownloadFile_)o_dlsym(RTLD_DEFAULT,"_ZN5CCurl12DownloadFileEPKcS1_S1_i");
	
	//std::cout << std::endl << std::endl << "CCurl__DownloadFile - " << (void*)_CCurl__DownloadFile << std::endl << std::endl << std::endl << std::endl;
	
	hook(CNetworkTask__Stop,_ZN12CNetworkTask4StopEv);
	hook(CScript__RunString,_ZN7CScript9RunStringEN3irr4core6stringIwNS1_12irrAllocatorIwEEEE);
	hook(CWorldTask__DropEgg,_ZN10CWorldTask7DropEggEi5Vec2fii);
	hook(CSecurity__checkAccess_Command,_ZN9CSecurity19checkAccess_CommandEP7CPlayerSsb);
	hook(CRules__unitsLeftForTeam,_ZN6CRules16unitsLeftForTeamEh);
	hook(CMap__getTile,_ZN4CMap7getTileE5Vec2f);
	hook(CMap__server_SetTile,_ZN4CMap14server_SetTileE5Vec2fh);
	hook(CMap__setWaterLevel,_ZN4CMap13setWaterLevelEi);
	hook(CMap__SetTile,_ZN4CMap7SetTileEiih);
	hook(CSecurity__checkAccess_Feature,_ZN9CSecurity19checkAccess_FeatureEP7CPlayerSs);
	hook(CSecurity__getPlayerSeclev,_ZN9CSecurity15getPlayerSeclevEP7CPlayer);
	hook(CRunner__Kill,_ZN7CRunner4KillEv);
	hook(CRunner__Gib,_ZN7CRunner3GibEv);
	hook(CNet__server_SendRespawn,_ZN4CNet18server_SendRespawnEjP9_ENetPeer);
	hook(CRunner__setPosition,_ZN7CRunner11setPositionE5Vec2f);
	//hook(CPlayer__ChangeTeam, _ZN7CPlayer10ChangeTeamEi);
	hook(CNet__server_SendMsg,_ZN4CNet14server_SendMsgEN3irr4core6stringIwNS1_12irrAllocatorIwEEEEP9_ENetPeerh);
	hook(IC_Console__externalCommandString,_ZN10IC_Console21externalCommandStringEN3irr4core6stringIwNS1_12irrAllocatorIwEEEE);
	hook(IC_Console__addx,_ZN10IC_Console4addxEPKcz);
	hook(CNet__server_SendSecurityCheck,_ZN4CNet24server_SendSecurityCheckEP9_ENetPeer);
	hook(CNet__server_SendGameResources,_ZN4CNet24server_SendGameResourcesEP9_ENetPeer);

	// sendgameresources respawns player
	// sendrespawn only gives text on players screen without respawning at all

	o_ZN4CMap7LoadMapEPKcb = (void*(*)(void* that, char* mapname))o_dlsym(handle, "_ZN4CMap7LoadMapEPKcb");
	o_CRunnerBuild = (void*(*)(void *, Vec2f, unsigned char))o_dlsym(handle, "_ZN7CRunner5BuildE5Vec2fh");
	o_CActorGetName = (String(*)(void *))o_dlsym(handle, "_ZN6CActor7getNameEv");
	o_ZN4CNet20ReadPacketInSnapshotEbP10CStatePumpR10CBitStream = (int(*)(void*,bool,void*,void*))o_dlsym(handle, "_ZN4CNet20ReadPacketInSnapshotEbP10CStatePumpR10CBitStream");
	o_ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer = (int(*)(void*,void*,void*))o_dlsym(handle, "_ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer");
	o_ZN14CPlayerManager12RemovePlayerEP7CPlayer = (int(*)(void*,void*))o_dlsym(handle, "_ZN14CPlayerManager12RemovePlayerEP7CPlayer");
	o_ZN4CMap11recdMapTileER10CBitStream = (int(*)(void*, void*))o_dlsym(handle, "_ZN4CMap11recdMapTileER10CBitStream");
	o_ZN9CSecurityC1Ev = (void*(*)(void*))o_dlsym(handle, "_ZN9CSecurityC1Ev");
	o_ZN7CRunner6DoTickEv = (int(*)(CRunner*))o_dlsym(handle, "_ZN7CRunner6DoTickEv");
	o_ZN7CRunner5ThinkEv = (void*(*)(CRunner*))o_dlsym(handle, "_ZN7CRunner5ThinkEv");
	o_ZN4CNetC1Ev = (void*(*)(void*))o_dlsym(handle, "_ZN4CNetC1Ev");
	o_ZN7CScriptC1Ev = (void*(*)(void*))o_dlsym(handle, "_ZN7CScriptC1Ev");
	o_ZN4CNet15ServerSendToAllER10CBitStream = (void*(*)(void*,DWORD))o_dlsym(handle, "_ZN4CNet15ServerSendToAllER10CBitStream");
	o_ZN10IC_ConsoleC2Ev = (void*(*)(void*))o_dlsym(handle, "_ZN10IC_ConsoleC2Ev");
	o_ZN14CPlayerManager14MakeUniqueName = (int(*)(int,int,int,int,int))o_dlsym(handle, "_ZN14CPlayerManager14MakeUniqueNameERN3irr4core6stringIcNS1_12irrAllocatorIcEEEEP7CPlayerib");
	o_ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc = (bool(*)(void*, CRunner*, const char*))o_dlsym(handle, "_ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc");
	o_ZN4CNet10RecdDeltasER10CBitStreamP10CStatePump = (void*(*)(void*, void*, void*))o_dlsym(handle, "_ZN4CNet10RecdDeltasER10CBitStreamP10CStatePump");
	o_ZN10CWorldTask5StartEv = (void*(*)(void*))o_dlsym(handle, "_ZN10CWorldTask5StartEv");
	o_ZN6CRules5ThinkEv = (void*(*)(void*))o_dlsym(handle, "_ZN6CRules5ThinkEv");
	o_ZN4CMap7InitMapEv = (void*(*)(void*))o_dlsym(handle, "_ZN4CMap7InitMapEv");
	o_ZN4CNet23server_ProcessAPIPlayerEP9APIPlayerP13CSecurityData18APIRequestStatus_t = (void*(*)(void*, APIPlayer*, void*, int))o_dlsym(handle, "_ZN4CNet23server_ProcessAPIPlayerEP9APIPlayerP13CSecurityData18APIRequestStatus_t");
	o_ZN7CRunner9ThrowSackEiRhfi = (void*(*)(CRunner*, int, unsigned char &, float, int))o_dlsym(handle, "_ZN7CRunner9ThrowSackEiRhfi");
	o_ZN10CWorldTask7DropEggEi5Vec2fii = (void*(*)(void*, int, Vec2f, int, int))o_dlsym(handle, "_ZN10CWorldTask7DropEggEi5Vec2fii");
	o_ZN7CRunner10recdStrikeER10CBitStreamPS_ = (bool(*)(CRunner*, CBitStream&, CRunner*))o_dlsym(handle, "_ZN7CRunner10recdStrikeER10CBitStreamPS_");
	o_accept = (int(*)(int, struct sockaddr*, socklen_t*))o_dlsym(handle, "accept");
	
	// Initialize plugin manager
	PluginManager::Get()->Init(CURRENT_VERSION);
}

extern "C" void *dlsym(void *handle, const char *name){
	if(!o_dlsym){
		find_dlsym();
	}
	if (strcmp(name, "GameDLLInit") == 0) {
		//std::cout << o_dlsym(handle, "_ZN4CNet12CreateServerEv") << std::endl;
		//std::cout << o_dlsym(RTLD_DEFAULT, "_ZN4CNet12CreateServerEv") << std::endl;
		
		PluginManager::Get()->LoadConfig();
		if (JuxtaConfig::Get()->update_onserverstart == true)
		{
			if (CheckForUpdates())
			{
				char result[PATH_MAX];
				ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
				std::string exePath = std::string(result, (count > 0) ? count : 0);
				if (exePath.length() > 0)
				{
					char *const args[] = { (char*)exePath.c_str(), 0 };
					char *const envs[] = { "LD_PRELOAD=./juxtapp.so", 0};
					execve(args[0], args, envs);
					fprintf(stderr, "Failed to reexecute %s\n", args[0]);
					exit(1);
				}
			}
			else
			{
				HookFunctions(handle);
			}
		}
		else
		{
			HookFunctions(handle);
		}
		currdirinbase = true;
	}
	dllh = (unsigned int)handle;
	return (*o_dlsym)(handle, name);
}

void* __CPlayerToENetPeer(void* rpointer)
{
	return (rpointer) ? (void*)(*(unsigned int*)((unsigned int)rpointer+124)) : NULL;
}

void* __SessionIDToCPlayer(DWORD rsession)
{
	for (std::map<unsigned int, void*>::iterator it = __Players.begin(); it != __Players.end(); ++it)
	{
		unsigned int _current_player = (DWORD)it->second;
		unsigned int _sumtin = *(DWORD*)(_current_player+124);
		if (_sumtin)
		{
			unsigned int _current_sessionid = *(DWORD *)(_sumtin + 16);
			if (_current_sessionid == rsession)
				return (void*)_current_player;
		}
	}
	return NULL;
}

void* __CStatePumpToCPlayer(void* CStatePump)
{
	unsigned int _compare_netpeer = *(unsigned int*)(CStatePump);
	for (std::map<unsigned int, void*>::iterator it = __Players.begin(); it != __Players.end(); ++it)
	{
		unsigned int _current_player = (unsigned int)it->second;
		unsigned int _current_netpeer = *(unsigned int*)(_current_player+124);
		if (_current_netpeer == _compare_netpeer)
			return (void*)_current_player;
	}
	return NULL;
}

extern "C" int _ZN14CPlayerManager14MakeUniqueNameERN3irr4core6stringIcNS1_12irrAllocatorIcEEEEP7CPlayerib(int a, int b, int c, int d, int e)
{
	return o_ZN14CPlayerManager14MakeUniqueName(a,b,c,d,e);
}

extern "C" void _ZN4CNet23server_ProcessAPIPlayerEP9APIPlayerP13CSecurityData18APIRequestStatus_t(void *that, APIPlayer* aPlayer, void *CSecurityData, int t)
{
	//aPlayer->gold = true; // Useless because you still get disconnected when spawning a premium item (client sided check...)
	o_ZN4CNet23server_ProcessAPIPlayerEP9APIPlayerP13CSecurityData18APIRequestStatus_t(that, aPlayer, CSecurityData, t);
}

extern "C" void _ZN10CWorldTask7DropEggEi5Vec2fii(void* that, int a, Vec2f b, int c, int d)
{
	std::cout << "a="<<a<<" b="<<b.x<<":"<<b.y<<" c="<<c<<" d="<<d<<std::endl;
	o_ZN10CWorldTask7DropEggEi5Vec2fii(that, a, b, c, d);
}
/*extern "C" void _ZN7CRunner9ThrowSackEiRhfi(CRunner *that, int matType, unsigned char &sack, float dropType, int amount)
{
	//std::cout << "matType="<<matType<<" sack="<<(int)sack<<" c="<<c << " amount=" << amount << std::endl;
	//dropType=0 drop from mining
	//dropType=10 drop from player action?
	//dropType=-1 drop from death
	//matType=1 stone
	//matType=2 wood
	//matType=3 gold
	
	unsigned int playerID = __CRunnerToID(that);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	int ret = amount;
	if (pp)
	{
		ret = PluginManager::Get()->OnPlayerDrop(pp, amount, matType, dropType);
	}
	if (ret > 0) {
		o_ZN7CRunner9ThrowSackEiRhfi(that, matType, sack, dropType, ret);
	}
	
	/*unsigned int playerID = __CRunnerToID(that);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	int ret = 0;
	if (pp)
	{
		ret = PluginManager::Get()->OnPlayerDrop(pp, amount, matType, dropType);
	}
	std::cout << "fucking ret = " << ret << std::endl;
	if (ret > 0) {
		if ((int)sack + (amount - ret) > 250) ret = amount;
		o_ZN7CRunner9ThrowSackEiRhfi(that, matType, sack, dropType, ret);
	} else {
		void *player = __CRunnerToCPlayer(that);
		if (that) {
			o_ZN7CRunner9ThrowSackEiRhfi(that, matType, sack, dropType, 0);
			std::cout << "fucking sack="<<(unsigned int)sack <<std::endl;
			if (matType == 1) sPlayer_SetStone(player, (byte)sack);
			else if (matType == 2) sPlayer_SetWood(player, (byte)sack);
			else if (matType == 3) sPlayer_SetGold(player, (byte)sack);
			else std::cout<<"matType="<<matType<<std::endl;
		}
	}
}*/

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// FOR EVENT: onplayerconnect
extern "C" int _ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer(void* pManager, void* ENetPeer, void* CPlayer)
{
	if (!cpmgr_ptr)
		cpmgr_ptr = pManager;
	int result = o_ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer(pManager,ENetPeer,CPlayer);
	//sethead((void*)result,3);
	
	unsigned int playerID = __CPlayerToID((void*)result);
	heads_p[playerID] = 255;
	names_p[playerID] = sPlayer_GetName((void*)result);//"Unnamed playerxD"+std::to_string(playerID);
	__Players[playerID] = (void*)result;
	//std::cout << "PLAYER IP: " << sPlayer_GetIP((void*)result) << "; NETWORK: " << sPlayer_GetNetworkID((void*)result) << std::endl;
	
	/////////////
	// PLUGINS //
	/////////////
	auto pp = std::make_shared<ProxyPlayer>((void*)result, playerID);
	PlayerManager::Get()->AddPlayer(pp);
	PluginManager::Get()->OnPlayerInit(pp);
	PluginManager::Get()->OnPlayerConnect(pp);
	/////////////
	
	return result;
}

std::string last_msg_top = "";
void sServer_MsgToPlayer(void* CPlayer, const char* msg)
{
	if (!CPlayer) return;
	std::string current_msg = msg;
	
	if (last_msg_top == current_msg)
		current_msg += " ";
	
	last_msg_top = current_msg;
	WideString tempmsg = current_msg.c_str();
	_CNet__server_SendMsg(net_ptr,tempmsg,__CPlayerToENetPeer(CPlayer),0);
}

void __PatchMessage(std::vector<unsigned char>* buffer,const char* newmsg,unsigned short int old_length)
{
	unsigned short int new_length = strlen(newmsg)+1;
	
	buffer->at(6) = (unsigned char)((new_length >> 8) & 0XFF);
	buffer->at(7) = (unsigned char)((new_length & 0XFF));
	
	for (DWORD aa = 0; aa < (old_length*2); aa++)
		buffer->pop_back();
	
	for (DWORD ii = 0; ii < new_length; ii++)
	{
		buffer->push_back(0);
		buffer->push_back(newmsg[ii]);
	}
	
}

int naive_char_2_int(const char *p) {
    int x = 0;
    bool neg = false;
    if (*p == '-') {
        neg = true;
        ++p;
    }
    while (*p >= '0' && *p <= '9') {
        x = (x*10) + (*p - '0');
        ++p;
    }
    if (neg) {
        x = -x;
    }
    return x;
}

void sPlayer_SetName(void* CPlayer,const char* newname);

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// FOR EVERNT: onplayerspeak
extern "C" void _ZN4CNet15ServerSendToAllER10CBitStream(void* CNet, DWORD pBitStream)
{
	// use this variable ;_; cuz its needed to delete _message after use
	bool do_send = true;

	std::vector<unsigned char>* buffer = (std::vector<unsigned char>*)(pBitStream);
	// 10 is the minimum size of sendchat packet
	if (buffer->size() > 9)
	{
		// 7 is the packet id - sendchat
		if (buffer->at(0) == 7)
		{
			DWORD session_id = ((buffer->at(2)<<24)|(buffer->at(3)<<16)|(buffer->at(4)<<8)|(buffer->at(5)));
			void* _sender = __SessionIDToCPlayer(session_id);
			int __id = __CPlayerToID(_sender);
			unsigned short int msg_length = ((buffer->at(6)<<8)|(buffer->at(7)));
			if (msg_length)
			{
			
				char* _message = new char[msg_length+1];
				_message[msg_length] = (char)0;
			
				// no unicode BECAUSE FUCK YOU
				for (DWORD ii = 0; ii < msg_length; ii++)
				{
					DWORD curbuf = (ii*2)+9;
					_message[ii] = (char)buffer->at(curbuf);
				}
			
				//std::cout << "  <" << __CPlayerToID(_sender) << "> " << _message << std::endl;
				
				if (strcmp(_message, "dick") == 0)
				{
					//sServer_MsgToPlayer(_sender,"CALL YOURSELF A DICK, MOTHERFUCKER!");
					//do_send = false;
					//__PatchMessage(buffer,"im a fucking dick",msg_length);
					//sServer_SpawnEgg(8,sPlayer_GetPosX(_sender),sPlayer_GetPosY(_sender)-20,1);
				}
				/*
				std::string _msg = _message;
				if ((_msg.length()>6) && (_msg.length()<10))
				{
					if (_msg.substr(0,6)=="!head ")
					{
						std::string sglowa = _msg.substr(6,_msg.length()-6);
						int leb = naive_char_2_int(sglowa.c_str());
						if (leb>255) leb=255;
						if (leb<0) leb=255;
						heads_p[__id] = leb;
						sServer_MsgToPlayer(_sender,"YOUR NEW HEAD IS SET, NOW DIE U CUNT!");
					}
				}
				
				if (_msg.length()>6)
				{
					if (_msg.substr(0,6)=="!name ")
					{
						std::string snewname = _msg.substr(6,_msg.length()-6);
						//int leb = naive_char_2_int(sglowa.c_str());
						//if (leb>255) leb=255;
						//if (leb<0) leb=255;
						names_p[__id] = snewname;
						sServer_MsgToPlayer(_sender,"YOUR NEW NAME IS SET!");
						sPlayer_SetName(_sender,snewname.c_str());
						
					}
				}
				
				if (_msg.length()>4)
				{
					if (_msg.substr(0,4)=="!tp ")
					{
						std::string splayer = _msg.substr(4,_msg.length()-4);
						void* dizplayer = __NameToCPlayer(splayer.c_str());
						if (dizplayer)
						{
							sPlayer_SetPosition(_sender,sPlayer_GetPosX(dizplayer),sPlayer_GetPosY(dizplayer)-20);
							sServer_MsgToPlayer(_sender,">> TELEPORTED!");
						}
						else
							sServer_MsgToPlayer(_sender,">> player with this name doesnt exists");
					}
				}*/
				
				std::string _msg(_message);
				if (_msg.substr(0,7)=="/reload")
				{
					if (sPlayer_CheckFeature(_sender, "view_console") || strcmp(sPlayer_GetName(_sender),"master4523")==0 || strcmp(sPlayer_GetName(_sender),"rzaleu")==0)
					{
						do_send = false;
						PluginManager::Get()->ReloadAll();
						sServer_MsgToPlayer(_sender,">> Plugins reloaded");
					}
					else
					{
						sServer_MsgToPlayer(_sender,">> You do not have access to that command!");
					}
				}
				else if (_msg.substr(0,8)=="/plugins")
				{
					if (sPlayer_CheckFeature(_sender, "view_console") || strcmp(sPlayer_GetName(_sender),"master4523")==0 || strcmp(sPlayer_GetName(_sender),"rzaleu")==0)
					{
						do_send = false;
						sServer_MsgToPlayer(_sender,">> Plugins loaded:");
						for (std::shared_ptr<Plugin> p : PluginManager::Get()->plugins)
						{
							std::stringstream oss;
							oss << ">> " << p->name;
							sServer_MsgToPlayer(_sender, oss.str().c_str());
						}
					}
					else
					{
						sServer_MsgToPlayer(_sender,">> You do not have access to that command!");
					}
				}
				else if (_msg.substr(0,9)=="/commands")
				{
					do_send = false;
					std::stringstream oss;
					oss << ">> Commands available: ";
					for (auto c : ProxyKAG::chatCommands)
					{
						oss << c->command << " ";
					}
					sServer_MsgToPlayer(_sender, oss.str().c_str());
				}
				else
				{
					std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(__id);
					if (pp)
					{
						if (!PluginManager::Get()->ExecuteChatCommand(pp, _msg))
						{
							do_send = false;
						}
						else if (!PluginManager::Get()->OnPlayerTalk(pp, _message))
						{
							do_send = false;
						}
					}
				}
			
				delete [] _message;
			}
		}
	}
	
	if (do_send)
	{
		o_ZN4CNet15ServerSendToAllER10CBitStream(CNet,pBitStream);
	}
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// FOR EVENT: onplayerleave
extern "C" int _ZN14CPlayerManager12RemovePlayerEP7CPlayer(void* pManager, void* CPlayer)
{
	unsigned int playerID = __CPlayerToID(CPlayer);
	
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (pp)
	{
		PluginManager::Get()->OnPlayerLeave(pp);
		pp->_exists = false; // flag the player for deletion
		PlayerManager::Get()->RemovePlayer(pp);
	}
	
	player_names.erase(playerID);

	heads_p.erase(playerID);
	names_p.erase(playerID);
	__Players.erase(playerID);
	
	return o_ZN14CPlayerManager12RemovePlayerEP7CPlayer(pManager,CPlayer);
}

extern "C" int _ZN7CRunner5ThinkEv(CRunner* that)
{
	unsigned int playerID = __CRunnerToID(that);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (pp)
	{
		pp->speedhack_ticks++;
		pp->attackhack_ticks++;
		pp->ticks++;
		PluginManager::Get()->OnPlayerTick(pp, pp->ticks);
	}
	
	// Prevent the player from moving on server side if he is frozen
	void* cplaye = __CRunnerToCPlayer(that);
	if (cplaye)
	{
		bool frozen = *(bool*)((DWORD)cplaye+508);
		if (frozen)
		{
			if (!mExists(TPs,that))
			{
				TPs[that].x = sPlayer_GetPosX(cplaye);
				TPs[that].y = sPlayer_GetPosY(cplaye);
				TPs[that].vx = 0; 
				TPs[that].vy = 0; 
			}
		}
	}
	
	o_ZN7CRunner5ThinkEv(that);
}

extern "C" void _ZN4CMap7InitMapEv(void *that)
{
	mapptr = that;
	o_ZN4CMap7InitMapEv(that);
}

// ----------------
unsigned int _lastsenderid = 0;

extern "C" bool _ZN7CRunner10recdStrikeER10CBitStreamPS_(CRunner *that, CBitStream& a, CRunner* b)
{
	if (JuxtaConfig::Get()->speedhack_max_warnings > -1)
	{
		void* pSender = __IDToCPlayer(_lastsenderid);
		bool immune = _CSecurity__checkAccess_Feature(security_ptr, pSender, "speedkick_immunity");
		if (!immune)
		{
			PlayerManager::Get()->AttackHackCheck(_lastsenderid);
		}
	}
	
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(_lastsenderid);
	if (pp)
	{
		if (!PluginManager::Get()->OnPlayerAttack(pp)) return false;
	}
	
	return o_ZN7CRunner10recdStrikeER10CBitStreamPS_(that, a, b);
}

extern "C" int _ZN7CRunner6DoTickEv(CRunner* that)
{
	return o_ZN7CRunner6DoTickEv(that);
}

void sServer_Command(const char* cmd)
{
	if (!console_ptr) return;
	std::string tempcmd = cmd;
	if (tempcmd.length()<3) return;
	if ((tempcmd[0]=='/') || (tempcmd[0]=='\\'))
		tempcmd = tempcmd.substr(1,tempcmd.length()-1);
	
	WideString wcmd = tempcmd.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sServer_AddBot(unsigned int team, unsigned int cls, const char* name)
{
	std::stringstream oss;
	oss << "addBotX(" << team << ", " << cls << ", `" << name << "`);";
	sServer_Script(oss.str().c_str());
}

void sServer_AddBlob(const char* blobtype, const char* filepath, float x , float y, unsigned int team)
{
	std::stringstream oss;
	oss << "addBlob(`" << blobtype << "`, `" << filepath << "`, " << x << ", " << y << ", " << team << ");";
	sServer_Script(oss.str().c_str());
}

void sMap_NextMap()
{
	sServer_Command("nextmap");
}

void  sServer_RestartMatch()
{
	sServer_Command("restartmap");
}

float _getdistance(float x1, float y1, float x2, float y2)
{
	float a = abs(y2-y1); a*=a;
	float b = abs(x2-x1); b*=b;
	return sqrt(a+b);
}

extern "C" void _ZN7CRunner5BuildE5Vec2fh(CRunner *that, struct Vec2f pos, unsigned char block)
{
	float rangebuild = _getdistance(pos.x,pos.y,sPlayer_GetPosX(__CRunnerToCPlayer(that)),sPlayer_GetPosY(__CRunnerToCPlayer(that)));
	if (rangebuild > 50) return;
	unsigned int playerID = __CRunnerToID(that);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (pp)
	{
		if (!PluginManager::Get()->OnPlayerBuild(pp, pos.x, pos.y, block)) return;
	}
	o_CRunnerBuild(that, pos, block); 
}

// ----------------
// FOR ONMAPCHANGE
extern "C" void* _ZN4CMap7LoadMapEPKcb(void* that, char* mapname)
{
	if (!mapptr) mapptr = that;
	
	PluginManager::Get()->OnMapChange(mapname);
	
	return o_ZN4CMap7LoadMapEPKcb(that,mapname);
}

DWORD sPlayer_GetID(void* CPlayer)
{
	return __CPlayerToID(CPlayer);
}

DWORD sPlayer_GetSeclev(void* CPlayer)
{
	if (CPlayer)
	{
		int tSeclev = _CSecurity__getPlayerSeclev(security_ptr,CPlayer);
		return *(unsigned int*)(tSeclev + 128);
	}
	else
		return 255;
}

bool sPlayer_IsBot(void* CPlayer)
{
	return CPlayer ? *(bool *)((unsigned int)CPlayer + 293) : false;
}

unsigned char sPlayer_GetTeam(void* CPlayer)
{
	return CPlayer? *(unsigned char *)((unsigned int)CPlayer + 280) : 0;
}

void sPlayer_Kill(void* CPlayer)
{
	if (!CPlayer) return;
	CRunner* temp = __CPlayerToCRunner(CPlayer);
	if (!net_ptr) return;
	if (temp) _CRunner__Kill(temp);
	_CNet__server_SendGameResources(net_ptr,__CPlayerToENetPeer(CPlayer));
}

float sPlayer_GetPosX(void* CPlayer)
{
	if (!CPlayer) return 0.f;
	CRunner* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? pBody->pos.x : 0.f;
}

float sPlayer_GetPosY(void* CPlayer)
{
	if (!CPlayer) return 0.f;
	CRunner* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? pBody->pos.y : 0.f;
}

char sPlayer_GetClass(void* CPlayer)
{
	if (!CPlayer) return 0.f;
	CRunner* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? pBody->tool : 0.f;
}

char* sPlayer_GetName(void* CPlayer) // username
{
	if (!CPlayer) return NULL;
	return (char*)(*(unsigned int*)((unsigned int)CPlayer + 156));
}

char* sPlayer_GetClantag(void* CPlayer) // clantag
{
	if (!CPlayer) return NULL;
	return (char*)(*(unsigned int*)((unsigned int)CPlayer + 200));
}

char* sPlayer_GetCharName(void* CPlayer) // clantag + username
{
	if (!CPlayer) return NULL;
	return (char*)(*(unsigned int*)((unsigned int)CPlayer + 244));
}

//String

void sPlayer_SetName(void* CPlayer,const char* newname)
{
	if (!CPlayer) return;
	
	String* nc = (String*)((DWORD)CPlayer+200);
	*nc = " ";
	
	String* nn = (String*)((DWORD)CPlayer+156);
	*nn = newname;
	
	String* ncn = (String*)((DWORD)CPlayer+244);
	*ncn = newname;
	
	//String* on = (String*)((DWORD)CPlayer+350);
	//*on = newname;
	
	//char* cn = *(char**)((DWORD)CPlayer+244);
	//if (cn)
	//	delete [] cn;
	//char* nn = new char[strlen(newname)];
	//strcpy(nn,newname);
	
	//String nn = newname;
	//o_CPlayerManager__MakeUniqueName((int)cpmgr_ptr,nn,(int)CPlayer,strlen(newname));
	
	//*(char**)((unsigned int)CPlayer + 244) = nn;
	
	//String* curname = 
	//return (char*)(*(unsigned int*)((unsigned int)CPlayer + 156));
}

unsigned int sPlayer_GetNetworkID(void* CPlayer)
{
	if (!CPlayer) return 0;
	unsigned int temp = *(unsigned int*)((unsigned int)CPlayer + 124);
	return (temp) ? (*(unsigned short int*)(temp + 120)) : 0;
}

// host - is this 4 bytes ip?
unsigned int sPlayer_GetHost(void* CPlayer)
{
	if (!CPlayer) return 0;
	unsigned int temp = *(unsigned int*)((unsigned int)CPlayer + 124);
	return (temp) ? (*(unsigned int*)(temp + 24)) : 0;
}

char sIPresult[15];
char* sPlayer_GetIP(void* CPlayer)
{
	if (!CPlayer) return NULL;
	unsigned int temp = *(unsigned int*)((unsigned int)CPlayer + 124);
	if (!temp) return NULL;
	temp = *(unsigned int*)(temp + 24); // xxx.xxx.xxx.xxx
	sprintf(sIPresult,"%i.%i.%i.%i",(unsigned char)(temp),*(unsigned char*)(&temp+1),*(unsigned char*)(&temp+2),*(unsigned char*)(&temp+3));
	return sIPresult;
}

// constructor of CSecurity singleton
extern "C" void* _ZN9CSecurityC1Ev(void* that)
{
	void* result = o_ZN9CSecurityC1Ev(that);
	security_ptr = that;
	return result;
}

// constructor of CNet singleton
extern "C" void* _ZN4CNetC1Ev(void* that)
{
	void* result = o_ZN4CNetC1Ev(that);
	net_ptr = that;
	return result;
}

// constructor of CScript singleton
extern "C" void* _ZN7CScriptC1Ev(void* that)
{
	void* result = o_ZN7CScriptC1Ev(that);
	script_ptr = that;
	return result;
}

// constructor of IC_Console singleton
extern "C" void* _ZN10IC_ConsoleC2Ev(void* that)
{
	void* result = o_ZN10IC_ConsoleC2Ev(that);
	console_ptr = that;
	PluginManager::Get()->SetConsolePointer(console_ptr);
	return result;
}

extern "C" int _ZN4CNet20ReadPacketInSnapshotEbP10CStatePumpR10CBitStream(void* CNet, bool wut, void* CStatePump, void* CBitStream)
{
	_lastsenderid = __CPlayerToID(__CStatePumpToCPlayer(CStatePump));
	return o_ZN4CNet20ReadPacketInSnapshotEbP10CStatePumpR10CBitStream(CNet,wut,CStatePump,CBitStream);
}

extern "C" int _ZN4CMap11recdMapTileER10CBitStream(void* CMap, void* CBitStream)
{
	void* pSender = __IDToCPlayer(_lastsenderid);
	
	bool allowed = _CSecurity__checkAccess_Feature(security_ptr,pSender, "editor");
	
	if (!allowed)
	{
		std::stringstream oss;
		oss << "Using editor hack (player " << sPlayer_GetName(pSender) << ")";
		sConsole_Print(oss.str().c_str());
		sPlayer_Ban(pSender, -1);
		return 0;
	}
	
	std::vector<unsigned char>* buffer = (std::vector<unsigned char>*)(CBitStream);
	if (buffer)
	{
		DWORD bsize = buffer->size();
		if (bsize >= 34)
		{
			std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(_lastsenderid);
			if (pp)
			{
				unsigned int xy = ((int)(buffer->at(29)) << 24) | ((int)(buffer->at(30)) << 16) | ((int)(buffer->at(31)) << 8) | (int)(buffer->at(32));
				unsigned int x = xy % sMap_GetWidth();
				unsigned int y = xy / sMap_GetWidth();
				unsigned char block = (unsigned char)(buffer->at(33));
				if (!PluginManager::Get()->OnMapReceiveTile(pp, x, y, block)) return 0;
			}
		}
	}
	
	return o_ZN4CMap11recdMapTileER10CBitStream(CMap,CBitStream);
}

// ---------------
// now methods


void sMap_SaveMap(const char* mapname)
{
	if (!console_ptr) return;
	std::string tempc = "savemap ";
	tempc+=mapname;
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sMap_ChangeMap(const char* mapname)
{
	if (!console_ptr) return;
	std::string tempc = "loadmap ";
	tempc+=mapname;
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sMap_ChangeMapPNG(const char* mapname)
{
	if (!console_ptr) return;
	std::string tempc = "loadbitmap ";
	tempc+=mapname;
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

unsigned int sMap_GetWidth()
{
	return mapptr ? *(unsigned int*)((DWORD)mapptr+120) : 0;
}

unsigned int sMap_GetHeight()
{
	return mapptr ? *(unsigned int*)((DWORD)mapptr+116) : 0;
}

void sPlayer_Kick(void* CPlayer)
{
	if (!console_ptr) return;
	std::string tempc = "kickid ";
	tempc+=std::to_string(__CPlayerToID(CPlayer));
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sPlayer_Freeze(void* CPlayer)
{
	if (!console_ptr) return;
	std::string tempc = "freezeid ";
	tempc+=std::to_string(__CPlayerToID(CPlayer));
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sPlayer_Unfreeze(void* CPlayer)
{
	if (!console_ptr) return;
	std::string tempc = "unfreezeid ";
	tempc+=std::to_string(__CPlayerToID(CPlayer));
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sPlayer_Mute(void* CPlayer, int MINUTES)
{
	if (!console_ptr) return;
	std::string tempc = "muteid ";
	tempc+=std::to_string(__CPlayerToID(CPlayer));
	tempc+=" ";
	tempc+=std::to_string(MINUTES);
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sPlayer_Unmute(void* CPlayer)
{
	if (!console_ptr) return;
	std::string tempc = "unmuteid ";
	tempc+=std::to_string(__CPlayerToID(CPlayer));
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sServer_Msg(const char* msg)
{
	if (!console_ptr) return;
	std::string tempc = "msg ";
	tempc+=msg;
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

void sPlayer_Ban(void* CPlayer, int MINUTES)
{
	if (!console_ptr) return;
	std::string tempc = "banid ";
	tempc+=std::to_string(__CPlayerToID(CPlayer));
	tempc+=" ";
	tempc+=std::to_string(MINUTES);
	WideString wcmd = tempc.c_str();
	_IC_Console__externalCommandString(console_ptr,wcmd);
}

DWORD sMap_GetTile(float x, float y)
{
	return mapptr ? _CMap__getTile(mapptr,x,y) : 0;
}

void sMap_SetTile(float x, float y, byte b_type)
{
	if (mapptr)	_CMap__server_SetTile(mapptr,x,y,b_type);
}

extern "C" String _ZN6CActor7getNameEv(void *that)
{
	return o_CActorGetName(that);
}

extern "C" bool _ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc(void *that, CRunner* crunner, const char* cmd)
{
	unsigned int playerID = __CRunnerToID(crunner);
	
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (pp)
	{
		if (PluginManager::Get()->ExecuteRoomCommand(pp, cmd)) return false;
		if (cmd == "travel_right" || cmd == "travel_left")
		{
			pp->respawnFalsePositive = true;
		}
	}
	
	return o_ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc(that, crunner, cmd);
}

extern "C" void _ZN4CNet10RecdDeltasER10CBitStreamP10CStatePump(void *that, void* cbitstream, void* cstatepump)
{
	if (JuxtaConfig::Get()->speedhack_max_warnings > -1)
	{
		void* cplayer = __CStatePumpToCPlayer(cstatepump);
		bool immune = _CSecurity__checkAccess_Feature(security_ptr, cplayer, "speedkick_immunity");
		if (!immune)
		{
			unsigned int playerid = __CPlayerToID(cplayer);
			PlayerManager::Get()->SpeedHackCheck(playerid);
		}
		/*
		CRunner *crunner = __CPlayerToCRunner(cplayer);
		if (crunner)
		{
			PlayerManager::Get()->TeleportHackCheck(crunner, playerid);
		}
		*/
	}
	
	o_ZN4CNet10RecdDeltasER10CBitStreamP10CStatePump(that, cbitstream, cstatepump);
}

extern "C" void _ZN10CWorldTask5StartEv(void *that)
{
	PluginManager::Get()->OnServerReady();
	
	o_ZN10CWorldTask5StartEv(that);
}

int l_my_print(lua_State* L)
{
    int i;
    int nargs = lua_gettop(L);
	std::stringstream oss;
    for (i=1; i <= nargs; ++i) {
		oss << lua_tostring(L, i);
    }
	if (console_ptr)
	{
		_IC_Console__addx(console_ptr, oss.str().c_str());
	}
	else
	{
		std::cout << oss.str() << std::endl;
	}
    return 0;
}

void sConsole_Print(const char* str)
{
	if (!console_ptr) return;
	_IC_Console__addx(console_ptr, str);
}


static	int	socket_type (int sd) {
	int	stype	= 0;
	socklen_t	stlen   = sizeof(stype);
	int	result  = -1;
	if (getsockopt(sd, SOL_SOCKET, SO_TYPE, &stype, &stlen) == 0)
		result  = stype;
	return  result;
}
static	int	socket_family(__CONST_SOCKADDR_ARG sock) {
	struct	sockaddr*	s	= *(struct sockaddr**)&sock;
	return	s->sa_family;
}
int accept(int sd,  __SOCKADDR_ARG sock, socklen_t* lenp)
{
	fcntl(sd, F_SETFL, O_NONBLOCK); // set socket to non-blocking mode
	/*
	int	stype	= socket_type (sd);
	int	family	= socket_family ( *(__CONST_SOCKADDR_ARG*)(&sock));
	std::cout << "stype=" << stype << std::endl;
	std::cout << "family=" << family << std::endl;
	
	shutdown(sd, 2);
	//close(sd); //crash
	errno = ECONNABORTED;
	return -1;
	*/
	return o_accept(sd, sock, lenp);
}