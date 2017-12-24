#pragma once

// Simple color class
class Color{
private:
	float r;
	float g;
	float b;
	float a;

public:
	Color(float r, float g, float b, float a);
	~Color();
	float getR() const;
	float getG() const;
	float getB() const;
	float getA() const;

	const static Color WHITE;
	const static Color GREEN;
	const static Color ORANGE;
};

