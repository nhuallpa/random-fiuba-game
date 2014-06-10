#include "TextManager.h"

void TextManager::init(SDL_Renderer * renderer){
	this->renderer = renderer;
}


void TextManager::loadFont(Tfont fuente){
	std::string path;
	std::string idFont;
	int h;
	int w;
	int letterH;
	int letterW;
	
	stFont font;

	if (fuente == Arial16){
		path = ARIAL16;
		idFont = "arial16";
		h = 256;
		w = 256;
		letterH = 16;
		letterW = 16;
	}
	if (fuente == Arial12){
		path = ARIAL12;
		idFont = "arial12";
		h = 192;
		w = 192;
		letterH = 12;
		letterW = 12;
	
	}

	
	font.idFont = idFont;
	font.alto = h;
	font.ancho = w;
	font.altoLetra = letterH;
	font.anchoLetra = letterW;

	TextureManager::Instance().load(path,idFont, this->renderer);
	this->font_map[idFont] = font;

}

void TextManager::wLetter(std::string idFont,int x, int y, char lett,Uint8 r,Uint8 g,Uint8 b){
	SDL_Rect destino, origen; 
	int fila, columna;
	int letrasPorFila, letrasPorColumna;

	font = this->font_map.find(idFont)->second;


	letrasPorFila = font.ancho/font.anchoLetra;
	letrasPorColumna = font.alto/font.altoLetra;
	fila = lett / letrasPorColumna;
	columna = lett % letrasPorColumna;
	origen.x = columna * font.anchoLetra;
	origen.y = fila * font.altoLetra;
	
	origen.w = font.anchoLetra;
	origen.h = font.altoLetra;
	destino.x = x;
	destino.y = y;
	destino.w = origen.w;
	destino.h = origen.h;
	try 
	{
	
	Log::t("fuente: %p",TextureManager::Instance().getTexture(idFont));
	
	SDL_RenderCopy(this->renderer,
                   TextureManager::Instance().getTexture(idFont),
                   &origen,
                   &destino);
	} catch (std::exception &e) {
		Log::e(e.what());
	}
	

}

void TextManager::write(Tfont fuente,int x, int y, std::string w,SDL_Color color){
	int i;
	std::string idFont;
	if (fuente == Arial16){
		idFont = "arial16";
	}
	if (fuente == Arial12){
		idFont = "arial12";	
	}


	for(i =0; i<w.size();i++){
		this->wLetter(idFont,x+(i*this->font.anchoLetra),y,w[i],color.r,color.g,color.b);
	}
}