#include "TextManager.h"

void TextManager::init(SDL_Renderer * renderer){
	this->renderer = renderer;
}


void TextManager::loadFont(std::string path,std::string idFont,int h,int w,int letterH,int letterW){
	stFont font;
	font.idFont = idFont;
	font.alto = h;
	font.ancho = w;
	font.altoLetra = letterH;
	font.anchoLetra = letterW;

	TextureManager::Instance().load(path, this->font.idFont, this->renderer);
	this->font_map[idFont] = font;

}

void TextManager::wLetter(std::string idFont,int x, int y, char lett){
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
	Log::i("fuente: %p",TextureManager::Instance().getTexture(idFont));
	SDL_RenderCopy(this->renderer,
                   TextureManager::Instance().getTexture(idFont),
                   &origen,
                   &destino);
}