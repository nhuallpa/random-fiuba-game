#include "ContenedorLayout.h"

#include "Vista/LayoutInfo.h"
#include "Vista/FuentesPosicion/FuenteLayout.h"
#include "Utils/iteracion.h"
#include <algorithm>
#include <vector>

ContenedorLayout::ContenedorLayout (const FuentePosicion& fuente, Dibujable* destino, bool horizontal)
	: Contenedor(fuente, destino)
	, horizontal(horizontal)
	, separacion(0.0)
{
}

ContenedorLayout::~ContenedorLayout ()
{
}

LayoutInfo ContenedorLayout::getLayoutInfo()
{
	LayoutInfo retval;
	auto elementos = elementosLayouteables();

	for (auto& elemento : invertir_iteracion(elementos)) {
		retval = retval.combinar(elemento->getLayoutInfo(), horizontal);
	}

	int cantidadSeparaciones = elementos.size() - 1;
	float multiplicadorSeparacion = 1.0 + std::max(0.0f, separacion * cantidadSeparaciones);
	if (horizontal) {
		retval.tamPreferido.x *= multiplicadorSeparacion;
	} else {
		retval.tamPreferido.y *= multiplicadorSeparacion;
	}

	return retval;
}

void ContenedorLayout::setSeparacion(float fraccion)
{
	separacion = fraccion;
}

void ContenedorLayout::resized (Vec2 tam)
{
	recalcularDimensiones();
}

void ContenedorLayout::regenerar()
{
	recalcularDimensiones();
	Contenedor::regenerar();
}

void ContenedorLayout::recalcularDimensiones()
{
	Vec2 tamContenedor(getSuperficie().tam());
	auto elementos = elementosLayouteables();

	float tamParalelo = horizontal ? tamContenedor.x : tamContenedor.y;
	auto layout = realizarLayout(0, 0);
	float espacioUsado = tamParalelo - layout.first;

	int cantidadSeparaciones = elementos.size() - 1;
	float multiplicadorSeparacion = std::max(0.0f, separacion * cantidadSeparaciones);
	float espacioSeparadores = espacioUsado * multiplicadorSeparacion;
	if (espacioSeparadores > layout.first) {
		espacioSeparadores = layout.first;
	}
	float espacioInfinitos = tamParalelo - espacioUsado - espacioSeparadores;

	int infinitos = 0;
	for (auto& emt : invertir_iteracion(elementos)) {
		if (emt->getLayoutInfo().infinitoParalelo(horizontal)) {
			infinitos++;
		}
	}
	float separacion = (cantidadSeparaciones == 0) ? 0.0 : (espacioSeparadores / cantidadSeparaciones);
	float extension = (infinitos == 0) ? 0.0 : (espacioInfinitos / infinitos);
	layout = realizarLayout(separacion, extension);
	commitLayout(move(layout.second));
}

/* Devuelve espacio no ocupado. Argumentos son el espacio a usar entre pares
 * de objetos, y espacio a usar para cada objeto extensible.
 */
std::pair<float, std::vector<Rect>> ContenedorLayout::realizarLayout (float separacion, float extension)
{
	std::pair<float, std::vector<Rect>> retval;

	auto paralelo = [horizontal] (Vec2& val) -> float& { return horizontal ? val.x : val.y; };
	auto perpendicular = [horizontal] (Vec2& val) -> float& { return horizontal ? val.y : val.x; };

	Vec2 tamContenedor(getSuperficie().tam());

	LayoutInfo miInfo(this->getLayoutInfo());
	Vec2 ratiosPadre = (tamContenedor - miInfo.tamMinimo)/ (miInfo.tamPreferido - miInfo.tamMinimo);
	float ratioPadre = paralelo(ratiosPadre);

	Vec2 media;
	perpendicular(media) = perpendicular(tamContenedor) / 2;
	auto elementos = elementosLayouteables();
	for (auto& emt : invertir_iteracion(elementos)) {
		LayoutInfo info(emt->getLayoutInfo());
		Vec2 nTam;
		if (ratioPadre < 1) {
			nTam = info.tamMinimo + (info.tamPreferido - info.tamMinimo) * ratioPadre;
		} else {
			nTam = info.tamPreferido;
			if (info.tamPreferido != info.tamMinimo) {
				Vec2 u = (tamContenedor - info.tamMinimo) / (info.tamPreferido - info.tamMinimo);
				float ratio = std::min(u.x, u.y);
				if (ratio < 1.0) {
					nTam = info.tamMinimo + (info.tamPreferido - info.tamMinimo) * ratio;
				}
			}
			if (info.infinitoParalelo(horizontal)) {
				paralelo(nTam) += extension;
			}
		}
		if (info.infinitoPerpendicular(horizontal)) {
			perpendicular(nTam) = perpendicular(tamContenedor);
		}

		Vec2 avance;
		paralelo(avance) = paralelo(nTam) / 2;
		Vec2 separador;
		paralelo(separador) = separacion;

		Vec2 nCentro = media + avance;
		Rect superficie = Rect::deCentro(nCentro, nTam);
		if (info.mantenerAspecto) {
			Vec2 dif = superficie.tam() / info.tamPreferido;
			superficie.setTam(info.tamPreferido * std::min(dif.x, dif.y));
		}
		retval.second.push_back(superficie);

		media = nCentro + avance + separador;
	}

	retval.first = paralelo(tamContenedor) - paralelo(media);
	return retval;
}

void ContenedorLayout::commitLayout(std::vector<Rect>&& posiciones)
{
	Vec2 miTamanio = this->getSuperficie().tam();
	for (auto& emt : elementosLayouteables()) {
		FuentePosicion* base = emt->getFuente();
		base->padreResizeado(miTamanio);
		FuenteLayout* fuente = dynamic_cast<FuenteLayout*>(emt->getFuente());
		if (fuente != NULL) {
			Rect superficie = posiciones.back();
			fuente->setSuperficie(superficie);
			emt->resized(superficie.tam());
			posiciones.pop_back();
		}
	}
}

std::vector<vista::Elemento*> ContenedorLayout::elementosLayouteables ()
{
	std::vector<vista::Elemento*> retval;
	auto elementos = listarElementos();
	for (auto& elemento : elementos) {
		if (dynamic_cast<FuenteLayout*>(elemento->getFuente()) != nullptr) {
			retval.push_back(elemento);
		}
	}
	return retval;
}
