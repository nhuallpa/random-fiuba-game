#ifndef FUENTEPOSICION_H_
#define FUENTEPOSICION_H_

class Vec2;
class Rect;

class FuentePosicion
{
public:
	virtual ~FuentePosicion () {}

	virtual Rect getSuperficie () const = 0;
	virtual void setSuperficie (const Rect& val) = 0;

	virtual Vec2 getTamPadre () const = 0;
	virtual void padreResizeado (Vec2) = 0;

	virtual float getAngulo () const = 0;
	virtual void setAngulo (float val) = 0;

	virtual bool getEstadoNormal () const = 0;
	virtual void setEstadoNormal (bool val) = 0;

	virtual FuentePosicion* clonar() const = 0;
};

#endif /* FUENTEPOSICION_H_ */
