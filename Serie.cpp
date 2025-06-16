/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

#include "Serie.h"

    Serie::Serie(const int _id, string _nombre, string _genero):
    Video(_id,_nombre,0,_genero){};
    Serie::~Serie() = default;

    vector<Video*> Serie::GetEpisodios() const{
        return episodios;
    }
    void Serie::Presentar(){
        cout<< id <<".- |"<< nombre << "| ------- Calificación: " << GetCalificacion() << endl
        << "   Capítulos: " << duration
        <<"\n   Genero: "<< genero
        << "\n   Calificado por: " << calificaciones.size() << " usuarios." << endl;
    }

    void Serie::MostrarEpisodios() const {
        for (Video* cap : episodios) {
            cap->Presentar();
        }
    }

    void Serie::AddEpisodio(Video* episodio) {
        try {
            for (const Video* cap : episodios) {
                if (cap->GetId() == episodio->GetId())
                    throw invalid_argument("Este id ya existe en esta serie. Por favor escoja otro.");
            }
            episodios.push_back(episodio);
            duration++;
        } catch (exception& e) {
            cerr << "InvalidObjectIdException: " << e.what() << endl;
        }
    }
