/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

#include <gtest/gtest.h>
#include  "Pelicula.h"
#include  "Serie.h"
#include  "Episodio.h"
#include  "Video.h"

class IntegrationTest : public ::testing::Test {
protected:
    vector<Video*> db;

    void SetUp() override {
        // Crear datos de prueba
        db.push_back(new Pelicula(1, "Avengers", 8400, "Accion"));
        db.push_back(new Pelicula(2, "Titanic", 11400, "Drama"));

        Serie* serie = new Serie(3, "Game of Thrones", "Fantasia");
        serie->AddEpisodio(new Episodio(31, "Winter is Coming", 3600, "Fantasia"));
        serie->AddEpisodio(new Episodio(32, "The Kingsroad", 3300, "Fantasia"));
        db.push_back(serie);
    }

    void TearDown() override {
        for (Video* video : db) {
            delete video;
        }
        db.clear();
    }
};

TEST_F(IntegrationTest, BuscarVideoPorId) {
    Video* encontrado = nullptr;
    for (Video* v : db) {
        if (v->GetId() == 1) {
            encontrado = v;
            break;
        }
    }

    ASSERT_NE(encontrado, nullptr);
    EXPECT_EQ(encontrado->GetNombre(), "Avengers");
}

TEST_F(IntegrationTest, BuscarVideoPorNombre) {
    Video* encontrado = nullptr;
    for (Video* v : db) {
        if (v->GetNombre() == "Titanic") {
            encontrado = v;
            break;
        }
    }

    ASSERT_NE(encontrado, nullptr);
    EXPECT_EQ(encontrado->getId(), 2);
}

TEST_F(IntegrationTest, FiltrarPorGenero) {
    vector<Video*> drama_videos;
    for (Video* v : db) {
        if (v->GetGenero() == "Drama") {
            drama_videos.push_back(v);
        }
    }

    EXPECT_EQ(drama_videos.size(), 1);
    EXPECT_EQ(drama_videos[0]->GetNombre(), "Titanic");
}

TEST_F(IntegrationTest, CalificarMultiplesVideos) {
    for (Video* v : db) {
        v->Calificar(4);
    }

    for (Video* v : db) {
        EXPECT_DOUBLE_EQ(v->GetCalificacion(), 4.0);
    }
}
