#pragma once

#include <string>
#include "Entidad.h"
#include "../view/ComponenteVistaEntidadEstatica.h"

class FireBarrel : public Entidad {
    public:
        FireBarrel(SDL_Renderer* renderer);
        void mostrar(Uint32 frames);
        void mover();
        std::string getRutaImagen();

    private:
        ComponenteVistaEntidadEstatica* compVista;
        static std::string rutaImagen;
};