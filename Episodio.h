/*
 * Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */
#ifndef EPISODIO_H
#define EPISODIO_H
#include "Video.h"


/**
 * @class Episodio
 * @brief Represents a single episode that inherits from the Video base class.
 *
 * This class provides functionality to describe and present an individual episode
 * with its specific attributes and overrides the presentation behavior defined in the Video class.
 */
class Episodio final : public Video {
    /**
     * Constructs an Episodio object, inheriting properties from the base Video class.
     *
     * @param _id The unique identifier for the episode.
     * @param _nombre The name of the episode.
     * @param _duration The duration of the episode in seconds.
     * @param _genero The genre of the episode.
     *
     * @return An initialized instance of the Episodio class.
     */
public:
    Episodio( int _id, string _nombre, int _duration, string _genero);

    /**
     * @brief Outputs the details of the episode to the standard output.
     *
     * This method provides a formatted presentation of the episode's
     * information, including the episode ID, title, duration in a human-readable
     * format, and the current rating. It utilizes auxiliary methods to format
     * the duration and retrieve the rating.
     *
     * The output format is as follows:
     * "<id>.- Titulo: <nombre> Duración: <formatted duration> Calificación: <rating>"
     *
     * The method is overridden from the `Video` base class.
     */
    void Presentar() override;
};



#endif //EPISODIO_H
