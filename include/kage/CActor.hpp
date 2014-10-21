#ifndef CACTOR_HPP
#define CACTOR_HPP

#include "CControllable.hpp"
#include "CBadassPtr.hpp"
#include "CBitStream.hpp"
#include "CPlayer.hpp"
#include "CEntity.hpp"

#define FUCKING_SHIT unsigned int

struct CActor : public CEntity, public CNetObject, public CControllable {
    static irr::core::array<FUCKING_SHIT, irr::core::irrAllocator<FUCKING_SHIT> > actorList;
    irr::f32 health;
    irr::f32 status;
    irr::f32 oldhealth;
    irr::f32 default_health;
    irr::u8 team;
    irr::u8 classnum;
    irr::u8 sex;
    irr::u8 head;
    irr::u8 hat;
    CBadassPtr<FUCKING_SHIT> ownerPlayer;
    CBadassPtr<FUCKING_SHIT> playerOfRecentDamage;
    int recentdamage_time;
    int recentdamage_way;
    CBadassPtr<FUCKING_SHIT> parent;
    CBadassPtr<FUCKING_SHIT> child;
    irr::s16 deadTime;
    irr::s16 deadTimeCounter;
    bool dead;
    Vec2f temppos;
    Vec2f boundcenter;
    Vec2f netboundcenter;
    float boundradius;
    float netboundradius;
    bool testactor;
    FUCKING_SHIT loadedBitStream;
    CBadassPtr<FUCKING_SHIT> damageownedplayer;
    //ringbuffer<CActor::ActorDeltaCheck, 60l> actordeltachecks;
    irr::f32 width;
    irr::f32 height;
    irr::f32 radius;
    bool collidable;
    bool default_collidable;
    //CBadassPtr<CScreenText> labelText;
    irr::core::position2di collision_tilepos;
    bool infected;
    String infected_factory;
    String infected_config;
    Vec2f last_shadeupdate_pos;
    bool inventorypickable;
    Vec2f mountOffset;
    CBadassPtr<FUCKING_SHIT> last_mounted_actor;
    int last_mount_counter;
  public:
    CActor(void);
    CActor(const irr::c8 *);
    ~CActor();
    virtual void Reset(void);
    virtual void Think(void);
    virtual void Render(void);
	virtual void DoTick(void);
    virtual bool Load(void);
    virtual Vec2f getPosition(void);
    virtual void setPosition(Vec2f);
    virtual Vec2f getVelocity(void);
    virtual void setVelocity(Vec2f);
    virtual irr::f32 getRadius(void);
    virtual bool isFacingLeft(void);
    virtual bool isOnGround(void);
    virtual bool isOnLadder(void);
    virtual String getName(void);
    virtual bool Kill(void);
    virtual void FreePlayer(void);
    virtual void Respawn(Vec2f);
    virtual void TakeDamage(irr::f32, FUCKING_SHIT);
    static FUCKING_SHIT getActorOfPlayer(FUCKING_SHIT, irr::u16);
    static FUCKING_SHIT CreateActor(const irr::c8 *, const irr::c8 *, irr::s32, const irr::c8 *);
    virtual void Destroy(void);
    virtual void setTeam(irr::u16);
    virtual void Send_Delta(FUCKING_SHIT, FUCKING_SHIT, FUCKING_SHIT);
    virtual bool Receive_Delta(FUCKING_SHIT &, FUCKING_SHIT, FUCKING_SHIT, bool &);
    virtual bool Mount(FUCKING_SHIT);
    virtual bool UnMount(FUCKING_SHIT);
    FUCKING_SHIT getHighestParent(void);
    virtual void SetDead(bool, int);
    virtual bool isDead(void);
    virtual bool shouldSendToPlayer(FUCKING_SHIT, bool);
    bool isBot(void);
    virtual void ResetTest(void);
    virtual bool RayTest(Vec2f, Vec2f, Vec2f &, int);
    virtual Vec2f getLaggedPosition(int);
    virtual bool onHit(Vec2f, Vec2f, float, FUCKING_SHIT, int, int);
    virtual void Serialize(FUCKING_SHIT &);
    virtual void Unserialize(FUCKING_SHIT &);
    virtual bool IsDangerTo(Vec2f);
    void SetOwnerPlayer(FUCKING_SHIT, bool);
    bool isMyPlayer(void);
    virtual bool collidesWithPoint(Vec2f, irr::f32);
    virtual void onAddScore(int, int);
    virtual void UpdateChild(void);
    virtual bool isShielded(void);
    virtual bool isBig(void);
    bool isInCollisionSector(irr::core::position2di &);
    virtual bool opensBridges(void);
    FUCKING_SHIT collidesWith(int, int, irr::f32);
    FUCKING_SHIT rayCastActors(Vec2f, Vec2f, Vec2f &);
};

#endif