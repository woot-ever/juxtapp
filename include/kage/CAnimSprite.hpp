#ifndef CANIMSPRITE_HPP
#define CANIMSPRITE_HPP

class CAnimSprite {
  public:
    irr::video::S3DVertex Vertices[4];
    irr::video::SMaterial Material;
    irr::video::ITexture *Texture;
    irr::video::ITexture *Texture2;
    irr::video::ITexture *normalMap;
    irr::f32 fWidth;
    irr::f32 fHeight;
    irr::f32 fActualWidth;
    irr::f32 fActualHeight;
    irr::f32 fFrameWidth;
    irr::f32 fFrameHeight;
    irr::core::vector3df vActualCenter;
    irr::s32 crntFrm;
    irr::s32 TotalFrm;
    irr::s32 stepww;
    irr::s32 stephh;
    bool forward;
    irr::s32 time;
    irr::s32 crTime;
    irr::s32 startFrame;
    irr::s32 endFrame;
    irr::f32 xCoord;
    irr::f32 yCoord;
    bool bMirrored;
    irr::f32 Z;
    irr::core::matrix4 AbsTransform;
    bool visible;
    static irr::u16 Indices[6];
    static irr::core::array<CAnimSprite*, irr::core::irrAllocator<CAnimSprite*> > animsprites;
    static bool bNeedsSorting;

    CAnimSprite(bool);
    ~CAnimSprite(int);
    static void RenderBack(bool);
    virtual void Load(const char *, irr::s32, irr::s32, irr::f32,
    irr::video::IImage *);
    void PlayForward(void);
    void PlayBackward(void);
    void setSpeed(int);
    void setFrame(int, bool);
    irr::s32 getFrame(void);
    virtual void Update(void);
    void setStartEndFrame(irr::s32, irr::s32);
    irr::s32 GetMaxFrames(void);
    void render(bool);
    void render(irr::video::SMaterial &);
    irr::video::SMaterial & getMaterial(irr::u32);
    irr::f32 getActualWidth(void);
    irr::f32 getActualHeight(void);
    irr::f32 getFrameWidth(void);
    irr::f32 getFrameHeight(void);
    irr::core::vector3df getActualCenter(void);
    bool getMirrored(void);
    void setVerticePos(irr::s32, irr::core::vector3df);
    irr::core::vector3df getVerticePos(irr::s32);
    irr::core::triangle3df getTriangle(irr::s32);
    irr::core::vector2df getTCoord(irr::s32);
    irr::video::ITexture * getTexture(void);
    void setColor(irr::video::SColor);
    void setAlpha(int);
    void setZValue(irr::f32);
    void setRotation(irr::f32);
    irr::f32 getRotation(void);
    static int Partition(irr::core::array<CAnimSprite*, irr::core::irrAllocator<CAnimSprite*> > &, int, int);
    static void SpritesQuicksort(irr::core::array<CAnimSprite*, irr::core::irrAllocator<CAnimSprite*> > &, int, int);
}

#endif