#ifndef FUENTEFUNCION_H_
#define FUENTEFUNCION_H_

#include "Utils/Rect.h"
#include "Utils/Vec2.h"
#include "Vista/FuentesPosicion/FuentePosicion.h"
#include <functional>

class FuenteFuncion : public FuentePosicion
{
public:
	FuenteFuncion(std::function<Rect()> sup,
	              std::function<float()> angulo,
	              std::function<bool()> estadoNormal,
	              std::function<Vec2()> padre);
	FuenteFuncion (const FuenteFuncion& rhs);
	FuenteFuncion& operator= (const FuenteFuncion&) = delete;
	virtual ~FuenteFuncion();

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
	std::function<Rect()> sup;
	std::function<float()> angulo;
	std::function<bool()> estadoNormal;
	std::function<Vec2()> padre;
};

#endif /* FUENTEFUNCION_H_ */
