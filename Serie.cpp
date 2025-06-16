//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#include "Serie.h"

    Serie::Serie(const int _id, string _nombre, string _genero):
    Video(_id,std::move(_nombre),0,std::move(_genero)){};
    Serie::~Serie() = default;

    vector<Video*> Serie::getEpisodios() const{
        return episodios;
    }
    void Serie::presentar(){
        cout<< id <<".- |"<< nombre << "| ------- Calificación: " << getCalificacion() << endl
        << "   Capítulos: " << duration
        <<"\n   Genero: "<< genero
        << "\n   Calificado por: " << calificaciones.size() << " usuarios." << endl;
    }

    void Serie::mostrarEpisodios() const {
        for (Video* cap : episodios) {
            cap->presentar();
        }
    }

    void Serie::addEpisodio(Video* episodio) {
        try {
            for (const Video* cap : episodios) {
                if (cap->getId() == episodio->getId())
                    throw invalid_argument("Este id ya existe en esta serie. Por favor escoja otro.");
            }
            episodios.push_back(episodio);
            duration++;
        } catch (exception& e) {
            cerr << "InvalidObjectIdException: " << e.what() << endl;
        }
    }
