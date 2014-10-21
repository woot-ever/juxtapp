#include "ProxyDB.hpp"

int ProxyDB::Open(const char* file)
{
	//TODO: check if file is valid name (without extension, and without special chars etc...)
	if (PluginManager::Get()->currentPlugin == nullptr)
	{
		//TODO: print error?
		return 0;
	}
	
	std::string pluginName(PluginManager::Get()->currentPlugin->name);
	std::string pluginPath = PluginManager::Get()->workingDir + pluginName + std::string("/") + std::string(file) + std::string(".db");
	
	auto db = std::make_shared<leveldb::DB>();
	leveldb::Options options;
	options.create_if_missing = true;
	leveldb::Status status = leveldb::DB::Open(options, pluginPath, &db);
	if (!status.ok())
	{
		std::cout << "DB::Open ERROR: " << status.ToString() << std::endl;
		return 0;
	}
	
	std::string value;
	leveldb::Status s = db->Get(leveldb::ReadOptions(), key1, &value);
	if (s.ok())
	{
		std::cout << "VALUE = "<< value << std::endl;
		s = db->Put(leveldb::WriteOptions(), key2, value);
	}
	if (s.ok()) s = db->Delete(leveldb::WriteOptions(), key1);
}

extern int l_my_print(lua_State* L);