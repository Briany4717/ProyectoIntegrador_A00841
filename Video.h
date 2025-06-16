//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#ifndef VIDEO_H
#define VIDEO_H

#import <string>
#import <sstream>
#import <iostream>
#import <vector>
using namespace std;

class Video {
protected:
    int id;
    string nombre;
    int duration;
    string genero;
    vector<int> calificaciones;
public:
    Video(int _id, string _nombre,int _duration, string _genero);

    int getId() const;
    string getNombre()const;
    int getDuration()const ;
    string getGenero()const;
    double getCalificacion() const;
    virtual void presentar() = 0;
    bool calificar(int calif);
    string formatDuration() const;
    virtual ~Video() = default;
};



#endif //VIDEO_H
