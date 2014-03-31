#include "ParserYaml.h"
#include <vector>
#include <iostream>


ParserYaml::ParserYaml(){}

ParserYaml::ParserYaml(std::string config, std::string level){
	this->confFilePath = config;
	//this->cargarConfYaml(this->confFilePath);
	this->isDefault = false;
	this->cargarNivelYaml(level);
}

ParserYaml::ParserYaml(std::string config){
	this->confFilePath = config;
	//this->cargarConfYaml(this->confFilePath);
	this->isDefault = true;
	this->startWithDefaultLevel();
}



ParserYaml::~ParserYaml(){}

void ParserYaml::startWithDefaultLevel(){
	this->levelFilePath = DEFAULT_YAML_LEVEL;
	this->isDefault = true;
	stEscenario lvl;
	lvl.ancho = "640";
	lvl.alto = "480";
	lvl.agua = "50";
	lvl.altoP = "500";
	lvl.anchoP = "1000";
	lvl.cielo = "cielo default";
	lvl.tierra = "tierra default";
	this->todo.escenario= lvl;
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
			Log::e(PARSER,"Archivo de escenario: %s, invalido/corrupto o no encontrado", file);
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


/*bool ParserYaml::existeElemen(std::string elem,std::vector <dtElemento>& elemVect){
	for(unsigned i=0;i<elemVect.size();i++){
		if (elemVect[i].nombre.compare(elem)==0) return true;
	}
	return false;
} */

void ParserYaml::cargarElementos(const YAML::Node& nodeVect,std::vector <stElemento>& elemVect){
	stElemento elem;
	bool fNombre = false;
	bool fX = false;
	bool fY = false;
	bool fRot = false;
	bool fMasa = false;
	bool fAlto = false;
	bool fAncho = false;
	bool fEstatico = false;
	bool fColor = false;
	
	elemVect.clear();//debo limpiar el elemVect de algun ciclo anterior

	for (unsigned i=0; i<nodeVect.size();i++){
		
		const YAML::Node& node = nodeVect[i];
		YAML::Mark mark = node.GetMark();

		for(YAML::Iterator it=node.begin();it!=node.end();++it){			
			std::string key = this->yamlNodeToString(it.first());
			if (key.compare("tipo")==0){
				fNombre = true;
				elem.tipo = this->yamlNodeToString(it.second());
			}
			else if (key.compare("x")==0){
				elem.x = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.x)){
					std::string aux = elem.x;
					if (aux.compare(elem.x) != 0)
						Log::d(PARSER,"Truncado valor de atributo X en linea: %d, columna: %d",(mark.line + 2),(mark.column + 1));
					fX = true;
				}else
					Log::e(PARSER,"Valor incorrecto para atributo X en linea: %d, columna: %d",(mark.line + 2),(mark.column + 1));
			}
			else if (key.compare("y")==0){
				elem.y = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.y)){
					std::string aux = elem.y;
					//elem.y = this->validaPosicion(elem.y);
					if (aux.compare(elem.y) != 0)
						Log::d(PARSER,"Truncado valor de atributo Y en linea: %d, columna: %d",(mark.line + 3),(mark.column + 1));
					fY = true;
				}else
					Log::e(PARSER,"Valor incorrecto para atributo Y en linea: %d, columna: %d",(mark.line + 3),(mark.column + 1));
			}
			else if (key.compare("ancho")==0){
				elem.ancho = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.ancho)){
					std::string aux = elem.ancho;
					//elem.ancho = this->validaAngulo(elem.ancho);
					if (aux.compare(elem.ancho) != 0)
						Log::d(PARSER,"Truncado valor de atributo ANCHO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
					fAncho = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo ANCHO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("alto")==0){
				elem.alto = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.alto)){
					std::string aux = elem.alto;
					//elem.alto = this->validaAngulo(elem.alto);
					if (aux.compare(elem.alto) != 0)
						Log::d(PARSER,"Truncado valor de atributo ALTO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
					fAlto = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo ALTO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("color")==0){
				elem.color = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.color)){
					std::string aux = elem.color;
					//elem.color = this->validaAngulo(elem.color);
					if (aux.compare(elem.color) != 0)
						Log::d(PARSER,"Truncado valor de atributo COLOR en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
					fColor = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo COLOR en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("masa")==0){
				elem.masa = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.masa)){
					std::string aux = elem.masa;
					//elem.masa = this->validaAngulo(elem.masa);
					if (aux.compare(elem.masa) != 0)
						Log::d(PARSER,"Truncado valor de atributo MASA en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
					fMasa = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo MASA en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("estatico")==0){
				elem.estatico = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.estatico)){
					std::string aux = elem.estatico;
					//elem.estatico = this->validaAngulo(elem.estatico);
					if (aux.compare(elem.estatico) != 0)
						Log::d(PARSER,"Truncado valor de atributo ESTATICO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
					fEstatico = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo ESTATICO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("rot")==0){
				elem.rot = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.rot)){
					std::string aux = elem.rot;
					//elem.rot = this->validaAngulo(elem.rot);
					if (aux.compare(elem.rot) != 0)
						Log::d(PARSER,"Truncado valor de atributo ROT en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
					fRot = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo ROT en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			
		}


		if (fNombre && fX && fY && fRot && fMasa && fAlto && fAncho && fEstatico && fColor){
			//Log::d(PARSER,"Elemento %s, cargado correctamente en posicion (%s,%s) con angulo %s",elem.nombre,elem.x,elem.y,elem.angulo);
			elemVect.push_back(elem);
			//Log se carga el elemento correctamente
		}
		else{
			if (!fNombre)Log::d(PARSER,"Atributo NOMBRE faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
			if (!fX) Log::d(PARSER,"Atributo X faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 2),(mark.column + 1));
			if (!fY) Log::d(PARSER,"Atributo Y faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 3),(mark.column + 1));
			if (!fRot) Log::d(PARSER,"Atributo ROT faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
			if (!fMasa) Log::d(PARSER,"Atributo MASA faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
			if (!fAlto) Log::d(PARSER,"Atributo ALTO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
			if (!fAncho) Log::d(PARSER,"Atributo ANCHO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
			if (!fEstatico) Log::d(PARSER,"Atributo ESTATICO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
			if (!fColor) Log::d(PARSER,"Atributo COLOR faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		}
		fNombre = false;
		fX = false;
		fY = false;
		fRot = false;
		fMasa = false;
		fAlto = false;
		fAncho = false;
		fEstatico = false;
		fColor = false;
	
	
	}

}

/*std::string ParserYaml::getImElem(const std::vector <dtElemento> dElemVect ,std::string nombreE){
	for(unsigned i=0;i<dElemVect.size();i++){
		dtElemento elem = dElemVect[i];
		if (elem.nombre.compare(nombreE)==0) return elem.imagen;
	}
	return "";//si retorna esto no encontro el elemento en la lista
}*/
/*
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
				Log::e(PARSER,"Element key no es un identificador correcto de elemento. Linea: %d, Columna: %d",(mark.line + 1),(mark.column + 1));
			}
		}
		if (fNombre && fImagen){
			dElemVect.push_back(elem);
			//Log carga elemento <elem> correctamente
			//Log::d(PARSER,"Elemento %s, cargado correctamente",elem.nombre);
		}
		else{
			if (!fNombre) Log::e(PARSER,"Elemento %s, no encontrado.",elem.nombre);
			if (!fImagen) Log::e(PARSER,"Imagen %s, no encontrada",elem.imagen);
		}
		fNombre = false;
		fImagen = false;
	}
}*/


void ParserYaml::cargarNiveles(const YAML::Node& nodeVect,stEscenario& escenarioVect){
	stEscenario escenario;
	//bool fNombre = false;
	bool fElem = false;
	bool fAncho = false;
	bool fAlto = false;
	bool fAnchoP = false;
	bool fAltoP = false;
	//bool fBackg = false;
	bool fAgua = false;
	bool fTierra = false;
	bool fCielo = false;
	//las dos lineas que estan comentadas, hacen que los escenarios sean un vector de escenarios
	//for (unsigned i=0; i<nodeVect.size();i++){
		
		//const YAML::Node& node = nodeVect[i];
		const YAML::Node& node = nodeVect;
		 YAML::Mark mark = node.GetMark();
		 try{
			 YAML::Iterator it=node.begin();
			 
			 if (!node.size()){
				Log::e(PARSER,"Error parseando escenario. Iniciando escenario con configuración default");
				this->startWithDefaultLevel();
				return;
			 }

			 for(;it!=node.end();++it){
				
				std::string key = this->yamlNodeToString(it.first());
				
				/*if (key.compare("nombre")==0){
					fNombre = true;
					nivel.nombre = this->yamlNodeToString(it.second());
				}
				else if(key.compare("background")==0){
					fBackg = true;
					nivel.fondo = this->yamlNodeToString(it.second());
				}*/
				if (key.compare("ancho-un")==0){

					escenario.ancho = this->yamlNodeToString(it.second());
					if (this->esNumero(escenario.ancho)){
						std::string aux = escenario.ancho;
						//nivel.ancho = this->validaPantalla(nivel.ancho);
						if (aux.compare(escenario.ancho) != 0)
							Log::d(PARSER,"Truncado valor de atributo ANCHO en nodo linea: %d.",(mark.line + 1));
							fAncho = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo ANCHO en nodo linea: %d.",(mark.line + 1));
				}
				else if (key.compare("alto-un")==0){

					escenario.alto = this->yamlNodeToString(it.second());
					if (this->esNumero(escenario.alto)){
						std::string aux = escenario.alto;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(escenario.alto) != 0)
							Log::d(PARSER,"Truncado valor de atributo ALTO en nodo linea: %d.",(mark.line + 1));
							fAlto = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo ALTO en nodo linea: %d.",(mark.line + 1));
				}

				else if (key.compare("ancho-px")==0){

					escenario.anchoP = this->yamlNodeToString(it.second());
					if (this->esNumero(escenario.anchoP)){
						std::string aux = escenario.anchoP;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(escenario.anchoP) != 0)
							Log::d(PARSER,"Truncado valor de atributo ANCHO PANTALLA en nodo linea: %d.",(mark.line + 1));
							fAnchoP = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo ANCHO PANTALLA en nodo linea: %d.",(mark.line + 1));
				}
				
				else if (key.compare("alto-px")==0){

					escenario.altoP = this->yamlNodeToString(it.second());
					if (this->esNumero(escenario.altoP)){
						std::string aux = escenario.altoP;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(escenario.altoP) != 0)
							Log::d(PARSER,"Truncado valor de atributo ALTO PANTALLA en nodo linea: %d.",(mark.line + 1));
							fAltoP = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo ALTO PANTALLA en nodo linea: %d.",(mark.line + 1));
				}
				
				else if (key.compare("nivel_agua")==0){

					escenario.agua = this->yamlNodeToString(it.second());
					if (this->esNumero(escenario.agua)){
						std::string aux = escenario.agua;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(escenario.agua) != 0)
							Log::d(PARSER,"Truncado valor de atributo AGUA en nodo linea: %d.",(mark.line + 1));
							fAgua = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo AGUA en nodo linea: %d.",(mark.line + 1));
				}
				


				else if (key.compare("imagen_tierra")==0){

					escenario.tierra = this->yamlNodeToString(it.second());
					if (this->esNumero(escenario.tierra)){
						std::string aux = escenario.tierra;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(escenario.tierra) != 0)
							Log::d(PARSER,"Truncado valor de atributo TIERRA en nodo linea: %d.",(mark.line + 1));
							fTierra = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo TIERRA en nodo linea: %d.",(mark.line + 1));
				}

				else if (key.compare("imagen_cielo")==0){

					escenario.cielo = this->yamlNodeToString(it.second());
					if (this->esNumero(escenario.cielo)){
						std::string aux = escenario.cielo;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(escenario.cielo) != 0)
							Log::d(PARSER,"Truncado valor de atributo CIELO en nodo linea: %d.",(mark.line + 1));
							fCielo = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo CIELO en nodo linea: %d.",(mark.line + 1));
				}

				else if (key.compare("objetos")==0){
					fElem = true;
					this->cargarElementos(it.second(),escenario.elem);
				}
				else {
					//LOG: key no es un identificador correcto del nivel + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e(PARSER,"Element key no es un identificador correcto de elemento. Linea: %d, Columna: %d",(mark.line + 1),(mark.column + 1));
				}
			}
		 }catch(YAML::Exception& e){ 
			Log::e(PARSER,"%s",e.what());
			exit(1);
		 }
		
		if (fElem && fAncho && fAlto && fAnchoP && fAltoP && fAgua && fTierra && fCielo){
			escenarioVect = escenario;
			//Log carga Nivel correctamente
		}
		else{
			if (!fElem){
				Log::e(PARSER,"Elemento no encontrado, seteando default");
			}
			if (!fAncho){
				Log::e(PARSER,"Ancho no encontrado, seteando default");
				escenario.ancho = "640";
			}
			if (!fAlto){
				Log::e(PARSER,"Alto no encontrado, seteando default");
				escenario.alto = "480";
			}
			if (!fAnchoP){
				Log::e(PARSER,"Ancho no encontrado, seteando default");
				escenario.ancho = "640";
			}
			if (!fAltoP){
				Log::e(PARSER,"Alto no encontrado, seteando default");
				escenario.alto = "480";
			}
			if (!fAgua){
				Log::e(PARSER,"Wlvl no encontrado, seteando default");
				escenario.agua="";
			}
			if (!fTierra){
				Log::e(PARSER,"Tierra no encontrado, seteando default");
				escenario.tierra="";
			}
			if (!fCielo){
				Log::e(PARSER,"Cielo no encontrado, seteando default");
				escenario.cielo="";
			}
			escenarioVect = escenario;
		}
	//}
	
}

/*
void ParserYaml::initializeElementMap(){
	for(unsigned i=0;i<this->getCantDataElem();i++){
		//std::cout<<"nombre: "<< aParser->getDataElemNombre(i)<<"\n\t";
		//std::cout<<"imagen: "<< aParser->getDataElemImagen(i)<<"\n\t";
		this->elementMap[ this->getDataElemNombre(i) ] = std::make_pair(i,this->getDataElemImagen(i));
	}
}*/

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

				Log::e(PARSER,"%s", e.what());
				Log::e(PARSER,"Iniciado juego con escenario default");
				this->startWithDefaultLevel();
				//exit(1);

			}

			for(YAML::Iterator it=node.begin();it!=node.end();++it){
				std::string key = this->yamlNodeToString(it.first());
				const YAML::Node& data = it.second();
				YAML::Mark mark = it.first().GetMark();
				if (key.compare("escenario")==0){
					fNivel = true;
					this->cargarNiveles(data,this->todo.escenario);
				}
				else{
					//LOG: key no es un identificador correcto del archivo de nivel + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e(PARSER,"%s no es un identificador correcto del archivo de escenario.", key);
				}
			}
			
			if(fNivel){
				//LOG: Se cargo el nivel correctamente
				Log::d(PARSER,"Se cargo el escenario correctamente");
				
			}
			else{
				//LOG: La carga del nivel guardado es incorrecta
				Log::e(PARSER,"La carga del escenario guardado es incorrecta");
				Log::e(PARSER,"Iniciando escenario con configuración default");
				this->startWithDefaultLevel();
				//exit(1);
			}
			fin.close();
		
		}catch(YAML::Exception& e){
			Log::e(PARSER,"%s", e.what());
			Log::e(PARSER,"Iniciando escenario con configuración default");
			this->startWithDefaultLevel();
		}
	
		fin.close();
	} else {
		//LOG: No se puede abrir el archivo de escenario
		Log::e(PARSER,"No se puede abrir el archivo de escenario");
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



/*
int ParserYaml::getCantDataElem(){
	return this->todo.dataE.size();
}
*//*
std::string ParserYaml::getDataElemNombre(int i){
	return this->todo.dataE[i].nombre;
}
*//*
std::string ParserYaml::getDataElemImagen(int i){
	return this->todo.dataE[i].imagen;

}*/

std::string ParserYaml::getEscenarioAltoU(){
	return this->todo.escenario.alto;
}

std::string ParserYaml::getEscenarioAnchoU(){
	return this->todo.escenario.ancho;
}

std::string ParserYaml::getEscenarioAltoP(){
	return this->todo.escenario.altoP;
}

std::string ParserYaml::getEscenarioAnchoP(){
	return this->todo.escenario.anchoP;
}

std::string ParserYaml::getEscenarioAgua(){
	return this->todo.escenario.agua;
}

std::string ParserYaml::getEscenarioTierra(){
	return this->todo.escenario.tierra;
}
std::string ParserYaml::getEscenarioCielo(){
	return this->todo.escenario.cielo;
}

int ParserYaml::getCantElem(){
	return this->todo.escenario.elem.size();
}

std::string ParserYaml::getElemTipo(int e){
	return this->todo.escenario.elem[e].tipo;
}
	
std::string ParserYaml::getElemX(int e){
	return this->todo.escenario.elem[e].x;
}

std::string ParserYaml::getElemY(int e){
	return this->todo.escenario.elem[e].y;
}

std::string ParserYaml::getElemAncho(int e){
	return this->todo.escenario.elem[e].ancho;
}

std::string ParserYaml::getElemAlto(int e){
	return this->todo.escenario.elem[e].alto;
}

std::string ParserYaml::getElemColor(int e){
	return this->todo.escenario.elem[e].color;
}

std::string ParserYaml::getElemMasa(int e){
	return this->todo.escenario.elem[e].masa;
}

std::string ParserYaml::getElemEstatico(int e){
	return this->todo.escenario.elem[e].estatico;
}

std::string ParserYaml::getElemRot(int e){
	return this->todo.escenario.elem[e].rot;
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




ParserYaml* ParserYaml::pInstance = NULL;