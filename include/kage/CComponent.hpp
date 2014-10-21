#ifndef CCOMPONENT_HPP
#define CCOMPONENT_HPP

struct CComponent {
  public:
    CBlob &blob;

    CComponent(CBlob &);
    ~CComponent(int);
    virtual bool ReceiveMessage(irr::u16, CBitStream &);
}

#endif