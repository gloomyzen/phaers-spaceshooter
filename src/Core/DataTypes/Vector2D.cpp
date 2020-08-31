#include "Vector2D.h"

using namespace TGEngine::core;

Vector2D::Vector2D() {
	x = 0.0f;
	y = 0.0f;
}

Vector2D::Vector2D(float _x, float _y) {
	x = _x;
	y = _y;
}

Vector2D &Vector2D::Add(const Vector2D &vec) {
	x += vec.x;
	y += vec.y;

	return *this;
}

Vector2D &Vector2D::Subtract(const Vector2D &vec) {
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vector2D &Vector2D::Multiply(const Vector2D &vec) {
	x *= vec.x;
	y *= vec.y;

	return *this;
}

Vector2D &Vector2D::Divide(const Vector2D &vec) {
	x /= vec.x;
	y /= vec.y;

	return *this;
}

Vector2D &Vector2D::Zero() {
	x = 0;
	y = 0;

	return *this;
}

Vector2D &operator+(Vector2D &v1, const Vector2D &v2) {
	return v1.Add(v2);
}

Vector2D &operator-(Vector2D &v1, const Vector2D &v2) {
	return v1.Subtract(v2);
}

Vector2D &operator*(Vector2D &v1, const Vector2D &v2) {
	return v1.Multiply(v2);
}

Vector2D &operator/(Vector2D &v1, const Vector2D &v2) {
	return v1.Divide(v2);
}

Vector2D &Vector2D::operator+=(const Vector2D &vec) {
	return Add(vec);
}

Vector2D &Vector2D::operator-=(const Vector2D &vec) {
	return Subtract(vec);
}

Vector2D &Vector2D::operator*=(const Vector2D &vec) {
	return Multiply(vec);
}

Vector2D &Vector2D::operator/=(const Vector2D &vec) {
	return Divide(vec);
}

std::ostream &operator<<(std::ostream &stream, const Vector2D &vec) {
	stream << "Vector2D (" << vec.getX() << "," << vec.getY() << ")";
	return stream;
}

template<typename T>
Vector2D &Vector2D::operator*(const T &i) {
	x *= static_cast<float>(i);
	y *= static_cast<float>(i);

	return *this;
}
