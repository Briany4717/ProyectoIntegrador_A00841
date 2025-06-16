/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

#ifndef SERIE_H
#define SERIE_H
#include "Video.h"


/**
 * Represents a TV series with related attributes and methods for managing series data.
 */
class Serie final : public Video {
    /**
     * @brief A vector container storing pointers to Video objects representing
     *        the episodes of a Serie. Each pointer pertains to an individual
     *        episode associated with a specific series.
     *
     * @details The container is used to manage the list of episodes belonging
     *          to a Serie object. Each Video object holds unique properties such
     *          as ID, name, duration, genre, and associated ratings. The episodios
     *          member supports operations like adding, retrieving, and iterating
     *          over the contained episodes. Only episodes with unique IDs are
     *          allowed to be added to this vector to ensure consistency.
     */
private:
    vector<Video*> episodios;
    /**
     * @brief Constructs a Serie object, inheriting properties from the base Video class.
     *
     * This constructor initializes a Serie instance with a unique identifier, a name,
     * and a genre. The duration is set to 0 as it represents a series and not a singular video.
     *
     * @param _id The unique identifier for the series.
     * @param _nombre The name of the series.
     * @param _genero The genre of the series.
     *
     * @return An initialized instance of the Serie class.
     */
public:
    Serie(const int _id, string _nombre, string _genero);

    /**
     * @brief Destructor for the Serie class.
     *
     * Releases any resources or memory allocated for the Serie object.
     * This includes the cleanup of the episodios vector and any associated
     * dynamic memory allocated for the episodes. The destructor is defined
     * as default, meaning it relies on the compiler-generated implementation.
     *
     * This destructor ensures proper cleanup when a Serie object goes out
     * of scope or is explicitly deleted, preventing resource leaks.
     */
    ~Serie();

    /**
     * Retrieves the list of episodes.
     *
     * @return A collection of episodes.
     */
    vector<Video*> GetEpisodios() const;

    /**
     * @brief Method responsible for presenting the required information or user interface.
     */
    void Presentar() override;

    /**
     * Displays the episodes.
     */
    void MostrarEpisodios() const;

    /**
     * Adds a new episode to the collection.
     *
     * @param episodio The episode object to be added.
     */
    void AddEpisodio(Video* episodio);
};



#endif //SERIE_H
