#ifndef FUENTEVENTANA_H_
#define FUENTEVENTANA_H_

#include "FuentePosicion.h"

class Ventana;

class FuenteVentana : public FuentePosicion
{
public:
	FuenteVentana (Ventana *ventana);
	FuenteVentana (const FuenteVentana& rhs);
	FuenteVentana& operator= (const FuenteVentana&) = delete;
	virtual ~FuenteVentana ();

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
	Ventana *ventana;
};

#endif /* FUENTEVENTANA_H_ */
