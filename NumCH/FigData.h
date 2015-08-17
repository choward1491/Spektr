

#ifndef _figdata_h_
#define _figdata_h_


#include "color_map.h"
#include "cpng.h"


enum shapes{ Circle = 0, Triangle, Square, Diamond };







class FigData2D {

public:

	FigData2D();
	FigData2D( Point2D* points, int num_data, int stype = Circle, int size = 1, int zdepth = 0 );
	~FigData2D();
	void drawData( PNG & img );
	void setColorMap( ColorMap * map );


private:
	Point2D* data;

	int num_data;
	int shape_type;
	float size;
	float zdepth;


	ColorMap* cmap;


	void drawCircle( Point2D & pt, Pixel & color, PNG & img );
	void drawTriangle( Point2D & pt, Pixel & color, PNG & img );
	void drawSquare( Point2D & pt, Pixel & color, PNG & img );
	void drawDiamond( Point2D & pt, Pixel & color, PNG & img );

};





#endif