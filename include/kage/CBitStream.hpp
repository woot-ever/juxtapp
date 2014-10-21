#ifndef CBITSTREAM_HPP
#define CBITSTREAM_HPP

#define FUCKING_SHIT unsigned int

class CBitStream {
  public:
    std::vector<unsigned char, std::allocator<unsigned char> > buffer;
    long bitIndex;
    long bitsUsed;
    bool doresize;
    static bool fastdeltas;
    irr::u8 buf[8];

    CBitStream(void);
    CBitStream(long);
    CBitStream(unsigned char *, long);
    void writeuc(unsigned char);
    void writeu32(unsigned int);
    void writeBitStream(FUCKING_SHIT);
    void writeBitStream(FUCKING_SHIT, int, int);
    void writeBuffer(unsigned char *, int);
    void write_force_bool(bool);
    unsigned char readuc(void);
    unsigned int readu32(void);
    bool read_force_bool(void);
    bool safe(int);
    bool saferead_force_bool(bool &);
	unsigned char * readBuffer(int &);
    bool Compress_FastLZ(int);
    bool Decompress_FastLZ(void);
    void ResetBitIndex(void);
    void SetBitIndex(long);
    void SetBitsUsed(long);
    long Length(void);
    unsigned char * Retrieve(void);
    unsigned char * Set(void);
    void ResetBuffer(void);
    void Clear(void);
    long getBitsUsed(void);
    long getBytesUsed(void);
    unsigned char * getBuffer(void);
    bool endBuffer(void);
    void SkipBits(irr::u32);
    long getBitIndex(void);
    bool onlyZeroesFrom(irr::u32);
    bool SaveToFile(const char *);
    bool LoadFromFile(const char *);
    static void Test(void);
    irr::core::stringc oldread_stringc(void);
    irr::core::stringw oldread_stringw(void);
	unsigned char read(void);
    void write(unsigned char);
    void write2(int);
    int read2(void);
    float read3(void);
    void write3(float);
};

#endif