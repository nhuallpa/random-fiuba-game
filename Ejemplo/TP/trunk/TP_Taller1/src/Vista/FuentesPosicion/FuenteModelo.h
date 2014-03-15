#ifndef FUENTEMODELO_H_
#define FUENTEMODELO_H_

#include "Modelo/EntidadWrapper.h"
#include "FuentePosicion.h"

class Canvas;
class Rect;
class Vec2;

class FuenteModelo : public FuentePosicion
{
public:
	FuenteModelo (Modelo::EntidadWrapper entidad, Canvas *canvas);
	FuenteModelo (const FuenteModelo& rhs) = default;
	FuenteModelo& operator= (const FuenteModelo&) = delete;
	virtual ~FuenteModelo ();

	virtual Rect getSuperficie () const;
	virtual void setSuperficie (const Rect& val);

	virtual Vec2 getTamPadre () const;
	virtual void padreResizeado (Vec2);

	virtual float getAngulo () const;
	virtual void setAngulo (float val);

	virtual bool getEstadoNormal () const;
	virtual void setEstadoNormal (bool val);

	Modelo::EntidadWrapper getEntidad();
	virtual FuentePosicion* clonar() const;

private:
	Modelo::EntidadWrapper entidad;
	Canvas *canvas;
};

#endif /* FUENTEMODELO_H_ */
