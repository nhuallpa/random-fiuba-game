#include "Objeto.h"

#include "Log/Suceso.h"
#include "Serializacion/Interno/Hoja.h"
#include "Serializacion/Interno/Mapa.h"
#include "Serializacion/Interno/Vector.h"
#include "Serializacion/YAML/ConvertStr.h"
#include "Serializacion/YAML/YAMLHelper.h"

using namespace Serializacion;

namespace YAML {

Node convert<Objeto>::encode(const Objeto& rhs) {
	Node nodo;
	switch (rhs.tipo()) {
	case Objeto::Tipo::Hoja:
		nodo = rhs.getHoja().aYaml();
		break;
	case Objeto::Tipo::Mapa:
		if (rhs.getMapa().atributos.size() == 0) {
			break;
		}
		for (auto& par : rhs.getMapa().atributos) {
			nodo[par.first] = par.second;
		}
		break;
	case Objeto::Tipo::Vector:
		if (rhs.getVector().size() == 0) {
			break;
		}
		for (auto& val : rhs.getVector().valores) {
			nodo.push_back(val);
		}
		break;
	case Objeto::Tipo::Nulo:
		break;
	case Objeto::Tipo::Borrado:
		nodo = "__BORRADO__";
	}
	return nodo;
}

bool convert<Objeto>::decode(const Node& node, Objeto& rhs) {
	if (node.IsMap()) {
		Mapa mapa;
		for (auto& par : node) {
			mapa[par.first.as<std::string>()] = par.second.as<Objeto>();
		}
		rhs = Objeto(mapa);
		return true;
	} else if (node.IsSequence()) {
		Vector vector;
		for (auto& val : node) {
			vector.push_back(val.as<Objeto>());
		}
		rhs = Objeto(vector);
		return true;
	} else if (node.IsNull() || (node.IsScalar() && node.Scalar() == "~")) {
		rhs = Objeto();
		return true;
	} else if (node.IsScalar() && node.Scalar() == "__BORRADO__") {
		rhs = Objeto::Borrado();
	} else if (node.IsScalar()) {
		Hoja hoja = Hoja::deYaml(node.Scalar());
		rhs = Objeto(hoja);
		return true;
	}
	return false;
}

} /* namespace YAML */
