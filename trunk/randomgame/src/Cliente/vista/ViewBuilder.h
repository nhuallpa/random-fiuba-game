#pragma once

#ifndef __VIEW_BUILDER_H__
#define __VIEW_BUILDER_H__
#include "ViewGroup.h"
#include "FigureViewGroup.h"
class ViewBuilder
{
public:
	ViewBuilder(void);

	/**
	* Build a view group to store a many views
	* @return ViewGroup a view group
	*/
	virtual ViewGroup* buildContainer() = 0;

	/**
	* Build a view group to store a many figures
	* @return ViewGroup a view group
	*/
	virtual FigureViewGroup* buildFigureContainer() = 0;

	/**
	* Build a sky view and add it to container
	* @param ViewGroup a container
	*/
	virtual void buildSky(ViewGroup* container) = 0;

	/**
	* Build many figures of view and add it to container
	* @param ViewGroup a container
	*/
	virtual void buildFigures(FigureViewGroup* container) = 0;

	/**
	* Build many figures of view and add it to container
	* @param ViewGroup a container
	*/
	virtual void buildCharacters(ViewGroup* container) = 0;


	/**
	* Build a water view and add it to container
	* @param ViewGroup a container
	*/
	virtual void buildWater(ViewGroup* container) = 0;

	/**
	* Build a terrain view and add it to container
	* @param ViewGroup a container
	*/
	virtual void buildTerrain(ViewGroup* container) = 0;


	virtual void buildEart(ViewGroup* container)=0;

	~ViewBuilder(void);
};

#endif /**__VIEW_BUILDER_H__*/

