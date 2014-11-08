#ifndef CSPRITE_HPP
#define CSPRITE_HPP

struct SpriteVars {
    irr::core::vector3df translation;
    irr::core::vector3df rotation;
    irr::u8 keys1;
    irr::u8 keys2;
    int last_hitter;
    Vec2f last_hitpoint;
    irr::f32 last_hitpower;
    bool gibbed;
    bool spawned;
    bool died;
    irr::f32 sound_emit_volume;
    irr::f32 sound_emit_pitch;
    bool facing_left;
};

struct SpriteConsts {
    std::string filename;
    irr::video::IImage *image;
    irr::s32 frameWidth;
    irr::s32 frameHeight;
    std::string sound_death_hit;
    std::string sound_flesh_hit;
    std::string sound_die;
    std::string sound_spawn;
    std::string sound_gib;
    std::string sound_emit;
    irr::f32 blood_multiplier;
    irr::video::SColor blood_color;
};

typedef struct _Animation {
    irr::u16 frames_num;
    irr::u16 time;

    irr::core::array<unsigned short, irr::core::irrAllocator<unsigned short> > frames;
    irr::u8 loop;
    irr::u16 frame;
    irr::u16 timer;
    bool backward;
  public:
    bool ended(void);
    void Animation(void);
} Animation;

class CSprite : public CComponent {
  public:
    SpriteVars vars;
    SpriteConsts consts;
    //CSprite::Animation *animation;

    std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, CSprite::Animation*, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, CSprite::Animation*> > > animations;
    irr::core::array<GibEntry*, irr::core::irrAllocator<GibEntry*> > giblist;
  protected:
    CAnimSprite *animsprite;
    //irrklang::ISound *emitsound;

  public:
    CSprite(CBitStream &, CBlob &);
    bool isFrame(irr::u16);
    ~CSprite(int);
    virtual void RenderDirect(void);
    virtual bool ReceiveMessage(irr::u16, CBitStream &);
    SpriteVars & getVars(void);
    SpriteConsts & getConsts(void);
    CAnimSprite * getAnimSprite(void);
    virtual void ReloadSprite(const char *);
    void LoadAnimation(CSprite::Animation &, CBitStream &);
    virtual void Update(void);
    virtual void HitEffect(irr::f32);
    void Gib(void);
    void SetAndReset(CSprite::Animation *);
    bool LoadGib(GibEntry &, CBitStream &, std::string);
  protected:
    virtual void SetTranslation(Vec2f, irr::f32);
    void StopEmitSound(void);
}

#endif