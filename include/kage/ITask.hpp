#ifndef ITASK_HPP
#define ITASK_HPP

struct ITask {
  public:
    bool canKill;
    bool stopped;
    long priority;
    bool framerate_independent;

    ITask(void);
    virtual bool Start(void);
    virtual void OnSuspend(void);
    virtual void Update(void);
    virtual void OnResume(void);
    virtual void Stop(void);
};

#endif