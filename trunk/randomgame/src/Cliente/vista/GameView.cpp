#include "GameView.h"


GameView::GameView(int x, int y, int width, int height)
								: ViewGroup(x, y,width, height)
{
	eart = NULL; 
	sky = NULL;
	water = NULL;
}


GameView::~GameView(void)
{

}

void GameView::putFigure(int id, FigureView* figure)
{
	figures[id] = figure;
	this->add(figure);
}
void GameView::putWorm(int id, WormView* worm)
{
	worms[id] = worm;
	this->add(worm);
}
void GameView::setEart(EartView* eart)
{
	this->eart = eart;
	this->add(eart);
}
void GameView::setSky(SkyView* sky)
{
	this->sky = sky;
	this->add(sky);
}
void GameView::setWater(WaterView* water)
{
	this->water = water;
	this->add(water);
}

void GameView::setTerrain(TerrainView* terrain) 
{
	this->terrain = terrain;
	this->add(water);
}

FigureView* GameView::findFigureById(int idElement)
	
{
	if (figures.find(idElement) != figures.end())
	{
		return figures[idElement];
	} 
	else 
	{
		std::stringstream msg;
		msg<<"GameView: not found figure view by id: "<<idElement;
		throw GameException(msg.str());
	}
}
WormView* GameView::findWormById(int idElement)
{
	if (worms.find(idElement) != worms.end())
	{
		return worms[idElement];
	} 
	else 
	{
		std::stringstream msg;
		msg<<"GameView: not found worm view by id: "<<idElement;
		throw GameException(msg.str());
	}
}