#ifndef CCONTROLS_HPP
#define CCONTROLS_HPP

class CControls {
  public:
    bool mousePressed1;
    bool mousePressed2;
    bool mousePressed3;
    irr::core::vector2d<int> mousepos;
    irr::core::vector2d<int> oldmousepos;
    irr::core::vector2d<int> mousepos_beforelock;
    Vec2f mouseposworld;
    Vec2f oldmouseposworld;
    bool keys[313];
    irr::s32 actionkeys[16];
    irr::u8 lastused_actionkeys1;
    irr::u8 lastused_actionkeys2;
    Vec2f lastused_mouseposworld;
    irr::u8 cmd;
    irr::u8 lastcmd;
    irr::u16 pickid;
    irr::u16 lastpickid;
    bool locked;
    bool togglecrouch;
    bool togglesneak;
    bool togglewalk;
	irr::s32 locked_keycode;
    int32 usejoystick;
    irr::s32 cursortype;
    CMainMenu *mainmenu;
    irr::s32 mainmenukey;
    irr::s32 inventorykey;
    bool bCanCloseMenu;
    irr::f32 fCamDistance;
    irr::f32 fCamTFactor;
    irr::f32 fCamMFactor;
    int mousecamstyle;
    CMapArea *mousearea;
    CMapArea *mapareaundercursor;
    irr::core::stringc configfilename;
    irr::f32 hat1deadzonex;
    irr::f32 hat1deadzoney;
    irr::f32 hat2deadzonex;
    irr::f32 hat2deadzoney;
    irr::f32 hat1fastzone;
    irr::f32 hat2fastzone;
    irr::f32 hat1slowzone;
    irr::f32 hat2slowzone;
    irr::f32 hat1acceleration;
    irr::f32 hat1menuacceleration;
    irr::f32 hat2acceleration;
    irr::f32 hat2menuacceleration;
    int32 menupreference;
    int key_setting;
    int key_setting_button;
    CCamera *camera;
    CNetControls *netcontrols;

    CControls(void);
    ~CControls(int);
    void MapKeys(void);
    bool ActionKeyPressed(irr::s32);
    bool ActionKeyReleased(irr::s32);
    void MapActionKey(irr::s32, irr::s32);
    void SetActionKey(irr::s32, bool);
    bool KeyPressed(irr::s32);
    void SetKey(irr::s32, bool);
    bool NoKeysPressed(void);
    bool OnlyKeyPressed(irr::s32);
    void ClearKeys(void);
    irr::u8 getPackedActionKeys(int);
    void setActionKeysFromPacked(int, irr::u8);
    void Lock(irr::s32);
    void Unlock(void);
    bool CheckMenuKey(irr::s32, bool);
    bool getMenuShow(void);
    void Serialize(CBitStream &);
    bool Unserialize(CBitStream &);
    bool LoadFromFile(const char *);
    void SaveToFile(const char *);
    bool isMenuOpened(void);
}

#endif