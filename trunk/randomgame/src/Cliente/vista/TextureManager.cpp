#include "TextureManager.h"


TextureManager::TextureManager(void) {
	this->screenWidth = 0;
	this->screenHeight = 0;
	this->firstTime = true;
}

void TextureManager::init(int w, int h)
{
	Log::i("TextureManager: Iniciando");
	TextureManager::Instance().setScreenSize(w, h);
}

void TextureManager::loadImages(std::map<std::string, std::string> map_images, SDL_Renderer * renderer)
{
	std::map<std::string, std::string>::iterator it;
	for (it=map_images.begin(); it!=map_images.end(); ++it) {
		try 
		{
			TextureManager::Instance().load(it->second.c_str(), it->first.c_str(), renderer);
		} catch (GameException & e) 
		{
			Log::e(BOOT, e.what());		
		}
	}
}

TextureManager::~TextureManager(void)
{
	std::map<std::string, SDL_Texture*>::iterator iter;
	for (iter = texture_map.begin(); iter!=texture_map.end(); ++iter)
	{
		SDL_DestroyTexture(iter->second);
	}
	texture_map.clear();

	std::map<std::string, SDL_Surface*>::iterator iterS;
	for (iterS = surface_map.begin(); iterS!=surface_map.end(); ++iterS)
	{
		SDL_FreeSurface(iterS->second);
	}
	surface_map.clear();
}

SDL_Texture* TextureManager::getTexture(std::string imageId)
{

	if (this->texture_map.find(imageId) != this->texture_map.end())
	{
		return this->texture_map[imageId];
	}
	else
	{
		std::stringstream msg;
		msg<<"TextureManager: Texture de ImagenID NO encontrada: "<<imageId;
		throw GameException(msg.str());
	}
}
SDL_Surface* TextureManager::getSurface(std::string imageId)
{

	if (this->surface_map.find(imageId) != this->surface_map.end())
	{
		return this->surface_map[imageId];
	}
	else
	{
		std::stringstream msg;
		msg<<"TextureManager: Surface de ImagenID NO encontrada: "<<imageId;
		throw GameException(msg.str());
	}
}

void TextureManager::setScreenSize(int w, int h)
{
	this->screenWidth = w;
	this->screenHeight = h;
}

bool TextureManager::load(std::string fileName,std::string id, SDL_Renderer* pRenderer, bool keepSurface)
{
	SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());

	SDL_Texture* newTexture = SDL_CreateTextureFromSurface(pRenderer, tmpSurface);

	if (keepSurface) {
		surface_map[id] = tmpSurface;	
	} else {
		SDL_FreeSurface(tmpSurface);
	}
	if (newTexture)
	{
		this->texture_map[id]=newTexture;

		
		return true;
	} 
	else 
	{
		std::stringstream msg;
		msg<<"TextureManager: Imagen NO encontrada: "<<fileName;
		throw GameException(msg.str());
	}
	return false;
}

bool TextureManager::loadStream(std::string fileName,std::string id, SDL_Renderer* pRenderer)
{
	/*this is filled in with a pointer to the locked pixels, appropriately offset by the locked area*/
	void* mPixels;

	/*Amount of bytes betweed rows */
	int mPitch;

	SDL_Surface* tmpSurface = IMG_Load(fileName.c_str());
	SDL_Texture* newTexture = NULL;
	if( tmpSurface == NULL )
	{
		Log::e( "Unable to load image %s! SDL_image Error: %s\n", fileName.c_str(), IMG_GetError() );
	} else {

		SDL_Surface* formattedSurface = SDL_ConvertSurfaceFormat( tmpSurface, SDL_PIXELFORMAT_RGBA8888, NULL );
		if( formattedSurface == NULL )
		{
			Log::e( "Unable to convert loaded surface to display format! %s\n", SDL_GetError() );
		}
		else
		{
			newTexture = SDL_CreateTexture(pRenderer, 
													SDL_PIXELFORMAT_RGBA8888, 
													SDL_TEXTUREACCESS_STREAMING, 
													formattedSurface->w, 
													formattedSurface->h );
			if( newTexture == NULL )
			{
				SDL_FreeSurface(formattedSurface);	
				Log::e( "Unable to create blank texture! SDL Error: %s\n", SDL_GetError() );
			}
			else
			{
				//Lock texture for manipulation
				//SDL_LockTexture( newTexture, NULL, &mPixels, &mPitch );

				//memcpy( mPixels, formattedSurface->pixels, mPitch * formattedSurface->h );

				////Unlock texture to update
				//SDL_UnlockTexture( newTexture );
				//mPixels = NULL;


				SDL_UpdateTexture(newTexture,NULL, formattedSurface->pixels, formattedSurface->pitch);

				surface_map[id] = formattedSurface;	
			}
		}
		SDL_FreeSurface(tmpSurface);	
	}
	if (newTexture)
	{
		this->texture_map[id]=newTexture;
		return true;
	} 
	else 
	{
		std::stringstream msg;
		msg<<"TextureManager: No se pudo crear el Texture para : "<<fileName;
		throw GameException(msg.str());
	}
	return false;
}

void TextureManager::draw(std::string id, int x, int y, 
					SDL_Renderer* pRenderer, SDL_RendererFlip flip) 
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	try {
		SDL_Texture * aTexture = getTexture(id);

		SDL_QueryTexture(aTexture, NULL, NULL,
		&srcRect.w, &srcRect.h);

		srcRect.x = 0;
		srcRect.y = 0;
	
		destRect.w = srcRect.w;
		destRect.h = srcRect.h;

		destRect.x = x;
		destRect.y = y;

		SDL_RenderCopyEx(pRenderer, aTexture, &srcRect,&destRect, 0, 0, flip);
	} catch (GameException & e) {
		Log::e(e.what());
	}

}

void TextureManager::draw(std::string id, int x, int y, int width, int
	height, SDL_Renderer* pRenderer, SDL_RendererFlip flip) 
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = 0;
	srcRect.y = 0;
	
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;

	try {
		SDL_RenderCopyEx(pRenderer, getTexture(id), &srcRect,&destRect, 0, 0, flip);
	} catch (GameException & e) {
		Log::e(e.what());
	}
}

void TextureManager::drawScrollableBackground(std::string imageId, SDL_Renderer* pRenderer) 
{
	SDL_Rect srcRect;
	SDL_Rect destRect;

	srcRect.x = this->cam.getX();
	srcRect.y = this->cam.getY();

	destRect.w = srcRect.w = this->cam.getW();
	destRect.h = srcRect.h = this->cam.getH();

	destRect.x = 0;
	destRect.y = 0;

	try {
		SDL_Texture * aTexture = getTexture(imageId);
		SDL_RenderCopyEx(pRenderer, aTexture, &srcRect,&destRect, 0, 0, SDL_FLIP_NONE);
	} catch (GameException & e) {
		Log::e(e.what());
	}
}

void TextureManager::drawBackground(std::string id, SDL_Renderer* pRenderer, SDL_RendererFlip flip) 
{
	try {
		SDL_RenderCopy(pRenderer, getTexture(id), 0, 0);
	} catch (GameException & e) {
		Log::e(e.what());
	}
}

void TextureManager::drawFrame(std::string id, int x, int y, int width, int	height, 
								int currentRow, int currentFrame, 
								SDL_Renderer*	pRenderer, bool grey, SDL_RendererFlip flip) 
{	
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Rect viewPort;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x - this->cam.getX();
	destRect.y = y - this->cam.getY();
	
	viewPort.x = 0;
	viewPort.y = 0;
	viewPort.w = this->cam.getW();
	viewPort.h = this->cam.getH();
	try {
		if (grey) SDL_SetTextureColorMod(getTexture(id),100,100,100);
		if (intersectRects(destRect, viewPort)) {
			SDL_RenderCopyEx(pRenderer, getTexture(id), &srcRect,&destRect, 0, 0, flip);
		}
		if (grey) SDL_SetTextureColorMod(getTexture(id),255,255,255);
	} catch (GameException & e) {
		Log::e(e.what());
	}
}


void TextureManager::drawFrameOnScreen(std::string id, int x, int y, int width, int
					height, int currentRow, int currentFrame, SDL_Renderer*
					pRenderer,bool grey, SDL_RendererFlip flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	SDL_Rect viewPort;
	srcRect.x = width * currentFrame;
	srcRect.y = height * currentRow;
	
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;

	destRect.x = x;
	destRect.y = y;
	
	viewPort.x = 0;
	viewPort.y = 0;
	viewPort.w = this->cam.getW();
	viewPort.h = this->cam.getH();
	//if (grey) SDL_SetTextureColorMod(this->texture_map[id],100,100,100);
	try {
		if (intersectRects(destRect, viewPort)) {
			SDL_RenderCopyEx(pRenderer, getTexture(id), &srcRect,&destRect, 0, 0, flip);
		}
	} catch (GameException & e) {
		Log::e(e.what());
	}
	//if (grey) SDL_SetTextureColorMod(this->texture_map[id],255,255,255);
}

std::pair<int, int> TextureManager::getDimension(std::string imageId)
{
	SDL_Rect rect;
	SDL_QueryTexture(this->texture_map[imageId], NULL, NULL,	&rect.w, &rect.h);
	std::pair<int, int> dimension = std::make_pair(rect.w, rect.h);
	return dimension;
}


void TextureManager::drawCircle(SDL_Renderer * renderer, 
								Sint16 x, 
								Sint16 y, 
								Sint16 r, 
								Uint32 color, 
								Uint32 borderColor)
{
	filledCircleColor(renderer,
						y,
						y,
						r,
						color);

	aacircleColor(renderer,
						y,
						y,
						r,
						borderColor);
}

void TextureManager::drawEllipse(SDL_Renderer * renderer, 
								Sint16 x, 
								Sint16 y, 
								Sint16 rx, 
								Sint16 ry, 
								Uint32 color, 
								Uint32 borderColor)
{
	x = x - this->cam.getX();
	y = y - this->cam.getY();

	filledEllipseColor(renderer,
						x,
						y,
						rx,
						ry,
						color);

	aaellipseColor(renderer,
						x,
						y,
						rx,
						ry,
						borderColor);
}

void TextureManager::drawText(SDL_Renderer * renderer,Sint16 x, Sint16 y,std::string text , Uint32 color){
	x = x - this->cam.getX();
	y = y - this->cam.getY();
	stringColor(renderer,x,y,text.c_str(),color);
}


void TextureManager::drawBox(SDL_Renderer * renderer, Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, Uint32 color)
{
	x1 = x1 - this->cam.getX();
	y1 = y1 - this->cam.getY();
	x2 = x2 - this->cam.getX();
	y2 = y2 - this->cam.getY();
	boxColor(renderer,
				x1, y1,
				x2, y2, color);
}

void TextureManager::drawPolygon(SDL_Renderer * renderer, 
								Sint16 * vx, 
								Sint16 * vy, 
								int n, 
								Uint32 color, 
								Uint32 borderColor)
{
	int i = 0;
	for (i=0; i<n; i++) 
	{
		vx[i] = vx[i] - this->cam.getX();
		vy[i] = vy[i] - this->cam.getY();
	}

	filledPolygonColor(renderer,
				vx,
				vy,
				n,
				color);

	polygonColor(renderer,
				vx,
				vy,
				n,
				borderColor);
}


bool TextureManager::intersectRects(SDL_Rect one, SDL_Rect two)
{
	SDL_bool hasIntersec = SDL_HasIntersection(&one, &two);
	if (hasIntersec == SDL_TRUE) 
	{
		return true;
	}
	else
	{
		return false;
	}
}


SDL_Point TextureManager::convertPointScreen2SDL(int x, int y)
{
	SDL_Point clickPoint;
	float kX = (float)this->getCamera().getW() / this->getScreenWidth();
	float kY = (float)this->getCamera().getH() / this->getScreenHeight();

	clickPoint.x = x * kX;
	clickPoint.y = y * kY;

	return clickPoint;
}


tPoint TextureManager::convertPointUL2PXSDL(float x, float y)
{
	tPoint aPoint;
	int heightScreen = this->getCamera().getHeightScenario();

	aPoint.x = (int)(x * (float)ESCALA_UL2PX);
	aPoint.y = (int)(heightScreen - (y * (float)ESCALA_UL2PX));	

	return aPoint;
}

void TextureManager::putPixel32( SDL_Surface *surface, int x, int y, Uint32 pixel )
{

    Uint32 *pixels = (Uint32 *)surface->pixels;
    
    pixels[ ( y * surface->w ) + x ] = pixel;
}

void TextureManager::drawCircleOn(SDL_Surface *surface, int centerX, int centerY, int radius, Uint32 pixel)
{
    // if the first pixel in the screen is represented by (0,0) (which is in sdl)
    // remember that the beginning of the circle is not in the middle of the pixel
    // but to the left-top from it:
 
    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = centerX - 0.5;
    double cy = centerY - 0.5;
 
    while (x >= y)
    {
        putPixel32(surface, (int)(cx + x), (int)(cy + y), pixel);
        putPixel32(surface, (int)(cx + y), (int)(cy + x), pixel);
 
        if (x != 0)
        {
            putPixel32(surface, (int)(cx - x), (int)(cy + y), pixel);
            putPixel32(surface, (int)(cx + y), (int)(cy - x), pixel);
        }
 
        if (y != 0)
        {
            putPixel32(surface, (int)(cx + x), (int)(cy - y), pixel);
            putPixel32(surface, (int)(cx - y), (int)(cy + x), pixel);
        }
 
        if (x != 0 && y != 0)
        {
            putPixel32(surface, (int)(cx - x), (int)(cy - y), pixel);
            putPixel32(surface, (int)(cx - y), (int)(cy - x), pixel);
        }
 
        error += y;
        ++y;
        error += y;
 
        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}

/*cx and cy are center points*/
void TextureManager::fillCircleOn(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{
 
	int w_imagen = surface->w;
	int h_imagen = surface->h;

    static const int BPP = 4;
 
    double r = (double)radius;
 
    for (double dy = 1; dy <= r; dy += 1.0) // media circunferencias superior
    {
        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));  // ancho en cada pixel y al centro

		//int x_col_left = cx - dx;
        int x = cx - dx; // old
		Log::t("Ancho fila circulo %f", dx);
		// validar que los pixeles se modifiquen dentro del

		// row_top = (cy - r + dy) * surface->pitch // Borde arriba hacia abajo
		// row_bottom = (cy + r - dy) * surface->pitch// Borde abajo hacia arriba   
        Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;
 
		// col_right = cx + dx;
        for (; x <= cx + dx; x++)
        {
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
        }
    }
}

void TextureManager::fillCircleOn(std::string imageId, int x, int y, int radius, Uint32 pixel)
{
	try
	{
		SDL_Texture* texture = this->getTexture(imageId);
		SDL_Surface* surface = this->getSurface(imageId);

		TextureManager::Instance().fillCircleOn(surface, x, y, radius, pixel);

		if (SDL_UpdateTexture(texture,NULL,surface->pixels,surface->pitch) < 0){
			Log::e("SDL_UpdateTexture Fail");
		}


	}
	catch (GameException & e) {
		Log::e(e.what());
		this->texture_map[imageId]=NULL;
	}
}