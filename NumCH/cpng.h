/*

@author : Christian Howard
@date   : 5 / 6 / 2015

*/




#ifndef _cpng_h_
#define _cpng_h_

#include "cpixel.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "png.h"




// The max value for a 16 bit unsigned int
#define CINT16_MAX 65535

// The max value for an 8 bit unsigned int
#define CINT8_MAX 255

// Definition for a PNG using 8 bit colors
#define BRIEF 0

// Definition for a png using 16 bit colors
#define EXACT 1

// Definition choosing which resolution to use
#define COLOR_RESOLUTION EXACT

// Choosing the bit depth based on the predefined
// choice of color resolution
#if COLOR_RESOLUTION == BRIEF

#define BIT_DEPTH 8
#define TYPE unsigned char
#define MAX_VAL CINT8_MAX

#else

#define BIT_DEPTH 16
#define TYPE uint16_t
#define MAX_VAL CINT16_MAX

#endif






/*
**
**  This is a PNG class that utilizes libpng 
**  to handle saving and loading a png image.
**	This class is designed just for image 
**  manipulation and creation. 
**
*/

class PNG {

public:

	// Null Constructor
	PNG();


	// Construct image with width and height specified, as well
	// as an optional background color parameter
	PNG( int width, int height, Pixel background_color = Pixel() );


	// The PNG destructor
	~PNG();


	// The PNG operator = definition
	PNG & operator=( PNG & img );


	// The operators to allow for accessing a pixel
	// within this image
	Pixel & operator()( int row, int col ) const;
	Pixel & operator()( int row, int col );


	// Get the width of the png
	int getWidth(){ return width; }

	// Get the height of the png
	int getHeight(){ return height; }


	// Save this png to file
	void save( char* filename );

	// Load a png into this object
	void load( char* filename );


private:

	// Method for clearing the png data
	void clear();

	// Method for copying an img's data
	// into this PNG instance
	void copy( PNG & img );


	// the width of the png in pixels
	int width;

	// the height of the png in pixels
	int height;

	// the 2D array of pixels
	Pixel** pixels;

};






#endif