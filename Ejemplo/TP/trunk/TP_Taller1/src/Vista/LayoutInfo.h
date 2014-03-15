#ifndef LAYOUTINFO_H_
#define LAYOUTINFO_H_

#include "Utils/Vec2.h"

struct LayoutInfo
{
	explicit LayoutInfo (const Vec2& tamPreferido = Vec2(1, 1),
	                     const Vec2& tamMinimo = Vec2(1, 1),
	                     bool infinitoHorizontal = false,
	                     bool infintoVertical = false,
	                     bool mantenerAspecto = false);
	virtual ~LayoutInfo ();

	// parametros de usuario
	Vec2 tamMinimo;
	Vec2 tamPreferido;
	bool infinitoHorizontal;
	bool infinitoVertical;
	bool mantenerAspecto;

	// para facilitar layout
	LayoutInfo combinar (const LayoutInfo& rhs, bool horizontal);
	bool infinitoParalelo (bool horizontal);
	bool infinitoPerpendicular (bool horizontal);
};

#endif /* LAYOUTINFO_H_ */
