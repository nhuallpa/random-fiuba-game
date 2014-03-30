#pragma once

#ifndef __VIEW_BUILDER_H__
#define __VIEW_BUILDER_H__
#include "ViewGroup.h"
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
	* Build a sky view and add it to container
	* @param ViewGroup a container
	*/
	virtual void buildSky(ViewGroup* container) = 0;

	/**
	* Build many figures of view and add it to container
	* @param ViewGroup a container
	*/
	virtual void buildFigures(ViewGroup* container) = 0;

	/**
	* Build a water view and add it to container
	* @param ViewGroup a container
	*/
	virtual void buildWater(ViewGroup* container) = 0;

	~ViewBuilder(void);
};

#endif /**__VIEW_BUILDER_H__*/

