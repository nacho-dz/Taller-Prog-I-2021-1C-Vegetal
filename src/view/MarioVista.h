#pragma once

#include <SDL2/SDL.h>
#include "../utils/marioStructs.h"

class MarioVista
{
public:
    MarioVista(SDL_Renderer *renderer);
    MarioVista(const MarioVista &other);
    void mostrar(const estadoMario_t &estado);
    void setColor(int color);
    ~MarioVista();

private:
    static SDL_Renderer *renderer;
    static SDL_Texture *texture;
    static size_t totalJugadores;
    SDL_Rect srcRect;
    SDL_Rect dstRect;
    SDL_RendererFlip flip{SDL_FLIP_HORIZONTAL};
    int tiempo{0};

    void updateReposo(char estado);
    void updateCorriendo(int nextX);
    void updateSaltando(int nextX);
    void updateTrepando(int nextY);
    void updateDesconectado(int nextX, int nextY);
};