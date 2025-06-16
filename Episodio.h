//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#ifndef EPISODIO_H
#define EPISODIO_H
#include "Video.h"


class Episodio final : public Video {
public:
    Episodio( int _id, string _nombre, int _duration, string _genero);
    void presentar() override;
};



#endif //EPISODIO_H
