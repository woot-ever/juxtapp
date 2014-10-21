#ifndef CCONTEXTMENU_HPPP
#define CCONTEXTMENU_HPPP

struct CContextMenu : public CGUIElement {
    CControls *controls;
    bool active;
    bool die;
    bool render;
    bool hover;
    bool cursorinside;
    bool autoscroll;
    bool *buttonpressed;
    bool *buttonpressed2;
    bool holdalive;
    bool staticpos;
    irr::core::recti rect;
    irr::core::recti translaterect;
    irr::core::position2di pos;
    int horspace;
    int verspace;
    int minitems;

    irr::core::array<ContextMenuItem*, irr::core::irrAllocator<ContextMenuItem*> > items;
    static irr::core::position2di mousepos;
    static irr::core::position2di oldmousepos;
    static irr::core::position2di mousetravel;
    static bool keysreleased;
    ContextMenuItem *edititem;
    static ContextMenuItem *globaledititem;
    static int carretblinkrate;
    static int carretblinkcounter;
    int carretpos;
    int carretx;
    bool mousebuttonrelease;
    WideString oldeditvalue;
    CContextMenu *parent;
    ContextMenuItem *parentitem;
    int style;
    irr::f32 radialradius;
    irr::f32 radialcenterradius;
    bool itemclicked;
    irr::gui::IGUIFont *font;
    irr::gui::IGUIFont *optionfont;
    irr::gui::IGUIFont *textfont;
    static int lastclickedindex;
    static bool canedit;
    static ContextMenuItem *lastClickedContextMenuItem;
    void *customdata;
    static irr::video::ITexture *piemenutexture;
    static irr::core::recti piemenutexturerect;
    static bool scrolling;
    static bool canscrollwest;
    static bool canscrolleast;
    static bool canscrollsouth;
    static bool canscrollnorth;
    static CContextMenu *active_menu;
    static ContextMenuItem *active_item;
    static irr::video::ITexture *icon_loading;
    irr::core::position2di infoboxoffset;
    String backsound;
    String selectsound;
    String validatesound;
    String pyksound;
    String optionsound;
    int ypos;
    static irr::core::position2di forcepos;
  public:
    CContextMenu(void);
    CContextMenu(CControls *, irr::core::position2di, int, bool &, bool &,
    irr::s32, bool, bool, int, bool);
    ~CContextMenu(int);
    virtual void Render(void);
    virtual bool Update(void);
    virtual bool UpdateControl(irr::core::position2di &, bool, bool);
    virtual void setPosition(irr::core::position2di);
    ContextMenuItem * AddItem(const wchar_t *, Functor *, wchar_t);
    ContextMenuItem * AddItem(const wchar_t *, Functor *, wchar_t, irr::u8,
    const wchar_t *, irr::video::ITexture *);
    ContextMenuItem * AddItem(const wchar_t *, irr::video::ITexture *);
    ContextMenuItem * AddItemString(const wchar_t *, WideString &,
    const wchar_t *, bool);
    ContextMenuItem * AddItemFloat(const wchar_t *, float &, const wchar_t *);
    ContextMenuItem * AddItemFloat(const wchar_t *, float &, Functor *,
    const wchar_t *);
    ContextMenuItem * AddItemInteger(const wchar_t *, int32 &,
    const wchar_t *);
    ContextMenuItem * AddItemInteger(const wchar_t *, int32 &, Functor *,
    const wchar_t *);
    ContextMenuItem * AddItemSeparator(void);
    ContextMenuItem * AddItemKey(const wchar_t *, int32 &, const wchar_t *);
    ContextMenuItem * AddItemRadio(const wchar_t *, int32 &, Functor *,
    const wchar_t *, irr::video::ITexture *);
    ContextMenuItem * AddItemCheck(const wchar_t *, int32 &, Functor *,
    const wchar_t *);
    ContextMenuItem * AddItemCheck(const wchar_t *, bool &, Functor *,
    const wchar_t *);
    ContextMenuItem * AddItemGUIElelemt(const wchar_t *, CGUIElement *,
    Functor *);
    ContextMenuItem * AddItemDisabled(const wchar_t *);
    ContextMenuItem * AddItemBack(void);
    CContextMenu * spawnContextMenu(ContextMenuItem *);
    virtual bool handleKeyPress(wchar_t, irr::s32, bool, bool,
    irr::IrrlichtDevice *);
    void NewItemRect(const wchar_t *, ContextMenuItem *);
    void UpdateItemPos(ContextMenuItem *);
    irr::core::position2di getTranslatePos(void);
    void CalcCarretPos(void);
    int ListMouseControl(ContextMenuItem *);
    int PieMouseControl(ContextMenuItem *);
    bool ItemClicked(ContextMenuItem *);
    bool ItemHovered(ContextMenuItem *);
    void DrawPie(ContextMenuItem *, int);
    static void FillFileMenu(CContextMenu *, const char *, const char *, int32 &, irr::core::array<irr::core::string<char, irr::core::irrAllocator<char> >, irr::core::irrAllocator<irr::core::string<char, irr::core::irrAllocator<char> > > > &, String *);
    int CallbackFilePick(void);
    void DeleteItems(void);
    void SaveConsoleVariable(ContextMenuItem *);
    void RepositionPie(irr::core::position2di, ContextMenuItem *);
    bool isDead(void);
    void DeactivateSubmenus(bool);
    void UpdateMenuRect(void);
    void ActivateMenu(void);
    void MakeInfoBox(ContextMenuItem *, irr::core::recti &);
    void AddBackButtons(void);
}

#endif