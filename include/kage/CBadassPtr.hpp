#ifndef CBADASSPTR_HPP
#define CBADASSPTR_HPP

// Definition taken from https://code.google.com/p/crimsonglory/source/browse/trunk/Engine/mmanager.h
template <class T>
class CBadassPtr
{
  protected:
    T* obj;
  public:
    CBadassPtr()
    {
        obj = 0;
    }
    CBadassPtr( T* o )
    {
        obj = 0; *this = o;
    }
    CBadassPtr( const CBadassPtr<T>& p )
    {
        obj = 0; *this = p;
    }

    ~CBadassPtr()
    {
        if ( obj )
        {
          obj->ReleaseBP();
        }
    }

    inline CBadassPtr<T>& operator =( const CBadassPtr<T>& p )
    {
        if ( obj )
        {
          obj->ReleaseBP();
        }
        obj = p.obj;
        if ( obj )
        {
          obj->AddBP();
        }
        return *this;
    }
    inline CBadassPtr<T>& operator =( T* o )
    {
        if ( obj )
        {
          obj->ReleaseBP();
        }
        obj = o;
        if ( obj )
        {
          obj->AddBP();
        }
        return *this;
    }

    inline T& operator *() const
    {
        assert( obj != 0 && "Tried to * a NULL smart pointer" );
        return *obj;
    }

    inline T* operator ->() const
    {
        assert( obj != 0 && "Tried to -> on a NULL smart pointer" );
        return obj;
    }

    inline operator T *() const
    {
        return obj;
    }

    inline bool operator !()
    {
        return !( obj );
    }

    inline bool isValid() const
    {
        return ( obj != 0 );
    }

    inline bool operator ==( const CBadassPtr<T>& p ) const
    {
        return ( obj == p.obj );
    }
    inline bool operator ==( const T* o ) const
    {
        return ( obj == o );
    }
};

#endif