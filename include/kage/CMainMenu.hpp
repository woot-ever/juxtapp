#ifndef CMAINMENU_HPP
#define CMAINMENU_HPP

class CMainMenu {
  public:
    irr::gui::CGUIBrowser *web;
    CContextMenu *mainmenu;
    CContextMenu *gameslistmenu;
    CContextMenu *joinmenu;
    ContextMenuItem *serverslistitem;
    CContextMenu *portalmenu;
    CContextMenu *newsmenu;
    bool usegenerated;
    CControls *controls;

    irr::core::array<irr::core::string<char, irr::core::irrAllocator<char> >, irr::core::irrAllocator<irr::core::string<char, irr::core::irrAllocator<char> > > > mapfiles;
    int32 mapindex;

    irr::core::array<irr::core::string<char, irr::core::irrAllocator<char> >, irr::core::irrAllocator<irr::core::string<char, irr::core::irrAllocator<char> > > > botfiles;
    int32 botindex;
    WideString votereason;
    WideString votemapreason;
	WideString savemapname;
    CBrowser *browser;
    irr::gui::IGUISpriteBank *bank;
    int startup;

    CMainMenu(void);
    ~CMainMenu(int);
    void ShowMenu(CControls *, irr::core::position2di, bool);
    void ShowAdminMenu(irr::core::position2di);
    void ExitMenu(void);
    void LoadSkin(irr::gui::IGUIFont *);
    void ShowLogin(void);
    void LoadBank(void);
    void ShowTerms(void);
    void Login(const char *, const char *);
    void Encrypt(irr::core::stringc &);
    void Decrypt(irr::core::stringc &);
    void ShowSocial(void);
    void ShowConnect(void);
    void ShowMain(int);
    void HideAllSettingsTabs(void);
    void GoToURL(const char *);
    void GoToChat(void);
    void NewHeadList(irr::gui::IGUIElement *);
    int LaunchServerBrowser(bool);
    void BuildTeamAdminMenu(int, CContextMenu *, bool, bool, bool, bool, bool,
    bool, bool, bool);
    void BuildTeamIgnoreMenu(int, CContextMenu *);
    int ContextCallback(void);
    int ExitCallback(void);
    int CallbackStartGame(void);
    int CallbackStartServer(void);
    int CallbackJoin(void);
    int CallbackDisconnect(void);
    int CallbackAddBot(void);
    int CallbackAddDummyBot(void);
    int CallbackVideoChange(void);
    int CallbackJoinLocalhost(void);
    int CallbackAuthenticate(void);
    int CallbackAuthenticateForEditor(void);
    void StartAuthentication(void);
    void FinishAuthentication(void);
    int CallbackJoinServer(void);
    int CallbackGenerateMap(void);
    int CallbackVoteKick(void);
    int CallbackVoteRestartMap(void);
    int CallbackRconKick(void);
    int CallbackRconBan(void);
    int CallbackRconMute(void);
    int CallbackRconUnmute(void);
    int CallbackRconFreeze(void);
    int CallbackRconUnfreeze(void);
    int CallbackRconRestartMap(void);
    int CallbackRconNextMap(void);
    int CallbackRconMoveTeam(void);
    int CallbackRconAssignSeclev(void);
    int CallbackIgnore(void);
    int CallbackUnignore(void);
    int CallbackVoteMana(void);
    int CallbackStartEditor(void);
    int CallbackSaveMap(void);
    int CallbackQuitEditor(void);
    int CallbackAddBrowser(void);
    int CallbackMovementTutorial(void);
    int CallbackBuildingTutorial(void);
    int CallbackTutorial2Tutorial(void);
    int CallbackSwordfightTutorial(void);
    int CallbackZombies(void);
    int CallbackSandbox(void);
    int CallbackLoginFail(void);
    int CallbackLoginSuccess(bool);
    int CallbackChat(void);
    int CallbackManual(void);
    int CallbackWiki(void);
    int CallbackSettings(void);
    int CallbackMainMenu(void);
    bool getMenuShow(void);
    bool getBannerShow(void);
}

#endif