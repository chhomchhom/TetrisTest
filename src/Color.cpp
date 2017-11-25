#include "Color.hpp"

Color::Color() {
	this->red = 1.0;
	this->green = 1.0;
	this->blue = 1.0;
	this->alpha = 1.0;
}

Color::Color(float red, float green, float blue, float alpha) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}

void Color::setColor(float red, float green, float blue, float alpha) {
	this->red = red;
	this->green = green;
	this->blue = blue;
	this->alpha = alpha;
}
