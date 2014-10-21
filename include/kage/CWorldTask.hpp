#ifndef CWORLDTASK_HPP
#define CWORLDTASK_HPP

#include "ITask.hpp"

#define FUCKING_SHIT unsigned int

class CWorldTask : public Singleton<FUCKING_SHIT>, public ITask {
  public:
    FUCKING_SHIT myPlayer[4];
    irr::f32 fCamPosLag;
    irr::f32 fCamTargetLag;
    irr::f32 fCamSpeedFactor;
    irr::f32 fCamMountFactor;
    int iCamOrtho;
    irr::f32 playerRespawnTime;
    irr::f32 waveRespawnTime;
    irr::f32 actorRespawnTime;
    FUCKING_SHIT map;
    FUCKING_SHIT camera[4];
    FUCKING_SHIT players;
    FUCKING_SHIT rules;
    FUCKING_SHIT respawn;
    FUCKING_SHIT physics;
    FUCKING_SHIT overworld;
    irr::core::array<FUCKING_SHIT, irr::core::irrAllocator<FUCKING_SHIT> > Entitys;

    irr::core::array<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, irr::core::irrAllocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > mapcycle;
    int currentmap_index;
    String mapcycle_file;
    irr::video::SColor AmbientMapColor;
    String lastloadedmap;
    bool loadededitor;
    static bool loaded;
    FUCKING_SHIT eventsrecorder;
    FUCKING_SHIT controlsrecorder;
    FUCKING_SHIT englishnames;
    bool gamePaused;

    irr::core::array<FUCKING_SHIT, irr::core::irrAllocator<FUCKING_SHIT> > loadActors;

    CWorldTask(void);
    ~CWorldTask();
    unsigned long size(void);
    virtual bool Start(void);
    virtual void Update(void);
    virtual void Stop(void);
    FUCKING_SHIT GetPhysics(void);
    FUCKING_SHIT GetMap(void);
    FUCKING_SHIT GetPlayers(void);
    FUCKING_SHIT GetRules(void);
    FUCKING_SHIT GetEntity(irr::s32);
    irr::s32 GetEntitysNum(void);
    bool EntityExists(irr::s32);
    irr::s32 GetEntityIndex(FUCKING_SHIT);
    void AddEntity(FUCKING_SHIT);
    void RemoveEntity(FUCKING_SHIT);
    void ClearEntities(void);
    void RenderWorld(FUCKING_SHIT);
    FUCKING_SHIT GetRespawn(void);
    void AddNewCamera(void);
    FUCKING_SHIT ReloadMap(const char *, bool);
    bool LoadMapCycle(const char *);
    FUCKING_SHIT ReloadRules(const char *);
    void RestartMap(void);
    void DestroyAllMenus(void);
    void Shake(int, int, Vec2f);
    void SaveWorld_WithConfigs(const char *);
    bool LoadWorld_WithConfigs(const char *);
    bool LoadWorld(const char *);
    void SaveWorld(const char *);
    void Explosion(const char *, const char *, Vec2f, Vec2f, irr::f32, int, int, int,
    FUCKING_SHIT, irr::f32, FUCKING_SHIT, int, bool);
    irr::f32 getTime(void);
    String getRandomEnglishName(bool);
    void DropCoins(Vec2f, int);
    void DropEgg(int, Vec2f, int, int);
    void LoadOverworld(void);
    void AddLoadActor(const char *, const char *, Vec2f, int, int);
};

#endif