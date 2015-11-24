

#include "FigData.h"


FigData2D::FigData2D(){
	data = 0;
	num_data = 0;
	shape_type = Circle;
	size = 0;
	zdepth = 0;
	cmap = 0;

}


FigData2D::FigData2D( Point2D* points, int n_data, int stype, int _size, int _zdepth ){
	data = points;
	num_data = n_data;
	shape_type = stype;
	size = _size;
	zdepth = _zdepth;

}


FigData2D::~FigData2D(){
	data = 0;
	cmap = 0;
}


void FigData2D::drawData( PNG & img ){

}


void FigData2D::setColorMap( ColorMap * map ){
	cmap = map;
}


/*
Point2D* data;

int num_data;
int shape_type;
float size;
float zdepth;


ColorMap* cmap;
*/


void FigData2D::drawCircle( Point2D & pt, Pixel & color, PNG & img ){

	

}

void FigData2D::drawTriangle( Point2D & pt,Pixel & color, PNG & img ){

}

void FigData2D::drawSquare( Point2D & pt,Pixel & color, PNG & img ){

}

void FigData2D::drawDiamond( Point2D & pt,Pixel & color, PNG & img ){

}






