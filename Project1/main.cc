/*
 * main.cc - отсюда всё начинается.
 *
 *  Created on: 14 окт. 2020 г.
 *      Author: unyuu
 */


#include <iostream>
#include <stdexcept>
#include <locale>

#include <SDL.h>
#include <SDL_main.h>

#include "MyWindow.h"
#include "ExampleWindow.h"


// Самая главная функция!
int main(int, char**)
{
	// Инициализация SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	try {

		MyWindow w { 800, 600 };

		w.main_loop();


	} catch (const std::exception &e) {
		// Обработка стандартных исключений
		std::cerr <<
				"При выполнении программы возникла "
				"ошибка:" << std::endl <<
				e.what() << std::endl;
		return 1;
	} catch (...) {
		// Обработка неизвестных исключений
		std::cerr <<
				"При выполнении программы возникла "
				"неизвестная ошибка." << std::endl;
		return 1;
	}


	return 0;
}

