#pragma once
#include <math.h>
#include <iostream>

class Vector2D {

public:
	Vector2D(); //default constructor sets x and y to 0
	Vector2D(float x, float y);

	//Getter and Setters:
	float getX();
	float getY();
	
	void setX(float x);
	void setY(float y);

	float length();
	void normalise();

	void print();

	//Operator Overrides:
	Vector2D operator+(const Vector2D& v2) const;
	Vector2D operator-(const Vector2D& v2) const;
	Vector2D operator*(float scalar);
	Vector2D operator/(float scalar);
	Vector2D& operator/=(float scalar);
	Vector2D& operator*=(float scalar);
		
	//These operators are friends as they access private members of v2:
	//Could be done with get functionality...
	friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2);
	friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2);

private:

	float m_x;
	float m_y;
};