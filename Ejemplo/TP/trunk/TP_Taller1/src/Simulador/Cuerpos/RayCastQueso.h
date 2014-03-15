/*
 * RayCastClosestCallback.h
 *
 *  Created on: Nov 28, 2013
 *      Author: lucia
 */

#ifndef RAYCASTQUESO_H_
#define RAYCASTQUESO_H_

#include <Box2D/Box2D.h>
#include <set>
#include "../Cuerpo.h"

namespace simulador {
class RayCastQueso : public b2RayCastCallback
{
public:
	RayCastQueso(Modelo::EntidadWrapper motorRaton);

	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,
		const b2Vec2& normal, float32 fraction);

	RayCastQueso (const RayCastQueso&) = delete;
	RayCastQueso& operator= (const RayCastQueso&) = delete;
	virtual ~RayCastQueso();

	bool veQueso();

private:
	b2Body* cuerpoChocado;
	bool m_hit;
	b2Vec2 m_point;
	b2Vec2 m_normal;
	Modelo::EntidadWrapper entidadVisora;
	static std::set<Modelo::TipoElemento> transparentes;

};
}
#endif /* RAYCASTQUESO_H_ */
