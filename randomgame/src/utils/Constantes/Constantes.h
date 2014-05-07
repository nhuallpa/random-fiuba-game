#pragma once

#ifndef __COSNTANTES__H_
#define __COSNTANTES__H_

#define TIME_STEP 30.0

#define MENU_WIDTH  140
#define USER_BAR_HEIGHT 80



#define SPRITES_WIDTH 48
#define SPRITES_HEIGHT 48

#define ELEM_WIDTH 10
#define ELEM_HEIGHT 10

#define LOGIC_UNITS 100

#define DELTA 20 // delta del scroll
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define ALIGN_SPRITE 50
#define ARROW_Y_POS 15

#define CONFIG_IMAGES 6

#define BACKGROUND "background"
#define ARROW_BUTTON "arrow"
#define SAVE_BUTTON "save"
#define EXIT_BUTTON "exit"
#define LOAD_BACK_BUTTON "loadButton"

#define DEFAULT_YAML_LEVEL "default_level.yaml"
#define CONFIG_FILE "config/config.yaml"

#define VERDE 0xFF3ADF00
#define AMARILLO 0xFF00BFFF
#define CELESTE 0xFFD7DF01
#define VIOLETA 0xFFDF01D7



/****************************************************************************************************/
/** Archivo de configuracion que reune todos los valores constantes que se utilizan en el proyecto **/
/****************************************************************************************************/

/** 1 Unidad logica equivale a 10 pixels*/
#define ESCALA_UL2PX  10

/**************************** Log ****************************/
#define LOG_RUTA "./DI_Log.txt"
#define LOG_MAX_LINE_SIZE 512

// Para setear el uso del archivo de log
#define LOG_ESCRITURA LOG_ON  // <<< Acá se setea, se puede poner LOG_OFF o LOG_ON
#define LOG_OFF 0
#define LOG_ON 1

/**************************** SDL ****************************/


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


/**************************** LOG2 ***************************/


/**************************** HANDLE CONTOUR ***************************/
#define HC_OFFSET 1000
#define HC_ERROR_1 /*1001*/ "Existen Lineas superpuestas"
#define HC_ERROR_2 /*1002*/ "Los puntos no esta en orde horario"
#define HC_ERROR_3 /*1003*/ "Existen Lineas superpuestas y ademas los puntos no esta en orde antihorario"
#define HC_ERROR_4 /*1004*/ "Error desconocido"
#define HC_INFO_VAL  "INICIANDO PROCESAMIENTO DE POLIGONOS"
#define HC_TRACE_VAL  "Chequeando la validacion del contorno"
#define HC_TRACE_RDP  "Procesando la eliminacion de puntos en el contorno"
#define HC_TRACE_SHAPES  "Procesando las formas para los poligonos"
#define HC_TRACE_MAX_VERTEX  "Procesando separacion de puntos por poligono"


/**************************** HANDLE CONTOUR ***************************/

/**************************** HANDLE PLAYER ***************************/
#define HP_OFFSET 2000
#define HP_ERROR_1 /*2001*/ "El nivel no admite mas jugadores"
#define HP_ERROR_2 /*2002*/ "Ocurrio un error al intentar agregar un jugador"
/**************************** HANDLE PLAYER ***************************/


#define LOG_PATH "./LOG"

#endif /*__COSNTANTES__H_*/