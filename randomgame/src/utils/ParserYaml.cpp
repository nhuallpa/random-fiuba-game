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


void ParserYaml::startWithDefaultElem(std::vector <stElemento>& vElem){
	stElemento elem;

	/* Para agregar uno o varios objetos default rapido copiar y pegar los parametros
	IMPORTANTE: recordar que no todos los objetos reciben los mismos parametros
	rec:
		tipo,id,x,y,rot,masa,alto,ancho,estatico,color
	tri:
		tipo,id,x,y,rot,masa,estatico,color	
	pent:
		tipo,id,x,y,rot,masa,escala,rot,estatico,color
	circ:
		tipo,id,x,y,rot,masa,escala,estatico,color,radio

	elem.tipo = "";
	elem.id = "";
	elem.escala = "";
	elem.x = "";
	elem.y = "";
	elem.alto = "";
	elem.ancho = "";
	elem.color = "";
	elem.estatico = "";
	elem.masa = "";
	elem.rot = "";
	elem.radio = "";
	vElem.push_back(elem);
	*/
	

}


void ParserYaml::startWithDefaultLevel(){
	this->levelFilePath = DEFAULT_YAML_LEVEL;
	this->isDefault = true;
	stMeta meta;
	
	meta.epsilon = "10";
	meta.scale = "12";

	stEscenario lvl;
	lvl.fps = "60";
	lvl.ancho = "400";
	lvl.alto = "400";
	lvl.agua = "20";
	lvl.altoP = "400";
	lvl.anchoP = "400";
	lvl.colorAgua = "#0000FF44";
	lvl.colorTierra = "#BC794FFF";
	lvl.cielo = "image/default.png";
	lvl.tierra = "tierra default";

	this->startWithDefaultElem(lvl.elem);

	this->todo.meta = meta;
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
			Log::d(PARSER,"Se carga informacion default");
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
	bool fId = false;
	bool fEscala = false;
	bool fRadio = false;

	
	elemVect.clear();//debo limpiar el elemVect de algun ciclo anterior

	for (unsigned i=0; i<nodeVect.size();i++){
		
		const YAML::Node& node = nodeVect[i];
		YAML::Mark mark = node.GetMark();

		for(YAML::Iterator it=node.begin();it!=node.end();++it){			
			std::string key = this->yamlNodeToString(it.first());
			if (key.compare("tipo")==0){
				elem.tipo = this->yamlNodeToString(it.second());
				if (this->esTipoValido(elem.tipo)){
					fNombre = true;
				}else
					Log::e(PARSER,"Valor incorrecto para atributo TIPO en linea: %d, columna: %d",(mark.line + 2),(mark.column + 1));
			}
			else if (key.compare("id")==0){
				fId = true;
				elem.id = this->yamlNodeToString(it.second());
			}

			else if (key.compare("escala")==0){
				elem.escala = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.escala)){
					fEscala = true;
				}else
					Log::e(PARSER,"Valor incorrecto para atributo ESCALA en linea: %d, columna: %d",(mark.line + 2),(mark.column + 1));
			}

			else if (key.compare("x")==0){
				elem.x = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.x)){
					std::string aux = elem.x;
					fX = true;
				}else
					Log::e(PARSER,"Valor incorrecto para atributo X en linea: %d, columna: %d",(mark.line + 2),(mark.column + 1));
			}
			else if (key.compare("y")==0){
				elem.y = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.y)){
					std::string aux = elem.y;
					fY = true;
				}else
					Log::e(PARSER,"Valor incorrecto para atributo Y en linea: %d, columna: %d",(mark.line + 3),(mark.column + 1));
			}
			else if (key.compare("ancho")==0){
				elem.ancho = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.ancho)){
					std::string aux = elem.ancho;
					fAncho = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo ANCHO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("alto")==0){
				elem.alto = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.alto)){
					std::string aux = elem.alto;
					fAlto = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo ALTO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("color")==0){
				elem.color = this->yamlNodeToString(it.second());
				if (this->esHexa(elem.color)){
					std::string aux = elem.color;
					fColor = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo COLOR en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("masa")==0){
				elem.masa = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.masa)){
					std::string aux = elem.masa;
					fMasa = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo MASA en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("estatico")==0){
				elem.estatico = this->yamlNodeToString(it.second());
				if (this->estaticoValido(elem.estatico)){
					std::string aux = elem.estatico;
					fEstatico = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo ESTATICO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("rot")==0){
				elem.rot = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.rot)){
					std::string aux = elem.rot;
					fRot = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo ROT en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else if (key.compare("radio")==0){
				elem.radio = this->yamlNodeToString(it.second());
				if (this->esNumero(elem.radio)){
					fRadio = true;
				} else
					Log::e(PARSER,"Valor incorrecto para atributo RADIO en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}
			else {
				Log::e(PARSER,"Atributo incorrecto en linea: %d, columna: %d",(mark.line + 4),(mark.column + 1));
			}

		}
		if (!fNombre) elem.tipo = "no init";

		if (validarGuardar(elem.tipo,fNombre,fId,fEscala,fX,fY,fRot,fMasa,fAlto,fAncho,fEstatico,fColor,fRadio)){

			elemVect.push_back(elem);
			//Log se carga el elemento correctamente
		}
		else{
			loggearErrGuardar(elem.tipo,fNombre,fId,fEscala,fX,fY,fRot,fMasa,fAlto,fAncho,fEstatico,fColor,fRadio,mark);
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
		fId = false;
		fEscala = false;
		fRadio = false;
	
	
	}

}

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
	bool fFPS = false;
	bool fCAgua = false;
	bool fCTierra = false;
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
				
				else if (key.compare("color_agua")==0){

					escenario.colorAgua = this->yamlNodeToString(it.second());
					if (this->esHexa(escenario.colorAgua)){
						fCAgua = true;
					} else
						Log::e(PARSER,"Valor incorrecto para atributo COLOR_AGUA en nodo linea: %d.",(mark.line + 1));
				}

				else if (key.compare("imagen_tierra")==0){

					escenario.tierra = this->yamlNodeToString(it.second());
					//if (this->esNumero(escenario.tierra)){
						std::string aux = escenario.tierra;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(escenario.tierra) != 0)
							Log::d(PARSER,"Truncado valor de atributo TIERRA en nodo linea: %d.",(mark.line + 1));
							fTierra = true;
						//} else
							//Log::e(PARSER,"Valor incorrecto para atributo TIERRA en nodo linea: %d.",(mark.line + 1));
				}
				else if (key.compare("color_tierra")==0){

					escenario.colorTierra = this->yamlNodeToString(it.second());
					if (this->esHexa(escenario.colorTierra)){
						fCTierra = true;
					} else
						Log::e(PARSER,"Valor incorrecto para atributo COLOR_TIERRA en nodo linea: %d.",(mark.line + 1));
				}

				else if (key.compare("imagen_cielo")==0){

					escenario.cielo = this->yamlNodeToString(it.second());
					//if (this->esNumero(escenario.cielo)){
						std::string aux = escenario.cielo;
						//nivel.alto = this->validaPantalla(nivel.alto);
						if (aux.compare(escenario.cielo) != 0)
							Log::d(PARSER,"Truncado valor de atributo CIELO en nodo linea: %d.",(mark.line + 1));
							fCielo = true;
						//} else
							//Log::e(PARSER,"Valor incorrecto para atributo CIELO en nodo linea: %d.",(mark.line + 1));
				}
				else if (key.compare("fps")==0){

					escenario.fps = this->yamlNodeToString(it.second());
					if (this->esNumero(escenario.fps)){
						fFPS = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo FPS en nodo linea: %d.",(mark.line + 1));
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
		
		if ( fCAgua && fCTierra && fFPS && fElem && fAncho && fAlto && fAnchoP && fAltoP && fAgua && fTierra && fCielo){
			escenarioVect = escenario;
			//Log carga Nivel correctamente
		}
		else{
			if (!fElem){
				Log::e(PARSER,"Elemento no encontrado, seteando default");
			}
			if (!fFPS){
				Log::e(PARSER,"FPS no encontrado, seteando default");
				escenario.fps = "60";
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
			if (!fCAgua){
				Log::e(PARSER,"Color_agua no encontrado, seteando default");
				escenario.colorAgua="";
			}
			if (!fTierra){
				Log::e(PARSER,"Tierra no encontrado, seteando default");
				escenario.tierra="";
			}
			if (!fCTierra){
				Log::e(PARSER,"Color_tierra no encontrado, seteando default");
				escenario.colorTierra="";
			}
			if (!fCielo){
				Log::e(PARSER,"Cielo no encontrado, seteando default");
				escenario.cielo="";
			}
			escenarioVect = escenario;
		}
	//}
	
}

void ParserYaml::cargarMeta(const YAML::Node& nodeVect,stMeta& esMeta){
	stMeta meta;
	//bool fNombre = false;
	bool fEps = false;
	bool fSca = false;
	
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
				
				if (key.compare("epsilon")==0){

					meta.epsilon = this->yamlNodeToString(it.second());
					if (this->esNumero(meta.epsilon)){
					fEps = true;
					} else
						Log::e(PARSER,"Valor incorrecto para atributo EPSILON en nodo linea: %d.",(mark.line + 1));
				}
				else if (key.compare("scale")==0){

					meta.scale = this->yamlNodeToString(it.second());
					if (this->esInt(meta.scale)){
						fSca = true;
						} else
							Log::e(PARSER,"Valor incorrecto para atributo SCALE en nodo linea: %d.",(mark.line + 1));
				}
				else {
					//LOG: key no es un identificador correcto del nivel + line +std::to_string(mark.line + 1) + column +std::to_string(mark.column + 1)
					Log::e(PARSER,"Metadata key no es un identificador correcto de metadata. Linea: %d, Columna: %d",(mark.line + 1),(mark.column + 1));
				}
			 }
			}catch(YAML::Exception& e){ 
			Log::e(PARSER,"%s",e.what());
			exit(1);
		 }
		 if ( fEps && fSca){
			esMeta = meta;
			//Log carga Nivel correctamente
		}
		else{
			if (!fEps){
				Log::e(PARSER,"epsilon no encontrado, seteando default");
				meta.epsilon = "10";
			}
			if (!fSca){
				Log::e(PARSER,"scale no encontrado, seteando default");
				meta.scale = "10";
			}
		}
		esMeta = meta;

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
	bool fMeta = false;

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
				else if (key.compare("metadata")==0){
					fMeta = true;
					this->cargarMeta(data,this->todo.meta);
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
			if(fMeta){
				//LOG: Se cargo el nivel correctamente
				Log::d(PARSER,"Se cargo la metadata correctamente");
				
			}
			else{
				//LOG: La carga del nivel guardado es incorrecta
				Log::e(PARSER,"La carga de la metadata guardado es incorrecta");
				Log::e(PARSER,"Iniciando metadata con configuración default");
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




//+++++geters++++++

std::string ParserYaml::getMetaEps(){
	return this->todo.meta.epsilon;
}

std::string ParserYaml::getMetaSca(){
	return this->todo.meta.scale;
}



std::string ParserYaml::getEscenarioFps(){
	return this->todo.escenario.fps;
}

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

std::string ParserYaml::getEscenarioColorAgua(){
	return this->todo.escenario.colorAgua;
}
std::string ParserYaml::getEscenarioTierra(){
	return this->todo.escenario.tierra;
}
std::string ParserYaml::getEscenarioColorTierra(){
	return this->todo.escenario.colorTierra;
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

std::string ParserYaml::getElemId(int e){
	return this->todo.escenario.elem[e].id;
}

std::string ParserYaml::getElemEscala(int e){
	return this->todo.escenario.elem[e].escala;
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
std::string ParserYaml::getElemRadio(int e){
	return this->todo.escenario.elem[e].radio;
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


std::string ParserYaml::validaAngulo(std::string ang){
	return "";
}


std::string ParserYaml::validaPosicion(std::string pos){
	return ""; }


std::string ParserYaml::validaPantalla(std::string tam){
	return "";
	}


bool ParserYaml::esInt(std::string str){
	for (unsigned int i=0;i<str.length();i++)
		if (isdigit(str[i])==0) return false;
	return true;

}

bool ParserYaml::esNumero(std::string str){
	int len = str.length();
	int i = 0;
	int ret = 1;
	int deccnt = 0;
	while(i < len && ret != 0)
    {
        if(str[i] == '.')           // is there a decimal
        {
            deccnt++;               // count a decimal
            if(deccnt > 1)          // is there too many decimal points
                ret = 0;            // too many decimals set return for not numeric
        }
        else
            ret = isdigit(str[i]); // is this character numeric
        i++;                       // increment to next character
    }
	// return result =0 not numeric !=0 is numeric
	if (ret == 0) return false;
	else return true;

}
bool ParserYaml::esHexa(std::string str){
	int len = str.length();
	int i = 1;
	bool ret = true;
	if (len != 9) return false;
	//else return true;
	if (str[0] != '#') return false;
	while(i < len && ret != 0)
    {
        if ((isdigit(str[i]) || str[i]=='A' || str[i]=='B' || str[i]=='C' || str[i]=='D' || str[i]=='E' || str[i]=='F') == false) return false;
        i++;                       // increment to next character
    }
	// return result =0 not numeric !=0 is numeric
	if (ret == false) return false;
	else return true;
}

bool ParserYaml::esHexaSdl(std::string str){
	int len = str.length();
	int i = 1;
	bool ret = true;
	if (len != 9) return false;
	//else return true;
	if (str[0] != '#') return false;
	while(i < 7 && ret != 0)
    {
        if ((isdigit(str[i]) || str[i]=='A' || str[i]=='B' || str[i]=='C' || str[i]=='D' || str[i]=='E' || str[i]=='F') == false) return false;
        i++;                       // increment to next character
    }
	// return result =0 not numeric !=0 is numeric
	if (ret == false) return false;
	if (str[7] != 'A') return false;
	if (str[8] != 'A') return false;
	return true;
}


bool ParserYaml::esTipoValido(std::string str){
	if ((str.compare("rec")==0) || (str.compare("tri")==0) || (str.compare("pent")==0) || (str.compare("circ")==0)) return true;
	return false;


}
bool ParserYaml::validarGuardar(std::string str,bool fNombre,bool fId,bool fEscala,bool fX,bool fY,bool fRot,bool fMasa,bool fAlto,bool fAncho,bool fEstatico,bool fColor,bool fRadio){
	
	if ((str.compare("rec")==0) && (fEscala || fRadio) ) return false;
	if ((str.compare("rec")==0) && fId && fNombre && fX && fY && fRot && fMasa && fAlto && fAncho && fEstatico && fColor) return true;
	if ((str.compare("tri")==0) && (fAlto || fAncho || fRadio)) return false;
	if ((str.compare("tri")==0) && fId && fNombre && fX && fY && fEscala && fRot && fMasa && fEstatico && fColor) return true;
	if ((str.compare("pent")==0) && (fAlto || fAncho || fRadio)) return false;
	if ((str.compare("pent")==0) && fId && fNombre && fX && fY && fEscala && fRot && fMasa && fEstatico && fColor) return true;
	if ((str.compare("circ")==0) && (fAlto || fAncho))return false;	
	if ((str.compare("circ")==0) && fId && fNombre && fX && fY && fEscala && fRot && fMasa && fEstatico && fColor && fRadio) return true;	

	return false;
}

void ParserYaml::loggearErrGuardar(std::string str,bool fNombre,bool fId,bool fEscala,bool fX,bool fY,bool fRot,bool fMasa,bool fAlto,bool fAncho,bool fEstatico,bool fColor,bool fRadio,YAML::Mark mark){
	if (str.compare("rec")==0){
		if (!fId)Log::d(PARSER,"Atributo ID faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::d(PARSER,"Atributo TIPO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::d(PARSER,"Atributo X faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 2),(mark.column + 1));
		if (!fY) Log::d(PARSER,"Atributo Y faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 3),(mark.column + 1));
		if (!fRot) Log::d(PARSER,"Atributo ROT faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fMasa) Log::d(PARSER,"Atributo MASA faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fAlto) Log::d(PARSER,"Atributo ALTO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fAncho) Log::d(PARSER,"Atributo ANCHO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fEstatico) Log::d(PARSER,"Atributo ESTATICO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fColor) Log::d(PARSER,"Atributo COLOR faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));

		if (fEscala) Log::d(PARSER,"Atributo ESCALA sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (fRadio) Log::d(PARSER,"Atributo RADIO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
	}
	else if (str.compare("tri")==0){
		if (!fId)Log::d(PARSER,"Atributo ID faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::d(PARSER,"Atributo TIPO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::d(PARSER,"Atributo X faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 2),(mark.column + 1));
		if (!fY) Log::d(PARSER,"Atributo Y faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 3),(mark.column + 1));
		if (!fEscala) Log::d(PARSER,"Atributo ESCALA faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 3),(mark.column + 1));
		if (!fRot) Log::d(PARSER,"Atributo ROT faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fMasa) Log::d(PARSER,"Atributo MASA faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fEstatico) Log::d(PARSER,"Atributo ESTATICO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fColor) Log::d(PARSER,"Atributo COLOR faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		
		if (fAlto) Log::d(PARSER,"Atributo ALTO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (fAncho) Log::d(PARSER,"Atributo ANCHO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (fRadio) Log::d(PARSER,"Atributo RADIO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
	}
	else if (str.compare("pent")==0){

		if (!fId)Log::d(PARSER,"Atributo ID faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::d(PARSER,"Atributo TIPO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::d(PARSER,"Atributo X faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 2),(mark.column + 1));
		if (!fY) Log::d(PARSER,"Atributo Y faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 3),(mark.column + 1));
		if (!fRot) Log::d(PARSER,"Atributo ROT faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fMasa) Log::d(PARSER,"Atributo MASA faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fEstatico) Log::d(PARSER,"Atributo ESTATICO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fEscala) Log::d(PARSER,"Atributo ESCALA faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fColor) Log::d(PARSER,"Atributo COLOR faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));

		if (fAlto) Log::d(PARSER,"Atributo ALTO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (fAncho) Log::d(PARSER,"Atributo ANCHO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (fRadio) Log::d(PARSER,"Atributo RADIO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));

	}
	else if (str.compare("circ")==0){
		if (!fId)Log::d(PARSER,"Atributo ID faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (!fNombre)Log::d(PARSER,"Atributo TIPO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (!fX) Log::d(PARSER,"Atributo X faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 2),(mark.column + 1));
		if (!fY) Log::d(PARSER,"Atributo Y faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 3),(mark.column + 1));
		if (!fRot) Log::d(PARSER,"Atributo ROT faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fMasa) Log::d(PARSER,"Atributo MASA faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fEstatico) Log::d(PARSER,"Atributo ESTATICO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fColor) Log::d(PARSER,"Atributo COLOR faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fEscala) Log::d(PARSER,"Atributo ESCALA faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));
		if (!fRadio) Log::d(PARSER,"Atributo RADIO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 4),(mark.column + 1));

		if (fAlto) Log::d(PARSER,"Atributo ALTO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
		if (fAncho) Log::d(PARSER,"Atributo ANCHO sobrante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
	}
	else if (str.compare("no init")==0){
		if (!fNombre)Log::d(PARSER,"Atributo TIPO faltante en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
	}
	else Log::d(PARSER,"Atributo TIPO incorrecto en linea: %d, columna: %d, descartando nodo.",(mark.line + 1),(mark.column + 1));
}

bool ParserYaml::estaticoValido(std::string str){
	if (str.compare("si") == 0) return true;
	if (str.compare("no") == 0) return true;
	return false;
}


ParserYaml* ParserYaml::pInstance = NULL;