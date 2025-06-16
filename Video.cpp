//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#include "Video.h"

    Video::Video(const int _id, string _nombre,const int _duration, string _genero):
    id(_id),nombre(std::move(_nombre)),duration(_duration),
    genero(std::move(_genero)){};

    int Video::getId() const {
        return id;
    }
    string Video::getNombre()const {
        return nombre;
    }
    int Video::getDuration()const {
        return duration;
    }
    string Video::getGenero()const {
        return genero;
    }
    double Video::getCalificacion() const {
        if (calificaciones.empty()) {
            return 0.0;  // O cualquier otro valor por defecto
        }

        double promedio = 0;
        for (int cal : calificaciones) {
            promedio += cal;
        }
        return promedio / static_cast<double>(calificaciones.size());
    }

    bool Video::calificar(const int calif) {
        try {
            if (calif < 0 || calif >5) throw invalid_argument("Calificación invalida. Debe ser un número entre 0 y 5 incluyente.");
            calificaciones.push_back(calif);
            return true;
        }catch (exception& e) {
            cerr << e.what() << endl;
            return false;
        }
    };
    string Video::formatDuration() const {
        const int hours = duration / 3600;
        const int minutes = (duration % 3600) / 60;
        const int seconds = (duration % 3600) % 60;
        try {
            stringstream ss;
            if (duration >= 3600) {
                ss << hours << (minutes<10?":0":":") << minutes << (seconds<10?":0":":") << seconds << " horas";
            } else if (duration >= 60) {
                ss << (minutes<10?"0":"") << minutes << (seconds<10?":0":":") << seconds << " minutos";
            } else if (duration >= 1) {
                ss << (seconds<10?"0":"") << seconds << " segundos";
            } else {
                ss << "El video con id " << id << "tiene una duración invalida de "<< duration << "s. Imposible formatear.";
                throw invalid_argument(ss.str());
            }
        return ss.str();
        }catch (exception& e) {
            cerr << "InvalidAttributeException: " << e.what() << endl;
            return "0 segundos";
        }
    }
