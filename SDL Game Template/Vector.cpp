#include "Vector.h"

Vector2D::Vector2D(float x, float y) : m_x(x), m_y(y) {}

Vector2D::Vector2D() : m_x(0.0), m_y(0.0) {}

//Getters and Setters:
float Vector2D::getX() { return m_x; }
float Vector2D::getY() { return m_y; }

void Vector2D::setX(float x) { m_x = x; }
void Vector2D::setY(float y) { m_y = y; }

float Vector2D::length() { return sqrt((m_x * m_x) + (m_y * m_y)); }

void Vector2D::normalise() {
	float l = length();
	if (l > 0) //avoids division by 0, length should always be > 0
	{
		(*this) *= 1 / l;
	}
}

void Vector2D::print() {
	std::cout << m_x << std::endl;
	std::cout << m_y << std::endl;
}


//Operator Overrides:
Vector2D Vector2D::operator+(const Vector2D& v2) const {
	return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}
Vector2D Vector2D::operator-(const Vector2D& v2) const {
	return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}
Vector2D Vector2D::operator*(float scalar) {
	return Vector2D(m_x * scalar, m_y * scalar);
}
Vector2D Vector2D::operator/(float scalar) {
	return Vector2D(m_x / scalar, m_y / scalar);
}
Vector2D& Vector2D::operator*=(float scalar) {
	m_x *= scalar;
	m_y *= scalar;
	return *this; 
}
Vector2D& Vector2D::operator/=(float scalar) {
	m_x /= scalar;
	m_y /= scalar;
	return *this;
}

//Friend Operator Overrides:

//As the operator is a friend of the class the Vector2D:: isn't needed 
Vector2D& operator+=(Vector2D& v1, const Vector2D& v2) {
	v1.m_x += v2.m_x;
	v1.m_y += v2.m_y;
	return v1;
}
Vector2D& operator-=(Vector2D& v1, const Vector2D& v2) {
	v1.m_x -= v2.m_x;
	v1.m_y -= v2.m_y;
	return v1;
}