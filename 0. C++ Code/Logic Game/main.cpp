//
//  main.cpp
//
//  Copyright � 2018 Compiled Creations Limited. All rights reserved.
//

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */ 

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "Tetris.h"
#include "./InfoJoc.h"


int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    

    double deltaTime = 0;
    Tetris tetris;
    int modeJoc;
    tetris.recuperaPuntuacions();
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);
    do
    {   
        modeJoc = tetris.menuTetris();
        switch (modeJoc)
        {
        case 1:
        case 2:
            tetris.juga(pantalla, deltaTime, modeJoc);
            break;
        case 3:
            tetris.mostraPuntuacions();
            break;
        case 4:
            cout << "Sortint del programa..." << endl;
            break;
        default:
            cout << "ERROR: Selecciona una opcio valida: " << endl; 
            break;
        }
        cout << endl;
    } while (modeJoc != 4);
    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();

    return 0;
}

