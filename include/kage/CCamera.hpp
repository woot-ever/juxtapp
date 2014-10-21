#ifndef CCAMERA_HPP
#define CCAMERA_HPP

class CCamera {
  public:
    irr::f32 fDistance;
    irr::f32 fDynaDistance;
    irr::f32 fTFactor;
    irr::f32 fMFactor;
    irr::f32 fPosLag;
    irr::f32 fTargetLag;
    irr::f32 fSpeedFactor;
    irr::f32 fMountFactor;
    irr::f32 fDynaZoom;
    int mousecamstyle;
    bool iOrtho;
    irr::f32 spectateMoveFactor;
    CBadassPtr<CActor> target;
    irr::scene::ICameraSceneNode *IrrCamera;
    CWorldTask *world;
    irr::core::matrix4 ProjMatrix;
    Vec2f vRealPos;
    Vec2f vRealTargetPos;
    Vec2f vPos;
    Vec2f vOldPos;
    irr::f32 fEditorZoomin;
    bool bSetCamera;
    CControls *controls;
    irr::core::rect<int> viewport;
    irr::core::vector3df vScreenCorner[4];
    bool rendermap;
    int shake_magnitude;
    int shake_time;

    CCamera(CWorldTask *, CControls *, irr::core::rect<int>);
    ~CCamera(int);
    irr::scene::ICameraSceneNode * getIrrCamera(void);
    virtual void Reset(void);
    virtual void Process(void);
    virtual void Process2(void);
    virtual void setTarget(CActor *);
    virtual CActor * getTarget(void);
    virtual Vec2f getPos(void);
    virtual void setPosition(Vec2f);
    virtual irr::f32 getDistance(void);
}

#endif