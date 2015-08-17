
#include "cpixel.h"


Pixel::Pixel(){
	red   = 0;
	green = 0;
	blue  = 0;
	alpha = 0;
}



Pixel::Pixel( float r, float g, float b, float a ){
	red = r;
	green = g;
	blue = b;
	alpha = a;
}



Pixel::Pixel( const Pixel & px ){
	red = px.red;
	green = px.green;
	blue = px.blue;
	alpha = px.alpha;
}


Pixel & Pixel::operator=( Pixel & px ){
	if( this != &px ){
		red = px.red;
		green = px.green;
		blue = px.blue;
		alpha = px.alpha;
	}

	return *this;
}


void Pixel::toBlack(){
	red   = 0.0;
	green = 0.0;
	blue  = 0.0;
	alpha = 1.0;
}


void Pixel::toWhite(){
	red   = 1.0;
	green = 1.0;
	blue  = 1.0;
	alpha = 1.0;
}


void Pixel::disappear(){
	alpha = 0.0;
}
