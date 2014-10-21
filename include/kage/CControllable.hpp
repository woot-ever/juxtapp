#ifndef CCONTROLLABLE_HPP
#define CCONTROLLABLE_HPP

#define FUCKING_SHIT unsigned int

class CControllable {
  public:
    FUCKING_SHIT control;

    CControllable(void);
    ~CControllable();
    void setControls(FUCKING_SHIT, bool);
    FUCKING_SHIT getControls(void);
    bool isMyControls(void);
    virtual void DrawHUD(void);
};

#endif