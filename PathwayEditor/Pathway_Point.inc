inline Point(float const& x, float const& y, float const& z, float const& tension, int const& numSegments)
	: x(x)
	, y(y)
	, z(z)
	, tension(tension)
	, numSegments(numSegments) {}

inline bool operator==(const Point& v) const noexcept {
	return x == v.x && y == v.y && z == v.z;
}
inline Point& operator+=(Point const& v) noexcept {
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}
inline Point operator+(Point const& v) const noexcept {
	return Point{ x + v.x, y + v.y, z + v.z, 0, 0 };
}
inline Point operator-(Point const& v) const noexcept {
	return Point{ x - v.x, y - v.y, z - v.z, 0, 0 };
}
inline Point operator*(float const& s) const noexcept {
	return Point{ x * s, y * s, z * s, 0, 0 };
}
inline Point operator/(float const& s) const noexcept {
	return Point{ x / s, y / s, z / s, 0, 0 };
}
