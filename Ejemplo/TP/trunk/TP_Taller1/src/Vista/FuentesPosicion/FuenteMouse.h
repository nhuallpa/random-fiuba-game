#ifndef FUENTEMOUSE_H_
#define FUENTEMOUSE_H_

#include "Vista/FuentesPosicion/FuentePosicion.h"
#include "Utils/Rect.h"
#include "Utils/Vec2.h"

namespace controlador {
	class Mouse;
}
class Ventana;

class FuenteMouse : public FuentePosicion
{
public:
	FuenteMouse ();
	FuenteMouse (const Ventana *ventana, const controlador::Mouse *mouse,
	             FuentePosicion* fuenteVieja);
	FuenteMouse (const FuenteMouse &rhs);
	FuenteMouse& operator= (const FuenteMouse&) = delete;
	virtual ~FuenteMouse ();

	virtual Rect getSuperficie () const;
	virtual void setSuperficie (const Rect& val);

	virtual Vec2 getTamPadre () const;
	virtual void padreResizeado (Vec2);

	virtual float getAngulo () const;
	virtual void setAngulo (float val);

	virtual bool getEstadoNormal () const;
	virtual void setEstadoNormal (bool val);

	virtual FuentePosicion* clonar() const;

	// Publicos por serializacion
	Rect superficieBase;
	float angulo;
	bool estadoNormal;

private:
	const Ventana *ventana;
	const controlador::Mouse *mouse;
};

#endif /* FUENTEMOUSE_H_ */
