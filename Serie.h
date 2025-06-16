//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#ifndef SERIE_H
#define SERIE_H
#include "Video.h"


class Serie final : public Video {
private:
    vector<Video*> episodios;
public:
    Serie(const int _id, string _nombre, string _genero);
    ~Serie();
    vector<Video*> getEpisodios() const;
    void presentar() override;
    void mostrarEpisodios() const;
    void addEpisodio(Video* episodio);
};



#endif //SERIE_H
