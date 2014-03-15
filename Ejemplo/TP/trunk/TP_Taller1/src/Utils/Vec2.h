#ifndef VEC2_H_
#define VEC2_H_

class Rect;
class b2Vec2;

struct Vec2
{
	float x;
	float y;

	Vec2 () : x(0), y(0) {}
	explicit Vec2 (float xy);
	Vec2 (float x, float y) : x(x), y(y) {}
	static Vec2 polar (float r, float a);

	Vec2 (const Vec2&) = default;
	Vec2 (Vec2&&) = default;
	Vec2& operator= (const Vec2&) = default;
	Vec2& operator= (Vec2&&) = default;
	~Vec2 () = default;

	bool operator== (const Vec2& rhs) const;
	bool operator!= (const Vec2& rhs) const;

	Vec2 operator+ (const Vec2& rhs) const {
		return Vec2(x + rhs.x, y + rhs.y);
	}
	Vec2 operator* (float rhs) const;
	Vec2 operator* (const Vec2& rhs) const;

	Vec2 operator- () const;
	Vec2 operator- (const Vec2& rhs) const {
		return Vec2(x - rhs.x, y - rhs.y);
	}
	Vec2 operator/ (float rhs) const;
	Vec2 operator/ (const Vec2& rhs) const;

	Vec2& operator+= (const Vec2& rhs);
	Vec2& operator-= (const Vec2& rhs);
	Vec2& operator*= (float rhs);
	Vec2& operator/= (float rhs);
	Vec2& operator*= (const Vec2& rhs);
	Vec2& operator/= (const Vec2& rhs);

	Vec2 cambioCoordenadas (const Rect& sistOrigen, const Rect& sistDestino) const;

	float abs () const;
	float distancia (Vec2 punto) const;

	// todos en grados
	float angulo () const;
	float anguloCon (Vec2 punto) const;
	Vec2 rotar (float angulo) const;

	// conversiones para Box2D
	Vec2 (b2Vec2);
	operator b2Vec2 () const;
};

#endif /* VEC2_H_ */
