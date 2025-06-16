//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#include "Pelicula.h"

    Pelicula::Pelicula(const int _id, string _nombre,const int _duration, string _genero):
    Video(_id,std::move(_nombre),_duration,std::move(_genero)){};
    Pelicula::~Pelicula() = default;
    void Pelicula::presentar() {
        cout<< id <<".- |"<< nombre << "| ------- Calificación: " << getCalificacion() << endl
        << "   Duración: " << formatDuration()
        << "\n   Genero: "<< genero
        << "\n   Calificado por: " << calificaciones.size() << " usuarios." << endl;
    }
