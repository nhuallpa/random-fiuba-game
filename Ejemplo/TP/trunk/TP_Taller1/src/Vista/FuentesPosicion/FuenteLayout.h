#ifndef FUENTELAYOUT_H_
#define FUENTELAYOUT_H_

#include "FuentePosicion.h"
#include "Utils/Rect.h"

class FuenteLayout : public FuentePosicion
{
public:
	FuenteLayout (const Vec2& tamPadre = Vec2(100, 100));
	FuenteLayout (const FuenteLayout& rhs);
	FuenteLayout& operator= (const FuenteLayout&) = delete;
	virtual ~FuenteLayout ();

	virtual Rect getSuperficie () const;
	virtual void setSuperficie (const Rect& val);

	virtual Vec2 getTamPadre () const;
	virtual void padreResizeado (Vec2 nTam);

	virtual float getAngulo () const;
	virtual void setAngulo (float val);

	virtual bool getEstadoNormal () const;
	virtual void setEstadoNormal (bool val);

	virtual FuentePosicion* clonar() const;

private:
	Vec2 tamPadre;
	Rect superficie;
};

#endif /* FUENTELAYOUT_H_ */
