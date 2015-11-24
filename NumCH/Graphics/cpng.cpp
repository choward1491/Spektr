
#include "cpng.h"




PNG::PNG(){
	width  = 0;
	height = 0;
	pixels = 0;
}





PNG::PNG( int w, int h, Pixel bg_color){
	width = w;
	height = h;

	pixels = new Pixel*[ height ];
	for( int i = 0; i < height; i++ ){
		pixels[i] = new Pixel[ width ];
		for( int j = 0; j < width; j++ ){
			pixels[i][j] = bg_color;
		}
	}
}






PNG::~PNG(){
	clear();
}





PNG & PNG::operator=( PNG & img ){
	copy( img );
	return *this;
}





Pixel & PNG::operator()( int row, int col ) const{
	return pixels[row][col];
}





Pixel & PNG::operator()( int row, int col ){
	return pixels[row][col];
}





void PNG::save( char* filename ){

	// Define the color type of this image to be RGBA
	png_byte color_type = PNG_COLOR_TYPE_RGBA;



	// Define the bit depth of the image
	png_byte bit_depth = BIT_DEPTH;
	


	// create a pointer instance to the image bytes
	png_bytep * row_pointers;



	// Try to open the png file with name 'filename'
	FILE * fp = fopen( filename, "wb" );



	// If the file could not be opened, exit the method
	if( !fp ){ return; }



	// Try to create png struct
	png_structp png = png_create_write_struct( PNG_LIBPNG_VER_STRING, 0, 0, 0 );



	// If the struct couldn't be created, exit the method
	if( !png ){ return; }



	// Try to create png info struct
	png_infop info = png_create_info_struct( png );



	// If the png info struct couldn't be made, exit the method
	if( !info ){ return; }



	// Exit the program if something is up with a jump buffer
	if( setjmp( png_jmpbuf( png ) ) ){ return; }



	// Initialize the png io stream
	png_init_io( png, fp );



	//Create the png header based on the
	// details provided earlier about the
	// image and the base setup conditions
	png_set_IHDR( 
		png,
		info,
		width, height,
		bit_depth,
		color_type,
		PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_DEFAULT,
		PNG_FILTER_TYPE_DEFAULT
		);



	// Write the png info to the file
	png_write_info( png, info );

	

	// Create the png byte array
	row_pointers = (png_bytep*)malloc( sizeof(png_bytep) * height );
	for( int i = 0; i < height; i++ ){
		row_pointers[i] = (png_byte*)malloc( png_get_rowbytes( png, info ) );
	}

	

	// Set values of the row pointers based on the PNG image
	// defined by this PNG object
	#if BIT_DEPTH == 8

		for( int row = 0; row < height; row++ ){
			png_bytep r = row_pointers[row];
			for( int col = 0; col < width; col++ ){
				png_bytep px = &(r[ col * 4 ]);

				px[0] = (TYPE)( pixels[row][col].red   * MAX_VAL);
				px[1] = (TYPE)( pixels[row][col].green * MAX_VAL);
				px[2] = (TYPE)( pixels[row][col].blue  * MAX_VAL);
				px[3] = (TYPE)( pixels[row][col].alpha * MAX_VAL);
			}
		}

	#else


		TYPE tred, tgreen, tblue, talpha;

		for( int row = 0; row < height; row++ ){
			png_bytep r = row_pointers[row];
			for( int col = 0; col < width; col++ ){
				png_bytep px = &(r[ col * 8 ]);

				tred   = (TYPE)( pixels[row][col].red   * MAX_VAL);
				tgreen = (TYPE)( pixels[row][col].green * MAX_VAL);
				tblue  = (TYPE)( pixels[row][col].blue  * MAX_VAL);
				talpha = (TYPE)( pixels[row][col].alpha * MAX_VAL);



				px[0] = tred & 0xff;
	            px[1] = ( tred >> 8 ) & 0xff;
				px[2] = tgreen & 0xff;
	            px[3] = ( tgreen >> 8 ) & 0xff;
				px[4] = tblue & 0xff;
	            px[5] = ( tblue >> 8 ) & 0xff;
				px[6] = talpha & 0xff;
	            px[7] = ( talpha >> 8 ) & 0xff;
			}
		}

	#endif



	// Write the image contents to file
	png_write_image( png, row_pointers );



	// End writing the png
	png_write_end( png, 0 );



	// Free up the row pointers memory
	for( int i = 0; i < height; i++ ){
		free( row_pointers[i] );
	}
	free( row_pointers );



	// Close the png file
	fclose( fp );
}







void PNG::load( char* filename ){

}





void PNG::clear(){
	if( pixels != 0 ){
		for( int i = 0; i < height; i++ ){
			delete [] pixels[i];
		}

		delete [] pixels;

		pixels = 0;
	}

	width = 0;
	height = 0;
}





void PNG::copy( PNG & img ){
	if( this != &img ){

		clear();

		int w = img.getWidth();
		int h = img.getHeight();

		width = w;
		height = h;

		pixels = new Pixel*[ height ];
		for( int i = 0; i < height; i++ ){
			pixels[i] = new Pixel[ width ];
			for( int j = 0; j < width; j++ ){
				pixels[i][j] = img(i,j);
			}
		}
	}
}