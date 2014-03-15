#ifndef FALSAFIGURA_H_
#define FALSAFIGURA_H_

#include "Vista/Imagen.h"
#include "Vista/FiguraVista.h"
#include "Vista/Texto.h"
#include "Vista/Interfases/Elemento.h"

class FuentePosicion;

namespace vista {

// Recibe clicks como un rectangulo, clona como una FiguraVista arbitraria. Para la toolbar.
class FalsaFigura : public Elemento
{
public:
	FalsaFigura (const FuentePosicion& fuente, Modelo::TipoElemento tipo, Dibujable *dib, size_t cantidad);

	FalsaFigura (const FalsaFigura&) = default;
	FalsaFigura (FalsaFigura&&) = default;
	FalsaFigura& operator= (const FalsaFigura&) = default;
	FalsaFigura& operator= (FalsaFigura&&) = default;
	virtual ~FalsaFigura();

	virtual void setSuperfice (const Rect& val);
	virtual void dibujarse (DestinoDibujo* window);
	virtual bool dirty ();

	virtual LayoutInfo getLayoutInfo ();

	virtual ClickInfo recibirClick (Vec2 pos);
	virtual Elemento* clonar () const;

	Modelo::TipoElemento getTipo () const;
	void setCantidad (size_t cantidad);

private:
	Modelo::TipoElemento tipo;
	Imagen imagen;
	Texto numero;
	FiguraVista real;
	size_t cantidad;
};

} /* namespace vista */
#endif /* FALSAFIGURA_H_ */
