

#include "three.h"

float Color::hue2rgb(float p, float q, float t) {
	if ( t < 0 ) t += 1;
	if ( t > 1 ) t -= 1;
	if ( t < 1 / 6 ) return p + ( q - p ) * 6 * t;
	if ( t < 1 / 2 ) return q;
	if ( t < 2 / 3 ) return p + ( q - p ) * 6 * ( 2 / 3 - t );
	return p;
}

void Color::handleAlpha(string value) {
	if (value == "") return;

	if (Math::IsFloat(value)) {
		//console.warn( 'THREE.Color: Alpha component of ' + style + ' will be ignored.' );
	}
}

Color::Color(float r, float g, float b) {
	this->setRGB( r, g, b );
}

Color::Color(float r) {
	// r is THREE.Color, hex or string
	this->set( r );
}

Color* Color::set(Color* value ) {
	this->copy( value );
	return this;
}

Color* Color::set(int value ) {
	this->setHex( value );
	return this;
}

Color* Color::set(string value ) {
	this->setStyle( value );
	return this;
}

Color* Color::setScalar(float scalar ) {
	this->r = scalar;
	this->g = scalar;
	this->b = scalar;

	return this;
}

Color* Color::setHex(int hex ) {
	hex = Math::Floor( hex );

	this->r = ( hex >> 16 & 255 ) / 255;
	this->g = ( hex >> 8 & 255 ) / 255;
	this->b = ( hex & 255 ) / 255;

	return this;
}

Color* Color::setRGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;

	return this;
}

Color* Color::setHSL(float h, float s, float l) {
	// h,s,l ranges are in 0.0 - 1.0
	h = Math::EuclideanModulo( h, 1 );
	s = Math::Clamp( s, 0, 1 );
	l = Math::Clamp( l, 0, 1 );

	if ( s == 0 ) {
		this->r = this->g = this->b = l;
	} else {
		float p = l <= 0.5 ? l * ( 1 + s ) : l + s - ( l * s );
		float q = ( 2 * l ) - p;

		this->r = hue2rgb( q, p, h + 1 / 3 );
		this->g = hue2rgb( q, p, h );
		this->b = hue2rgb( q, p, h - 1 / 3 );
	}

	return this;
}

Color* Color::setStyle(string style ) {
/*
	string m;

	if ( m = /^((?:rgb|hsl)a?)\(\s*([^\)]*)\)/.exec( style ) ) {
		// rgb / hsl
		var color;
		var name = m[ 1 ];
		var components = m[ 2 ];

		switch ( name ) {
			case "rgb":
			case "rgba":
				if ( color = /^(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*(,\s*([0-9]*\.?[0-9]+)\s*)?$/.exec( components ) ) {
					// rgb(255,0,0) rgba(255,0,0,0.5)
					this->r = Math::Min( 255, parseInt( color[ 1 ], 10 ) ) / 255;
					this->g = Math::Min( 255, parseInt( color[ 2 ], 10 ) ) / 255;
					this->b = Math::Min( 255, parseInt( color[ 3 ], 10 ) ) / 255;

					handleAlpha( color[ 5 ] );

					return this;
				}

				if ( color = /^(\d+)\%\s*,\s*(\d+)\%\s*,\s*(\d+)\%\s*(,\s*([0-9]*\.?[0-9]+)\s*)?$/.exec( components ) ) {
					// rgb(100%,0%,0%) rgba(100%,0%,0%,0.5)
					this->r = Math::Min( 100, parseInt( color[ 1 ], 10 ) ) / 100;
					this->g = Math::Min( 100, parseInt( color[ 2 ], 10 ) ) / 100;
					this->b = Math::Min( 100, parseInt( color[ 3 ], 10 ) ) / 100;

					handleAlpha( color[ 5 ] );

					return this;
				}

				break;
			case "hsl":
			case "hsla":
				if ( color = /^([0-9]*\.?[0-9]+)\s*,\s*(\d+)\%\s*,\s*(\d+)\%\s*(,\s*([0-9]*\.?[0-9]+)\s*)?$/.exec( components ) ) {
					// hsl(120,50%,50%) hsla(120,50%,50%,0.5)
					var h = parseFloat( color[ 1 ] ) / 360;
					var s = parseInt( color[ 2 ], 10 ) / 100;
					var l = parseInt( color[ 3 ], 10 ) / 100;

					handleAlpha( color[ 5 ] );

					return this->setHSL( h, s, l );
				}

				break;
		}
	} else if ( m = /^\#([A-Fa-f0-9]+)$/.exec( style ) ) {
		// hex color
		var hex = m[ 1 ];
		var size = hex.length;

		if ( size == 3 ) {
			// #ff0
			this->r = parseInt( hex.charAt( 0 ) + hex.charAt( 0 ), 16 ) / 255;
			this->g = parseInt( hex.charAt( 1 ) + hex.charAt( 1 ), 16 ) / 255;
			this->b = parseInt( hex.charAt( 2 ) + hex.charAt( 2 ), 16 ) / 255;

			return this;
		} else if ( size == 6 ) {
			// #ff0000
			this->r = parseInt( hex.charAt( 0 ) + hex.charAt( 1 ), 16 ) / 255;
			this->g = parseInt( hex.charAt( 2 ) + hex.charAt( 3 ), 16 ) / 255;
			this->b = parseInt( hex.charAt( 4 ) + hex.charAt( 5 ), 16 ) / 255;

			return this;
		}
	}

	if ( style && style.length > 0 ) {
		// color keywords
		var hex = ColorKeywords[ style ];
		if ( hex != undefined ) {
			// red
			this->setHex( hex );
		} else {
			// unknown color
			//console.warn( 'THREE.Color: Unknown color ' + style );
		}
	}
*/
	return this;
}

Color* Color::clone() {
	return new Color( this->r, this->g, this->b );
}

Color* Color::copy(Color* color ) {
	this->r = color->r;
	this->g = color->g;
	this->b = color->b;

	return this;
}

Color* Color::copyGammaToLinear(Color* color, float gammaFactor ) {
//			if ( gammaFactor == undefined ) gammaFactor = 2.0;

	this->r = Math::Pow( color->r, gammaFactor );
	this->g = Math::Pow( color->g, gammaFactor );
	this->b = Math::Pow( color->b, gammaFactor );

	return this;
}

Color* Color::copyLinearToGamma(Color* color, float gammaFactor ) {
//			if ( gammaFactor == undefined ) gammaFactor = 2.0;
	float safeInverse = ( gammaFactor > 0 ) ? ( 1.0 / gammaFactor ) : 1.0;

	this->r = Math::Pow( color->r, safeInverse );
	this->g = Math::Pow( color->g, safeInverse );
	this->b = Math::Pow( color->b, safeInverse );

	return this;
}

Color* Color::convertGammaToLinear() {
	float r = this->r, g = this->g, b = this->b;

	this->r = r * r;
	this->g = g * g;
	this->b = b * b;

	return this;
}

Color* Color::convertLinearToGamma() {
	this->r = Math::Sqrt( this->r );
	this->g = Math::Sqrt( this->g );
	this->b = Math::Sqrt( this->b );

	return this;
}

int Color::getHex() {
	return ((int)(this->r * 255.0f)) << 16 ^ ((int)(this->g * 255.0f)) << 8 ^ ((int)(this->b * 255.0f)) << 0;
}

string Color::getHexString() {
	stringstream ss;
	ss << std::hex << this->getHex();
	return ss.str();
}

HSL* Color::getHSL(HSL* optionalTarget ) {
	// h,s,l ranges are in 0.0 - 1.0
	HSL* hsl = (optionalTarget ? optionalTarget : new HSL());

	float r = this->r, g = this->g, b = this->b;

	float max = Math::Max( r, g, b );
	float min = Math::Min( r, g, b );

	float hue = 0;
	float saturation = 0;
	float lightness = ( min + max ) / 2.0;

	if ( min == max ) {
		hue = 0;
		saturation = 0;
	} else {
		float delta = max - min;

		saturation = lightness <= 0.5 ? delta / ( max + min ) : delta / ( 2 - max - min );

		if (max == r) hue = ( g - b ) / delta + ( g < b ? 6 : 0 );
		else if (max == g) hue = ( b - r ) / delta + 2;
		else if (max == b) hue = ( r - g ) / delta + 4;

		hue /= 6;
	}

	hsl->h = hue;
	hsl->s = saturation;
	hsl->l = lightness;

	return hsl;
}

string Color::getStyle() {
	ostringstream ss;
	ss << "rgb(" << ((int)(this->r * 255.0f)) << "," << ((int)(this->g * 255.0f)) << "," << ((int)(this->b * 255.0f)) << ")";
	return ss.str();
}

Color* Color::offsetHSL(float h, float s, float l) {
	HSL* hsl = this->getHSL(nullptr);
	hsl->h += h; hsl->s += s; hsl->l += l;
	this->setHSL( hsl->h, hsl->s, hsl->l );
	return this;
}

Color* Color::add(Color* color ) {
	this->r += color->r;
	this->g += color->g;
	this->b += color->b;

	return this;
}

Color* Color::addColors(Color* color1, Color* color2 ) {
	this->r = color1->r + color2->r;
	this->g = color1->g + color2->g;
	this->b = color1->b + color2->b;

	return this;
}

Color* Color::addScalar(float s) {
	this->r += s;
	this->g += s;
	this->b += s;

	return this;
}

Color* Color::sub(Color* color ) {
	this->r = Math::Max( 0, this->r - color->r );
	this->g = Math::Max( 0, this->g - color->g );
	this->b = Math::Max( 0, this->b - color->b );

	return this;
}

Color* Color::multiply(Color* color ) {
	this->r *= color->r;
	this->g *= color->g;
	this->b *= color->b;

	return this;
}

Color* Color::multiplyScalar(float s ) {
	this->r *= s;
	this->g *= s;
	this->b *= s;

	return this;
}

Color* Color::lerp(Color* color, float alpha) {
	this->r += ( color->r - this->r ) * alpha;
	this->g += ( color->g - this->g ) * alpha;
	this->b += ( color->b - this->b ) * alpha;

	return this;
}

bool Color::equals(Color* c ) {
	return ( c->r == this->r ) && ( c->g == this->g ) && ( c->b == this->b );
}

Color* Color::fromArray(vector<float> array, int offset) {
//			if ( offset == undefined ) offset = 0;

	this->r = array[ offset ];
	this->g = array[ offset + 1 ];
	this->b = array[ offset + 2 ];

	return this;
}

vector<float> Color::toArray(vector<float> array, int offset ) {
//			if ( array == undefined ) array = [];
//			if ( offset == undefined ) offset = 0;

	array[ offset ] = this->r;
	array[ offset + 1 ] = this->g;
	array[ offset + 2 ] = this->b;

	return array;
}
/*
Color::toJSON() {
	return this->getHex();
}
*/
