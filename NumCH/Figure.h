


#ifndef _figure_h_
#define _figure_h_

#include "cpng.h"
#include "heap.h"
#include "FigData.h"


typedef struct Axis{
	float axis[6];
	int num_use;
} Axis;





class Figure {
public:
	Figure();



	void setPlotBounds( float perc_x, float perc_y, float perc_width, float perc_height );
	void setFrameBackgroundColor( const Pixel & color );
	void setPlotBackgroundColr( const Pixel & color );



private:

	MaxHeap< FigData2D* > data2plot;
	float plot_bounds[4];
	Axis  plot_ax;
	Pixel plot_bg_color;
	Pixel frame_bg_color;



};




#endif