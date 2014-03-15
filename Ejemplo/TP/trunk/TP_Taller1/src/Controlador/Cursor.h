/*
 * Cursor.h
 *
 *  Created on: 11/10/2013
 *  Last Amended: 11/10/2013
 *      Author: natuchis
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include <string>

class SDL_Cursor;

class Cursor {
public:
	Cursor ();
	Cursor (std::string path, int x = 0, int y = 0);

	Cursor (const Cursor&) = delete;
	Cursor (Cursor&&);
	Cursor& operator= (const Cursor&) = delete;
	Cursor& operator= (Cursor&&);
	~Cursor();

	void mostrar();
	void ocultar();
	void activar();

private:
	SDL_Cursor *cursor;
};

#endif /* CURSOR_H_ */
