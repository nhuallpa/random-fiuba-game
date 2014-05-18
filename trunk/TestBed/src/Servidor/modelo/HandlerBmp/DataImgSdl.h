#ifndef DataImgSdl_H
#define DataImgSdl_H

#include <list>
#include <vector>
#include "C:\random-fiuba-game\TestBed\libs\SDL2-2.0.0\include\SDL.h"
#include "C:\random-fiuba-game\TestBed\libs\SDL2_image-2.0.0\include\SDL_image.h"
#include "C:\random-fiuba-game\TestBed\libs\SDL2-2.0.0\include\SDL_surface.h"
#include "DataBmp.h"
#include "ColorRgb.h"
#include "PixelBmp.h"


using namespace std;

class DataImgSdl : public DataBmp
{
private:

	SDL_Surface *surface;
	ColorRgb *getPixel(Uint32 *pixels,int x, int y );
	int getAlpha(Uint32 *pixels,int x, int y );
public:
	DataImgSdl(char* path);
	DataImgSdl();
	virtual ~DataImgSdl();

protected:
		void loadMatrix(char* data,int row_padded=0, int height=0, int width=0);


};

#endif // DataImgSdl_H
