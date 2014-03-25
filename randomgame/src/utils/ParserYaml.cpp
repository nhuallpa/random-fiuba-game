#include "ParserYaml.h"
#include <vector>
#include <iostream>



ParserYaml::ParserYaml(){}

ParserYaml::ParserYaml(std::string config, std::string level){
	this->confFilePath = config;
	this->cargarConfYaml(this->confFilePath);
	this->isDefault = false;
	this->cargarNivelYaml(level);
}

ParserYaml::ParserYaml(std::string config){
	this->confFilePath = config;
	this->cargarConfYaml(this->confFilePath);
	this->isDefault = true;
	this->startWithDefaultLevel();
}



ParserYaml::~ParserYaml(){}

void ParserYaml::startWithDefaultLevel(){
	this->levelFilePath = DEFAULT_YAML_LEVEL;
	this->isDefault = true;
	stNivel lvl;
	lvl.ancho = "640";
	lvl.alto = "480";
	lvl.fondo = "";
	lvl.nombre = "TIMv1";
	lvl.agua = "50";
	this->todo.nivel.push_back(lvl);
}

void ParserYaml::DestroySingleton(){
	if(pInstance != NULL) delete pInstance;
}

ParserYaml* ParserYaml::getInstance(){
	if(pInstance == NULL){
		pInstance = new ParserYaml(CONFIG_FILE);
	}
	return pInstance;
}


ParserYaml* ParserYaml::getInstance(std::string file){
	if(pInstance == NULL){
		std::ifstream fin(file.c_str());
		if( fin.good() == true){
			pInstance = new ParserYaml(CONFIG_FILE,file);
		}else{
			Log::e("Archivo de nivel: %s, invalido/corrupto o no encontrado", file);
			pInstance = new ParserYaml(CONFIG_FILE);
		}
	}
	return pInstance;
}

bool ParserYaml::getDefault(){
	return this->isDefault;
}

std::string ParserYaml::yamlNodeToString(const YAML::Node& node){
	std::string sNode;
	node >> sNode;
	return sNode;
}

bool ParserYaml::existeNivel(std::string nivel,std::vector <stNivel>& nivelVect){
	for(unsigned i=0;i<nivelVect.size();i++){
		if (nivelVect[i].nombre.compare(nivel)==0) return true;
	}
	return false;
}

bool ParserYaml::existeElemen(std::string elem,std::vector <dtElemento>& elemVect){
	for(unsigned i=0;i<elemVect.size();i++){
		if (elemVect[i].nombre.compare(elem)==0) return true;
	}
	return false;
} 

void ParserYaml::cargarElementos(const YAML::Node& nodeVect,std::vector <stElemento>& elemVect){
	stElemento elem;
	bool fNombre = false;
	bool fX = false;
	bool fY = false;
	bool fAngulo = false;
	bool fExisteElem;
	
	elemVect.clear();//debo limpiar el elemVect de algun ciclo anterior

	for (unsigned i=0; i<nodeVect.size();i++){
		
		const YAML::Node& node = nodeVect[i];
		YAML::Mark mark = node.GetMark();

		for(YAML::Iterator it=node.begin();it!=node.end();++it){			
			std::string key = this->yamlNodeToString(it.first());
			if (key.compare("nombre")==0){
				fNombre = true;
				elem.nombre = this->yamlNodeToString(it.second());
				fExisteElem = this->existeElemen(elem.nombre,this->todo.dataE);
				if (!fExisteElem ){
					Log::e("Valor incorrecto para atributo NOMBRE en linea: %d, columna: %d",(mark.line + 1),(mark.column + 1));
				}
			}
			else if (key.compare("x")==0){
				elem.x = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.x)){
					std::string aux = elem.x;
					//elem.x = this->validaPosicion(elem.x);
					if (aux.compare(elem.x) != 0)
						Log::d("Truncado valor de atributo X en linea: %d, columna: %d",(mark.line + 2),(mark.column + 1));
					fX = true;
				}else
					Log::e("Valor incorrecto para atributo X en linea: %d, columna: %d",(mark.line + 2),(mark.column + 1));
			}
			else if (key.compare("y")==0){
				elem.y = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.y)){
					std::string aux = elem.y;
					//elem.y = this->validaPosicion(elem.y);
					if (aux.compare(elem.y) != 0)
						Log::d("Truncado valor de atributo Y en linea: %d, columna: %d",(mark.line + 3),(mark.column + 1));
					fY = true;
				}else
					Log::e("Valor incorrecto para atributo Y en linea: %d, columna: %d",(mark.line + 3),(mark.column + 1));
			}
			else if (key.compare("angulo")==0){
				elem.angulo = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.angulo)){
					std::string aux = elem.angulo;
					//elem.angulo = this->validaAngulo(elem.angulo);
					if (aux.compare(elem.angulo) != 0)
						Log::d("Truncado valor de atributo ANGULO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
					fAngulo = true;
				} else
					Log::e("Valor incorrecto para atributo ANGULO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			//else{
			//	//LOG: key no es un identificador correcto de elemento + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
			//	Log::e("Element key no es un identificador correcto de elemento. Linea: %d, Columna: %d",(mark.line + 1),(mark.column + 1));
			//}
		}

		//fExisteElem = this->existeElemen(elem.nombre,this->todo.dataE);
		if (fNombre && fX && fY && fAngulo && fExisteElem){
			//Log::d("Elemento %s, cargado correctamente en posicion (%s,%s) con angulo %s",elem.nombre,elem.x,elem.y,elem.angulo);
			elemVect.push_back(elem);
			//Log se carga el elemento correctamente
		}
		else{
			if (!fNombre)Log::d("Atributo NOMBRE faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
			if (!fX) Log::d("Atributo X faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 2),(mark.column + 1));
			if (!fY) Log::d("Atributo Y faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 3),(mark.column + 1));
			if (!fAngulo) Log::d("Atributo ANGULO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
			if (!fExisteElem) Log::d("Elemento inexistente en linea: %d, columna: %d",(mark.line + 1),(mark.column + 1));
		}
		fNombre = false;
		fX = false;
		fY = false;
		fAngulo = false;
	
	
	}

}

std::string ParserYaml::getImElem(const std::vector <dtElemento> dElemVect ,std::string nombreE){
	for(unsigned i=0;i<dElemVect.size();i++){
		dtElemento elem = dElemVect[i];
		if (elem.nombre.compare(nombreE)==0) return elem.imagen;
	}
	return "";//si retorna esto no encontro el elemento en la lista
}

void ParserYaml::cargarDataElementos(const YAML::Node& nodeVect,std::vector <dtElemento>& dElemVect){
	dtElemento elem;
	bool fNombre = false;
	bool fImagen = false;
	
	for (unsigned i=0; i<nodeVect.size();i++){
		
		const YAML::Node& node = nodeVect[i];
		YAML::Mark mark = node.GetMark();
		for(YAML::Iterator it=node.begin();it!=node.end();++it){			
			std::string key = this->yamlNodeToString(it.first());
			if (key.compare("nombre")==0){
				fNombre = true;
				elem.nombre = this->yamlNodeToString(it.second());
			}
			else if (key.compare("imagen")==0){
				fImagen = true;
				elem.imagen = this->yamlNodeToString(it.second());
			}
			else {
				//LOG: key no es un identificador correcto de los datos de los elementos + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
				Log::e("Element key no es un identificador correcto de elemento. Linea: %d, Columna: %d",(mark.line + 1),(mark.column + 1));
			}
		}
		if (fNombre && fImagen){
			dElemVect.push_back(elem);
			//Log carga elemento <elem> correctamente
			//Log::d("Elemento %s, cargado correctamente",elem.nombre);
		}
		else{
			if (!fNombre) Log::e("Elemento %s, no encontrado.",elem.nombre);
			if (!fImagen) Log::e("Imagen %s, no encontrada",elem.imagen);
		}
		fNombre = false;
		fImagen = false;
	}
}


void ParserYaml::cargarNiveles(const YAML::Node& nodeVect,std::vector <stNivel>& nivelVect){
	stNivel nivel;
	bool fNombre = false;
	bool fElem = false;
	bool fAncho = false;
	bool fAlto = false;
	bool fAnchoP = false;
	bool fAltoP = false;
	bool fBackg = false;
	bool fAgua = false;
	bool fTierra = false;
	for (unsigned i=0; i<nodeVect.size();i++){
		
		const YAML::Node& node = nodeVect[i];
		 YAML::Mark mark = node.GetMark();
		 try{
			 YAML::Iterator it=node.begin();
			 
			 if (!node.size()){
				Log::e("Error parseando nivel. Iniciando nivel con configuración default");
				this->startWithDefaultLevel();
				return;
			 }

			 for(;it!=node.end();++it){
				
				std::string key = this->yamlNodeToString(it.first());
				
				if (key.compare("nombre")==0){
					fNombre = true;
					nivel.nombre = this->yamlNodeToString(it.second());
				}
				else if(key.compare("background")==0){
					fBackg = true;
					nivel.fondo = this->yamlNodeToString(it.second());
				}
				else if (key.compare("ancho")==0){

					nivel.ancho = this->yamlNodeToString(it.second());
					if (this->esNumero(nivel.ancho)){
						std::string aux = nivel.ancho;
						//nivel.ancho = this->validaPantalla(nivel.ancho);
						if (aux.compare(nivel.ancho) != 0)
							Log::d("Truncado valor de atributo ANCHO en nodo linea: %d.",(mark.line + 1));
							fAncho = true;
						} else
							Log::e("Valor incorrecto para atributo ANCHO en nodo linea: %d.",(mark.line + 1));
				}
				else if (key.compare("alto")==0){

					nivel.alto = this->yamlNodeToString(it.second());
					if (this->esNumero(nivel.alto)){
						std::string aux = nivel.alto;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(nivel.alto) != 0)
							Log::d("Truncado valor de atributo ALTO en nodo linea: %d.",(mark.line + 1));
							fAlto = true;
						} else
							Log::e("Valor incorrecto para atributo ALTO en nodo linea: %d.",(mark.line + 1));
				}

				else if (key.compare("anchoPantalla")==0){

					nivel.anchoP = this->yamlNodeToString(it.second());
					if (this->esNumero(nivel.anchoP)){
						std::string aux = nivel.anchoP;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(nivel.anchoP) != 0)
							Log::d("Truncado valor de atributo ANCHO PANTALLA en nodo linea: %d.",(mark.line + 1));
							fAnchoP = true;
						} else
							Log::e("Valor incorrecto para atributo ANCHO PANTALLA en nodo linea: %d.",(mark.line + 1));
				}
				
				else if (key.compare("altoPantalla")==0){

					nivel.altoP = this->yamlNodeToString(it.second());
					if (this->esNumero(nivel.altoP)){
						std::string aux = nivel.altoP;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(nivel.altoP) != 0)
							Log::d("Truncado valor de atributo ALTO PANTALLA en nodo linea: %d.",(mark.line + 1));
							fAltoP = true;
						} else
							Log::e("Valor incorrecto para atributo ALTO PANTALLA en nodo linea: %d.",(mark.line + 1));
				}
				
				else if (key.compare("wlvl")==0){

					nivel.agua = this->yamlNodeToString(it.second());
					if (this->esNumero(nivel.agua)){
						std::string aux = nivel.agua;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(nivel.agua) != 0)
							Log::d("Truncado valor de atributo WLVL en nodo linea: %d.",(mark.line + 1));
							fAgua = true;
						} else
							Log::e("Valor incorrecto para atributo WLVL en nodo linea: %d.",(mark.line + 1));
				}
				


				else if (key.compare("tierra")==0){

					nivel.tierra = this->yamlNodeToString(it.second());
					if (this->esNumero(nivel.tierra)){
						std::string aux = nivel.tierra;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(nivel.tierra) != 0)
							Log::d("Truncado valor de atributo TIERRA en nodo linea: %d.",(mark.line + 1));
							fTierra = true;
						} else
							Log::e("Valor incorrecto para atributo TIERRA en nodo linea: %d.",(mark.line + 1));
				}



				else if (key.compare("elementos")==0){
					fElem = true;
					this->cargarElementos(it.second(),nivel.elem);
				}
				else {
					//LOG: key no es un identificador correcto del nivel + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e("Element key no es un identificador correcto de elemento. Linea: %d, Columna: %d",(mark.line + 1),(mark.column + 1));
				}
			}
		 }catch(YAML::Exception& e){ 
			Log::e("%s",e.what());
			exit(1);
		 }
		
		if (fNombre && fElem && fAncho && fAlto && fAnchoP && fAltoP && fBackg && fAgua && fTierra){
			nivelVect.push_back(nivel);
			//Log carga Nivel correctamente
		}
		else{
			if (!fNombre){
				Log::e("Nombre no encontrado, seteando default");
				nivel.nombre = "TIMv1 - Nivel1";
			}
			if (!fElem){
				Log::e("Elemento no encontrado, seteando default");
			}
			if (!fAncho){
				Log::e("Ancho no encontrado, seteando default");
				nivel.ancho = "640";
			}
			if (!fAlto){
				Log::e("Alto no encontrado, seteando default");
				nivel.alto = "480";
			}
			if (!fAnchoP){
				Log::e("Ancho no encontrado, seteando default");
				nivel.ancho = "640";
			}
			if (!fAltoP){
				Log::e("Alto no encontrado, seteando default");
				nivel.alto = "480";
			}
			if (!fBackg){
				Log::e("Background no encontrado, seteando default");
				nivel.fondo ="";
			}
			if (!fAgua){
				Log::e("Wlvl no encontrado, seteando default");
				nivel.agua="";
			}
			if (!fTierra){
				Log::e("Tierra no encontrado, seteando default");
				nivel.tierra="";
			}
			nivelVect.push_back(nivel);
		}
	}
	
}


void ParserYaml::cargarConfYaml(std::string file){
	std::ifstream fin(file.c_str());
	this->confFilePath = file;
	
	//flags
	bool fElem = false;
	
	if (fin.good() == true){
		try{
			YAML::Parser parser(fin);
			YAML::Node node;
			parser.GetNextDocument(node);
			

			for(YAML::Iterator it=node.begin();it!=node.end();++it){
				std::string key = this->yamlNodeToString(it.first());
				const YAML::Node& data = it.second();
				YAML::Mark mark = it.first().GetMark();

				if (key.compare("elementos")==0){
					fElem = true;
					this->cargarDataElementos(data,this->todo.dataE);
					
				}
				
				else{
					//LOG: key no es un identificador correcto del archivo de configuracion + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e("Key: %s, no es un identificador correcto del archivo de configuracion.",key);
				}
			}

			if (fElem){
				//LOG: Datos de los elementos encontrados correctamente
				Log::d("Datos de los elementos encontrados correctamente");	
			}
			else if (!fElem){
				/*LOG: Error al cargar la configuracion, no se encontraron los datos de los elementos*/
				Log::e("Error al cargar la configuracion, no se encontraron los datos de los elementos");
			}

		}catch(YAML::Exception& e){ 
			Log::e("%s",e.what());
		}
		fin.close();
	} 
	else if (fin.eof()){
		/*LOG: El archivo de configuracion esta vacio*/
		Log::e("El archivo de configuracion esta vacio");
		fin.close();
		exit(1);
	}
	else {
		int x;
		/*LOG: No se puede abirir el archivo de configuracion*/
		Log::e("No se puede abirir el archivo de configuracion");
		exit(1);
	}
	
	//populate map
	this->initializeElementMap();

}


void ParserYaml::initializeElementMap(){
	for(unsigned i=0;i<this->getCantDataElem();i++){
		//std::cout<<"nombre: "<< aParser->getDataElemNombre(i)<<"\n\t";
		//std::cout<<"imagen: "<< aParser->getDataElemImagen(i)<<"\n\t";
		this->elementMap[ this->getDataElemNombre(i) ] = std::make_pair(i,this->getDataElemImagen(i));
	}
}

int ParserYaml::getElementPosition(std::string name){
	std::map< std::string, std::pair<int,std::string> >::iterator it;
	it = this->elementMap.find(name);
	return it->second.first;
}

std::string ParserYaml::getImagePath(std::string name){
	std::map< std::string, std::pair<int,std::string> >::iterator it;
	it = this->elementMap.find(name);
	return it->second.second;
}

std::string ParserYaml::getElementType(int id){
	std::map< std::string, std::pair<int,std::string> >::iterator it = this->elementMap.begin();
	for ( ; it!=this->elementMap.end() ; it++){
		if ( (*it).second.first == id){
			return (*it).first;
		}
	}
}

void ParserYaml::cargarNivelYaml(std::string file){
	std::ifstream fin(file.c_str());
	this->levelFilePath = file;
	
	//flags
	bool fNivel = false;


	if (fin.good() == true){
		try{
			YAML::Parser parser(fin);
			YAML::Node node;
			try{ parser.GetNextDocument(node);
			}catch(YAML::Exception& e){

				Log::e("%s", e.what());
				Log::e("Iniciado juego con nivel default");
				this->startWithDefaultLevel();
				//exit(1);

			}

			for(YAML::Iterator it=node.begin();it!=node.end();++it){
				std::string key = this->yamlNodeToString(it.first());
				const YAML::Node& data = it.second();
				YAML::Mark mark = it.first().GetMark();
				if (key.compare("niveles")==0){
					fNivel = true;
					this->cargarNiveles(data,this->todo.nivel);
				}
				else{
					//LOG: key no es un identificador correcto del archivo de nivel + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e("%s no es un identificador correcto del archivo de nivel.", key);
				}
			}
			
			if(fNivel){
				//LOG: Se cargo el nivel correctamente
				Log::d("Se cargo el nivel correctamente");
				
			}
			else{
				//LOG: La carga del nivel guardado es incorrecta
				Log::e("La carga del nivel guardado es incorrecta");
				Log::e("Iniciando nivel con configuración default");
				this->startWithDefaultLevel();
				//exit(1);
			}
			fin.close();
		
		}catch(YAML::Exception& e){
			Log::e("%s", e.what());
			Log::e("Iniciando nivel con configuración default");
			this->startWithDefaultLevel();
		}
	
		fin.close();
	} else {
		//LOG: No se puede abrir el archivo de nivel
		Log::e("No se puede abrir el archivo de nivel");
		this->startWithDefaultLevel();
		//exit(1);	
	}
	fin.close();
}



//Esto hay que programarlo de nuevo sin boost, salvo q quieran usarlo
//bool ParserYaml::esNumero(std::string cadena){
//	try{ 
//		float f=boost::lexical_cast<float>(cadena);
//		return true;
//	}catch(boost::bad_lexical_cast& e){
//		return false;
//	}
//
//}

bool ParserYaml::esNumero(std::string cadena){
	return true;
}

//+++++geters++++++



int ParserYaml::getCantDataElem(){
	return this->todo.dataE.size();
}

std::string ParserYaml::getDataElemNombre(int i){
	return this->todo.dataE[i].nombre;
}

std::string ParserYaml::getDataElemImagen(int i){
	return this->todo.dataE[i].imagen;

}

int ParserYaml::getCantNiveles(){
	return this->todo.nivel.size();
}
	
std::string ParserYaml::getNivelNombre(int i){
	return this->todo.nivel[i].nombre;
}

std::string ParserYaml::getNivelFondo(int i){
	return this->todo.nivel[i].fondo;
}

std::string ParserYaml::getNivelAlto(int i){
	return this->todo.nivel[i].alto;
}

std::string ParserYaml::getNivelAncho(int i){
	return this->todo.nivel[i].ancho;
}

std::string ParserYaml::getNivelAltoPantalla(int i){
	return this->todo.nivel[i].altoP;
}

std::string ParserYaml::getNivelAnchoPantalla(int i){
	return this->todo.nivel[i].anchoP;
}

std::string ParserYaml::getNivelAgua(int i){
	return this->todo.nivel[i].agua;
}

std::string ParserYaml::getNivelTierra(int i){
	return this->todo.nivel[i].tierra;
}

int ParserYaml::getCantElem(int i){
	return this->todo.nivel[i].elem.size();
}

std::string ParserYaml::getElemNombre(int n,int e){
	return this->todo.nivel[n].elem[e].nombre;
}
	
std::string ParserYaml::getElemX(int n,int e){
	return this->todo.nivel[n].elem[e].x;
}

std::string ParserYaml::getElemY(int n,int e){
	return this->todo.nivel[n].elem[e].y;
}

std::string ParserYaml::getElemAngulo(int n,int e){
	return this->todo.nivel[n].elem[e].angulo;
}

std::string ParserYaml::getLevelFilePath(){
	return this->levelFilePath;
}


std::string parserFloat2String(float n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}

std::string parserInt2String(int n){
	std::stringstream ss;
	ss << n;
	return ss.str();
}

//reprogrmar usa boost...
//std::string ParserYaml::validaAngulo(std::string ang){
//	try{ 
//		int i=boost::lexical_cast<int>(ang);
//		i=i%360;
//		if(i<0) i+=360;
//		return parserInt2String(i);
//	}catch(boost::bad_lexical_cast& e){
//		return "";
//	}
//
//}

std::string ParserYaml::validaAngulo(std::string ang){
	return "";
}

//reprogramar usa boost
//std::string ParserYaml::validaPosicion(std::string pos){
//	try{ 
//		float f=boost::lexical_cast<float>(pos);
//		if(f<0) f=0;
//		if(f>100) f=100;
//		return parserFloat2String(f);
//	}catch(boost::bad_lexical_cast& e){
//		return "";
//	}
//}

std::string ParserYaml::validaPosicion(std::string pos){
	return ""; }


//reprogramar usa boost
//std::string ParserYaml::validaPantalla(std::string tam){
//	try{ 
//		int f=boost::lexical_cast<int>(tam);
//		if(f<0) f=600;
//		if(f>2000) f=800;
//		return parserFloat2String(f);
//	}catch(boost::bad_lexical_cast& e){
//		return "";
//	}
//}
std::string ParserYaml::validaPantalla(std::string tam){
	return "";
	}



//para trabajar con un solo nivel
std::string ParserYaml::getNivelNombre(){return  this->getNivelNombre(0);}
std::string ParserYaml::getNivelFondo(){return this->getNivelFondo(0);}
std::string ParserYaml::getNivelAlto(){return this->getNivelAlto(0);}
std::string ParserYaml::getNivelAncho(){return this->getNivelAncho(0);}
std::string ParserYaml::getNivelAgua(){return this->getNivelAgua(0);}
std::string ParserYaml::getNivelTierra(){return this->getNivelTierra(0);}
int ParserYaml::getCantElem(){return this->getCantElem(0);}
std::string ParserYaml::getElemNombre(int){return this->getElemNombre(0);}
std::string ParserYaml::getElemX(int){return this->getElemX(0);}
std::string ParserYaml::getElemY(int){return this->getElemY(0);}
std::string ParserYaml::getElemAngulo(int){return this->getElemAngulo(0);}






ParserYaml* ParserYaml::pInstance = NULL;