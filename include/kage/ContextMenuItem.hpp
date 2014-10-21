#ifndef CONTEXTMENUITEM_HPP
#define CONTEXTMENUITEM_HPP

struct ContextMenuItem {
    WideString label;
    WideString value;
    WideString name;
    WideString consolevarname;
    Functor *functor;
    wchar_t shortcutkey;
    int shortcutpos;
    irr::core::recti rect;
    irr::core::recti translaterect;
    irr::video::SColor fontcolor;
    irr::video::SColor backcolor;
    bool hover;
    bool checked;
    int index;
    irr::core::dimension2di labeldimension;
    CContextMenu *submenu;
    CContextMenu *ownermenu;
    irr::u8 type;
    bool showinfo;
    irr::core::dimension2di infodimension;

    irr::core::array<irr::core::string<wchar_t, irr::core::irrAllocator<wchar_t> >, irr::core::irrAllocator<irr::core::string<wchar_t, irr::core::irrAllocator<wchar_t> > > > values;
    WideString *varwidestring;
    String *varstring;
    float *varfloat;
    int32 *varint;
    bool *varbool;
    irr::core::line2di ray1;
    irr::core::line2di ray2;
    irr::f32 pieangle1;
    irr::f32 pieangle2;
    irr::video::ITexture *icon;
    irr::core::recti iconrect;
    irr::core::recti inforect;
    irr::core::position2di icondrawpos;

    irr::core::array<irr::video::ITexture*, irr::core::irrAllocator<irr::video::ITexture*> > icons;
    CGUIElement *guielement;
    bool password;
    irr::f32 complete;
    int hovertime;
    irr::gui::IGUIFont *font;
    int fontHeight;
    int rectypos;
  public:
    ~ContextMenuItem(int);
}
	
#endif