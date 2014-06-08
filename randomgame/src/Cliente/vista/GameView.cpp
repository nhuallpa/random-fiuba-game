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

void GameView::setWormContainer(WormViewGroup * wormViewGroup)
{
	this->wormViewGroup = wormViewGroup;
	this->add(wormViewGroup);
}

void GameView::setProjectileContainer(ProjectileViewGroup * projectileViewGroup)
{
	this->projectileViewGroup = projectileViewGroup;
	this->add(projectileViewGroup);
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

void GameView::setStateBar(StateBarView* stateBar)
{
	this->stateBar = stateBar;
	this->add(stateBar);
}

void GameView::setMenuWeapon(MenuWeaponView* menuWeapon)
{
	this->menuWeapon = menuWeapon;
	this->add(menuWeapon);
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
	return this->wormViewGroup->findById(idElement);
}


void GameView::getDestroyEart(int x, int y, int radio)
{
	this->eart->drawExplotion(x, y, radio);
}

void GameView::actionMenu(){
	this->menuWeapon->actionMenu();
}

bool GameView::hasClickedMenu(SDL_Point clickPoint){
	return this->menuWeapon->hasClickedMenu(clickPoint);
}

bool GameView::hasClickedWeapon(SDL_Point clickPoint){
	return this->menuWeapon->hasClickedWeapon(clickPoint);
}

Weapon* GameView::retrieveWeaponClicked(SDL_Point clickPoint){
	return this->menuWeapon->retrieveWeaponClicked(clickPoint);
}

Weapon* GameView::findWeaponById(int idWeapon){
	return this->menuWeapon->findWeaponById(idWeapon);
}