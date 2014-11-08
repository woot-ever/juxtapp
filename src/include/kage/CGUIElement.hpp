#ifndef CGUIELEMENT_HPP
#define CGUIELEMENT_HPP

struct CGUIElement {
  public:
    bool kill;
    bool externalupdatecontrol;
    bool cursoronelement;
    irr::core::recti rect;
    bool hover;
    irr::core::position2di position;
    WideString label;
    static char alpha;
    static irr::video::SColor backgroundcolor;
    static irr::video::SColor outlinecolor;
    static irr::video::SColor buttoncolor;
    static irr::video::SColor buttonoutlinecolor;
    static irr::video::SColor buttonfontcolor;
    static irr::video::SColor buttonfonthovercolor;
    static irr::video::SColor errorcolor;
    static irr::video::SColor shadowcolor;
    static irr::video::SColor gaugecolor;
    static irr::video::SColor inventoryhovercolor;
    static std::string guiFont;
    static std::string consoleFont;
    static std::string introFont;
    static std::string hudFont;
    static std::string menuFont;
    static std::string menuTextFont;
    static std::string menuOptionFont;

    CGUIElement(void);
    ~CGUIElement(int);
    virtual void Render(void);
    virtual bool Update(void);
    virtual bool UpdateControl(irr::core::position2di &, bool, bool);
    virtual bool handleKeyPress(wchar_t, irr::s32, bool, bool,
    irr::IrrlichtDevice *);
    virtual void setPosition(irr::core::position2di);
    static bool LoadConfig(const char *);
}

#endif