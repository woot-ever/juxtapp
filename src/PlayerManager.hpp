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

class ProxyPlayer;
class ProxyBlob;
class ProxyActor;
class PlayerManager;

////////////////////
////////////////////

class ProxyActor
{
public:
	void *cactor;
	
	ProxyActor(void* p)
	{
		this->cactor = p;
		//std::cout << "ProxyActor::ProxyActor, cactor pointer = " << this->cactor << std::endl;
	}
	~ProxyActor() {}
	
	unsigned short GetID();
	unsigned char GetType();
	std::shared_ptr<ProxyPlayer> GetPlayer();
};

class ProxyBlob
{
public:
	void *cactor;
	unsigned int id;
	bool _exists;
	
	ProxyBlob(void* p)
	{
		this->cactor = p;
		this->_exists = true;
		this->id = p ? (*(unsigned short int*)((unsigned int)p+184)) : 0;
		//std::cout << "ProxyBlob::ProxyBlob, cactor pointer = " << this->cactor << std::endl;
	}
	~ProxyBlob() {}
	bool exists() { return this->_exists; }
	
	std::string GetFactoryName();
	std::string GetConfigFileName();
	unsigned short GetID();
	unsigned char GetType();
	unsigned char GetTeam();
	float GetX();
	float GetY();
	float GetHealth();
	void SetHealth(float health);
	std::shared_ptr<ProxyPlayer> GetPlayer();
	bool IsFacingLeft();
	void Kill();
};

//class ProxyPlayer : public ProxyBlob
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
	
	bool keys[15];
	bool oldkeys[15];
	
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
	
	//ProxyPlayer(void* p, unsigned int id) : ProxyBlob(p)
	ProxyPlayer(void* p, unsigned int id)
	{
		this->cplayer = p; 
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
	
	std::shared_ptr<ProxyBlob> GetBlob() {
		void* pRunner = sPlayer_GetRunner(this->cplayer);
		std::shared_ptr<ProxyBlob> blob;
		if (pRunner) blob = std::make_shared<ProxyBlob>((void*)pRunner);
		return blob;
	}
	unsigned int GetID() { return this->id; }
	const char* GetName() { return sPlayer_GetName(this->cplayer); }
	const char* GetClantag() { return sPlayer_GetClantag(this->cplayer); }
	const char* GetCharacterName() { return sPlayer_GetCharName(this->cplayer); }
	unsigned int GetSeclevID() { return sPlayer_GetSeclev(this->cplayer); }
	bool IsBot() { return sPlayer_IsBot(this->cplayer); }
	char GetClass() { return sPlayer_GetClass(this->cplayer); }
	
	//unsigned int GetNetworkID() { return sPlayer_GetNetworkID(this->cplayer); }
	unsigned int GetHost() { return sPlayer_GetHost(this->cplayer); }
	const char* GetIP() { return sPlayer_GetIP(this->cplayer); }
	unsigned char GetTeam() { return sPlayer_GetTeam(this->cplayer); }
	float GetX() { return sPlayer_GetPosX(this->cplayer); }
	float GetY() { return sPlayer_GetPosY(this->cplayer); }
	float GetVelX() { return sPlayer_GetVelX(this->cplayer); }
	float GetVelY() { return sPlayer_GetVelY(this->cplayer); }
	float GetMouseX() { return sPlayer_GetMouseX(this->cplayer); }
	float GetMouseY() { return sPlayer_GetMouseY(this->cplayer); }
	unsigned int GetIdleTime() { return sPlayer_GetIdleTime(this->cplayer); }
	float GetHealth() { return sPlayer_GetHealth(this->cplayer); }
	float GetDefaultHealth() { return sPlayer_GetDefaultHealth(this->cplayer); }
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
	void SetVelocity(float vx, float vy) { sPlayer_SetVelocity(this->cplayer, vx, vy); }
	void SetHealth(float health) { sPlayer_SetHealth(this->cplayer, health); }
	void SetDefaultHealth(float health) { sPlayer_SetDefaultHealth(this->cplayer, health); }
	void SetBombs(unsigned char i) { sPlayer_SetBombs(this->cplayer, i); }
	void SetArrows(unsigned char i) { sPlayer_SetArrows(this->cplayer, i); }
	void SetWood(unsigned char i) { sPlayer_SetWood(this->cplayer, i); }
	void SetStone(unsigned char i) { sPlayer_SetStone(this->cplayer, i); }
	void SetGold(unsigned char i) { sPlayer_SetGold(this->cplayer, i); }
	void SetCoins(unsigned short int i) { sPlayer_SetCoins(this->cplayer, i); }
	void SetScore(unsigned short int i) { sPlayer_SetScore(this->cplayer, i); }
	
	void ChangeTeam(unsigned char team) { sPlayer_ChangeTeam(this->cplayer, team); }
	void SetClass(unsigned char tool) { sPlayer_SetClass(this->cplayer, tool); }
	unsigned char GetSex() { return sPlayer_GetSex(this->cplayer); }
	void SetSex(unsigned char sex) { sPlayer_SetSex(this->cplayer, sex); }
	unsigned char GetSpecialColor() { return sPlayer_GetSpecialColor(this->cplayer); }
	void SetSpecialColor(unsigned char color) { sPlayer_SetSpecialColor(this->cplayer, color); }
	unsigned char GetHead() { return sPlayer_GetHead(this->cplayer); }
	void SetHead(unsigned char head) { sPlayer_ForceHead(this->cplayer, head); }
	
	void Kill() { sPlayer_Kill(this->cplayer); }
	void Kick() { sPlayer_Kick(this->cplayer); }
	void Freeze() { sPlayer_Freeze(this->cplayer); }
	void Unfreeze() { sPlayer_Unfreeze(this->cplayer); }
	void Mute(int i) { sPlayer_Mute(this->cplayer, i); }
	void Unmute() { sPlayer_Unmute(this->cplayer); }
	void Ban(int i) { sPlayer_Ban(this->cplayer, i); }
	void SendMessage(const char* msg) { sServer_MsgToPlayer(this->cplayer, msg); }
	bool IsPlaying() { return this->playing; }
	bool IsDead() { return sPlayer_IsDead(this->cplayer); }
	bool IsCrouching() { return sPlayer_IsCrouching(this->cplayer); }
	bool IsJumping() { return sPlayer_IsJumping(this->cplayer); }
	bool IsShielding() { return sPlayer_IsShieldingUp(this->cplayer) || sPlayer_IsShieldingSide(this->cplayer) || sPlayer_IsShieldingDown(this->cplayer); }
	bool IsShieldingUp() { return sPlayer_IsShieldingUp(this->cplayer); }
	bool IsShieldingDown() { return sPlayer_IsShieldingDown(this->cplayer); }
	bool IsShieldingSide() { return sPlayer_IsShieldingSide(this->cplayer); }
	
	bool HasFeature(const char* feature) { return sPlayer_CheckFeature(this->cplayer, feature); }
	bool HasCommand(const char* command) { return sPlayer_CheckCommand(this->cplayer, command); }
	
	void SetBoolean(const char* name, bool value) { this->vars_bool[name] = value; }
	void SetNumber(const char* name, double value) { this->vars_number[name] = value; }
	void SetString(const char* name, std::string value) { this->vars_string[name] = value; }
	void SetTable(const char* name, LuaGlueLuaValue value) { this->vars_table[name] = value; }
	
	bool GetBoolean(const char* name) { auto search = this->vars_bool.find(name); return search != vars_bool.end() ? search->second : false; }
	double GetNumber(const char* name) { auto search = this->vars_number.find(name); return search != vars_number.end() ? search->second : 0; }
	std::string GetString(const char* name) { auto search = this->vars_string.find(name); return search != vars_string.end() ? search->second : ""; }
	LuaGlueLuaValue GetTable(const char* name) { auto search = this->vars_table.find(name); return search != vars_table.end() ? search->second : NULL; }
	
	bool IsKeyDown(unsigned char k) { return sPlayer_IsKeyDown(this->cplayer, k); }
	bool WasKeyPressed(unsigned char k) { return this->keys[k] && !this->oldkeys[k]; }
	bool WasKeyReleased(unsigned char k) { return this->oldkeys[k] && !this->keys[k]; }
	void ShootArrow(float x, float y, unsigned char angle, unsigned char power, bool fake) { sPlayer_ShootArrow(this->cplayer, x, y, angle, power, fake); }
	
	void MountPlayer(std::shared_ptr<ProxyPlayer> p) {
		//TODO: use __CPlayerToCRunner instead
		void* runner = (void*)(*(unsigned int*)((unsigned int)p->cplayer+304));
		if (runner) sPlayer_Mount(this->cplayer, runner);
	}
	void MountBlob(std::shared_ptr<ProxyBlob> b) { sPlayer_Mount(this->cplayer, b->cactor); }
	void UnMountPlayer(std::shared_ptr<ProxyPlayer> p) {}
	void UnMountBlob(std::shared_ptr<ProxyBlob> b) {}
};

////////////////////
////////////////////

class PlayerManager
{
public:
	static PlayerManager *s_instance;
	
	std::vector<std::shared_ptr<ProxyPlayer>> players;
	std::vector<std::shared_ptr<ProxyBlob>> blobs;
	
	PlayerManager();
	~PlayerManager();
	
	void AddPlayer(std::shared_ptr<ProxyPlayer>);
	void RemovePlayer(std::shared_ptr<ProxyPlayer>);
	
	void AddBlob(std::shared_ptr<ProxyBlob>);
	void RemoveBlob(std::shared_ptr<ProxyBlob>);
	
	//std::list<std::shared_ptr<ProxyPlayer>> GetPlayers();
	//std::list<std::shared_ptr<ProxyPlayer>> GetPlayersBySeclev(unsigned int);
	std::shared_ptr<ProxyPlayer> GetPlayerByID(unsigned int);
	std::shared_ptr<ProxyPlayer> GetPlayerByName(const char*);
	std::shared_ptr<ProxyPlayer> GetPlayerByPartialName(const char*);
	std::shared_ptr<ProxyPlayer> GetPlayerByIndex(unsigned int);
	unsigned int GetPlayersCount();
	
	std::shared_ptr<ProxyBlob> GetBlobByID(unsigned int);
	std::shared_ptr<ProxyBlob> GetBlobByIndex(unsigned int);
	unsigned int GetBlobsCount();
	
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

void PlayerManager::AddBlob(std::shared_ptr<ProxyBlob> blob)
{
	if (!blob) return;
	this->blobs.push_back(blob);
}

void PlayerManager::RemovePlayer(std::shared_ptr<ProxyPlayer> player)
{
	this->players.erase(std::remove_if(this->players.begin(), this->players.end(), [](std::shared_ptr<ProxyPlayer> &p)
	{
		return !p->exists();
	}), this->players.end());
}

void PlayerManager::RemoveBlob(std::shared_ptr<ProxyBlob> blob)
{
	this->blobs.erase(std::remove_if(this->blobs.begin(), this->blobs.end(), [](std::shared_ptr<ProxyBlob> &o)
	{
		return !o->exists();
	}), this->blobs.end());
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

//

std::shared_ptr<ProxyBlob> PlayerManager::GetBlobByID(unsigned int id)
{
	for (auto &o : this->blobs)
	{
		if (o->id == id) return o;
	}
	return std::shared_ptr<ProxyBlob>(nullptr);
}

unsigned int PlayerManager::GetBlobsCount()
{
	return this->blobs.size();
}

std::shared_ptr<ProxyBlob> PlayerManager::GetBlobByIndex(unsigned int index)
{
	// index starts at 1 in Lua
	if (index < 1 || index > this->blobs.size()) return nullptr;
	return this->blobs[index-1];
}

////////////////////
////////////////////

std::string ProxyBlob::GetFactoryName() {
	std::string factoryName = (char*)(*(unsigned int*)((unsigned int)this->cactor+76));
	//std::cout << "ProxyBlob::GetFactoryName factoryName = " << factoryName << std::endl;
	return factoryName;
}
std::string ProxyBlob::GetConfigFileName() {
	std::string configFileName = (char*)(*(unsigned int*)((unsigned int)this->cactor+80));
	//std::cout << "ProxyBlob::GetConfigFileName configFileName = " << configFileName << std::endl;
	return configFileName;
}
unsigned short ProxyBlob::GetID() {
	unsigned short networkid = (unsigned short)(*(unsigned int*)((unsigned int)this->cactor+184));
	//std::cout << "ProxyBlob::GetID networkid = " << networkid << std::endl;
	return networkid;
}
unsigned char ProxyBlob::GetType() {
	unsigned char type = (unsigned char)(*(unsigned int*)((unsigned int)this->cactor+72));
	//std::cout << "ProxyBlob::GetType type = " << (int)type << std::endl;
	return type;
}
unsigned char ProxyBlob::GetTeam() {
	return *(unsigned char *)((unsigned int)this->cactor + 212);
}
float ProxyBlob::GetX() {
	void* pSprite = (void*)(*(unsigned int*)((unsigned int)this->cactor+536));
	return pSprite ? (*(float*)((unsigned int)pSprite+8)) : 0.f;
}
float ProxyBlob::GetY() {
	void* pSprite = (void*)(*(unsigned int*)((unsigned int)this->cactor+536));
	return pSprite ? (*(float*)((unsigned int)pSprite+12)) : 0.f;
}
float ProxyBlob::GetHealth() {
	return (*(float*)((unsigned int)this->cactor+196));
}
void ProxyBlob::SetHealth(float health) {
	*(float *)((unsigned int)this->cactor+196) = health;
}
std::shared_ptr<ProxyPlayer> ProxyBlob::GetPlayer() {
	//TODO: use __CRunnerToID instead
	unsigned int PlayerPTR = *(unsigned int*)((unsigned int)this->cactor+220);
	if (!PlayerPTR) return nullptr;
	unsigned int PlayerID = (*(unsigned short int*)(PlayerPTR+120));
	return PlayerManager::Get()->GetPlayerByID(PlayerID);
}
bool ProxyBlob::IsFacingLeft() {
	return sActor_IsFacingLeft(this->cactor);
}
void ProxyBlob::Kill() {
	sActor_Kill(this->cactor);
}

////////////////////
////////////////////

unsigned short ProxyActor::GetID() {
	unsigned short networkid = (unsigned short)(*(unsigned int*)((unsigned int)this->cactor+184));
	//std::cout << "ProxyActor::GetID networkid = " << networkid << std::endl;
	return networkid;
}
unsigned char ProxyActor::GetType() {
	unsigned char type = (unsigned char)(*(unsigned int*)((unsigned int)this->cactor+72));
	//std::cout << "ProxyActor::GetType type = " << (int)type << std::endl;
	return type;
}
std::shared_ptr<ProxyPlayer> ProxyActor::GetPlayer() {
	//TODO: use __CRunnerToID instead
	unsigned int PlayerPTR = *(unsigned int*)((unsigned int)this->cactor+220);
	if (!PlayerPTR) return nullptr;
	unsigned int PlayerID = (*(unsigned short int*)(PlayerPTR+120));
	return PlayerManager::Get()->GetPlayerByID(PlayerID);
}

////////////////////
////////////////////

#endif