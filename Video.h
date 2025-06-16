/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

#ifndef VIDEO_H
#define VIDEO_H

#import <string>
#import <sstream>
#import <iostream>
#import <vector>
using namespace std;

/**
 * @brief Represents a generic video object.
 *
 * This is an abstract base class that provides the structure for video objects.
 * It holds information such as the video's ID, name, duration, genre, and associated ratings.
 * Subclasses must implement the virtual method Presentar to provide specific presentation functionality.
 */
class Video {
 /**
  * @brief A unique identifier for the object.
  *
  * This variable serves as a distinct numeric ID to differentiate between
  * instances of the object. It is typically used for internal operations
  * such as identification, selection, or lookup purposes.
  */
protected:
    int id;
 /**
  * @brief Represents the name or title of a video.
  *
  * The `nombre` member holds the name or title for a `Video` instance. It is used
  * to uniquely identify or describe the video content, such as the title of a movie,
  * episode, or series. This value is of type `string` and is initialized during object
  * instantiation.
  *
  * This attribute is accessed and utilized in various class methods, including
  * `GetNombre()` to retrieve its value and in overridden methods like `Presentar()`
  * for formatted output.
  */
 string nombre;
 /**
  * @brief Represents the duration of a video in seconds.
  *
  * The `duration` variable holds the total duration of a video in seconds.
  * It serves as a core metric for determining the video's length, which can
  * be used in operations such as formatting the duration into a human-readable
  * format, calculating cumulative durations, or determining video playtime or runtime.
  *
  * This value should generally be a non-negative integer.
  */
 int duration;
 /**
  * @brief Stores the genre of a video.
  *
  * @details This member variable represents the genre associated with a
  *          specific video object, which could belong to categories such
  *          as movies, series, or individual episodes. The genre is stored
  *          as a string, allowing for flexible descriptions such as "Action",
  *          "Comedy", "Drama", etc. It is utilized in various functionalities
  *          like filtering, presentation, and categorization of videos.
  */
 string genero;
 /**
  * @brief A container for storing user-provided ratings for a video.
  *
  * This variable holds the list of integer ratings given to a video by users.
  * It is primarily used to calculate the average rating and track the number
  * of users who rated the video.
  *
  * The vector contains integers representing individual ratings, allowing the
  * storage and processing of multiple ratings for a single video instance.
  */
 vector<int> calificaciones;
 /**
  * Constructs a Video object with the specified attributes.
  *
  * @param _id The unique identifier for the video.
  * @param _nombre The name of the video.
  * @param _duration The duration of the video in seconds.
  * @param _genero The genre of the video.
  * @return An initialized instance of the Video class.
  */
public:
    Video(int _id, string _nombre,int _duration, string _genero);

 /**
  * Retrieves the unique identifier of the video.
  *
  * @return The ID of the video as an integer.
  */
 int GetId() const;

 /**
  * Retrieves the name of the video.
  *
  * @return A string representing the name of the video.
  */
 string GetNombre()const;

 /**
  * Retrieves the duration of the video in seconds.
  *
  * @return The duration of the video.
  */
 int GetDuration()const ;

 /**
  * Retrieves the genre of the video.
  *
  * @return A string representing the genre of the video.
  */
 string GetGenero()const;

 /**
  * Calculates and returns the average rating (calificación) of the video.
  * If there are no ratings, returns 0.0 by default.
  *
  * @return The average rating of the video as a double. Returns 0.0 if there are no ratings.
  */
 double GetCalificacion() const;

    /**
     * Pure virtual function to present the video details.
     * Classes inheriting from the `Video` class must provide their own implementation
     * of this function to display the relevant information about the video.
     */
    virtual void Presentar() = 0;

 /**
  * Assigns a rating to the video if the provided rating is valid.
  *
  * @param calif The rating to assign, must be an integer between 0 and 5 (inclusive).
  * @return True if the rating was successfully assigned, otherwise false.
  *         Returns false if the provided rating is invalid.
  */
 bool Calificar(int calif);

 /**
  * Formats the duration of the video into a human-readable string.
  *
  * The formatted string includes hours, minutes, and seconds depending on the
  * duration of the video.
  * - If the duration is greater than or equal to 3600 seconds, it is formatted
  *   in the form "HH:MM:SS horas".
  * - If the duration is less than 3600 seconds but greater than or equal to
  *   60 seconds, it is formatted in the form "MM:SS minutos".
  * - If the duration is less than 60 seconds but greater than or equal to 1
  *   second, it is formatted in the form "SS segundos".
  *
  * In the case of invalid or non-positive durations, it throws an
  * invalid_argument exception with a message including the video ID and invalid
  * duration.
  * If an exception is caught, a default value of "0 segundos" is returned.
  *
  * @return A string representing the formatted duration of the video, or
  *         "0 segundos" if an invalid duration is encountered.
  */
 string FormatDuration() const;

    /**
     * @brief Virtual destructor for the Video class.
     *
     * Ensures proper cleanup of resources for derived classes when a Video object
     * is deleted through a base class pointer.
     */
    virtual ~Video() = default;
};



#endif //VIDEO_H
