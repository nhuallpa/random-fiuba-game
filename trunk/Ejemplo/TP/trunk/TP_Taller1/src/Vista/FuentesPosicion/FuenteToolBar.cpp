/*
 * FuenteToolBar.cpp
 *
 *  Created on: 21/09/2013
 *      Author: stephanie
 */

#include "FuenteToolBar.h"

#include "Vista/ToolBar.h"

FuenteToolBar::FuenteToolBar(ToolBar* toolbar)
	: toolbar(toolbar)
	, superficie()
{
}

FuenteToolBar::FuenteToolBar(const FuenteToolBar& rhs)
	: toolbar(rhs.toolbar)
	, superficie(rhs.superficie)
{
}

FuenteToolBar::~FuenteToolBar() {
}

Rect FuenteToolBar::getSuperficie () const
{
	return superficie;
}

void FuenteToolBar::setSuperficie (const Rect& sup)
{
	superficie = sup;
}

float FuenteToolBar::getAngulo () const
{
	return 0.0f;
}

void FuenteToolBar::setAngulo (float)
{
}

bool FuenteToolBar::getEstadoNormal () const
{
	return true;
}

void FuenteToolBar::setEstadoNormal (bool)
{
}

Vec2 FuenteToolBar::getTamPadre () const
{
	return toolbar->getSuperficie().tam();
}

void FuenteToolBar::padreResizeado (Vec2)
{
}

FuentePosicion *FuenteToolBar::clonar() const{
	return new FuenteToolBar(*this);
}
