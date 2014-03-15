#pragma once

#define MENU_WIDTH  140
#define USER_BAR_HEIGHT 80



#define SPRITES_WIDTH 48
#define SPRITES_HEIGHT 48

#define ELEM_WIDTH 10
#define ELEM_HEIGHT 10

#define LOGIC_UNITS 100


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define ALIGN_SPRITE 50
#define ARROW_Y_POS 15

#define CONFIG_IMAGES 4





/****************************************************************************************************/
/** Archivo de configuracion que reune todos los valores constantes que se utilizan en el proyecto **/
/****************************************************************************************************/

/**************************** Directorios ****************************/
#define DIRECTORIO_IMG "./img"
#define DIRECTORIO_CONFIG "./config"

/**************************** Log ****************************/
#define LOG_RUTA "./DI_Log.txt"
#define LOG_NIVEL LOG_NIVEL_DEBUG_ALTO  /* <<< Acá se cambia el nivel del log, se usa uno de los de abajo */
#define LOG_NIVEL_RELEASE 1		/* Nivel 1: Release, Nivel 2: Debug Bajo, Nivel 3: Debug Alto, se pueden habilitar niveles mas altos. El nivel elegido incluye los niveles inferiores*/
#define LOG_NIVEL_DEBUG_BAJO 2
#define LOG_NIVEL_DEBUG_ALTO 3

// Para setear el uso del archivo de log
#define LOG_ESCRITURA LOG_ON  // <<< Acá se setea, se puede poner LOG_OFF o LOG_ON
#define LOG_OFF 0
#define LOG_ON 1

/**************************** SDL ****************************/
// Para el ejemplo SDL
#define PANTALLA_ANCHO 640
#define PANTALLA_ALTO 480
#define TAMANIO_SPRITE 32


/*********************CONTROLES EN PANTALLA ******************/
#define DEFAULT_FONT "./src/utils/Fonts/verdana.ttf"

/**************************** YAML ***************************/

#define YAML_RUTA_ARCHIVO_JUEGO "./config/juego.yaml"
#define YAML_RUTA_ARCHIVO_CONEXION "./config/conexion.yaml"
#define YAML_RUTA_DIRECTORIO_IMG "./img/"
#define YAML_RUTA_DIRECTORIO_JUEGOS "./config/"

#define YAML_STRING_VACIO ""
#define YAML_ERROR_INT -1

#define YAML_TIPO_STRING "Cadena de caracteres"
#define YAML_TIPO_INT "Entero"

#define YAML_DEAFAULT_PANTALLA_ALTO 600
#define YAML_DEAFAULT_PANTALLA_ANCHO 800
#define YAML_DEAFAULT_VEL_PERSONAJE 100
#define YAML_DEAFAULT_MARGEN_SCROLL 20
#define YAML_DEAFAULT_NOMBRE "default"
#define YAML_DEAFAULT_RUTA_IMAGEN "default.png"
#define YAML_DEAFAULT_ANCHO_BASE 1
#define YAML_DEAFAULT_ALTO_BASE 1
#define YAML_DEAFAULT_PIXEL_REF_X 0
#define YAML_DEAFAULT_PIXEL_REF_Y 0
#define YAML_DEAFAULT_FPS 15
#define YAML_DEAFAULT_DELAY 1
#define YAML_DEAFAULT_ALTO_NIVEL 100
#define YAML_DEAFAULT_ANCHO_NIVEL 100

#define YAML_PANTALLA_ALTO_TOPE_MINIMO 1
#define YAML_PANTALLA_ALTO_TOPE_MAXIMO 1080
#define YAML_PANTALLA_ANCHO_TOPE_MINIMO 1
#define YAML_PANTALLA_ANCHO_TOPE_MAXIMO 1920
#define YAML_VELOCIDAD_PERSONAJE_TOPE_MINIMO 0
#define YAML_VELOCIDAD_PERSONAJE_TOPE_MAXIMO 5000
#define YAML_MARGEN_SCROLL_TOPE_MINIMO 1
#define YAML_PERSONAJE_LONGITUD_MAXIMA 50
#define YAML_FPS_TOPE_MAXIMO 99
#define YAML_DELAY_TOPE_MAXIMO 99
#define YAML_CANTIDAD_OBLIGATORIA_DE_ANIMACIONES_PROTAGONISTA 24
