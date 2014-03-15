#ifndef INFOFIGURAS_H_
#define INFOFIGURAS_H_

#include "Modelo/TipoElemento.h"
#include "Utils/Vec2.h"
#include <string>
#include <map>

namespace vista {

struct InfoFiguras
{
	Modelo::TipoElemento tipo;
	std::string pathImagenToolbar;
	std::string pathImagenCanvas;
	Vec2 tamCanvas;
	float anguloCanvas;


	InfoFiguras ();
	InfoFiguras (Modelo::TipoElemento, std::string, std::string, Vec2, float);

	InfoFiguras (const InfoFiguras&) = default;
	InfoFiguras (InfoFiguras&&) = default;
	InfoFiguras& operator= (const InfoFiguras&) = default;
	InfoFiguras& operator= (InfoFiguras&&) = default;
	~InfoFiguras() = default;

	static std::map<Modelo::TipoElemento, InfoFiguras> datos;
};

} /* namespace vista */
#endif /* INFOFIGURAS_H_ */
