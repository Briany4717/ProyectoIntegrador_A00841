/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

/**
 * @brief Constructs an instance of the Episodio class, representing an episode
 *        that inherits from the Video class.
 *
 * @param _id The unique identifier for the episode.
 * @param _nombre The name of the episode.
 * @param _duration The duration of the episode in seconds.
 * @param _genero The genre of the episode.
 */
#include "Episodio.h"
Episodio::Episodio(const int _id, string _nombre,const int _duration, string _genero):
    Video(_id,std::move(_nombre),_duration,std::move(_genero)){};

/**
 * @brief Method to present the episode's details including title, duration, and rating.
 *
 * This function outputs the formatted details of an episode to the standard console.
 * It displays the episode's unique ID, title, duration in a formatted manner
 * and its current rating.
 */
void Episodio::Presentar() {
        cout << id << ".- Titulo: " << nombre
                 << " Duración: " << FormatDuration()
                 << " Calificación: " << GetCalificacion() << endl;
    };
