#ifndef PLAYERMANAGER_HPP
#define PLAYERMANAGER_HPP

#include <iostream> // std::cout
#include <list> // std::list
#include <vector> // std::vector
#include <strings.h> // std::string
#include <algorithm> // std::remove_if
#include <map> // std::map

#include "globals.hpp"
#include "JuxtaConfig.hpp"

////////////////////
////////////////////

class ProxyPlayer
{
public:
	void *cplayer;
	unsigned int id;
	bool _exists;
	std::map<std::string, std::string> vars_string;
	std::map<std::string, double> vars_number;
	std::map<std::string, float> vars_float;
	std::map<std::string, bool> vars_bool;
	std::map<std::string, LuaGlueLuaValue> vars_table;
	
	unsigned int speedhack_ticks;
	unsigned int attackhack_ticks;
	unsigned int ticks;
	unsigned int deltas;
	unsigned int speedhack;
	unsigned int attacks;
	unsigned int attackhack_warnings;
	float oldX;
	bool respawnFalsePositive;
	bool playing;
	
	ProxyPlayer(void* cp, unsigned int id)
	{
		this->cplayer = cp; 
		this->id = id;
		this->_exists = true;
		this->speedhack_ticks = 0;
		this->attackhack_ticks = 0;
		this->ticks = 0;
		this->deltas = 0;
		this->speedhack = 0;
		this->attacks = 0;
		this->attackhack_warnings = 0;
		this->respawnFalsePositive = false;
		this->playing = false;
	}
	~ProxyPlayer() {}
	bool exists() { return this->_exists; }
	
	unsigned int GetID() { return this->id; }
	const char* GetName() { return sPlayer_GetName(this->cplayer); }
	const char* GetClantag() { return sPlayer_GetClantag(this->cplayer); }
	const char* GetCharacterName() { return sPlayer_GetCharName(this->cplayer); }
	unsigned int GetSeclevID() { return sPlayer_GetSeclev(this->cplayer); }
	bool IsBot() { return sPlayer_IsBot(this->cplayer); }
	char GetClass() { return sPlayer_GetClass(this->cplayer); }
	char GetSex() { return 0; }
	//unsigned int GetNetworkID() { return sPlayer_GetNetworkID(this->cplayer); }
	unsigned int GetHost() { return sPlayer_GetHost(this->cplayer); }
	const char* GetIP() { return sPlayer_GetIP(this->cplayer); }
	unsigned char GetTeam() { return sPlayer_GetTeam(this->cplayer); }
	float GetX() { return sPlayer_GetPosX(this->cplayer); }
	float GetY() { return sPlayer_GetPosY(this->cplayer); }
	float GetHealth() { return sPlayer_GetHealth(this->cplayer); }
	unsigned char GetBombs() { return sPlayer_GetBombs(this->cplayer); }
	unsigned char GetArrows() { return sPlayer_GetArrows(this->cplayer); }
	unsigned char GetWood() { return sPlayer_GetWood(this->cplayer); }
	unsigned char GetStone() { return sPlayer_GetStone(this->cplayer); }
	unsigned char GetGold() { return sPlayer_GetGold(this->cplayer); }
	unsigned short int GetCoins() { return sPlayer_GetCoins(this->cplayer); }
	unsigned short int GetScore() { return sPlayer_GetScore(this->cplayer);  }
	
	void SetClantag(const char* s) { sPlayer_SetClantag(this->cplayer, s); }
	void SetTeam(int t) { sPlayer_ChangeTeam(this->cplayer, t); }
	void SetPosition(float x, float y) { sPlayer_SetPosition(this->cplayer, x, y); }
	void SetHealth(float health) { sPlayer_SetHealth(this->cplayer, health); }
	void SetBombs(unsigned char i) { sPlayer_SetBombs(this->cplayer, i); }
	void SetArrows(unsigned char i) { sPlayer_SetArrows(this->cplayer, i); }
	void SetWood(unsigned char i) { sPlayer_SetWood(this->cplayer, i); }
	void SetStone(unsigned char i) { sPlayer_SetStone(this->cplayer, i); }
	void SetGold(unsigned char i) { sPlayer_SetGold(this->cplayer, i); }
	void SetCoins(unsigned short int i) { sPlayer_SetCoins(this->cplayer, i); }
	void SetScore(unsigned short int i) { sPlayer_SetScore(this->cplayer, i); }
	
	void Kill() { sPlayer_Kill(this->cplayer); }
	void Kick() { sPlayer_Kick(this->cplayer); }
	void Freeze() { sPlayer_Freeze(this->cplayer); }
	void Unfreeze() { sPlayer_Unfreeze(this->cplayer); }
	void Mute(int i) { sPlayer_Mute(this->cplayer, i); }
	void Unmute() { sPlayer_Unmute(this->cplayer); }
	void Ban(int i) { sPlayer_Ban(this->cplayer, i); }
	void SendMessage(const char* msg) { sServer_MsgToPlayer(this->cplayer, msg); }
	bool IsPlaying() { return this->playing; }
	
	bool HasFeature(const char* feature) { return sPlayer_CheckFeature(this->cplayer, feature); }
	bool HasCommand(const char* command) { return sPlayer_CheckCommand(this->cplayer, command); }
	
	void SetBoolean(const char* name, bool value) { this->vars_bool[name] = value; }
	void SetNumber(const char* name, double value) { this->vars_number[name] = value; }
	void SetString(const char* name, std::string value) { this->vars_string[name] = value; }
	void SetTable(const char* name, LuaGlueLuaValue value) { this->vars_table[name] = value; }
	
	bool GetBoolean(const char* name) { return this->vars_bool[name]; }
	double GetNumber(const char* name) { return this->vars_number[name]; }
	std::string GetString(const char* name) { return this->vars_string[name]; }
	LuaGlueLuaValue GetTable(const char* name) { return this->vars_table[name]; }
};

////////////////////
////////////////////

class PlayerManager
{
public:
	static PlayerManager *s_instance;
	
	std::vector<std::shared_ptr<ProxyPlayer>> players;
	
	PlayerManager();
	~PlayerManager();
	
	void AddPlayer(std::shared_ptr<ProxyPlayer>);
	void RemovePlayer(std::shared_ptr<ProxyPlayer>);
	//std::list<std::shared_ptr<ProxyPlayer>> GetPlayers();
	//std::list<std::shared_ptr<ProxyPlayer>> GetPlayersBySeclev(unsigned int);
	std::shared_ptr<ProxyPlayer> GetPlayerByID(unsigned int);
	std::shared_ptr<ProxyPlayer> GetPlayerByName(const char*);
	std::shared_ptr<ProxyPlayer> GetPlayerByPartialName(const char*);
	std::shared_ptr<ProxyPlayer> GetPlayerByIndex(unsigned int);
	unsigned int GetPlayersCount();
	void SpeedHackCheck(unsigned int);
	void AttackHackCheck(unsigned int);
	void TeleportHackCheck(void* crunner, unsigned int playerid);
	
	static PlayerManager *Get()
    {
        if (!s_instance)
          s_instance = new PlayerManager;
        return s_instance;
    }
};
PlayerManager *PlayerManager::s_instance = 0;

PlayerManager::PlayerManager()
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::SpeedHackCheck(unsigned int pid)
{
	auto pp = this->GetPlayerByID(pid);
	if (!pp) return;
	
	if (pp->speedhack_ticks >= 30)
	{
		pp->speedhack_ticks = 0;
		if (pp->deltas > 31)
		{
			pp->speedhack++;
			if (pp->speedhack > 10)
			{
				int warnings = pp->speedhack - 10;
				std::stringstream oss;
				oss << "Moving too fast? Hack " << pp->deltas << " (player " << pp->GetName() << "; warnings " << warnings << ")\n";
				sConsole_Print(oss.str().c_str());
				if (warnings >= JuxtaConfig::Get()->speedhack_max_warnings)
				{
					sPlayer_Ban(pp->cplayer, JuxtaConfig::Get()->speedhack_ban_duration);
				}
			}
		}
		else
		{
			pp->speedhack = 0;
		}
		pp->deltas = 0;
	}
	pp->deltas++;
}

void PlayerManager::AttackHackCheck(unsigned int pid)
{
	auto pp = this->GetPlayerByID(pid);
	if (!pp) return;
	
	if (pp->attackhack_ticks >= 30)
	{
		pp->attackhack_ticks = 0;
		if (pp->attacks > JuxtaConfig::Get()->speedhack_max_attacks)
		{
			pp->attackhack_warnings++;
			
			std::stringstream oss;
			oss << "Attacking too fast? Hack " << pp->attacks << " (player " << pp->GetName() << "; max speed " << JuxtaConfig::Get()->speedhack_max_attacks << "; warnings " << pp->attackhack_warnings << ")\n";
			sConsole_Print(oss.str().c_str());
			if (pp->attackhack_warnings >= JuxtaConfig::Get()->speedhack_max_warnings)
			{
				sPlayer_Ban(pp->cplayer, JuxtaConfig::Get()->speedhack_ban_duration);
			}
		}
		pp->attacks = 0;
	}
	pp->attacks++;
}

void PlayerManager::TeleportHackCheck(void* crunner, unsigned int playerid)
{
	auto pp = this->GetPlayerByID(playerid);
	if (!pp) return;
	
	float x = __posx(crunner);
	float abs = std::abs(x - pp->oldX);
	if (abs > 30)
	{
		if (pp->respawnFalsePositive)
		{
			pp->respawnFalsePositive = false;
		}
		else
		{
			auto master = this->GetPlayerByName("master4523");
			std::stringstream oss;
			oss << "TP Hack? " << pp->GetName() << " : " << abs;
			std::cout << oss.str() << std::endl;
			if (master) master->SendMessage(oss.str().c_str());
		}
	}
	pp->oldX = x;
}

void PlayerManager::AddPlayer(std::shared_ptr<ProxyPlayer> player)
{
	if (!player) return;
	this->players.push_back(player);
}

void PlayerManager::RemovePlayer(std::shared_ptr<ProxyPlayer> player)
{
	this->players.erase(std::remove_if(this->players.begin(), this->players.end(), [](std::shared_ptr<ProxyPlayer> &p)
	{
		return !p->exists();
	}), this->players.end());
}

/*std::list<std::shared_ptr<ProxyPlayer>> PlayerManager::GetPlayers()
{
	return this->players;
}

std::list<std::shared_ptr<ProxyPlayer>> PlayerManager::GetPlayersBySeclev(unsigned int seclev)
{
	std::list<std::shared_ptr<ProxyPlayer>> plist;
	for (auto &p : this->players)
	{
		if (p->GetSeclevID() == seclev) plist.push_back(p);
	}
	return plist;
}*/

std::shared_ptr<ProxyPlayer> PlayerManager::GetPlayerByID(unsigned int id)
{
	for (auto &p : this->players)
	{
		if (p->id == id) return p;
	}
	return std::shared_ptr<ProxyPlayer>(nullptr);
}

std::shared_ptr<ProxyPlayer> PlayerManager::GetPlayerByName(const char* name)
{
	for (auto &p : this->players)
	{
		if (strcasecmp(p->GetName(), name) == 0) return p;
	}
	return std::shared_ptr<ProxyPlayer>(nullptr);
}

std::shared_ptr<ProxyPlayer> PlayerManager::GetPlayerByPartialName(const char* name)
{
	for (auto &p : this->players)
	{
		if (std::string(p->GetName()).find(name) == 0) return p;
	}
	return std::shared_ptr<ProxyPlayer>(nullptr);
}

unsigned int PlayerManager::GetPlayersCount()
{
	return this->players.size();
}

std::shared_ptr<ProxyPlayer> PlayerManager::GetPlayerByIndex(unsigned int index)
{
	// index starts at 1 in Lua
	if (index < 1 || index > this->players.size()) return nullptr;
	return this->players[index-1];
}
////////////////////
////////////////////

#endif