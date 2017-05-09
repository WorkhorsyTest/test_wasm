


#include "three.h"


Fog::Fog(int color) : Fog(color, 1, 1000) {
}

Fog::Fog(int color, float near, float far) {
	this->isFog = true;
	this->name = "";
	this->color = new Color(color);
	this->near = near;
	this->far = far;
}

Fog* Fog::clone() {
	return new Fog(this->color->getHex(), this->near, this->far);
}
/*
string Fog::toJSON( meta ) {
	return {
		type: 'Fog',
		color: this->color.getHex(),
		near: this->near,
		far: this->far
	};
}
*/
