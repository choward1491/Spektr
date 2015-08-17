
#ifndef _color_map_h_
#define _color_map_h_


#include "point.h"
#include "queue.h"
#include "cpixel.h"



class ColorMap {

public:

	ColorMap(){}
	virtual ~ColorMap(){}

	virtual Queue<Pixel> operator()( Point2D * points, int num_pts ) = 0;

};






#endif