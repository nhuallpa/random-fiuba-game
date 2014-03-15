#include "HojaImpl.h"

#include "Log/Suceso.h"
#include <netinet/in.h>

namespace Serializacion {

Hoja_ImplBase* Hoja_ImplBase::deYaml (std::string valor)
{
	if (valor == "true") {
		return new Hoja_Impl<bool>(true);
	} else if (valor == "false") {
		return new Hoja_Impl<bool>(false);
	}

	try {
		if (std::to_string(std::stoul(valor)) == valor) {
			return new Hoja_Impl<size_t>(static_cast<size_t>(std::stoul(valor)));
		}
	} catch (...) {
	}

	try {
		return new Hoja_Impl<float>(std::stof(valor));
	} catch (...) {
	}

	return new Hoja_Impl<std::string>(valor);
}

Hoja_ImplBase* Hoja_ImplBase::deRed (const std::vector<uint8_t>& valor, unsigned& inicio)
{
	switch (valor[inicio++]) {
	case 'T':
		return new Hoja_Impl<bool>(true);
	case 'F':
		return new Hoja_Impl<bool>(false);
	case 'u':
		return Hoja_Impl<size_t>::deRed(valor, inicio);
	case 'f':
		return Hoja_Impl<float>::deRed(valor, inicio);
	case 's':
		return Hoja_Impl<std::string>::deRed(valor, inicio);
	}
	throw Log::Suceso(Log::DEBUG, "Mal tipo al leer de red");
}



bool Hoja_Impl<bool>::equals (Hoja_ImplBase* otro) const
{
	return valor == static_cast<decltype(this)>(otro)->valor;
}

Hoja_Impl<bool>* Hoja_Impl<bool>::clonar()
{
	return new Hoja_Impl<bool>(*this);
}

std::string Hoja_Impl<bool>::aYaml()
{
	return valor ? "true" : "false";
}

std::vector<uint8_t> Hoja_Impl<bool>::aRed()
{
	std::vector<uint8_t> retval;
	retval.push_back(valor ? 'T' : 'F');
	return retval;
}



bool Hoja_Impl<size_t>::equals (Hoja_ImplBase* otro) const
{
	return valor == static_cast<decltype(this)>(otro)->valor;
}

Hoja_Impl<size_t>* Hoja_Impl<size_t>::clonar()
{
	return new Hoja_Impl<size_t>(*this);
}

std::string Hoja_Impl<size_t>::aYaml()
{
	return std::to_string(valor);
}

std::vector<uint8_t> Hoja_Impl<size_t>::aRed()
{
	std::vector<uint8_t> retval;
	retval.resize(5);
	retval[0] = 'u';
	*(uint32_t*)(&retval[1]) = htonl(valor);
	return retval;
}

Hoja_Impl<size_t>* Hoja_Impl<size_t>::deRed(const std::vector<uint8_t>& origen, unsigned& inicio)
{
	auto retval = new Hoja_Impl<size_t>();
	retval->valor = ntohl(*(uint32_t*)(&origen[inicio]));
	inicio += 4;
	return retval;
}



bool Hoja_Impl<float>::equals (Hoja_ImplBase* otro) const
{
	return valor == static_cast<decltype(this)>(otro)->valor;
}

Hoja_Impl<float>* Hoja_Impl<float>::clonar()
{
	return new Hoja_Impl<float>(*this);
}

std::string Hoja_Impl<float>::aYaml()
{
	return std::to_string(valor);
}

std::vector<uint8_t> Hoja_Impl<float>::aRed()
{
	std::vector<uint8_t> retval;
	retval.resize(5);
	retval[0] = 'f';
	*(uint32_t*)(&retval[1]) = htonl(*(uint32_t*)(&valor));
	return retval;
}

Hoja_Impl<float>* Hoja_Impl<float>::deRed(const std::vector<uint8_t>& origen, unsigned& inicio)
{
	auto retval = new Hoja_Impl<float>();
	uint32_t temp = ntohl(*(uint32_t*)(&origen[inicio]));
	retval->valor = *(float*)(&temp);
	inicio += 4;
	return retval;
}


bool Hoja_Impl<std::string>::equals (Hoja_ImplBase* otro) const
{
	return valor == static_cast<decltype(this)>(otro)->valor;
}

Hoja_Impl<std::string>* Hoja_Impl<std::string>::clonar()
{
	return new Hoja_Impl<std::string>(*this);
}

std::string Hoja_Impl<std::string>::aYaml()
{
	return valor;
}

std::vector<uint8_t> Hoja_Impl<std::string>::aRed()
{
	std::vector<uint8_t> retval;
	retval.push_back('s');
	for (char ch : valor) {
		retval.push_back(ch);
	}
	retval.push_back('\0');
	return retval;
}

Hoja_Impl<std::string>* Hoja_Impl<std::string>::deRed(const std::vector<uint8_t>& origen, unsigned& inicio)
{
	auto retval = new Hoja_Impl<std::string>();
	retval->valor = (char*)(&origen[inicio]);
	inicio += 1 + retval->valor.size();
	return retval;
}

} /* namespace Serializacion */
