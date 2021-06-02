#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include "model/Entidad.h"
#include "model/Nivel1.h"
#include "model/Nivel2.h"
#include "model/Barril.h"
#include "model/Fuego.h"
#include "model/PlataformaMovil.h"
#include "model/EnemigoFuego.h"
#include "model/Peach.h"
#include "model/Mario.hpp"
#include "model/DonkeyKong.h"
#include "model/FactoryEnemigos.h"
#include "configuration.hpp"
#include "logger.h"
#include "utils/window.hpp"
#include "utils/Constants.hpp"
#include "controller/MarioController.h"

int main(void)
{
    logger::Logger::getInstance().logNewGame();
    
    auto configuration = configuration::GameConfiguration(CONFIG_FILE);
    auto log_level = configuration.getLogLevel();
    logger::Logger::getInstance().setDebugLevel(log_level);

    // TODO: Handle errors...
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow(NOMBRE_JUEGO.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, ANCHO_PANTALLA, ALTO_PANTALLA, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    bool terminarPrograma = false;

    SDL_Event event;
    
    Nivel1 n1(renderer, configuration.getDefaultConfigFlag());
    Nivel2 n2(renderer, configuration.getDefaultConfigFlag());

    Mario mario(N1_MARIO_POS_X, N1_MARIO_POS_Y, renderer);
    MarioController marioController(&mario);

    n1.agregarObjeto(&mario);
    n1.inicializarObjetos(renderer);
    
    FactoryEnemigos factoryEnem;
    auto enemies = configuration.getEnemies();
    for (auto enemy: enemies)
    {
        for(unsigned int i = 0; i < enemy.getQuantity(); i++) {
            Coordenada posAleatoria = n1.getPosicionAleatoria();
            Entidad* enemigo = factoryEnem.crearEnemigo(enemy.getType(), posAleatoria.getX(), posAleatoria.getY(), renderer);
            
            if(enemigo != NULL)
                n1.agregarObjeto(enemigo);
        }

        logger::Logger::getInstance().logDebug("Enemy type: " + enemy.getType());
        logger::Logger::getInstance().logDebug("Enemy quantity: " + std::to_string(enemy.getQuantity()));
    }

    auto stages = configuration.getStages();
    for (unsigned int i = 0; i < stages.size(); ++i) {
        if (i == 0) {
            logger::Logger::getInstance().logDebug("Stage 1 background img: " + stages[i].getBackgrounds()[0]);
            n1.setFondo(stages[i].getBackgrounds()[0]);
        } else if (i == 1) {
            logger::Logger::getInstance().logDebug("Stage 2 background img: " + stages[i].getBackgrounds()[0]);
            n2.setFondo(stages[i].getBackgrounds()[0]);
        }
    }

    
    // http://gameprogrammingpatterns.com/game-loop.html#play-catch-up
    Uint32 previous, current, elapsed, lag, updated;
    previous = SDL_GetTicks();
    lag = 0;

    while(!terminarPrograma) {
        current = SDL_GetTicks();
        elapsed = current - previous;
        previous = current;
        lag += elapsed;

        // Handle event
        while(SDL_PollEvent(&event)) {
            terminarPrograma = (event.type == SDL_QUIT);
            
            // Cambio de nivel
            if (event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_TAB) {
                logger::Logger::getInstance().logInformation("End of Level 1");
                goto nivel2;
            }

            // Handle input for Mario
            marioController.handleEvent(&event);
        }

        // Update Model
        updated = 0;
        while (lag >= MS_PER_UPDATE) {
            n1.actualizarNivel();
            lag -= MS_PER_UPDATE;
            ++updated;
        }

        // Update View and render
        if (updated) {
            SDL_RenderClear(renderer);
            n1.actualizarVista();
            SDL_RenderPresent(renderer);
        }
    }

    nivel2:
    SDL_RenderClear(renderer);

    n2.agregarObjeto(&mario);
    n2.inicializarObjetos(renderer);
    logger::Logger::getInstance().logInformation("Level 2 starts");

    mario.setStartPos(N2_MARIO_POS_X, N2_MARIO_POS_Y);

    previous = SDL_GetTicks();
    lag = 0;
    while(!terminarPrograma) {
        current = SDL_GetTicks();
        elapsed = current - previous;
        previous = current;
        lag += elapsed;

        // Handle event
        while(SDL_PollEvent(&event)) {
            terminarPrograma = (event.type == SDL_QUIT);

            // Fin del nivel
            if(event.type == SDL_KEYDOWN && event.key.repeat == 0 && event.key.keysym.sym == SDLK_TAB) {
                logger::Logger::getInstance().logInformation("End of Level 2");
                goto fin;
            }

            // Handle input for mario
            marioController.handleEvent(&event);
        }

        // Update Model
        updated = 0;
        while (lag >= MS_PER_UPDATE) {
            n2.actualizarNivel();
            lag -= MS_PER_UPDATE;
            updated++;
        }

        // Update View and render
        if (updated) {
            SDL_RenderClear(renderer);
            n2.actualizarVista();
            SDL_RenderPresent(renderer);
        }
    };

    fin:
    logger::Logger::getInstance().logInformation("Game over");

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
} 
