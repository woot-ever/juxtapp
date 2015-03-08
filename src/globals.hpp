#ifndef GLOBALS_HPP
#define GLOBALS_HPP

#include "lua/lua.hpp"
#include "lua/lauxlib.h"

#define DWORD unsigned int
#define byte unsigned char
#define WORD unsigned short int

// macros for main.cpp

#define __velx(a) (*(float*)(((unsigned int)a)+644))
#define __vely(a) (*(float*)(((unsigned int)a)+648))
#define __posx(a) (*(float*)(((unsigned int)a)+620))
#define __posy(a) (*(float*)(((unsigned int)a)+624))

#define myfunc(TYPE,NAME,PARAMS...) typedef TYPE (*o_ ## NAME ## _) (PARAMS); \
			o_ ## NAME ## _ o_ ## NAME = NULL; \
			TYPE my_##NAME (PARAMS)

#define detour(NAME,PROC,SIZE) o_ ## NAME = (o_ ## NAME ## _) DetourFunc((void*)o_dlsym(handle, #PROC),(void*)&my_ ## NAME , SIZE)

#define mirror(TYPE,NAME,PARAMS...) typedef TYPE (*_## NAME ##_) (PARAMS); \
			_## NAME ##_ _## NAME = NULL

#define hook(NAME,PROC) _ ## NAME = (_ ## NAME ## _)o_dlsym(handle, #PROC)

// --------------------------------------------------------
// functions for lua to call

extern void  sMap_ChangeMap      (const char* mapname);
extern void  sMap_ChangeMapPNG   (const char* mapname);
extern void  sMap_SaveMap        (const char* mapname);
extern void  sMap_NextMap        ();
extern DWORD sMap_GetTile        (float x, float y);
extern void  sMap_SetTile        (float x, float y, byte b_type);
extern DWORD sMap_GetWidth       ();
extern DWORD sMap_GetHeight      ();
extern float sMap_GetDayTime     ();
extern void  sMap_SetDayTime     (float t);

extern void  sServer_MsgToPlayer (void* CPlayer, const char* msg);
extern void  sServer_Msg         (const char* msg);
extern void  sServer_Command     (const char* cmd);
extern void  sServer_Script      (const char* script);
extern void  sServer_AddBot      (unsigned int team, unsigned int cls, const char* name);
extern void  sServer_AddBlob     (const char* blobtype, const char* filepath, float x , float y, unsigned int team);
extern void  sServer_RestartMatch();

extern DWORD sPlayer_GetID              (void* CPlayer);
extern DWORD sPlayer_GetSeclev          (void* CPlayer);
extern bool  sPlayer_IsBot              (void* CPlayer);
extern float sPlayer_GetPosX            (void* CPlayer);
extern float sPlayer_GetPosY            (void* CPlayer);
extern unsigned int sPlayer_GetIdleTime (void* CPlayer);
extern char  sPlayer_GetClass           (void* CPlayer);
extern void* sPlayer_GetRunner          (void* CPlayer);
extern char* sPlayer_GetName            (void* CPlayer); // username
extern char* sPlayer_GetClantag         (void* CPlayer); // clantag
extern char* sPlayer_GetCharName        (void* CPlayer); // clantag + username
extern DWORD sPlayer_GetNetworkID       (void* CPlayer);
extern DWORD sPlayer_GetHost            (void* CPlayer);
extern char* sPlayer_GetIP              (void* CPlayer);
extern byte  sPlayer_GetTeam            (void* CPlayer);
extern WORD  sPlayer_GetCoins           (void* CPlayer);
extern byte  sPlayer_GetStone           (void* CPlayer);
extern byte  sPlayer_GetWood            (void* CPlayer);
extern byte  sPlayer_GetGold            (void* CPlayer);
extern byte  sPlayer_GetArrows          (void* CPlayer);
extern byte  sPlayer_GetBombs           (void* CPlayer);
extern float sPlayer_GetHealth          (void* CPlayer);

// new!
extern void  sPlayer_ChangeTeam  (void* CPlayer, DWORD team);
extern void  sPlayer_SetScore    (void* CPlayer, WORD score);
extern WORD  sPlayer_GetScore    (void* CPlayer);
extern bool  sPlayer_CheckFeature(void* CPlayer, const char* feature);
extern bool  sPlayer_CheckCommand(void* CPlayer, const char* command);
extern bool  sPlayer_IsKeyDown   (void* CPlayer, unsigned char key);

extern void  sPlayer_ForceHead   (void* CPlayer, byte head);
extern byte  sPlayer_GetHead     (void* CPlayer);

extern void  sPlayer_SetSex      (void* CPlayer, byte sex);
extern byte  sPlayer_GetSex      (void* CPlayer);

extern void  sPlayer_SetSpecialColor (void* CPlayer, byte color);
extern byte  sPlayer_GetSpecialColor (void* CPlayer);

extern void  sPlayer_SetClass    (void* CPlayer, byte _class);

// new!
extern DWORD sServer_GetUnits    (byte team);
extern void  sServer_SpawnEgg    (byte type, float x, float y, WORD amount);

extern void  sPlayer_SetClantag  (void* CPlayer, const char* name);
extern void  sPlayer_SetPosition (void* CPlayer, float x, float y);
extern void  sPlayer_SetHealth   (void* CPlayer, float health);
extern void  sPlayer_SetCoins    (void* CPlayer, WORD coins);
extern void  sPlayer_SetTeam     (void* CPlayer, WORD team);
extern void  sPlayer_SetStone    (void* CPlayer, byte amount);
extern void  sPlayer_SetWood     (void* CPlayer, byte amount);
extern void  sPlayer_SetGold     (void* CPlayer, byte amount);
extern void  sPlayer_SetArrows   (void* CPlayer, byte amount);
extern void  sPlayer_SetBombs    (void* CPlayer, byte amount);

extern void  sPlayer_Kill        (void* CPlayer);
extern void  sPlayer_Kick        (void* CPlayer);
extern void  sPlayer_Freeze      (void* CPlayer);
extern void  sPlayer_Unfreeze    (void* CPlayer);
extern void  sPlayer_Mute        (void* CPlayer, int i);
extern void  sPlayer_Unmute      (void* CPlayer);
extern void  sPlayer_Ban         (void* CPlayer, int MINUTES);
extern bool  sPlayer_IsDead      (void* CPlayer);

extern void  sConsole_Print      (const char* str);
// endf
// --------------------------------------------------------

extern int l_my_print(lua_State* L);

#endif