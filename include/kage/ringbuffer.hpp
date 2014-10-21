#ifndef RINGBUFFER_HPP
#define RINGBUFFER_HPP

template <class T, long L> class ringbuffer {
  public:
    T *buf;
    long carret;
    long oldcarret;
	
    bool operator<<(T &);
    bool operator>>(T &);
    void flood(const T &);
    T * getCurrent(void);
    void MoveForward(int);
    void MoveBackward(int);
    void SaveCarret(void);
    void LoadCarret(void);
};

#endif