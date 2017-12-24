#include "Color.h"

// static member initialization
const Color Color::WHITE(1.0f, 1.0f, 1.0f, 1.0f);
const Color Color::GREEN(0.0f, 1.0f, 0.0f, 1.0f);
const Color Color::ORANGE(1.0f, 0.27f, 0.0f, 1.0f);

Color::Color(float fr, float fg, float fb, float falpha)
	: r(fr), g(fg), b(fb), a(falpha){
	
}

Color::~Color(){
}

float Color::getR() const {
	return r;
}

float Color::getG() const {
	return g;
}

float Color::getB() const {
	return b;
}

float Color::getA() const {
	return a;
}

