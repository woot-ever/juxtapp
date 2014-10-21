#ifndef CBALL_HPP
#define CBALL_HPP

#include "CBitStream.hpp"

struct BallVars {
    Vec2f pos;
    Vec2f oldpos;
    Vec2f vel;
    Vec2f oldvel;
    irr::f32 maxhspeed;
    irr::f32 maxfallspeed;
    irr::f32 maxupspeed;
    irr::f32 vellen;
    irr::f32 oldvellen;
    bool onground;
    bool onladder;
    bool onwall;
    bool onceiling;
    bool catapult_shot;
    bool old_onground;
    bool old_onladder;
    bool old_onwall;
    bool old_catapult_shot;
    bool old_onceiling;
    int aircount;
    Vec2f ground_normal;
    CActor *old_parent;
};

struct BallConsts {
    irr::f32 width;
    irr::f32 height;
    irr::f32 radius;
    irr::f32 gravity;
    irr::f32 max_fallspeed;
    irr::f32 max_upspeed;
    irr::f32 max_airspeed;
    irr::f32 max_groundspeed;
    irr::f32 max_actionspeed;
    irr::f32 groundslide;
    irr::f32 ladderslide;
    irr::f32 wallslide;
    irr::f32 groundbounce;
    irr::f32 wallbounce;
    bool opens_doors;
    bool opens_bridges;
    irr::f32 hit_momentum;
};

class CBall : public CComponent {
  public:
    BallVars vars;
    BallConsts consts;
    int last_tile_collision;
    ringbuffer<BallVars, 60l> balldeltachecks;

    CBall(CBitStream &, CBlob &);
    void SetPosition(Vec2f);
    void SetVelocity(Vec2f);
    ~CBall(int);
    virtual void Update(void);
    virtual bool ReceiveMessage(irr::u16, CBitStream &);
    BallVars & getVars(void);
    BallConsts & getConsts(void);
    void onMounted(void);
    virtual void ResolveCollisions(void);
    virtual void CollideWithMap(void);
    virtual void CollideWithObjects(void);
    virtual bool doesCollideWith(CActor *);
    virtual void SendTouchMsg(irr::u16, Vec2f, Vec2f);
    virtual void OpenBlocks(void);
    virtual void HitMomentum(Vec2f, Vec2f, float);
}

#endif