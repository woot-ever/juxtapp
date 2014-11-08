#ifndef CBLOB_HPP
#define CBLOB_HPP

class CBlob : public CInventoryActor {
  public:
    std::vector<CBlob::Message, std::allocator<CBlob::Message> > messages;
    bool send_message_lock;
    std::vector<CBlob::Message, std::allocator<CBlob::Message> > lock_messages;
    irr::core::array<CComponent*, irr::core::irrAllocator<CComponent*> > components;
    CSprite *sprite;
    CBall *ball;
    CMovement *movement;
    CWeapon *weapon;
    CBrain *brain;
    CAttachment *attachment;
    irr::f32 gib_health;
    irr::f32 lightsource_radius;
    irr::f32 lightsource_radius_sqr;
    irr::video::SColor lightsource_color;
    bool lightsource_default_on;
    irr::f32 lightsource_color_r;
    irr::f32 lightsource_color_g;
    irr::f32 lightsource_color_b;
    static irr::core::array<CBlob*, irr::core::irrAllocator<CBlob*> > blobList;
    static
    std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::vector<CBlob*, std::allocator<CBlob*> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, std::vector<CBlob*, std::allocator<CBlob*> > > > > blobs_byname;
  private:
    std::string blob_name;

  public:
    CBlob(const irr::c8 *);
    ~CBlob(int);
    virtual void Reset(void);
    virtual void DoTick(void);
    virtual void Render(void);
    virtual bool Load(void);
    virtual void Unserialize(CBitStream &);
    void PushMessage(irr::u16, CBitStream &, bool);
    virtual Vec2f getPosition(void);
    virtual void setPosition(Vec2f);
    virtual Vec2f getVelocity(void);
    virtual void setVelocity(Vec2f);
    virtual irr::f32 getRadius(void);
    virtual bool Mount(CActor *);
    virtual bool UnMount(CActor *);
    virtual String getName(void);
    virtual irr::u8 getKeys1(void);
    virtual irr::u8 getKeys2(void);
    virtual bool isOnGround(void);
	virtual bool isOnLadder(void);
    virtual bool isOnWall(void);
    virtual bool isOnCeiling(void);
    virtual bool isFacingLeft(void);
    virtual bool isInAction(void);
    virtual bool isWalking(void);
    virtual bool isCatapultShot(void);
    virtual bool wasOnGround(void);
    virtual bool wasOnLadder(void);
    virtual void Send_Delta(CBitStream *, CBitStream *, CBitStream *);
    virtual bool Receive_Delta(CBitStream &, CBitStream *, ENetPeer *, bool &);
    virtual void Send_CreateData(CBitStream *);
    virtual bool Receive_CreateData(CBitStream &, bool);
    int getMovementSignificance(void);
    virtual void SetDead(bool, int);
    virtual bool onHit(Vec2f, Vec2f, float, CActor *, int, int);
    virtual bool collidesWithPoint(Vec2f, irr::f32);
    virtual void TakeDamage(irr::f32, CPlayer *);
    virtual bool UseMenu(CActor *, CGameContextMenu *);
    virtual void SetLight(irr::f32, irr::video::SColor);
    virtual bool isLightSource(void);
    virtual irr::f32 getLightRadius(void);
    irr::f32 getGibHealth(void);
    virtual void UpdateChild(void);
    virtual irr::video::SColor getColor(void);
    virtual void SetVisible(bool);
    virtual bool opensBridges(void);
    virtual void ForceCollideWithMap(void);
    virtual void setTeamHit(bool);
    virtual void getCollidesWith(std::vector<CBlob*, std::allocator<CBlob*> > &);
    static irr::u32 getBlobsSize(void);
    static CBlob * getBlob(irr::u32);
    static void getBlobsByName(const char *, std::vector<CBlob*, std::allocator<CBlob*> > &);
    static void getBlobsByType(int, std::vector<CBlob*, std::allocator<CBlob*> > &);
    virtual bool ReceiveMessage(irr::u16, CBitStream &);
    void ReadMessages(std::vector<CBlob::Message, std::allocator<CBlob::Message> > &);
}

#endif