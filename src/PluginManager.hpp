#ifndef PLUGINMANAGER_HPP
#define PLUGINMANAGER_HPP

#include <iostream>
#include <vector> // for std::vector
#include <string>
#include <sstream>
#include <fstream>

#define LUAGLUE_TYPECHECK 1
#include "LuaGlue/LuaGlue.h"

//#include "TheHTTP.hpp"

#include "globals.hpp"
#include "JuxtaConfig.hpp"
#include "PlayerManager.hpp"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

////////////////////
////////////////////

class Blocks {};
class Teams {};

////////////////////
////////////////////

class Plugin;
class RoomCommand
{
public:
	std::string command;
	std::function<void(std::shared_ptr<ProxyPlayer>)> function;
	std::shared_ptr<Plugin> plugin;
};

////////////////////
////////////////////

class ChatCommand
{
public:
	std::string command;
	std::function<void(std::shared_ptr<ProxyPlayer>, std::string)> function;
	std::shared_ptr<Plugin> plugin;
};

////////////////////
////////////////////

class ProxyPlugin
{
public:
	static const char* GetName();
	static const char* GetPath();
};

////////////////////
////////////////////

class ProxyJuxta
{
public:
	static const int GetVersion();
};

////////////////////
////////////////////

class ProxyKAG
{
public:
	static std::vector<std::shared_ptr<ChatCommand>> chatCommands;
	static std::vector<std::shared_ptr<ChatCommand>> oldChatCommands;
	static std::vector<std::shared_ptr<RoomCommand>> roomCommands;
	static std::vector<std::shared_ptr<RoomCommand>> oldRoomCommands;
	
	static void CreateChatCommand(const char*, std::function<void(std::shared_ptr<ProxyPlayer>, std::string)>);
	static void CreateRoomCommand(const char*, std::function<void(std::shared_ptr<ProxyPlayer>)>);
	
	/*static std::list<std::shared_ptr<ProxyPlayer>> GetPlayers()
	{
		return PlayerManager::Get()->GetPlayers();
	}
	
	static std::list<std::shared_ptr<ProxyPlayer>> GetPlayersBySeclev(unsigned int seclev)
	{
		return PlayerManager::Get()->GetPlayersBySeclev(seclev);
	}*/
	
	static std::shared_ptr<ProxyPlayer> GetPlayerByID(unsigned int id)
	{
		return PlayerManager::Get()->GetPlayerByID(id);
	}
	
	static std::shared_ptr<ProxyPlayer> GetPlayerByName(const char* name)
	{
		return PlayerManager::Get()->GetPlayerByName(name);
	}
	
	static std::shared_ptr<ProxyPlayer> GetPlayerByPartialName(const char* name)
	{
		return PlayerManager::Get()->GetPlayerByPartialName(name);
	}
	
	static std::shared_ptr<ProxyPlayer> GetPlayerByIndex(unsigned int index)
	{
		return PlayerManager::Get()->GetPlayerByIndex(index);
	}
	
	static unsigned int GetPlayersCount()
	{
		return PlayerManager::Get()->GetPlayersCount();
	}
	
	static void SendRcon(const char* cmd)
	{
		if (cmd[0] == '/' || cmd[0] == '\\')
		{
			sServer_Command(cmd);
		}
		else
		{
			sServer_Script(cmd);
		}
	}
	
	static void NextMap()
	{
		sMap_NextMap();
	}
	
	static void RestartMap()
	{
		sServer_RestartMatch();
	}
	
	static void SaveMap(const char* map)
	{
		sMap_SaveMap(map);
	}
	
	static void ChangeMap(const char* mapname)
	{
		sMap_ChangeMap(mapname);
	}
	
	static void ChangeMapPNG(const char* mapname)
	{
		sMap_ChangeMapPNG(mapname);
	}
	
	static unsigned int GetTile(float x, float y)
	{
		return sMap_GetTile(x, y);
	}
	
	static unsigned int GetMapWidth()
	{
		return sMap_GetWidth();
	}
	
	static unsigned int GetMapHeight()
	{
		return sMap_GetHeight();
	}
	
	static void SetTile(float x, float y, char b_type)
	{
		sMap_SetTile(x, y, b_type);
	}
	
	static void TriggerAutoBalance()
	{
	
	}
	
	static unsigned int GetUnitsLeft(unsigned int team)
	{
		return sServer_GetUnits(team);
	}
	
	static bool IsWarmup()
	{
		
	}
	
	static void SpawnEgg(unsigned int type, float x, float y, unsigned short int amount)
	{
		sServer_SpawnEgg(type, x, y, amount);
	}
	
	static void SpawnBot(unsigned int team, unsigned int cls, const char* name)
	{
		sServer_AddBot(team, cls, name);
	}
	
	static void SpawnBlob(const char* blobtype, const char* filepath, float x , float y, unsigned int team)
	{
		sServer_AddBlob(blobtype, filepath, x, y, team);
	}
	
	static void SendMessage(const char* msg)
	{
		sServer_Msg(msg);
	}
	
	static unsigned int GetBuildVersion()
	{
		return 591;//TODO: return real version
	}
	
	static const char* GetVersion()
	{
		return "0.91A";//TODO: return real version
	}
	
	static void Break()
	{
		raise(SIGINT);
	}
};
std::vector<std::shared_ptr<ChatCommand>> ProxyKAG::chatCommands;
std::vector<std::shared_ptr<ChatCommand>> ProxyKAG::oldChatCommands;
std::vector<std::shared_ptr<RoomCommand>> ProxyKAG::roomCommands;
std::vector<std::shared_ptr<RoomCommand>> ProxyKAG::oldRoomCommands;

////////////////////
////////////////////

class Plugin
{
public:
	LuaGlue state;
	std::string name;
	std::string path;
	bool loaded;
	
	Plugin(std::string, std::string);
	~Plugin() {}
};

////////////////////
////////////////////

class PluginManager
{
public:
    static PluginManager *s_instance;
	void* console_ptr;
	int version;
	std::string workingDir;
	std::shared_ptr<Plugin> currentPlugin;
	
	std::vector<std::shared_ptr<Plugin>> plugins;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerTalk;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerDie;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerTick;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerHit;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerRespawn;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerBuild;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerDrop;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerChangeTeam;
	std::vector<std::shared_ptr<Plugin>> pluginsOnServerTick;
	std::vector<std::shared_ptr<Plugin>> pluginsOnTeamVictory;
	std::vector<std::shared_ptr<Plugin>> pluginsOnServerReady;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerConnect;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerJoin;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerLeave;
	std::vector<std::shared_ptr<Plugin>> pluginsOnPlayerAttack;
	std::vector<std::shared_ptr<Plugin>> pluginsOnMatchEnd;
	std::vector<std::shared_ptr<Plugin>> pluginsOnMatchStart;
	std::vector<std::shared_ptr<Plugin>> pluginsOnMapChange;
	std::vector<std::shared_ptr<Plugin>> pluginsOnMapReceiveTile;
	
	PluginManager();
	~PluginManager();
	void SetConsolePointer(void* ptr);
	void Init(const int v);
	void LoadConfig();
	void LoadAll();
	void UnloadAll();
	void ReloadAll();
	void LoadPlugin(std::string);
	void UnloadPlugin(std::string);
	bool ExecuteChatCommand(std::shared_ptr<ProxyPlayer>, std::string);
	bool ExecuteRoomCommand(std::shared_ptr<ProxyPlayer>, std::string);
	void Panic();
	
	void OnPlayerConnect(std::shared_ptr<ProxyPlayer>);
	void OnPlayerJoin(std::shared_ptr<ProxyPlayer>);
	void OnPlayerLeave(std::shared_ptr<ProxyPlayer>);
	bool OnPlayerTalk(std::shared_ptr<ProxyPlayer>, char*);
	bool OnPlayerAttack(std::shared_ptr<ProxyPlayer>);
	void OnPlayerTick(std::shared_ptr<ProxyPlayer>, unsigned int);
	void OnPlayerDie(std::shared_ptr<ProxyPlayer>, std::shared_ptr<ProxyPlayer>, unsigned char);
	float OnPlayerHit(std::shared_ptr<ProxyPlayer>, std::shared_ptr<ProxyPlayer>, float);
	void OnPlayerRespawn(std::shared_ptr<ProxyPlayer>, float, float);
	bool OnPlayerChangeTeam(std::shared_ptr<ProxyPlayer>, unsigned char);
	bool OnPlayerBuild(std::shared_ptr<ProxyPlayer>, float, float, unsigned char);
	int OnPlayerDrop(std::shared_ptr<ProxyPlayer>, int, int, float);
	void OnMapChange(char*);
	bool OnMapReceiveTile(std::shared_ptr<ProxyPlayer>, float, float, unsigned char);
	void OnMatchWarmup();
	void OnMatchStart();
	void OnMatchEnd();
	void OnTeamVictory(unsigned char);
	void OnServerTick(unsigned int);
	void OnServerStart();
	void OnServerReady();
	void OnPlayerInit(std::shared_ptr<ProxyPlayer>);
	
    static PluginManager *Get()
    {
        if (!s_instance)
          s_instance = new PluginManager;
        return s_instance;
    }
};
PluginManager *PluginManager::s_instance = 0;

PluginManager::PluginManager()
{
	this->version = 0;
	this->workingDir = "./";
}

PluginManager::~PluginManager()
{
}

void PluginManager::Init(const int v)
{
	this->version = v;
	this->LoadAll();
	
	this->workingDir = "../";
	
	// add global vars
	for (auto &plugin : this->plugins)
	{
		plugin->state.doString(std::string(std::string("_G[\"__dirname\"] = \"") + this->workingDir + plugin->path + std::string("\"")).c_str());
	}
}

void PluginManager::SetConsolePointer(void* ptr)
{
	this->console_ptr = ptr;
}

void PluginManager::LoadConfig()
{
	std::string path = std::string(this->workingDir) + std::string("juxtapp_config.cfg");
	std::ifstream infile(path);
	if (infile.good())
	{
		JuxtaConfig::Get()->Load(path.c_str());
		JuxtaConfig::Get()->update_onserverstart = JuxtaConfig::Get()->GetBoolean("update_onserverstart", JuxtaConfig::Get()->update_onserverstart);
		JuxtaConfig::Get()->update_onmatchend = JuxtaConfig::Get()->GetBoolean("update_onmatchend", JuxtaConfig::Get()->update_onmatchend);
		JuxtaConfig::Get()->speedhack_max_warnings = JuxtaConfig::Get()->GetNumber("speedhack_max_warnings", JuxtaConfig::Get()->speedhack_max_warnings);
		JuxtaConfig::Get()->speedhack_ban_duration = JuxtaConfig::Get()->GetNumber("speedhack_ban_duration", JuxtaConfig::Get()->speedhack_ban_duration);
		JuxtaConfig::Get()->speedhack_max_attacks = JuxtaConfig::Get()->GetNumber("speedhack_max_attacks", JuxtaConfig::Get()->speedhack_max_attacks);
		JuxtaConfig::Get()->enable_lua_sandbox = JuxtaConfig::Get()->GetBoolean("enable_lua_sandbox", JuxtaConfig::Get()->enable_lua_sandbox);
		infile.close();
	}
	else
	{
		infile.close();
		
		std::ofstream outfile;
		outfile.open(this->workingDir + "juxtapp_config.cfg");
		if (outfile.good())
		{
			outfile << "# Check for updates on server start. Set to false to disable it" << "\n";
			outfile << "update_onserverstart = true" << "\n\n";
			outfile << "# Automatically restarts the server on match end, when an update has been downloaded. Set to true to enable it" << "\n";
			outfile << "update_onmatchend = false" << "\n\n";
			outfile << "# Maximum amount of warnings when a player is speedhacking, set it to -1 to disable speedhack detection" << "\n";
			outfile << "speedhack_max_warnings = 5" << "\n\n";
			outfile << "# Duration of a speedhack ban in minutes, set it to -1 for a permanent ban" << "\n";
			outfile << "speedhack_ban_duration = 15" << "\n\n";
			outfile << "# Maximum amount of attacks per second" << "\n";
			outfile << "speedhack_max_attacks = 3" << "\n\n";
			outfile << "# Enable or disable Lua sandbox.\n# Disabling it allows the use of risky functions that could possibly execute malicious code on your machine.\n# Use with caution." << "\n";
			outfile << "enable_lua_sandbox = true" << "\n\n";
		}
		outfile.close();
	}
	infile.close();
}

void PluginManager::LoadAll()
{
	std::ifstream infile(this->workingDir + "plugins.cfg");
	if (infile.good())
	{
		std::string line;
		while (std::getline(infile, line))
		{
			if (line.length() == 0) continue;
			if (line[0] == '#') continue;
			this->LoadPlugin(line);
		}
	}
	infile.close();
	
	for (std::shared_ptr<Plugin> p : this->plugins)
	{
		if (!p->state.globalExists("OnInit")) continue;
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnInit");
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::UnloadAll()
{
	for (std::shared_ptr<Plugin> p : this->plugins)
	{
		if (!p->state.globalExists("OnUnload")) continue;
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnUnload");
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
	
	this->pluginsOnPlayerTalk.clear();
	this->pluginsOnPlayerAttack.clear();
	this->pluginsOnPlayerDie.clear();
	this->pluginsOnPlayerTick.clear();
	this->pluginsOnPlayerHit.clear();
	this->pluginsOnPlayerRespawn.clear();
	this->pluginsOnPlayerBuild.clear();
	this->pluginsOnPlayerDrop.clear();
	this->pluginsOnPlayerChangeTeam.clear();
	this->pluginsOnServerTick.clear();
	this->pluginsOnTeamVictory.clear();
	this->pluginsOnServerReady.clear();
	this->pluginsOnPlayerConnect.clear();
	this->pluginsOnPlayerJoin.clear();
	this->pluginsOnPlayerLeave.clear();
	this->pluginsOnMatchStart.clear();
	this->pluginsOnMatchEnd.clear();
	this->pluginsOnMapChange.clear();
	this->pluginsOnMapReceiveTile.clear();
	this->plugins.clear();
	
	// DIRTY HACK
	for (int i = ProxyKAG::chatCommands.size() - 1; i >= 0; i--)
	{
		ProxyKAG::oldChatCommands.emplace_back(std::move(ProxyKAG::chatCommands.back()));
		ProxyKAG::chatCommands.pop_back();
	}
	// DIRTY HACK
	for (int i = ProxyKAG::roomCommands.size() - 1; i >= 0; i--)
	{
		ProxyKAG::oldRoomCommands.emplace_back(std::move(ProxyKAG::roomCommands.back()));
		ProxyKAG::roomCommands.pop_back();
	}
}

void PluginManager::ReloadAll()
{
	this->LoadConfig();
	this->UnloadAll();
	this->LoadAll();
	
	PluginManager::OnServerReady();
	for (auto &p : PlayerManager::Get()->players)
	{
		PluginManager::OnPlayerInit(p);
	}
}

void PluginManager::UnloadPlugin(std::string name)
{
	/*for (auto &plugin : this->plugins)
	{
		if (plugin->name == name)
		{
			plugin->loaded = false; // flag as not loaded
		}
	}
	this->pluginsOnPlayerDie.erase(
		std::remove_if(
			this->pluginsOnPlayerDie.begin(),
			this->pluginsOnPlayerDie.end(),
			[](const std::shared_ptr<Plugin> &o) { return !o->loaded; }
		),
		this->pluginsOnPlayerDie.end()
	);*/
	/*this->pluginsOnPlayerTick.clear();
	this->pluginsOnPlayerHit.clear();
	this->pluginsOnPlayerRespawn.clear();
	this->pluginsOnPlayerBuild.clear();
	this->pluginsOnPlayerChangeTeam.clear();
	this->pluginsOnServerTick.clear();
	this->pluginsOnTeamVictory.clear();
	this->pluginsOnServerReady.clear();
	this->pluginsOnPlayerConnect.clear();
	this->pluginsOnPlayerJoin.clear();
	this->pluginsOnPlayerLeave.clear();
	this->pluginsOnMatchStart.clear();
	this->pluginsOnMatchEnd.clear();
	this->pluginsOnMapChange.clear();
	this->pluginsOnMapReceiveTile.clear();
	this->plugins.clear();*/
}

void PluginManager::LoadPlugin(std::string name)
{
	std::stringstream path;
	path << "Plugins/" << name;
	
	std::shared_ptr<Plugin> plugin = std::make_shared<Plugin>(name, path.str());
	std::stringstream oss;
	if (!plugin->loaded)
	{
		oss << "Could not load plugin " << name;
		//delete plugin;
	}
	else
	{
		oss << "Loaded plugin " << name;
		this->plugins.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerTalk")) this->pluginsOnPlayerTalk.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerAttack")) this->pluginsOnPlayerAttack.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerDie")) this->pluginsOnPlayerDie.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerTick")) this->pluginsOnPlayerTick.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerHit")) this->pluginsOnPlayerHit.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerRespawn")) this->pluginsOnPlayerRespawn.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerBuild")) this->pluginsOnPlayerBuild.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerDrop")) this->pluginsOnPlayerDrop.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerChangeTeam")) this->pluginsOnPlayerChangeTeam.push_back(plugin);
		if (plugin->state.globalExists("OnServerTick")) this->pluginsOnServerTick.push_back(plugin);
		if (plugin->state.globalExists("OnTeamVictory")) this->pluginsOnTeamVictory.push_back(plugin);
		if (plugin->state.globalExists("OnServerReady")) this->pluginsOnServerReady.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerConnect")) this->pluginsOnPlayerConnect.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerJoin")) this->pluginsOnPlayerJoin.push_back(plugin);
		if (plugin->state.globalExists("OnPlayerLeave")) this->pluginsOnPlayerLeave.push_back(plugin);
		if (plugin->state.globalExists("OnMatchStart")) this->pluginsOnMatchStart.push_back(plugin);
		if (plugin->state.globalExists("OnMatchEnd")) this->pluginsOnMatchEnd.push_back(plugin);
		if (plugin->state.globalExists("OnMapChange")) this->pluginsOnMapChange.push_back(plugin);
		if (plugin->state.globalExists("OnMapReceiveTile")) this->pluginsOnMapReceiveTile.push_back(plugin);
	}
	sConsole_Print(oss.str().c_str());
}

////////////

void PluginManager::OnServerReady()
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnServerReady)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnServerReady");
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnPlayerInit(std::shared_ptr<ProxyPlayer> player)
{
	for (std::shared_ptr<Plugin> p : this->plugins)
	{
		if (!p->state.globalExists("OnPlayerInit")) continue;
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnPlayerInit", player);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnPlayerConnect(std::shared_ptr<ProxyPlayer> player)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerConnect)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnPlayerConnect", player);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnPlayerJoin(std::shared_ptr<ProxyPlayer> player)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerJoin)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnPlayerJoin", player);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnPlayerLeave(std::shared_ptr<ProxyPlayer> player)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerLeave)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnPlayerLeave", player);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

bool PluginManager::OnPlayerAttack(std::shared_ptr<ProxyPlayer> player)
{
	int ret = 0;
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerAttack)
	{
		this->currentPlugin = p;
		ret = p->state.invokeFunction<int>("OnPlayerAttack", player);
		if (ret == 0)
		{
			return false;
		}
	}
	return true;
}

bool PluginManager::OnPlayerTalk(std::shared_ptr<ProxyPlayer> player, char* msg)
{
	int ret = 0;
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerTalk)
	{
		this->currentPlugin = p;
		ret = p->state.invokeFunction<int>("OnPlayerTalk", player, (const char*)msg);
		if (ret == 0)
		{
			return false;
		}
	}
	return true;
}

void PluginManager::OnPlayerDie(std::shared_ptr<ProxyPlayer> victim, std::shared_ptr<ProxyPlayer> killer, unsigned char reason)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerDie)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnPlayerDie", victim, killer, reason);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnPlayerTick(std::shared_ptr<ProxyPlayer> player, unsigned int ticks)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerTick)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnPlayerTick", player, ticks);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

float PluginManager::OnPlayerHit(std::shared_ptr<ProxyPlayer> victim, std::shared_ptr<ProxyPlayer> attacker, float damage)
{
	float damageReturnedByPlugins = -1;
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerHit)
	{
		this->currentPlugin = p;
		float tmpdmg = p->state.invokeFunction<float>("OnPlayerHit", victim, attacker, damage);
		if (tmpdmg == 0)
		{
			return 0;
		}
		else if (damageReturnedByPlugins == -1 || tmpdmg < damageReturnedByPlugins)
		{
			damageReturnedByPlugins = tmpdmg;
		}
	}
	float ret = damageReturnedByPlugins > -1 ? damageReturnedByPlugins : damage;
	return ret;
}

void PluginManager::OnPlayerRespawn(std::shared_ptr<ProxyPlayer> player, float x, float y)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerRespawn)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnPlayerRespawn", player, x, y);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

bool PluginManager::OnPlayerChangeTeam(std::shared_ptr<ProxyPlayer> player, unsigned char team)
{
	int ret = 0;
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerChangeTeam)
	{
		this->currentPlugin = p;
		ret = p->state.invokeFunction<int>("OnPlayerChangeTeam", player);
		if (ret == 0)
		{
			return false;
		}
	}
	return true;
}

bool PluginManager::OnPlayerBuild(std::shared_ptr<ProxyPlayer> player, float x, float y, unsigned char block)
{
	int ret = 0;
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerBuild)
	{
		this->currentPlugin = p;
		ret = p->state.invokeFunction<int>("OnPlayerBuild", player, x, y, block);
		if (ret == 0)
		{
			return false;
		}
	}
	return true;
}

int PluginManager::OnPlayerDrop(std::shared_ptr<ProxyPlayer> player, int amount, int matType, float dropType)
{
	int ret = amount;
	for (std::shared_ptr<Plugin> p : this->pluginsOnPlayerDrop)
	{
		this->currentPlugin = p;
		try {
			ret = p->state.invokeFunction<int>("OnPlayerDrop", player, amount, matType, dropType);
			if (ret <= 0) return ret;
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
	return ret;
}

void PluginManager::OnMapChange(char* mapname)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnMapChange)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnMapChange", (const char*)mapname);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

bool PluginManager::OnMapReceiveTile(std::shared_ptr<ProxyPlayer> player, float x, float y, unsigned char block)
{
	int ret = 0;
	for (std::shared_ptr<Plugin> p : this->pluginsOnMapReceiveTile)
	{
		this->currentPlugin = p;
		ret = p->state.invokeFunction<int>("OnMapReceiveTile", player, x, y, block);
		if (ret == 0)
		{
			return false;
		}
	}
	return true;
}

void PluginManager::OnMatchWarmup()
{
	for (std::shared_ptr<Plugin> p : this->plugins)
	{
		if (!p->state.globalExists("OnMatchWarmup")) continue;
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnMatchWarmup");
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnMatchStart()
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnMatchStart)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnMatchStart");
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnMatchEnd()
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnMatchEnd)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnMatchEnd");
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnTeamVictory(unsigned char team)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnTeamVictory)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnTeamVictory", team);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnServerTick(unsigned int ticks)
{
	for (std::shared_ptr<Plugin> p : this->pluginsOnServerTick)
	{
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnServerTick", ticks);
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

void PluginManager::OnServerStart()
{
	for (std::shared_ptr<Plugin> p : this->plugins)
	{
		if (!p->state.globalExists("OnServerStart")) continue;
		this->currentPlugin = p;
		try {
			p->state.invokeVoidFunction("OnServerStart");
		} catch (...) {
			PluginManager::Get()->Panic();
		}
	}
}

bool PluginManager::ExecuteChatCommand(std::shared_ptr<ProxyPlayer> player, std::string message)
{
	if (message.length() == 0) { return false; } // No message
	
	std::vector<std::string> vmsg = split(message, ' ');
	std::string command(vmsg[0]);
	bool commandExists = false;
	for (auto it = ProxyKAG::chatCommands.begin(); it != ProxyKAG::chatCommands.end(); ++it)
	{
		if ((*it)->command == command)
		{
			this->currentPlugin = (*it)->plugin;
			try {
				(*it)->function(player, message);
			} catch (...) {
				PluginManager::Get()->Panic();
			}
			commandExists = true;
		}
	}
	
	return commandExists;
}

bool PluginManager::ExecuteRoomCommand(std::shared_ptr<ProxyPlayer> player, std::string message)
{
	if (message.length() == 0) { return false; } // No message
	
	std::vector<std::string> vmsg = split(message, ' ');
	std::string command(vmsg[0]);
	bool commandExists = false;
	for (auto it = ProxyKAG::roomCommands.begin(); it != ProxyKAG::roomCommands.end(); ++it)
	{
		if ((*it)->command == command)
		{
			this->currentPlugin = (*it)->plugin;
			try {
				(*it)->function(player);
			} catch (...) {
				PluginManager::Get()->Panic();
			}
			commandExists = true;
		}
	}
	
	return commandExists;
}

void PluginManager::Panic()
{
	std::string err = std::string("[WARNING] The plugin \"") + this->currentPlugin->name + std::string("\" just had a Lua PANIC error, you better fix this!");
	sConsole_Print(err.c_str());
}

////////////////////
////////////////////

void ProxyKAG::CreateChatCommand(const char* cmd, std::function<void(std::shared_ptr<ProxyPlayer>, std::string)> f)
{
	auto chatcommand = std::make_shared<ChatCommand>();
	chatcommand->command = std::string(cmd);
	chatcommand->function = f;
	chatcommand->plugin = PluginManager::Get()->currentPlugin;
	chatCommands.push_back(chatcommand);
}

void ProxyKAG::CreateRoomCommand(const char* cmd, std::function<void(std::shared_ptr<ProxyPlayer>)> f)
{
	auto roomcommand = std::make_shared<RoomCommand>();
	roomcommand->command = std::string(cmd);
	roomcommand->function = f;
	roomcommand->plugin = PluginManager::Get()->currentPlugin;
	roomCommands.push_back(roomcommand);
}

////////////////////
////////////////////

const char* ProxyPlugin::GetName()
{
	return PluginManager::Get()->currentPlugin->name.c_str();
}

const char* ProxyPlugin::GetPath()
{
	return std::string(PluginManager::Get()->workingDir + PluginManager::Get()->currentPlugin->path + std::string("/")).c_str();
}

////////////////////
////////////////////

const int ProxyJuxta::GetVersion()
{
	return PluginManager::Get()->version;
}

////////////////////
////////////////////

Plugin::Plugin(std::string name, std::string path)
{
	this->name = name;
	this->path = path;
	
	this->state.Class<Blocks>("Blocks").
		constants({
			{"AIR", 0},
			{"BEDROCK", 106},
			{"DIRT", 16},
			{"DIRT_BACK", 32},
			{"GOLD_NUGGET", 80},
			{"ROCK", 96},
			{"THICK_ROCK", 208},
			{"TREE", 119},
			{"RUBBLE", 155},
			{"LADDER", 144},
			{"CASTLE_WALL", 48},
			{"CASTLE_BACK", 64},
			{"GOLD_BULLION", 160},
			{"BLUE_DOOR", 128},
			{"RED_DOOR", 130},
			{"BLUE_BRIDGE", 176},
			{"RED_BRIDGE", 178},
			{"SPIKES", 167},
			{"WORKSHOP", 146},
			{"WOODEN_WALL", 196},
			{"WOODEN_BACK", 205},
		})
	.end();
	
	this->state.Class<Teams>("Teams").
		constants({
			{"SPECTATOR", 200},
		})
	.end();
	
	this->state.Class<ProxyPlugin>("Plugin")
		.method("GetName", &ProxyPlugin::GetName)
		.method("GetPath", &ProxyPlugin::GetPath)
	.end();
	
	this->state.Class<ProxyJuxta>("Juxta")
		.method("GetVersion", &ProxyJuxta::GetVersion)
	.end();
	
	this->state.Class<ProxyPlayer>("Player")
		.method("GetID", &ProxyPlayer::GetID)
		.method("GetName", &ProxyPlayer::GetName)
		.method("GetClantag", &ProxyPlayer::GetClantag)
		.method("GetCharacterName", &ProxyPlayer::GetCharacterName)
		.method("GetName", &ProxyPlayer::GetName)
		.method("GetSeclevID", &ProxyPlayer::GetSeclevID)
		.method("IsBot", &ProxyPlayer::IsBot)
		.method("GetClass", &ProxyPlayer::GetClass)
		.method("GetSex", &ProxyPlayer::GetSex)
		//.method("GetNetworkID", &ProxyPlayer::GetNetworkID)
		.method("GetHost", &ProxyPlayer::GetHost)
		.method("GetIP", &ProxyPlayer::GetIP)
		.method("GetTeam", &ProxyPlayer::GetTeam)
		//.method("GetPosition", &ProxyPlayer::GetPosition)
		.method("GetX", &ProxyPlayer::GetX)
		.method("GetY", &ProxyPlayer::GetY)
		.method("GetHealth", &ProxyPlayer::GetHealth)
		.method("GetBombs", &ProxyPlayer::GetBombs)
		.method("GetArrows", &ProxyPlayer::GetArrows)
		.method("GetWood", &ProxyPlayer::GetWood)
		.method("GetStone", &ProxyPlayer::GetStone)
		.method("GetGold", &ProxyPlayer::GetGold)
		.method("GetCoins", &ProxyPlayer::GetCoins)
		.method("GetScore", &ProxyPlayer::GetScore)
		
		.method("SetPosition", &ProxyPlayer::SetPosition)
		.method("SetTeam", &ProxyPlayer::SetTeam)
		.method("SetHealth", &ProxyPlayer::SetHealth)
		.method("SetBombs", &ProxyPlayer::SetBombs)
		.method("SetArrows", &ProxyPlayer::SetArrows)
		.method("SetWood", &ProxyPlayer::SetWood)
		.method("SetStone", &ProxyPlayer::SetStone)
		.method("SetGold", &ProxyPlayer::SetGold)
		.method("SetCoins", &ProxyPlayer::SetCoins)
		.method("SetScore", &ProxyPlayer::SetScore)
		
		.method("Kill", &ProxyPlayer::Kill)
		.method("Kick", &ProxyPlayer::Kick)
		.method("Freeze", &ProxyPlayer::Freeze)
		.method("Unfreeze", &ProxyPlayer::Unfreeze)
		.method("Mute", &ProxyPlayer::Mute)
		.method("Unmute", &ProxyPlayer::Unmute)
		.method("Ban", &ProxyPlayer::Ban)
		.method("SendMessage", &ProxyPlayer::SendMessage)
		.method("IsPlaying", &ProxyPlayer::IsPlaying)
		
		.method("HasFeature", &ProxyPlayer::HasFeature)
		.method("HasCommand", &ProxyPlayer::HasCommand)
		
		.method("SetBoolean", &ProxyPlayer::SetBoolean)
		.method("SetNumber", &ProxyPlayer::SetNumber)
		.method("SetString", &ProxyPlayer::SetString)
		.method("SetTable", &ProxyPlayer::SetTable)
		
		.method("GetBoolean", &ProxyPlayer::GetBoolean)
		.method("GetNumber", &ProxyPlayer::GetNumber)
		.method("GetString", &ProxyPlayer::GetString)
		.method("GetTable", &ProxyPlayer::GetTable)
	.end();
	
	this->state.Class<ProxyKAG>("KAG")
		.method("ChangeMap", &ProxyKAG::ChangeMap)
		.method("ChangeMapPNG", &ProxyKAG::ChangeMapPNG)
		.method("GetTile", &ProxyKAG::GetTile)
		.method("GetMapWidth", &ProxyKAG::GetMapWidth)
		.method("GetMapHeight", &ProxyKAG::GetMapHeight)
		.method("SetTile", &ProxyKAG::SetTile)
		.method("CreateChatCommand", &ProxyKAG::CreateChatCommand)
		.method("CreateRoomCommand", &ProxyKAG::CreateRoomCommand)
		//.method("GetPlayers", &ProxyKAG::GetPlayers)
		//.method("GetPlayersBySeclev", &ProxyKAG::GetPlayersBySeclev)
		.method("GetPlayerByID", &ProxyKAG::GetPlayerByID)
		.method("GetPlayerByName", &ProxyKAG::GetPlayerByName)
		.method("GetPlayerByPartialName", &ProxyKAG::GetPlayerByPartialName)
		.method("GetPlayerByIndex", &ProxyKAG::GetPlayerByIndex)
		.method("GetPlayersCount", &ProxyKAG::GetPlayersCount)
		.method("SendRcon", &ProxyKAG::SendRcon)
		.method("NextMap", &ProxyKAG::NextMap)
		.method("RestartMap", &ProxyKAG::RestartMap)
		.method("SaveMap", &ProxyKAG::SaveMap)
		.method("TriggerAutoBalance", &ProxyKAG::TriggerAutoBalance)
		.method("GetUnitsLeft", &ProxyKAG::GetUnitsLeft)
		.method("IsWarmup", &ProxyKAG::IsWarmup)
		.method("SpawnEgg", &ProxyKAG::SpawnEgg)
		.method("SpawnBot", &ProxyKAG::SpawnBot)
		.method("SpawnBlob", &ProxyKAG::SpawnBlob)
		.method("SendMessage", &ProxyKAG::SendMessage)
		.method("GetBuildVersion", &ProxyKAG::GetBuildVersion)
		.method("GetVersion", &ProxyKAG::GetVersion)
		.method("Break", &ProxyKAG::Break)
	.end();
	
	this->state.open().glue();
	
	std::string file = PluginManager::Get()->workingDir + path + std::string("/init.lua");
	
	// add global vars
	this->state.doString(std::string(std::string("_G[\"__dirname\"] = \"") + PluginManager::Get()->workingDir + path + std::string("\"")).c_str());
	
	// add current plugin path to package.path
	std::string pluginPackagePath = std::string("package.path = \";") + PluginManager::Get()->workingDir + path + std::string("/?.lua\" .. package.path");
	this->state.doString(pluginPackagePath.c_str());
	
	// add libs path
	std::string libsPackagePath = std::string("package.path = \";") + PluginManager::Get()->workingDir + std::string("Plugins/__libs/?.lua\" .. package.path");
	this->state.doString(libsPackagePath.c_str());
	
	// lua sandbox
	if (JuxtaConfig::Get()->enable_lua_sandbox)
	{
		this->state.doString(
			"debug.debug=nil\n"
			"debug.getfenv=getfenv\n"
			"debug.getregistry=nil\n"
			"dofile=nil\n"
			//"io={write=io.write}\n"
			"loadfile=nil\n"
			"os.execute=nil\n"
			"os.getenv=nil\n"
			"os.remove=nil\n"
			"os.rename=nil\n"
			"os.tmpname=nil\n"
			
			"do\n"
				"local basename = function(string_, suffix)\n"
					"string_ = string_ or ''\n"
					"local b = string.gsub (string_, '[^'.. \"/\" ..']*'.. \"/\" ..'', '')\n"
					"if suffix then\n"
						"b = string.gsub (b, suffix, '')\n"
					"end\n"
					"return b\n"
				"end\n"
				"local oldOpen = io.open\n"
				"io.open = function (filename, mode)\n"
					"filename = __dirname .. \"/\" .. basename(filename)\n"
					"if (filename == \"init.lua\") then\n"
						"return nil, \"access denied\"\n"
					"end\n"
					"return oldOpen(filename, mode)\n"
				"end\n"
			"end\n"
		);
	}
	
	this->loaded = this->state.doFile(file.c_str());
	
	if(!this->loaded)
	{
		printf("failed to dofile: %s\n", file.c_str());
		printf("err: %s\n", this->state.lastError().c_str());
	}
}

#endif