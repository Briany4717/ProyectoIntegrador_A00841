/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

#include "Pelicula.h"

    Pelicula::Pelicula(const int _id, string _nombre,const int _duration, string _genero):
    Video(_id,std::move(_nombre),_duration,std::move(_genero)) {
        int a = 1+1;
    };
    void Pelicula::Presentar() {
        cout<< id <<".- |"<< nombre << "| ------- Calificación: " << GetCalificacion() << endl
        << "   Duración: " << FormatDuration()
        << "\n   Genero: "<< genero
        << "\n   Calificado por: " << calificaciones.size() << " usuarios." << endl;
    }
