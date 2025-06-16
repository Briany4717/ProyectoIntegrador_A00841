//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#include "Episodio.h"

    Episodio::Episodio(const int _id, string _nombre,const int _duration, string _genero):
    Video(_id,std::move(_nombre),_duration,std::move(_genero)){};

    void Episodio::presentar() {
        cout << id << ".- Titulo: " << nombre
                 << " Duración: " << formatDuration()
                 << " Calificación: " << getCalificacion() << endl;
    };