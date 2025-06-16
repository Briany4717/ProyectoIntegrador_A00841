//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#ifndef PELICULA_H
#define PELICULA_H

#include "Video.h"

class Pelicula final : public Video {
public:
    Pelicula(const int _id, string _nombre,const int _duration, string _genero);
    ~Pelicula();
    void presentar() override;

};



#endif //PELICULA_H
