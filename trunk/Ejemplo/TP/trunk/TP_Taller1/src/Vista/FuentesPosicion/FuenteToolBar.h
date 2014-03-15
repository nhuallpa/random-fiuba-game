/*
 * FuenteToolBar.h
 *
 *  Created on: 21/09/2013
 *      Author: stephanie
 */

#ifndef FUENTETOOLBAR_H_
#define FUENTETOOLBAR_H_

#include "FuentePosicion.h"
#include "Utils/Rect.h"

class ToolBar;

class FuenteToolBar: public FuentePosicion{
public:
	FuenteToolBar(ToolBar* toolbar);
	FuenteToolBar(const FuenteToolBar& rhs);
	FuenteToolBar& operator= (const FuenteToolBar&) = delete;
	virtual ~FuenteToolBar();

	virtual Rect getSuperficie () const;
	virtual void setSuperficie (const Rect& val);

	virtual Vec2 getTamPadre () const;
	virtual void padreResizeado (Vec2);

	virtual float getAngulo () const;
	virtual void setAngulo (float val);

	virtual bool getEstadoNormal () const;
	virtual void setEstadoNormal (bool val);

	virtual FuentePosicion* clonar() const;

private:
	ToolBar* toolbar;
	Rect superficie;
};

#endif /* FUENTETOOLBAR_H_ */
