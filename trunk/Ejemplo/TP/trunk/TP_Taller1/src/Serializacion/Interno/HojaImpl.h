#ifndef HOJAIMPL_H_
#define HOJAIMPL_H_

#include <string>
#include <vector>

namespace Serializacion {

struct Hoja_ImplBase
{
	Hoja_ImplBase() = default;
	virtual ~Hoja_ImplBase() {}

	virtual Hoja_ImplBase* clonar () = 0;

	virtual std::string aYaml () = 0;
	static Hoja_ImplBase* deYaml (std::string);
	virtual std::vector<uint8_t> aRed () = 0;
	static Hoja_ImplBase* deRed (const std::vector<uint8_t>&, unsigned&);

	virtual bool equals (Hoja_ImplBase*) const = 0; // asume que ambos argumentos son del mismo tipo
};

template <class T>
struct Hoja_Impl : public Hoja_ImplBase
{
	Hoja_Impl () = default;
	~Hoja_Impl () = default;

	static constexpr bool basico = false;

	// ningun metodo para que cualquier llamado sea error
};


// especializaciones para tipos basicos

template <>
struct Hoja_Impl<bool> : public Hoja_ImplBase
{
	Hoja_Impl () : valor() {}
	explicit Hoja_Impl (bool valor) : valor(valor) {}
	static constexpr bool basico = true;

	bool equals (Hoja_ImplBase*) const;
	Hoja_Impl<bool>* clonar();
	std::string aYaml ();
	std::vector<uint8_t> aRed ();
	bool valor;
};

template <>
struct Hoja_Impl<size_t> : public Hoja_ImplBase
{
	Hoja_Impl () : valor() {}
	explicit Hoja_Impl (size_t valor) : valor(valor) {}
	static constexpr bool basico = true;

	bool equals (Hoja_ImplBase*) const;
	Hoja_Impl<size_t>* clonar();
	std::string aYaml ();
	std::vector<uint8_t> aRed ();
	static Hoja_Impl<size_t>* deRed (const std::vector<uint8_t>&, unsigned&);
	size_t valor;
};

template <>
struct Hoja_Impl<float> : public Hoja_ImplBase
{
	Hoja_Impl () : valor() {}
	explicit Hoja_Impl (float valor) : valor(valor) {}
	static constexpr bool basico = true;

	bool equals (Hoja_ImplBase*) const;
	Hoja_Impl<float>* clonar();
	std::string aYaml ();
	std::vector<uint8_t> aRed ();
	static Hoja_Impl<float>* deRed (const std::vector<uint8_t>&, unsigned&);
	float valor;
};

template <>
struct Hoja_Impl<std::string> : public Hoja_ImplBase
{
	Hoja_Impl () : valor() {}
	explicit Hoja_Impl (std::string valor) : valor(valor) {}
	static constexpr bool basico = true;

	bool equals (Hoja_ImplBase*) const;
	Hoja_Impl<std::string>* clonar();
	std::string aYaml ();
	std::vector<uint8_t> aRed ();
	static Hoja_Impl<std::string>* deRed (const std::vector<uint8_t>&, unsigned&);
	std::string valor;
};


// implementacion de templates

} /* namespace Serializacion */
#endif /* HOJAIMPL_H_ */
