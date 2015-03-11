#ifndef JUXTACONFIG_HPP
#define JUXTACONFIG_HPP

#include "ini.hpp"

class JuxtaConfig
{
public:
	static JuxtaConfig *s_instance;
	
	bool update_onserverstart;
	bool update_onmatchend;
	int speedhack_max_warnings;
	int speedhack_ban_duration;
	int speedhack_max_attacks;
	bool enable_lua_sandbox;
	INI::Parser *parser;
	
	JuxtaConfig() :
		update_onserverstart(true),
		update_onmatchend(false),
		speedhack_max_warnings(5),
		speedhack_ban_duration(15),
		speedhack_max_attacks(3),
		enable_lua_sandbox(true)
	{
	}
	
	~JuxtaConfig()
	{
		delete parser;
	}
	
	static JuxtaConfig *Get()
    {
        if (!s_instance)
          s_instance = new JuxtaConfig;
        return s_instance;
    }
	
	void Load(const char* path)
	{
		parser = new INI::Parser(path);
	}
	
	bool GetBoolean(const char* name, bool d)
	{
		std::string v(parser->top()[name]);
		if (v.length() == 0) return d;
		if (v == "1" || v == "true" || v == "yes") return true;
		return false;
	}
	
	int GetNumber(const char* name, int d)
	{
		std::string v(parser->top()[name]);
		if (v.length() == 0) return d;
		return atoi(v.c_str());
	}
	
	std::string GetString(const char* name, std::string d)
	{
		std::string v(parser->top()[name]);
		if (v.length() == 0) return d;
		return v;
	}
};
JuxtaConfig *JuxtaConfig::s_instance = 0;

#endif