#ifndef VEC2F_HPP
#define VEC2F_HPP

struct Vec2f {
    float x;
    float y;
  public:
    Vec2f(void);
    Vec2f(float, float);
    void SetZero(void);
    void Set(float, float);
    Vec2f operator-(void) const;
    Vec2f operator-(const Vec2f &);
    Vec2f & operator=(const Vec2f &);
    Vec2f operator*(float);
    float operator*(const Vec2f &) const;
    Vec2f operator/(float);
    Vec2f operator+(const Vec2f &);
    bool operator==(const Vec2f &);
    bool operator!=(const Vec2f &);
    Vec2f & operator*=(const Vec2f &);
    Vec2f & operator*=(float);
    Vec2f & operator/=(const Vec2f &);
    Vec2f & operator/=(float);
    Vec2f & operator+=(const Vec2f &);
    Vec2f & operator+=(float);
    Vec2f & operator-=(const Vec2f &);
    Vec2f & operator-=(float);
    bool operator<=(const Vec2f &) const;
    bool operator>=(const Vec2f &) const;
    bool operator<(const Vec2f &) const;
    bool operator>(const Vec2f &) const;
    float Length(void) const;
    float LengthSquared(void) const;
    float Normalize(void);
    float Angle(void) const;
    float AngleWith(const Vec2f &) const;
    Vec2f & RotateBy(float, const Vec2f &);
    bool isValid(void) const;
};

#endif