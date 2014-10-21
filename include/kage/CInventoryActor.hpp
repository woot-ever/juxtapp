#ifndef CINVENTORYACTOR_HPP
#define CINVENTORYACTOR_HPP

#include "CActor.hpp"

#define FUCKING_SHIT unsigned int

class CInventoryActor : public CActor {
  public:
    irr::video::ITexture *inventoryicon;
    WideString inventoryname;
    int inventoryicon_frame;
    int inventoryicon_size;
    WideString given_name;
    bool inwater;
    bool old_inwater;
    int last_water_sound_play;
    irr::f32 buoyancy;
    CBadassPtr<FUCKING_SHIT> attached;
    static irr::core::array<FUCKING_SHIT, irr::core::irrAllocator<FUCKING_SHIT> > inventoryActorList;

    CInventoryActor(const irr::c8 *);
    ~CInventoryActor();
    virtual void Reset(void);
    virtual void DoTick(void);
    virtual void setPosition(Vec2f);
    virtual void Send_Delta(FUCKING_SHIT, FUCKING_SHIT, FUCKING_SHIT);
    virtual bool Receive_Delta(FUCKING_SHIT &, FUCKING_SHIT, FUCKING_SHIT, bool &);
    virtual void Send_CreateData(FUCKING_SHIT);
    virtual bool Receive_CreateData(FUCKING_SHIT &, bool);
    virtual WideString getGivenName(void);
    virtual bool isInWater(void);
    virtual void SkipWater(void);
    void WaterUpdate(void);
    void PutAttachmentPoints(std::vector<FUCKING_SHIT, std::allocator<FUCKING_SHIT> > &);
    void RemoveFromAttachments(void);
};

#endif