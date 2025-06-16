/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

#include "Video.h"

    Video::Video(const int _id, string _nombre,const int _duration, string _genero):
    id(_id),nombre(std::move(_nombre)),duration(_duration),
    genero(std::move(_genero)),calificaciones({}){};

    int Video::GetId() const {
        return id;
    }
    string Video::GetNombre()const {
        return nombre;
    }
    int Video::GetDuration()const {
        return duration;
    }
    string Video::GetGenero()const {
        return genero;
    }
    double Video::GetCalificacion() const {
        if (calificaciones.empty()) {
            return 0.0;  // O cualquier otro valor por defecto
        }

        double promedio = 0;
        for (const int cal : calificaciones) {
            promedio += cal;
        }
        return promedio / static_cast<double>(calificaciones.size());
    }

    bool Video::Calificar(const int calif) {
        try {
            if (calif < 0 || calif >5) throw invalid_argument("Calificación invalida. Debe ser un número entre 0 y 5 incluyente.");
            calificaciones.push_back(calif);
            return true;
        }catch (exception& e) {
            cerr << e.what() << endl;
            return false;
        }
    };
    string Video::FormatDuration() const {
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
