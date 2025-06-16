/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

#ifndef PELICULA_H
#define PELICULA_H

#include "Video.h"

/**
 * @class Pelicula
 * @brief Represents a movie. This class inherits from the Video class.
 *
 * The Pelicula class is a specific implementation of the Video class
 * and provides details and functionalities specific to movies, such as
 * presenting the movie's details including its ID, name, duration, genre,
 * and rating.
 */
class Pelicula final : public Video {
    /**
     * Constructor for the Pelicula class, which represents a movie by initializing
     * its attributes, inheriting from the Video class.
     *
     * @param _id The unique identifier of the movie.
     * @param _nombre The name or title of the movie.
     * @param _duration The duration of the movie in seconds.
     * @param _genero The genre of the movie.
     * @return An instance of the Pelicula class.
     */
public:
    Pelicula(const int _id, string _nombre,const int _duration, string _genero);

    /**
     * Destructor for the Pelicula class.
     *
     * Cleans up any resources used by the Pelicula instance. Since this destructor
     * is defined as `default`, it relies on the compiler to generate the
     * appropriate cleanup code.
     */
    ~Pelicula() override = default;

    /**
     * @brief Outputs detailed information about the movie to standard output.
     *
     * This method displays the movie's ID, name, average rating, duration, genre,
     * and the number of users who have rated the movie. The information is
     * well-formatted for readability. It utilizes helper methods such as
     * `getCalificacion()` to retrieve the average rating and `formatDuration()`
     * to display the formatted duration of the movie.
     */
    void Presentar() override;

};



#endif //PELICULA_H
