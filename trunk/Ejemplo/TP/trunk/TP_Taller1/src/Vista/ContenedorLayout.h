#ifndef CONTENEDORLAYOUT_H_
#define CONTENEDORLAYOUT_H_

#include "Vista/Contenedor.h"
#include <utility>
#include <vector>

class ContenedorLayout : public Contenedor
{
public:
	ContenedorLayout (const FuentePosicion& fuente, Dibujable* destino, bool horizontal);
	virtual ~ContenedorLayout ();

	virtual LayoutInfo getLayoutInfo();
	virtual void resized (Vec2 tam);

	void setSeparacion (float fraccion);

private:
	bool horizontal;
	float separacion;

	virtual void regenerar();
	void recalcularDimensiones();
	std::pair<float, std::vector<Rect>> realizarLayout(float separacion, float extension);
	void commitLayout(std::vector<Rect>&& tamanios);
	std::vector<vista::Elemento*> elementosLayouteables ();
};

#endif /* CONTENEDORLAYOUT_H_ */
