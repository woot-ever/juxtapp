#ifndef CENTITY_HPP
#define CENTITY_HPP

#define FUCKING_SHIT unsigned int

class CEntity {
  public:
    bool bInvalidEntity;
    irr::s32 alive;
    irr::s32 timeOut;
    bool bCanDie;
    bool bZombie;
    irr::core::array<FUCKING_SHIT, irr::core::irrAllocator<FUCKING_SHIT> > badasspointers;
    irr::core::vector2d<int> debugScreenPos;
    String debugText;

    CEntity(void);
    ~CEntity();
    virtual void Reset(void);
    virtual void Think(void);
    virtual void Render(void);
    virtual void UpdateVisuals(void);
    void setDebugText(String);
    const irr::c8 * getDebugText(void);
    void setDebugPos(irr::core::vector2d<int>);
    irr::core::vector2d<int> getDebugPos(void);
    bool isValidEntity(void);
    irr::s32 getAliveTime(void);
    virtual void Destroy(void);
    void Die(void);
    void ReleaseBP(FUCKING_SHIT);
    void AddBP(FUCKING_SHIT);
    void NullBP(void);
};

#endif