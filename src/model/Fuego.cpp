#include "Fuego.h"
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../view/ComponenteVistaFuego.h"

Fuego::Fuego(int posX, int posY, SDL_Renderer* renderer) 
: Entidad(posX, posY, ANCHO_FUEGO, ALTO_FUEGO) {
    compVista = new ComponenteVistaFuego(posX, posY, renderer);
}

void Fuego::mostrar(SDL_Renderer* renderer) {
    compVista->mostrar(renderer);
}

void Fuego::mover() {}

void Fuego::destruir() {
    delete compVista;
}