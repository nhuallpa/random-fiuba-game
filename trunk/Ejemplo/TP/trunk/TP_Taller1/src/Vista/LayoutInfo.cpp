#include "LayoutInfo.h"

#include <algorithm>

LayoutInfo::LayoutInfo (const Vec2& tamPreferido, const Vec2& tamMinimo,
                        bool infinitoHorizontal, bool infinitoVertical, bool mantenerAspecto)
	: tamMinimo(tamMinimo)
	, tamPreferido(tamPreferido)
	, infinitoHorizontal(infinitoHorizontal)
	, infinitoVertical(infinitoVertical)
	, mantenerAspecto(mantenerAspecto)
{
	if (this->tamMinimo.x < 1) this->tamMinimo.x = 1;
	if (this->tamMinimo.y < 1) this->tamMinimo.y = 1;

	if (this->tamPreferido.x <= this->tamMinimo.x)
		this->tamPreferido.x = this->tamMinimo.x + 1;
	if (this->tamPreferido.y <= this->tamMinimo.y)
		this->tamPreferido.y = this->tamMinimo.y + 1;
}

LayoutInfo::~LayoutInfo ()
{
}

Vec2 combinarHorizontal (const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(lhs.x + rhs.x, std::max(lhs.y, rhs.y));
}

Vec2 combinarVertical (const Vec2& lhs, const Vec2& rhs)
{
	return Vec2(std::max(lhs.x, rhs.x), lhs.y + rhs.y);
}

LayoutInfo LayoutInfo::combinar (const LayoutInfo& rhs, bool horizontal)
{
	LayoutInfo retval;

	if (horizontal) {
		retval.tamMinimo = combinarHorizontal(this->tamMinimo, rhs.tamMinimo);
		retval.tamPreferido = combinarHorizontal(this->tamPreferido, rhs.tamPreferido) + Vec2(1, 1);
	} else {
		retval.tamMinimo = combinarVertical(this->tamMinimo, rhs.tamMinimo);
		retval.tamPreferido = combinarVertical(this->tamPreferido, rhs.tamPreferido) + Vec2(1, 1);
	}
	retval.infinitoHorizontal = this->infinitoHorizontal || rhs.infinitoHorizontal;
	retval.infinitoVertical = this->infinitoVertical || rhs.infinitoVertical;

	return retval;
}

bool LayoutInfo::infinitoParalelo (bool horizontal)
{
	return horizontal ? infinitoHorizontal : infinitoVertical;
}

bool LayoutInfo::infinitoPerpendicular (bool horizontal)
{
	return horizontal ? infinitoVertical : infinitoHorizontal;
}
