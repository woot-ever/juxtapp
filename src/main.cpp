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

#include "kage/Vec2f.hpp"

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

const int CURRENT_VERSION = 5;

bool currdirinbase = false;

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
static bool (*o_ZN7CRunner9FireArrowE5Vec2fhh)(void*, float, float, unsigned char, unsigned char) = 0;
static int (*o_ZN4CNet20ReadPacketInSnapshotEbP10CStatePumpR10CBitStream)(void*, bool, void*, void*) = 0;
static int (*o_ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer)(void*, void*, void*) = 0;
static int (*o_ZN14CPlayerManager12RemovePlayerEP7CPlayer)(void*, void*) = 0;
static int (*o_ZN4CMap11recdMapTileER10CBitStreamP7CPlayer)(void*,void*,void*) = 0;
static void* (*o_ZN9CSecurityC1Ev)(void*) = 0;
static int (*o_ZN7CRunner6DoTickEv) (void*) = 0;
static void (*o_ZN14CPlayerManager6UpdateEv) (void*) = 0;
static void* (*o_ZN7CRunner5ThinkEv) (void*) = 0;
static void* (*o_ZN4CNetC1Ev)(void*) = 0;
static void* (*o_ZN7CScriptC1Ev)(void*) = 0;
static void* (*o_ZN4CNet15ServerSendToAllER10CBitStream) (void*,DWORD) = 0;
static void* (*o_ZN10IC_ConsoleC2Ev) (void*) = 0;
static int (*o_ZN14CPlayerManager14MakeUniqueName) (int,int,int,int,int) = 0;
static bool (*o_ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc) (void*, void*, const char*) = 0;
static void* (*o_ZN4CNet10RecdDeltasER10CBitStreamP10CStatePump) (void*, void*, void*) = 0;
static void* (*o_ZN10CWorldTask5StartEv) (void*) = 0;
static void* (*o_ZN6CRules5ThinkEv) (void*) = 0;
static void* (*o_ZN4CMap7LoadMapEPKcb) (void*, char*) = 0;
static void* (*o_ZN4CMap7InitMapEv) (void*) = 0;
static void* (*o_ZN4CNet23server_ProcessAPIPlayerEP9APIPlayerP13CSecurityData18APIRequestStatus_t) (void*, APIPlayer*, void*, int) = 0;
static void* (*o_ZN7CRunner9ThrowSackEiRhfi) (void*, int, unsigned char &, float, int) = 0;
static void* (*o_ZN10CWorldTask7DropEggEi5Vec2fii) (void*, int, Vec2f, int, int) = 0;
//static void* (*o_ZN14CPlayerManager8CastVoteEhtPKw) (void*, irr::u8, irr::u16, const wchar_t *) = 0;
static void* (*o_ZN4CEgg5MountEP6CActor) (void*, void*) = 0;
static void* (*o_ZN4CEgg7UnMountEP6CActor) (void*, void*) = 0;
static void* (*o_ZN7CRunner5MountEP6CActor) (void*, void*) = 0;
static void* (*o_ZN7CRunner7UnMountEP6CActor) (void*, void*) = 0;
static void* (*o_ZN4CMap12CollapseTileEi) (void*, int) = 0;
static void* (*o_ZN5CBlob4LoadEv) (void*) = 0;
static void* (*o_ZN5CBlobD0Ev) (void*) = 0;
static void* (*o_ZN5CBlobD1Ev) (void*) = 0;
static void* (*o_ZN5CBlobD2Ev) (void*) = 0;
static void* (*o_ZN4CEgg4LoadEv) (void*) = 0;
static void* (*o_ZN6CActor11CreateActorEPKcS1_iS1_) (const char*, const char*, int, const char*) = 0;
static void* (*o_ZN9CNetFiles8SendFileEPKchP9_ENetPeer) (void*, const char*, unsigned char, void*) = 0;
static void* (*o_ZN6CActor7DestroyEv) (void*) = 0;
static void* (*o_ZN6CActor4LoadEv) (void*) = 0;
static void* (*o_ZN7CPlayer10ChangeTeamEi) (void*, int) = 0;
static void* (*o_ZN7CRunner10SwitchToolEhb) (void*, unsigned char, bool) = 0;
static void* (*o_ZN6CActor7setTeamEt) (void*, unsigned short) = 0;
static void* (*o_ZN6CActor4KillEv) (void*) = 0;
static bool (*o_ZN7CRunner10recdStrikeER10CBitStreamPS_) (void*, void*&, void*) = 0;
static void (*o_ZN4CNet18server_SendRespawnEjP9_ENetPeer) (void*, unsigned int, void*) = 0;
static void (*o_ZN5CRoom9BuildRoomEhP7CRunner) (void*, unsigned char, void*) = 0;
static void (*o_ZN7CRunner11changeClassE5Vec2fi) (void*, Vec2f, int) = 0;
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
typedef int (*_CBlob__isFacingLeft_) (void* CBlob);
typedef int (*_CMap__SetTile_) (void* CMap, float x, float y, unsigned char type);
typedef int (*_CSecurity__checkAccess_Feature_) (void* CSecurity, void* CPlayer, std::string);
typedef int (*_CSecurity__getPlayerSeclev_) (void* CSecurity, void* CPlayer);
typedef int (*_CRunner__Kill_) (void* runner);
typedef int (*_CRunner__Gib_) (void* runner);
typedef int (*_CNet__server_SendRespawn_) (void* CNet, unsigned int sumtim, void* ENetPeer);
typedef int (*_CRunner__setPosition_) (void* runner, float x, float y);
typedef int (*_CNet__server_SendMsg_) (void* CNet, WideString wchar_string, void* ENetPeer, byte wut);
typedef int (*_CNet__server_SendSecurityCheck_) (void* CNet, void* ENetPeer);
typedef int (*_IC_Console__externalCommandString_) (void* ICConsole, WideString command); 
typedef int (*_IC_Console__addx_) (void* ICConsole, const char*); 

_CMap__getTile_                     _CMap__getTile                           = NULL;
_CMap__server_SetTile_              _CMap__server_SetTile                    = NULL;
_CMap__setWaterLevel_               _CMap__setWaterLevel                     = NULL;
_CBlob__isFacingLeft_               _CBlob__isFacingLeft                     = NULL;
_CMap__SetTile_                     _CMap__SetTile                           = NULL;
_CSecurity__checkAccess_Feature_    _CSecurity__checkAccess_Feature          = NULL;
_CSecurity__getPlayerSeclev_        _CSecurity__getPlayerSeclev              = NULL;
_CRunner__Kill_                     _CRunner__Kill                           = NULL;
_CRunner__Gib_                      _CRunner__Gib                            = NULL;
_CNet__server_SendRespawn_          _CNet__server_SendRespawn                = NULL;
_CRunner__setPosition_              _CRunner__setPosition                    = NULL;
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

void NopAddr( void *src, const int len )
{
    //byte *jmp = (byte*)malloc( len );
	//unsigned long mallocpage = (unsigned long)jmp & ~(sysconf(_SC_PAGESIZE)-1);
    //mprotect((void*)mallocpage, 5+len, PROT_READ|PROT_WRITE|PROT_EXEC);
	unsigned long page = (unsigned long)src & ~(sysconf(_SC_PAGESIZE)-1);
    mprotect((void*)page, len, PROT_READ|PROT_WRITE|PROT_EXEC);
	
	for (int i = 0; i < len; i++)
	{
		*(byte*)(((DWORD)src)+i) = 0x90;
	}
	
    //memcpy( jmp, src, len );
    //jmp += len;
//jmp[0] = 0x90;
	
   // *(DWORD*)( jmp + 1 ) = (DWORD)( (unsigned int)src + len - (unsigned int)jmp ) - 5;
	//unsigned char* p = (unsigned char*)src;
   // p[0] = 0xE9;
   // *(unsigned long*)(p+1) = (DWORD)( (unsigned int)dst - (unsigned int)src ) - 5;
   // return ( jmp - len );
}

void* __CPlayerToCRunner(void* rpointer);
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

#define mExists(m,a) ( m.find(a) != m.end() )

std::map <void*,byte> forcing_heads;

void sPlayer_ForceHead(void* CPlayer, byte head)
{
	if (!CPlayer) return;
	forcing_heads[CPlayer] = head;
	if (head==0xFF)
		forcing_heads.erase(CPlayer);
}

byte sPlayer_GetHead(void* CPlayer)
{
	if (!CPlayer) return 0;
	return *(byte*)((unsigned int)CPlayer + 283);
}

void sPlayer_SetSpecialColor(void* CPlayer, byte color)
{
	if (!CPlayer) return;
	*(byte*)((unsigned int)CPlayer + 362) = 0;
	*(byte*)((unsigned int)CPlayer + 363) = 0;
	
	if (color==0) // normal
		*(byte*)((unsigned int)CPlayer + 361) = 0;
	else if (color==1) // premium
		*(byte*)((unsigned int)CPlayer + 361) = 1;
	else if (color==2) // guard
		*(byte*)((unsigned int)CPlayer + 362) = 1;
	else if (color==3) // kag_staff
		*(byte*)((unsigned int)CPlayer + 363) = 1;
}

byte sPlayer_GetSpecialColor(void* CPlayer)
{
	if (!CPlayer) return 0;
	
	if (*(byte*)((unsigned int)CPlayer + 363))
		return 3;
	else if (*(byte*)((unsigned int)CPlayer + 362))
		return 2;
	else if (*(byte*)((unsigned int)CPlayer + 361))
		return 1;
	else
		return 0;
}

void sPlayer_SetSex(void* CPlayer, byte sex)
{
	if (!CPlayer) return;
	*(byte*)((unsigned int)CPlayer + 282) = sex;
}

byte sPlayer_GetSex(void* CPlayer)
{
	if (!CPlayer) return 0;
	return *(byte*)((unsigned int)CPlayer + 282);
}

WORD sPlayer_GetPing(void* CPlayer)
{
	if (!CPlayer) return 0;
	return *(WORD*)((unsigned int)CPlayer + 302);
}

int my_CPlayerManager__MakeUniqueName(int a1, String a2, int a3, int a4)
{

	int iid = __CPlayerToID((void*)a3);
	int result = 0;
	if (iid>0)
	{
		if (sPlayer_CheckFeature((void*)a3, "staff_color")) {
			*(byte*)((unsigned int)a3 + 363) = 1; // set staff flag to 1
		}
		if (sPlayer_CheckFeature((void*)a3, "guard_color")) {
			*(byte*)((unsigned int)a3 + 362) = 1; // set mod flag to 1
		}
		
		if mExists(forcing_heads,(void*)a3)
		{
			*(byte*)((unsigned int)a3 + 283) = forcing_heads[(void*)a3];
			if (forcing_heads[(void*)a3]<6)
			{
				if (forcing_heads[(void*)a3]==2)
					*(byte*)((unsigned int)a3 + 362) = 1;
				else
				{
					*(byte*)((unsigned int)a3 + 362) = 0;
					*(byte*)((unsigned int)a3 + 363) = 1;
				}
			}
		}
		
		std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(iid);
		if (pp)
		{
			if (!pp->playing)
			{
				pp->playing = true;
				PluginManager::Get()->OnPlayerJoin(pp);
			}
		}
	}
	return o_CPlayerManager__MakeUniqueName(a1,a2,a3,a4);
}

bool __lmb_(void* dat)
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

// ID, CPlayer
std::map <unsigned int, void*> __Players;

// -----------------------------
// standard conversion functions
unsigned int __CRunnerToID(void* rpointer)
{
	if (rpointer == 0) return 0;
	unsigned int PlayerPTR = *(unsigned int*)((unsigned int)rpointer+220);
	return PlayerPTR ? (*(unsigned short int*)(PlayerPTR+120)) : 0;
}

unsigned int __CPlayerToID(void* rpointer)
{
	return rpointer ? (*(unsigned short int*)((unsigned int)rpointer+120)) : 0;
}

unsigned int __CActorToID(void* rpointer)
{
	return rpointer ? (*(unsigned short int*)((unsigned int)rpointer+184)) : 0;
}

unsigned int __CBlobToID(void* rpointer)
{
	return rpointer ? (*(unsigned short int*)((unsigned int)rpointer+184)) : 0;
}

void* __CRunnerToCPlayer(void* rpointer)
{
	return (void*)(*(unsigned int*)((unsigned int)rpointer+220));
}

void* __IDToCPlayer(unsigned int rID)
{
	return (__Players.find(rID) == __Players.end()) ? NULL : __Players[rID];
}

void* __CPlayerToCRunner(void* rpointer)
{
	return (void*)(*(unsigned int*)((unsigned int)rpointer+304));
}

void* __IDToCRunner(unsigned int rID)
{
	void* rpointer = __IDToCPlayer(rID);
	return rpointer ? (void*)(*(unsigned int*)((unsigned int)rpointer+304)) : (void*)NULL;
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
	void* cplay = __CPlayerToCRunner(CPlayer);
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
int my_CRunner__Send_Delta(void* pRunner, void* b1, void* b2, void* b3)
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

typedef bool (*o_CRunner__getMovementSignificance_) (void*);
o_CRunner__getMovementSignificance_ o_CRunner__getMovementSignificance = NULL;

struct TP_rza
{
	float x;
	float y;
	float vx;
	float vy;
};

std::map<void*, TP_rza> TPs;

bool my_CRunner__getMovementSignificance(void* tBody)
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
	void* tBody = __CPlayerToCRunner(CPlayer);
	if (tBody)
	{
		TPs[tBody].x = x;
		TPs[tBody].y = y;
		TPs[tBody].vx = 0;
		TPs[tBody].vy = 0;
	}
}

void sPlayer_SetVelocity(void* CPlayer, float vx, float vy)
{
	void* tBody = __CPlayerToCRunner(CPlayer);
	if (tBody)
	{
		TPs[tBody].x = sPlayer_GetPosX(CPlayer);
		TPs[tBody].y = sPlayer_GetPosY(CPlayer);
		TPs[tBody].vx = vx;
		TPs[tBody].vy = vy;
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
	void* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte *)((DWORD)_r + 800) = amount;
}

void sPlayer_SetWood(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	void* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte *)((DWORD)_r + 801) = amount;
}

void sPlayer_SetGold(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	void* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte *)((DWORD)_r + 802) = amount;
}

void sPlayer_SetArrows(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	void* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(byte*)((DWORD)_r + 803) = amount;
}

byte sPlayer_GetStone(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 800) : 0;
}

float sPlayer_GetHealth(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(float*)((DWORD)_r + 196) : 0;
}

float sPlayer_GetDefaultHealth(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(float*)((DWORD)_r + 208) : 0;
}

void sPlayer_SetHealth(void* CPlayer, float health)
{
	if (!CPlayer) return;
	void* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(float *)((DWORD)_r + 196) = health;
}

void sPlayer_SetDefaultHealth(void* CPlayer, float health)
{
	if (!CPlayer) return;
	void* _r = __CPlayerToCRunner(CPlayer);
	if (!_r) return;
	*(float *)((DWORD)_r + 208) = health;
}

byte sPlayer_GetWood(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 801) : 0;
}

byte sPlayer_GetGold(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 802) : 0;
}

byte sPlayer_GetArrows(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 803) : 0;
}

byte sPlayer_GetBombs(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(byte*)((DWORD)_r + 804) : 0;
}

void sPlayer_SetBombs(void* CPlayer, byte amount)
{
	if (!CPlayer) return;
	void* _r = __CPlayerToCRunner(CPlayer);
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
	void* ret = o_CNetCreateServer(that);
	PluginManager::Get()->OnServerReady();
	return ret;
}

typedef int (*o_CBlob__onHit_) (void* dis, float x1, float y1, float x2, float y2, float sumtin, void* p2, int s2, int s3);
o_CBlob__onHit_ o_CBlob__onHit = NULL;

int my_CBlob__onHit(void* dis, float x1, float y1, float x2, float y2, float damage, void* who, int s2, int s3)
{
	/*
	std::cout << "x1 = "<< x1 << std::endl;
	std::cout << "y1 = "<< y1 << std::endl;
	std::cout << "x2 = "<< x2 << std::endl;
	std::cout << "y2 = "<< y2 << std::endl;
	std::cout << "damage = "<< damage << std::endl;
	std::cout << "who = "<< __CRunnerToID(who) << std::endl;
	std::cout << "s2 = "<< s2 << std::endl;
	std::cout << "s3 = "<< s3 << std::endl;
	*/
	
	//dis+48 = " 9x\bties/Rooms/Spawn_Room.cfg"
	//dis+80 = "Entities/Rooms/Spawn_Room.cfg"
	//std::cout << "victim pointer = " << dis << std::endl;
	unsigned int victimID = __CBlobToID(dis);
	//std::cout << "victimID = " << victimID << std::endl;
	std::shared_ptr<ProxyBlob> pbVictim = PlayerManager::Get()->GetBlobByID(victimID);
	std::shared_ptr<ProxyActor> paAttacker;
	if (pbVictim) {
		if (who) {
			paAttacker = std::make_shared<ProxyActor>(who);
		}
		damage = PluginManager::Get()->OnBlobHit(pbVictim, paAttacker, damage);
	}
	
	return o_CBlob__onHit(dis,x1,y1,x2,y2,damage,who,s2,s3);
}

typedef int (*o_CRunner__onHit_) (void* dis, float x1, float y1, float x2, float y2, float sumtin, void* p2, int s2, int s3);
o_CRunner__onHit_ o_CRunner__onHit = NULL;

int my_CRunner__onHit(void* dis, float x1, float y1, float x2, float y2, float damage, void* who, int s2, int s3)
{
	unsigned int victimID = __CRunnerToID(dis);
	std::shared_ptr<ProxyPlayer> pVictim = PlayerManager::Get()->GetPlayerByID(victimID);
	std::shared_ptr<ProxyActor> paAttacker;
	if (who) {
		paAttacker = std::make_shared<ProxyActor>(who);
	}
	damage = PluginManager::Get()->OnPlayerHit(pVictim, paAttacker, damage);
	return o_CRunner__onHit(dis,x1,y1,x2,y2,damage,who,s2,s3);
	
	/*
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
	*/
	
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

/*myfunc(int,CPlayerManager__CastVote, void* dis, irr::u8 a, irr::u16 b, const wchar_t * c)
{
	std::cout << "WOOT CAST VOTE" << std::endl;
	std::cout << "a = " << (int)a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	return o_CPlayerManager__CastVote(dis, a, b, c);
}*/

myfunc(int,CRunner__UpdateVisuals,void* tBody)
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
		void* sitter = (void*)(*(DWORD*)((DWORD)dis+240));
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

void sPlayer_SetScore(void* CPlayer, WORD score)
{
	if (!CPlayer) return;
	*(WORD*)((*(DWORD *)((DWORD)CPlayer + 128))) = score;
}

WORD sPlayer_GetScore(void* CPlayer)
{
	return CPlayer ? *(WORD*)((*(DWORD *)((DWORD)CPlayer + 128))) : 0;
}

myfunc(int,CRules__OnPlayerJoin,void* rulesptr, void* CPlayer)
{
	int a_t = *(byte*)((DWORD)CPlayer+292);
	int b_t = *(byte*)((DWORD)CPlayer+280);
	
	if ((a_t != 255) && (b_t != 255))
	{
		if (a_t != b_t)
		{
			unsigned int playerID = __CPlayerToID(CPlayer);
			std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
			if (pp)
			{
				PluginManager::Get()->OnPlayerChangeTeam(pp, b_t, a_t);
			}
		}
	}
	
	return o_CRules__OnPlayerJoin(rulesptr,CPlayer);
}

mirror(void*,CRunner__FireArrow, DWORD runnor, float x, float y, unsigned char angle, unsigned char power);

void sPlayer_ChangeTeam(void* CPlayer, DWORD team)
{
	if (!CPlayer) return;
	*(byte*)((DWORD)CPlayer+292) = *(byte*)((DWORD)CPlayer+280);
	*(byte*)((DWORD)CPlayer+280) = team;
	o_CRules__OnPlayerJoin(rules_ptr,CPlayer);
}

mirror(void*,CRunner__SwitchTool, DWORD runnor, unsigned char tool, bool updateClass);

mirror(byte,CBitStream__readuc, void* bstream);
void sPlayer_SetClass(void* CPlayer, byte _class)
{
	if (!CPlayer) return;
	DWORD runner = (DWORD)__CPlayerToCRunner(CPlayer);
	if (!runner) return;
	_CRunner__SwitchTool(runner, _class, true);
}

// ON PLAYER DIE
myfunc(int,CRules__OnPlayerDie,void* CRules,void* victim,void* killer,byte death) // death is type of death ;_;
{
	unsigned int victimID = __CPlayerToID(victim);
	std::shared_ptr<ProxyPlayer> pVictim = PlayerManager::Get()->GetPlayerByID(victimID);
	if (pVictim) {
		unsigned int killerID = __CPlayerToID(killer);
		std::shared_ptr<ProxyPlayer> pKiller = PlayerManager::Get()->GetPlayerByID(killerID);
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
			PluginManager::Get()->OnMatchStart();
		}
	}
	o_CRules__StartMatch(CRules);
}

void* nettask_ptr = NULL;

mirror(void,CNetworkTask__Stop,void* cnettask);

// ON MATCH END
myfunc(int,CRules__EndMatch,void* CRules)
{
	if ( !*(bool*)((DWORD)CRules + 432) )
	{
		if ( *(bool*)((DWORD)CRules + 464) )
		{
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
	
	server_ticks++;
	PluginManager::Get()->OnServerTick(server_ticks);
	
	return o_CRules__Think(CRules);
}

mirror(byte,CRules__unitsLeftForTeam,void* CRules,byte team);
//mirror(int,CPlayerManager__CastVote,void* CPlayerManager, irr::u8 a, irr::u16 b, const wchar_t * c);

DWORD sServer_GetUnits(byte team)
{
	if (!rules_ptr)
		return 0;
	return _CRules__unitsLeftForTeam(rules_ptr,team);
}

unsigned int GetKeyAddress(unsigned char key)
{
	unsigned int kaddr = 0;
	switch(key) {
		case 0: kaddr = 733; break; // up
		case 1: kaddr = 734; break; // down
		case 2: kaddr = 735; break; // left
		case 3: kaddr = 736; break; // right
		case 4: kaddr = 737; break; // action
		case 5: kaddr = 738; break; // action2
		case 6: kaddr = 739; break; // zoomin
		case 7: kaddr = 740; break; // zoomout
		case 8: kaddr = 741; break; // use
		case 9: kaddr = 742; break; // change
		case 10: kaddr = 743; break; // drop
		case 11: kaddr = 744; break; // taunts
		case 12: kaddr = 745; break; // bubbles
		case 13: kaddr = 746; break; // menu
		case 14: kaddr = 747; break; // party
	}
	return kaddr;
}

bool sPlayer_IsKeyDown(void* player, unsigned char key)
{
	unsigned int kaddr = GetKeyAddress(key);
	if (!kaddr) return false; // invalid key
	void* runner = __CPlayerToCRunner(player);
	if (!runner) return false; // no runners
	byte k = *(byte*)((DWORD)runner+kaddr);
	return k == 1;
}

bool sPlayer_IsCrouching(void* player)
{
	void* runner = __CPlayerToCRunner(player);
	if (!runner) return false;
	return *(byte*)((DWORD)runner+712) == 1;
}

bool sPlayer_IsJumping(void* player)
{
	void* runner = __CPlayerToCRunner(player);
	if (!runner) return false;
	int jc = *(int*)((DWORD)runner+688);
	return jc > 0;
}

bool sPlayer_IsShieldingUp(void* player)
{
	void* runner = __CPlayerToCRunner(player);
	if (!runner) return false;
	return *(byte*)((DWORD)runner+713) == 1;
}

bool sPlayer_IsShieldingDown(void* player)
{
	void* runner = __CPlayerToCRunner(player);
	if (!runner) return false;
	return *(byte*)((DWORD)runner+715) == 1;
}

bool sPlayer_IsShieldingSide(void* player)
{
	void* runner = __CPlayerToCRunner(player);
	if (!runner) return false;
	return *(byte*)((DWORD)runner+714) == 1;
}

bool sPlayer_IsFrozen(void* player)
{
	if (!player) return false;
	return *(bool*)((DWORD)player+508);
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

mirror(float,CMap__getDayTime,void* cmap);

float sMap_GetDayTime()
{
	return _CMap__getDayTime(mapptr);
}

mirror(void*,CMap__SetDayTime,void* cmap, float t);

void sMap_SetDayTime(float t)
{
	_CMap__SetDayTime(mapptr, t);
}

mirror(void*,CRunner__Mount,void* cplayer,void* cactor);

void sPlayer_Mount(void* cplayer, void* cactor)
{
	void* runner = __CPlayerToCRunner(cplayer);
	if (!runner) return;
	_CRunner__Mount(runner, cactor);
}

mirror(void*,CWorldTask__DropEgg,void* cworldtask, byte style, float x, float y, char idk, WORD amount);
mirror(void,CBlob__setPosition,void* cblob,float x, float y);

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
	//std::cout << "CActor__setTeam " << team << std::endl;
	return o_CActor__setTeam(CActor,team);
}

mirror(void,CNet__server_SendGameResources,void* cnet, void* enetpeer);

myfunc(int,CNetworkTask__Start,void* cnettask)
{
	nettask_ptr = cnettask;
	return o_CNetworkTask__Start(cnettask);
}

mirror(void, CBitStream__newCBitStream, void* CBitStream);
mirror(void, CBitStream__write_ushort, void* CBitStream, unsigned short Value);
mirror(void, CBitStream__writeuc, void* CBitStream, unsigned char Value);
mirror(void, CBitStream__delCBitStream, void* CBitStream);
mirror(void, CNet__ServerPumpOnceToAll, void* CNet, void* CBitStream, unsigned char packet_type);
mirror(void, CNet__client_recdProjectile, void* CNet, void* CBitSteam);

void sPlayer_ShootArrow(void* CPlayer, float x, float y, unsigned char angle, unsigned char power, bool RealDamage)
{
	DWORD netid = 0;
	if (CPlayer)
	{
		netid = sPlayer_GetNetworkID(CPlayer);
		if (netid==0) return;
	}
	else netid = 0;
	
	void* bitstream = malloc(0x20);
	_CBitStream__newCBitStream(bitstream);
	
	_CBitStream__write_ushort(bitstream, netid);
	_CBitStream__write_ushort(bitstream, (short)x);
	_CBitStream__write_ushort(bitstream, (short)y);
	
	_CBitStream__writeuc(bitstream, angle);
	_CBitStream__writeuc(bitstream, power);
	_CBitStream__writeuc(bitstream, 33);
	
	if (net_ptr) 
	{
		_CNet__ServerPumpOnceToAll(net_ptr, bitstream, 0x3D);
		if (RealDamage)
		{
			*(DWORD*)((DWORD)bitstream+0xC) = 0;
			_CNet__client_recdProjectile(net_ptr, bitstream);
		}
	}
	
	_CBitStream__delCBitStream(bitstream);
	free(bitstream);
	
}

void HookFunctions(void* handle)
{
	//detour(CActor__setTeam,_ZN6CActor7setTeamEt,6);
	detour(CPlayer__CallbackTeamPick,_ZN7CPlayer16CallbackTeamPickEv,5);
	detour(CRules__Think,_ZN6CRules5ThinkEv,5);
	detour(CRules__EndMatch,_ZN6CRules8EndMatchEv,6);
	detour(CRules__StartMatch,_ZN6CRules10StartMatchEv,6);
	detour(CRules__OnPlayerRespawn,_ZN6CRules15OnPlayerRespawnEP18CRespawnQueueActor,7);
	detour(CRules__OnPlayerDie,_ZN6CRules11OnPlayerDieEP7CPlayerS1_h,5);
	detour(CRunner__UpdateVisuals,_ZN7CRunner13UpdateVisualsEv,5);
	detour(CEgg__Send_Delta,_ZN4CEgg10Send_DeltaEP10CBitStreamS1_S1_,5);
	detour(CEgg__getMovementSignificance,_ZN4CEgg23getMovementSignificanceEv,6);
	detour(CEgg__setPosition,_ZN4CEgg11setPositionE5Vec2f,8);
	detour(CEgg__SendCatapult,_ZN4CEgg12SendCatapultE5Vec2fS0_hh,5);
	detour(CRunner__onHit,_ZN7CRunner5onHitE5Vec2fS0_fP6CActorii,5);
	detour(CBlob__onHit,_ZN5CBlob5onHitE5Vec2fS0_fP6CActorii,5);
	detour(CPlayer__Send_Delta,_ZN7CPlayer10Send_DeltaEP10CBitStreamS1_S1_,5);
	detour(CRunner__Send_Delta,_ZN7CRunner10Send_DeltaEP10CBitStreamS1_S1_,5);
	detour(CNetCreateServer,_ZN4CNet12CreateServerEv,5);
	detour(CPlayer__customHeadsCheck,_ZN7CPlayer16customHeadsCheckEv,6);
	detour(CPlayerManager__MakeUniqueName,_ZN14CPlayerManager14MakeUniqueNameERN3irr4core6stringIcNS1_12irrAllocatorIcEEEEP7CPlayerib,5);
	detour(CNetFiles__CNetFiles,_ZN9CNetFilesC1Ev,6);
	//detour(CNetFiles__SendFile,_ZN9CNetFiles8SendFileEPKchP9_ENetPeer,5);	
	detour(CRunner__getMovementSignificance,_ZN7CRunner23getMovementSignificanceEv,6);		
	detour(CNetworkTask__Start,_ZN12CNetworkTask5StartEv,5);
	//detour(CPlayerManager__CastVote,_ZN14CPlayerManager8CastVoteEhtPKw,5);
	detour(CRules__OnPlayerJoin,_ZN6CRules12OnPlayerJoinEP7CPlayer,5);
	
	hook(CNetworkTask__Stop,_ZN12CNetworkTask4StopEv);
	hook(CScript__RunString,_ZN7CScript9RunStringEN3irr4core6stringIwNS1_12irrAllocatorIwEEEE);
	hook(CWorldTask__DropEgg,_ZN10CWorldTask7DropEggEi5Vec2fii);
	hook(CSecurity__checkAccess_Command,_ZN9CSecurity19checkAccess_CommandEP7CPlayerSsb);
	hook(CRules__unitsLeftForTeam,_ZN6CRules16unitsLeftForTeamEh);
	//hook(CPlayerManager__CastVote,_ZN14CPlayerManager8CastVoteEhtPKw);
	hook(CMap__getDayTime,_ZN4CMap7getTimeEv);
	hook(CMap__SetDayTime,_ZN4CMap10SetDayTimeEf);
	hook(CRunner__Mount,_ZN7CRunner5MountEP6CActor);
	hook(CMap__getTile,_ZN4CMap7getTileE5Vec2f);
	hook(CMap__server_SetTile,_ZN4CMap14server_SetTileE5Vec2fh);
	hook(CMap__setWaterLevel,_ZN4CMap13setWaterLevelEi);
	hook(CBlob__isFacingLeft,_ZN5CBlob12isFacingLeftEv);
	hook(CMap__SetTile,_ZN4CMap7SetTileEiih);
	hook(CSecurity__checkAccess_Feature,_ZN9CSecurity19checkAccess_FeatureEP7CPlayerSs);
	hook(CSecurity__getPlayerSeclev,_ZN9CSecurity15getPlayerSeclevEP7CPlayer);
	hook(CRunner__Kill,_ZN7CRunner4KillEv);
	hook(CRunner__Gib,_ZN7CRunner3GibEv);
	hook(CNet__server_SendRespawn,_ZN4CNet18server_SendRespawnEjP9_ENetPeer);
	hook(CRunner__setPosition,_ZN7CRunner11setPositionE5Vec2f);
	hook(CNet__server_SendMsg,_ZN4CNet14server_SendMsgEN3irr4core6stringIwNS1_12irrAllocatorIwEEEEP9_ENetPeerh);
	hook(IC_Console__externalCommandString,_ZN10IC_Console21externalCommandStringEN3irr4core6stringIwNS1_12irrAllocatorIwEEEE);
	hook(IC_Console__addx,_ZN10IC_Console4addxEPKcz);
	hook(CNet__server_SendSecurityCheck,_ZN4CNet24server_SendSecurityCheckEP9_ENetPeer);
	hook(CNet__server_SendGameResources,_ZN4CNet24server_SendGameResourcesEP9_ENetPeer);
	hook(CRunner__SwitchTool,_ZN7CRunner10SwitchToolEhb);
	hook(CRunner__FireArrow,_ZN7CRunner9FireArrowE5Vec2fhh);
	hook(CBitStream__readuc,_ZN10CBitStream6readucEv);
	hook(CBlob__setPosition,_ZN5CBlob11setPositionE5Vec2f);
	
	// sendgameresources respawns player
	// sendrespawn only gives text on players screen without respawning at all

	o_ZN4CMap7LoadMapEPKcb = (void*(*)(void* that, char* mapname))o_dlsym(handle, "_ZN4CMap7LoadMapEPKcb");
	o_CRunnerBuild = (void*(*)(void *, Vec2f, unsigned char))o_dlsym(handle, "_ZN7CRunner5BuildE5Vec2fh");
	o_ZN7CRunner9FireArrowE5Vec2fhh = (bool(*)(void*, float, float, unsigned char, unsigned char))o_dlsym(handle, "_ZN7CRunner9FireArrowE5Vec2fhh");
	o_ZN4CNet20ReadPacketInSnapshotEbP10CStatePumpR10CBitStream = (int(*)(void*,bool,void*,void*))o_dlsym(handle, "_ZN4CNet20ReadPacketInSnapshotEbP10CStatePumpR10CBitStream");
	o_ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer = (int(*)(void*,void*,void*))o_dlsym(handle, "_ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer");
	o_ZN14CPlayerManager12RemovePlayerEP7CPlayer = (int(*)(void*,void*))o_dlsym(handle, "_ZN14CPlayerManager12RemovePlayerEP7CPlayer");
	o_ZN4CMap11recdMapTileER10CBitStreamP7CPlayer = (int(*)(void*, void*, void*))o_dlsym(handle, "_ZN4CMap11recdMapTileER10CBitStreamP7CPlayer");
	o_ZN9CSecurityC1Ev = (void*(*)(void*))o_dlsym(handle, "_ZN9CSecurityC1Ev");
	o_ZN7CRunner6DoTickEv = (int(*)(void*))o_dlsym(handle, "_ZN7CRunner6DoTickEv");
	o_ZN14CPlayerManager6UpdateEv = (void(*)(void*))o_dlsym(handle, "_ZN14CPlayerManager6UpdateEv");
	o_ZN7CRunner5ThinkEv = (void*(*)(void*))o_dlsym(handle, "_ZN7CRunner5ThinkEv");
	o_ZN4CNetC1Ev = (void*(*)(void*))o_dlsym(handle, "_ZN4CNetC1Ev");
	o_ZN7CScriptC1Ev = (void*(*)(void*))o_dlsym(handle, "_ZN7CScriptC1Ev");
	o_ZN4CNet15ServerSendToAllER10CBitStream = (void*(*)(void*,DWORD))o_dlsym(handle, "_ZN4CNet15ServerSendToAllER10CBitStream");
	o_ZN10IC_ConsoleC2Ev = (void*(*)(void*))o_dlsym(handle, "_ZN10IC_ConsoleC2Ev");
	o_ZN14CPlayerManager14MakeUniqueName = (int(*)(int,int,int,int,int))o_dlsym(handle, "_ZN14CPlayerManager14MakeUniqueNameERN3irr4core6stringIcNS1_12irrAllocatorIcEEEEP7CPlayerib");
	o_ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc = (bool(*)(void*, void*, const char*))o_dlsym(handle, "_ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc");
	o_ZN4CNet10RecdDeltasER10CBitStreamP10CStatePump = (void*(*)(void*, void*, void*))o_dlsym(handle, "_ZN4CNet10RecdDeltasER10CBitStreamP10CStatePump");
	o_ZN10CWorldTask5StartEv = (void*(*)(void*))o_dlsym(handle, "_ZN10CWorldTask5StartEv");
	o_ZN6CRules5ThinkEv = (void*(*)(void*))o_dlsym(handle, "_ZN6CRules5ThinkEv");
	o_ZN4CMap7InitMapEv = (void*(*)(void*))o_dlsym(handle, "_ZN4CMap7InitMapEv");
	o_ZN4CNet23server_ProcessAPIPlayerEP9APIPlayerP13CSecurityData18APIRequestStatus_t = (void*(*)(void*, APIPlayer*, void*, int))o_dlsym(handle, "_ZN4CNet23server_ProcessAPIPlayerEP9APIPlayerP13CSecurityData18APIRequestStatus_t");
	o_ZN7CRunner9ThrowSackEiRhfi = (void*(*)(void*, int, unsigned char &, float, int))o_dlsym(handle, "_ZN7CRunner9ThrowSackEiRhfi");
	o_ZN10CWorldTask7DropEggEi5Vec2fii = (void*(*)(void*, int, Vec2f, int, int))o_dlsym(handle, "_ZN10CWorldTask7DropEggEi5Vec2fii");
	o_ZN7CRunner10recdStrikeER10CBitStreamPS_ = (bool(*)(void*, void*&, void*))o_dlsym(handle, "_ZN7CRunner10recdStrikeER10CBitStreamPS_");
	o_ZN4CNet18server_SendRespawnEjP9_ENetPeer = (void(*)(void*, unsigned int, void*))o_dlsym(handle, "_ZN4CNet18server_SendRespawnEjP9_ENetPeer");
	o_ZN5CRoom9BuildRoomEhP7CRunner = (void(*)(void*, unsigned char, void*))o_dlsym(handle, "_ZN5CRoom9BuildRoomEhP7CRunner");
	o_ZN7CRunner11changeClassE5Vec2fi = (void(*)(void*, Vec2f, int))o_dlsym(handle, "_ZN7CRunner11changeClassE5Vec2fi");
	o_accept = (int(*)(int, struct sockaddr*, socklen_t*))o_dlsym(handle, "accept");
	//o_ZN14CPlayerManager8CastVoteEhtPKw = (void*(*)(void*, irr::u8, irr::u16, const wchar_t *))o_dlsym(handle, "_ZN14CPlayerManager8CastVoteEhtPKw");
	o_ZN4CEgg5MountEP6CActor = (void*(*)(void*, void*))o_dlsym(handle, "_ZN4CEgg5MountEP6CActor");
	o_ZN4CEgg7UnMountEP6CActor = (void*(*)(void*, void*))o_dlsym(handle, "_ZN4CEgg7UnMountEP6CActor");
	o_ZN7CRunner5MountEP6CActor = (void*(*)(void*, void*))o_dlsym(handle, "_ZN7CRunner5MountEP6CActor");
	o_ZN7CRunner7UnMountEP6CActor = (void*(*)(void*, void*))o_dlsym(handle, "_ZN7CRunner7UnMountEP6CActor");
	o_ZN4CMap12CollapseTileEi = (void*(*)(void*, int))o_dlsym(handle, "_ZN4CMap12CollapseTileEi");
	o_ZN5CBlob4LoadEv = (void*(*)(void*))o_dlsym(handle, "_ZN5CBlob4LoadEv");
	o_ZN5CBlobD0Ev = (void*(*)(void*))o_dlsym(handle, "_ZN5CBlobD0Ev");
	o_ZN5CBlobD1Ev = (void*(*)(void*))o_dlsym(handle, "_ZN5CBlobD1Ev");
	o_ZN5CBlobD2Ev = (void*(*)(void*))o_dlsym(handle, "_ZN5CBlobD2Ev");
	o_ZN4CEgg4LoadEv = (void*(*)(void*))o_dlsym(handle, "_ZN4CEgg4LoadEv");
	o_ZN6CActor11CreateActorEPKcS1_iS1_ = (void*(*)(const char*, const char*, int, const char*))o_dlsym(handle, "_ZN6CActor11CreateActorEPKcS1_iS1_");
	o_ZN9CNetFiles8SendFileEPKchP9_ENetPeer = (void*(*)(void*, const char*, unsigned char, void*))o_dlsym(handle, "_ZN9CNetFiles8SendFileEPKchP9_ENetPeer");
	o_ZN6CActor7DestroyEv = (void*(*)(void*))o_dlsym(handle, "_ZN6CActor7DestroyEv");
	o_ZN6CActor4KillEv = (void*(*)(void*))o_dlsym(handle, "_ZN6CActor4KillEv");
	o_ZN6CActor4LoadEv = (void*(*)(void*))o_dlsym(handle, "_ZN6CActor4LoadEv");
	o_ZN7CPlayer10ChangeTeamEi = (void*(*)(void*, int))o_dlsym(handle, "_ZN7CPlayer10ChangeTeamEi");
	o_ZN7CRunner10SwitchToolEhb = (void*(*)(void*, unsigned char, bool))o_dlsym(handle, "_ZN7CRunner10SwitchToolEhb");
	o_ZN6CActor7setTeamEt = (void*(*)(void*, unsigned short))o_dlsym(handle, "_ZN6CActor7setTeamEt");

	// Initialize plugin manager
	PluginManager::Get()->Init(CURRENT_VERSION);
}

extern "C" void *dlsym(void *handle, const char *name){
	if(!o_dlsym){
		find_dlsym();
	}
	if (strcmp(name, "GameDLLInit") == 0) {
		PluginManager::Get()->LoadConfig();
		HookFunctions(handle);
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
	//std::cout << "a="<<a<<" b="<<b.x<<":"<<b.y<<" c="<<c<<" d="<<d<<std::endl;
	o_ZN10CWorldTask7DropEggEi5Vec2fii(that, a, b, c, d);
}

extern "C" void _ZN7CRunner5MountEP6CActor(void* that, void* actor)
{
	//std::cout << "_ZN7CRunner5MountEP6CActor: " << actor << std::endl;
	
	if (actor)
	{
		bool ret = true;
		
		unsigned int blobID = __CBlobToID(actor);
		std::shared_ptr<ProxyBlob> pBlob = PlayerManager::Get()->GetBlobByID(blobID);
		unsigned int mounterID = __CRunnerToID(that);
		std::shared_ptr<ProxyPlayer> pMounter = PlayerManager::Get()->GetPlayerByID(mounterID);
		if (pBlob && pMounter) {
			ret = PluginManager::Get()->OnBlobMount(pBlob, pMounter);
			if (!ret) return;
		}
		
		wchar_t* wcInventoryName = (wchar_t*)(*(unsigned int*)((unsigned int)actor+432));
		char *inventoryname = new char[256];
		wcstombs(inventoryname, wcInventoryName, 256);
		if (strcmp(inventoryname, "Red Flag") == 0 || strcmp(inventoryname, "Blue Flag") == 0) {
			std::shared_ptr<ProxyPlayer> pMounter = PlayerManager::Get()->GetPlayerByID(mounterID);
			ret = PluginManager::Get()->OnFlagPick(pMounter, std::string(inventoryname).c_str());
		}
		delete[] inventoryname;
		if (!ret) return;
	}
	
	//std::wstring toast(L"Testing test");
	//const wchar_t* szToast = toast.c_str();
	//_CPlayerManager__CastVote(cpmgr_ptr, __CRunnerToID(that), __CRunnerToID(that), szToast);
	
	o_ZN7CRunner5MountEP6CActor(that, actor);
}

extern "C" void _ZN7CRunner7UnMountEP6CActor(void* that, void* actor)
{
	unsigned int blobID = __CBlobToID(actor);
	std::shared_ptr<ProxyBlob> pBlob = PlayerManager::Get()->GetBlobByID(blobID);
	unsigned int mounterID = __CRunnerToID(that);
	std::shared_ptr<ProxyPlayer> pMounter = PlayerManager::Get()->GetPlayerByID(mounterID);
	if (pBlob && pMounter) {
		bool ret = PluginManager::Get()->OnBlobUnMount(pBlob, pMounter);
		if (!ret) return;
	}
	o_ZN7CRunner7UnMountEP6CActor(that, actor);
}

extern "C" void _ZN4CMap12CollapseTileEi(void* that, int xy)
{
	unsigned int x = xy % sMap_GetWidth();
	unsigned int y = xy / sMap_GetWidth();
	unsigned char block = sMap_GetTile(x, y);
	if (!PluginManager::Get()->OnMapCollapseTile(x, y, block)) return;
	o_ZN4CMap12CollapseTileEi(that, xy);
}

extern "C" void _ZN5CBlobD0Ev(void* that)
{
	//std::cout << "_ZN5CBlobD0Ev " << that << std::endl;
	unsigned int actorID = __CActorToID(that);
	std::shared_ptr<ProxyBlob> pa = PlayerManager::Get()->GetBlobByID(actorID);
	pa->_exists = false;
	if (pa) PlayerManager::Get()->RemoveBlob(pa);
	o_ZN5CBlobD0Ev(that);
}

extern "C" void _ZN5CBlobD1Ev(void* that)
{
	//std::cout << "_ZN5CBlobD1Ev " << that << std::endl;
	unsigned int actorID = __CActorToID(that);
	std::shared_ptr<ProxyBlob> pa = PlayerManager::Get()->GetBlobByID(actorID);
	pa->_exists = false;
	if (pa) PlayerManager::Get()->RemoveBlob(pa);
	o_ZN5CBlobD1Ev(that);
}

extern "C" void _ZN5CBlobD2Ev(void* that)
{
	//std::cout << "_ZN5CBlobD2Ev " << that << std::endl;
	unsigned int actorID = __CActorToID(that);
	//std::cout << "actorID = " << actorID << std::endl;
	std::shared_ptr<ProxyBlob> pa = PlayerManager::Get()->GetBlobByID(actorID);
	pa->_exists = false;
	if (pa) PlayerManager::Get()->RemoveBlob(pa);
	o_ZN5CBlobD2Ev(that);
}

extern "C" void _ZN5CBlob4LoadEv(void* that)
{
	o_ZN5CBlob4LoadEv(that);
	
	auto pa = std::make_shared<ProxyBlob>(that);
	PlayerManager::Get()->AddBlob(pa);
	PluginManager::Get()->OnBlobInit(pa);
}

extern "C" void _ZN4CEgg4LoadEv(void* that)
{
	o_ZN4CEgg4LoadEv(that);
	
	auto pa = std::make_shared<ProxyEgg>(that);
	PlayerManager::Get()->AddEgg(pa);
	PluginManager::Get()->OnEggInit(pa);
}

extern "C" void* _ZN6CActor11CreateActorEPKcS1_iS1_(const char* a, const char* b, int c, const char* d)
{
	return o_ZN6CActor11CreateActorEPKcS1_iS1_(a, b, c, d);
}

extern "C" void* _ZN9CNetFiles8SendFileEPKchP9_ENetPeer(void* that, const char* a, unsigned char b, void* c)
{
	std::cout << "_ZN9CNetFiles8SendFileEPKchP9_ENetPeer " << that << std::endl;
	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << (int)b << std::endl;
	return o_ZN9CNetFiles8SendFileEPKchP9_ENetPeer(that, a, b, c);
}

extern "C" void _ZN6CActor7DestroyEv(void* that)
{
	unsigned int blobID = __CBlobToID(that);
	std::shared_ptr<ProxyBlob> pBlob = PlayerManager::Get()->GetBlobByID(blobID);
	if (pBlob) {
		PluginManager::Get()->OnBlobDie(pBlob);
	}
	/*std::cout << "_ZN6CActor7DestroyEv " << that << std::endl;
	unsigned int actorID = __CActorToID(that);
	std::shared_ptr<ProxyBlob> pa = PlayerManager::Get()->GetActorByID(actorID);
	if (pa) PlayerManager::Get()->RemoveActor(pa);*/
	o_ZN6CActor7DestroyEv(that);
}

extern "C" void _ZN6CActor4KillEv(void* that)
{
	/*unsigned int actorID = __CActorToID(that);
	std::shared_ptr<ProxyBlob> pa = PlayerManager::Get()->GetActorByID(actorID);
	if (pa) PluginManager::Get()->OnActorDie(pa);*/
	o_ZN6CActor4KillEv(that);
}

extern "C" void _ZN6CActor4LoadEv(void* that)
{
	//std::cout << "_ZN6CActor4LoadEv " << that << std::endl;
	o_ZN6CActor4LoadEv(that);
}

extern "C" void _ZN6CActor7setTeamEt(void* that, unsigned short team)
{
	//std::cout << "_ZN6CActor7setTeamEt " << team << std::endl;
	o_ZN6CActor7setTeamEt(that, team);
}

extern "C" void _ZN4CEgg5MountEP6CActor(void* that, void* actor)
{
	//std::cout << "_ZN4CEgg5MountEP6CActor = flag mounted by " << __CPlayerToID(actor) << std::endl;
	o_ZN4CEgg5MountEP6CActor(that, actor);
}

extern "C" void _ZN4CEgg7UnMountEP6CActor(void* that, void* actor)
{
	//std::cout << "_ZN4CEgg7UnMountEP6CActor = flag unmounted by " << __CPlayerToID(actor) << std::endl;
	o_ZN4CEgg7UnMountEP6CActor(that, actor);
}

/*
extern "C" void _ZN14CPlayerManager8CastVoteEhtPKw(void* that, irr::u8 a, irr::u16 b, const wchar_t * c)
{
	std::cout << "_ZN14CPlayerManager8CastVoteEhtPKw" << std::endl;
	std::cout << "a = " << (int)a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "c = " << c << std::endl;
	o_ZN14CPlayerManager8CastVoteEhtPKw(that, a, b, c);
}
*/

extern "C" void* _ZN7CRunner9ThrowSackEiRhfi(void *that, int matType, unsigned char &sack, float dropType, int amount)
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
		void* yo = o_ZN7CRunner9ThrowSackEiRhfi(that, matType, sack, dropType, ret);
		return yo;
	}
	return NULL;
	
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
	}*/
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// FOR EVENT: onplayerconnect
extern "C" int _ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer(void* pManager, void* ENetPeer, void* CPlayer)
{
	if (!cpmgr_ptr)
		cpmgr_ptr = pManager;
	int result = o_ZN14CPlayerManager9AddPlayerEP9_ENetPeerP7CPlayer(pManager,ENetPeer,CPlayer);
	
	unsigned int playerID = __CPlayerToID((void*)result);
	__Players[playerID] = (void*)result;
	
	auto pp = std::make_shared<ProxyPlayer>((void*)result, playerID);
	PlayerManager::Get()->AddPlayer(pp);
	PluginManager::Get()->OnPlayerInit(pp);
	PluginManager::Get()->OnPlayerConnect(pp);
	
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
// FOR EVENT: onplayertalk
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
				
				std::string _msg(_message);
				if (_msg.substr(0,1)=="/")
				{
					if (_msg.substr(0,7)=="/reload")
					{
						do_send = false;
						if (sPlayer_CheckFeature(_sender, "view_console"))
						{
							PluginManager::Get()->ReloadAll();
							sServer_MsgToPlayer(_sender,">> Plugins reloaded");
						}
						else
						{
							sServer_MsgToPlayer(_sender,">> You do not have access to that command!");
						}
					}
					else if (_msg.substr(0,6)=="/arrow")
					{
						std::cout << "BOOM!" << std::endl;
						DWORD runner = (DWORD)__CPlayerToCRunner(_sender);
						_CRunner__FireArrow(runner, sPlayer_GetPosX(_sender), sPlayer_GetPosY(_sender), 114, 33);
						std::cout << "BOOM DONE!" << std::endl;
					}
					else if (_msg.substr(0,8)=="/plugins")
					{
						do_send = false;
						if (sPlayer_CheckFeature(_sender, "view_console"))
						{
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
				}
				std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(__id);
				if (pp)
				{
					if (do_send)
					{
						// Check if there is a custom command set by a plugin
						if (PluginManager::Get()->ExecuteChatCommand(pp, _msg))
						{
							do_send = false; // Command exists, do not send chat message
						}
						else if (_msg.substr(0,1)=="/")
						{
							// No custom commands, but the message starts with "/", so do not send
							pp->SendMessage(">> Command not found");
							do_send = false;
						}
					}
					if (do_send)
					{
						// Check what OnPlayerTalk returns
						if (!PluginManager::Get()->OnPlayerTalk(pp, _message))
						{
							do_send = false; // Returned false, do not send chat message
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
	__Players.erase(playerID);
	
	return o_ZN14CPlayerManager12RemovePlayerEP7CPlayer(pManager,CPlayer);
}

extern "C" int _ZN7CRunner5ThinkEv(void* that)
{
	unsigned int playerID = __CRunnerToID(that);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (pp)
	{
		for (unsigned int i=0; i<10; i++) {
			pp->oldkeys[i] = pp->keys[i];
			pp->keys[i] = sPlayer_IsKeyDown(pp->cplayer, i);
		}
		
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

extern "C" void _ZN4CNet18server_SendRespawnEjP9_ENetPeer(void* that, unsigned int a, void* b)
{
	//std::cout << "_ZN4CNet18server_SendRespawnEjP9_ENetPeer" << std::endl;
	//a = 3000;
	//std::cout << "a = " << a << std::endl;
	return o_ZN4CNet18server_SendRespawnEjP9_ENetPeer(that, a, b);
}

extern "C" void _ZN5CRoom9BuildRoomEhP7CRunner(void* that, unsigned char a, void* b)
{
	unsigned int playerID = __CRunnerToID(b);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (!PluginManager::Get()->OnRoomBuild(a, pp)) return;
	return o_ZN5CRoom9BuildRoomEhP7CRunner(that, a, b);
}

extern "C" void _ZN7CRunner11changeClassE5Vec2fi(void* that, Vec2f a, int b)
{
	unsigned int playerID = __CRunnerToID(that);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (!PluginManager::Get()->OnPlayerChangeClass(pp, b)) return;
	return o_ZN7CRunner11changeClassE5Vec2fi(that, a, b);
}

extern "C" bool _ZN7CRunner10recdStrikeER10CBitStreamPS_(void *that, void*& a, void* b)
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

extern "C" int _ZN7CRunner6DoTickEv(void* that)
{
	return o_ZN7CRunner6DoTickEv(that);
}

extern "C" void _ZN14CPlayerManager6UpdateEv(void* that)
{
	return o_ZN14CPlayerManager6UpdateEv(that);
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

DWORD sServer_AddBlob(const char* blobtype, const char* filepath, float x , float y, unsigned int team)
{
	DWORD new_blob = (DWORD)o_ZN6CActor11CreateActorEPKcS1_iS1_(blobtype, filepath, -1, "");
	if ( !new_blob )
		return 0;
	_ZN5CBlob4LoadEv((void*)new_blob);
	_CBlob__setPosition((void*)new_blob,x,y);
	*(byte*)(new_blob+0xD4) = team;
	return new_blob;
}

DWORD sServer_SpawnEgg(byte type, float x, float y, WORD amount, WORD team)
{
	DWORD new_egg = (DWORD)_CWorldTask__DropEgg(NULL, type, x, y, team, amount);
	std::cout << "SpawnEgg " << new_egg << std::endl;
	if ( !new_egg )
		return 0;
	_ZN4CEgg4LoadEv((void*)new_egg);
	//_CBlob__setPosition((void*)new_egg,x,y);
	//*(byte*)(new_blob+0xD4) = team;
	return new_egg;
	//_CWorldTask__DropEgg(NULL,type,x,y,0,amount);
}

void sServer_SpawnBomb(float x, float y, float vx, float vy, WORD timer, WORD team)
{
	DWORD shit = (DWORD)_CWorldTask__DropEgg(NULL,8,x,y,team,timer);
	if (shit)
	{
		*(float*)(shit+0x218) = vx;
		*(float*)(shit+0x218+4) = vy;
	}
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

extern "C" void _ZN7CRunner5BuildE5Vec2fh(void *that, struct Vec2f pos, unsigned char block)
{
	//std::cout << that << std::endl;
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

extern "C" bool _ZN7CRunner9FireArrowE5Vec2fhh(void* that, float a1, float a2, unsigned char b, unsigned char c)
{
	unsigned int playerID = __CPlayerToID(that);
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (pp) {
		if (!PluginManager::Get()->OnPlayerShotArrow(pp, a1, a2, b, c)) return false;
	}
	return o_ZN7CRunner9FireArrowE5Vec2fhh(that, a1, a2, b, c);
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
	void* temp = __CPlayerToCRunner(CPlayer);
	if (!net_ptr) return;
	if (temp) {
		_CRunner__Kill(temp);
		_CNet__server_SendGameResources(net_ptr,__CPlayerToENetPeer(CPlayer));
	}
}

bool sPlayer_IsDead(void* CPlayer)
{
	if (!CPlayer) return true;
	void* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? true : false;
}

unsigned int sPlayer_GetIdleTime(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? *(unsigned int*)((unsigned int)pBody+532) : 0;
}

float sPlayer_GetPosX(void* CPlayer)
{
	if (!CPlayer) return 0.f;
	void* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? (*(Vec2f*)((unsigned int)pBody+620)).x : 0.f;
}

float sPlayer_GetPosY(void* CPlayer)
{
	if (!CPlayer) return 0.f;
	void* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? (*(Vec2f*)((unsigned int)pBody+620)).y : 0.f;
}

float sPlayer_GetVelX(void* CPlayer)
{
	if (!CPlayer) return 0.f;
	void* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? (*(Vec2f*)((unsigned int)pBody+644)).x : 0.f;
}

float sPlayer_GetVelY(void* CPlayer)
{
	if (!CPlayer) return 0.f;
	void* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? (*(Vec2f*)((unsigned int)pBody+644)).y : 0.f;
}

float sPlayer_GetMouseX(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(float*)((DWORD)_r + 696) : 0;
}

float sPlayer_GetMouseY(void* CPlayer)
{
	if (!CPlayer) return 0;
	void* _r = __CPlayerToCRunner(CPlayer);
	return (_r) ? *(float*)((DWORD)_r + 700) : 0;
}

char sPlayer_GetClass(void* CPlayer)
{
	if (!CPlayer) return 0.f;
	void* pBody = __CPlayerToCRunner(CPlayer);
	return pBody ? *(unsigned char*)((unsigned int)pBody+516) : 0.f;
}

void* sPlayer_GetRunner(void* CPlayer) // username
{
	if (!CPlayer) return NULL;
	return __CPlayerToCRunner(CPlayer);
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

void sPlayer_SetClantag(void* CPlayer, const char* newtag)
{
	if (!CPlayer) return;
	
	const char* name = (char*)(*(unsigned int*)((unsigned int)CPlayer + 156));
	const char* newCharName = std::string(std::string(newtag) + std::string(" ") + std::string(name)).c_str();
	
	String* nc = (String*)((DWORD)CPlayer+200);
	*nc = newtag;
	
	String* ncn = (String*)((DWORD)CPlayer+244);
	*ncn = newCharName;
	
	String* ocn = (String*)((DWORD)CPlayer+364);
	*ocn = newCharName;
}

void sPlayer_SetName(void* CPlayer,const char* newname)
{
	if (!CPlayer) return;
	
	//String* nc = (String*)((DWORD)CPlayer+200);
	//*nc = " ";
	
	String* nn = (String*)((DWORD)CPlayer+156);
	*nn = newname;
	
	String* ncn = (String*)((DWORD)CPlayer+244);
	const char* tag = (char*)(*(unsigned int*)((unsigned int)CPlayer + 200));
	*ncn = std::string(std::string(tag) + std::string(" ") + std::string(newname)).c_str();
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
	sprintf(sIPresult,"%d.%d.%d.%d",temp & 0xFF, (temp >> 8) & 0xFF, (temp >> 16) & 0xFF, (temp >> 24) & 0xFF);
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

extern "C" int _ZN4CMap11recdMapTileER10CBitStreamP7CPlayer(void* CMap, void* CBitStream, void* pSender)
{
	if (!pSender) return 0;
	bool allowed = _CSecurity__checkAccess_Feature(security_ptr,pSender, "editor");
	
	if (!allowed)
	{
		std::stringstream oss;
		oss << "Using editor hack (player " << sPlayer_GetName(pSender) << ")";
		sConsole_Print(oss.str().c_str());
		//sPlayer_Ban(pSender, -1);
		return 0;
	}
	
	std::vector<unsigned char>* buffer = (std::vector<unsigned char>*)(CBitStream);
	if (buffer)
	{
		DWORD bsize = buffer->size();
		if (bsize >= 34)
		{
			std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(__CPlayerToID(pSender));
			if (pp)
			{
				unsigned int xy = ((int)(buffer->at(29)) << 24) | ((int)(buffer->at(30)) << 16) | ((int)(buffer->at(31)) << 8) | (int)(buffer->at(32));
				unsigned int x = xy % sMap_GetWidth();
				unsigned int y = xy / sMap_GetWidth();
				unsigned char block = (unsigned char)(buffer->at(33));
				
				if (!PluginManager::Get()->OnMapReceiveTile(pp, x, y, block)) return 0;
				
				sMap_SetTile(x*8,y*8,block);
				
				
				// code deleting the packet from buffer
				
				DWORD v7 = *(DWORD*)((DWORD)CBitStream+0xC) + 32;
				*(DWORD*)((DWORD)CBitStream+0xC) = v7;
				
				if (v7 > (*(DWORD*)((DWORD)CBitStream+0x10)))
					*(DWORD*)((DWORD)CBitStream+0x10) += 32;
				
				byte shit = _CBitStream__readuc(CBitStream);
				
				// ------ end
				
				return 1;
			}
		}
	}
	
	return 1;
	//return o_ZN4CMap11recdMapTileER10CBitStreamP7CPlayer(CMap,CBitStream,pSender);
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

extern "C" bool _ZN5CRoom26hasEnoughResourcesFunctionEP7CRunnerPKc(void *that, void* crunner, const char* cmd)
{
	unsigned int playerID = __CRunnerToID(crunner);
	
	std::shared_ptr<ProxyPlayer> pp = PlayerManager::Get()->GetPlayerByID(playerID);
	if (pp)
	{
		if (PluginManager::Get()->ExecuteRoomCommand(pp, cmd)) return false;
		if (strcmp(cmd, "travel_right")==0 || strcmp(cmd, "travel_left")==0)
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
		void *crunner = __CPlayerToCRunner(cplayer);
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
	o_ZN10CWorldTask5StartEv(that);
}

extern "C" void _ZN7CRunner10SwitchToolEhb(void* that, unsigned char tool, bool updateClass)
{
	std::cout << "tool = " << (int)tool << std::endl;
	std::cout << "updateClass = " << updateClass << std::endl;
	o_ZN7CRunner10SwitchToolEhb(that, tool, updateClass);
}

extern "C" void _ZN7CRunner9HitEffectEf(void* that, float a)
{
	//std::cout << "_ZN7CRunner9HitEffectEf = " << that << " = " << a << std::endl;
	return;
}

/*
extern "C" int _ZN4CEgg5onHitE5Vec2fS0_fP6CActorii(void *that, Vec2f a, Vec2f b, float c, void* d, int e, int f)
{
	std::cout << "_ZN4CEgg5onHitE5Vec2fS0_fP6CActorii" << std::endl;
	std::cout << "a = " << a.x << ":" << a.y << std::endl;
	std::cout << "b = " << b.x << ":" << b.y << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "f = " << f << std::endl;
	return o_ZN4CEgg5onHitE5Vec2fS0_fP6CActorii(that, a, b, c, d, e, f);
}
*/

/*extern "C" int _ZN5CBlob5onHitE5Vec2fS0_fP6CActori(void *that, Vec2f a, Vec2f b, float c, void* d, int e, int f)
{
	std::cout << "_ZN5CBlob5onHitE5Vec2fS0_fP6CActori" << std::endl;
	std::cout << "a = " << a.x << ":" << a.y << std::endl;
	std::cout << "b = " << b.x << ":" << b.y << std::endl;
	std::cout << "c = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e = " << e << std::endl;
	std::cout << "f = " << f << std::endl;
	return o_ZN5CBlob5onHitE5Vec2fS0_fP6CActori(that, a, b, c, d, e, f);
}*/

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

static int socket_family(__CONST_SOCKADDR_ARG sock) {
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

bool sActor_IsFacingLeft(void* CActor)
{
	return _CBlob__isFacingLeft(CActor);
}

void sActor_Kill(void* CActor)
{
	if (!CActor) return;
	o_ZN6CActor4KillEv(CActor);
}

void sActor_SetPosition(void* CActor, float x, float y)
{
	if (!CActor) return;
	_CBlob__setPosition(CActor, x, y);
}