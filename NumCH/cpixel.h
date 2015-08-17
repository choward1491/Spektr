
#ifndef _cpixel_h_
#define _cpixel_h_



class Pixel {

public:

	Pixel();
	Pixel( float r, float g, float b, float a );
	Pixel( const Pixel & px );
	Pixel & operator=( Pixel & px );

	void toBlack();
	void toWhite();
	void disappear();

	float red;
	float green;
	float blue;
	float alpha;

};



#endif