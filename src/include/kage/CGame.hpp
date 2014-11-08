class CGame : public Singleton<CGame>, public ICApplication {
  public:
    CScript *script;
    IC_Console *console;
    CKernel *kernel;
    CIrrlichtTask *irrlicht;
    CSoundEngine *sound;
    CRender *renderer;
    bool worldLoaded;
    int goalTicks;
    bool bPrecache;
    bool bRenderLimit;
    CPrecache *precache;
    CBugTracker *bugtracker;
    String auth_login;
    String auth_password;
    bool auth_remember;
    int32 auth_autologin;
    int buildnum;
    int mapgenerator_width;
    int mapgenerator_height;
    int mapgenerator_seed;
    WideString mapgenerator_file;
    irr::f32 vote_kick_percent;
    irr::f32 vote_map_percent;
    int vote_time;
    int vote_kick_bantime;
    int sort;
    int filterplayerlower;
    int filterplayerupper;
    int filtergold;
    int filterpass;
    WideString filtermode;
    WideString key;
    String autojoinserver;
    String autojoinpassword;
  private:
    CIrrlichtTask *irrlichtTask;
    CScriptTask *scriptTask;
    CSoundEngine *soundTask;
    CNetworkTask *networkTask;
    CWorldTask *worldTask;
    bool tasksAdded;

  public:
    virtual void Run(int, char **);
    virtual void Shutdown(void);
    virtual void Restart(void);
    bool AddMainTasks(void);
    void CreateNewWorld(const irr::c8 *);
	void RunTests(const char *, const char *);
    void EncryptUserPassword(void);
    void DecryptUserPassword(void);
    void EncryptPremium(void);
    bool checkPremium(void);
    void LoadDefines(const char *);
    bool CheckMana(int);
    void RestartServer(const char *);
  private:
    int ParseCmdLine(int, char **);
}
