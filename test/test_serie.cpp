/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */
#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

#include "Episodio.h"
#include "Serie.h"

class SerieTest : public ::testing::Test {
protected:
    Serie* serie;
    Video* episodio1;
    Video* episodio2;

    void SetUp() override {
        serie = new Serie(100, "Breaking Bad", "Drama");
        episodio1 = new Episodio(101, "Episodio 1", 2700, "Drama");
        episodio2 = new Episodio(102, "Episodio 2", 2800, "Drama");
    }

    void TearDown() override {
        delete serie;
        delete episodio1;
        delete episodio2;
    }
};

TEST_F(SerieTest, ConstructorInicializaCorrectamente) {
    EXPECT_EQ(serie->GetId(), 100);
    EXPECT_EQ(serie->GetNombre(), "Breaking Bad");
    EXPECT_EQ(serie->GetDuration(), 0); // Inicia con 0 episodios
    EXPECT_EQ(serie->GetGenero(), "Drama");
}

TEST_F(SerieTest, AgregarEpisodioIncrementa) {
    serie->AddEpisodio(episodio1);
    EXPECT_EQ(serie->GetDuration(), 1); // Ahora tiene 1 episodio

    vector<Video*> episodios = serie->GetEpisodios();
    EXPECT_EQ(episodios.size(), 1);
    EXPECT_EQ(episodios[0]->GetId(), 101);
}

TEST_F(SerieTest, AgregarMultiplesEpisodios) {
    serie->AddEpisodio(episodio1);
    serie->AddEpisodio(episodio2);

    EXPECT_EQ(serie->GetDuration(), 2);
    vector<Video*> episodios = serie->GetEpisodios();
    EXPECT_EQ(episodios.size(), 2);
}

TEST_F(SerieTest, AgregarEpisodioConIdDuplicado) {
    Video* episodio_duplicado = new Episodio(101, "Episodio Duplicado", 3000, "Drama");

    serie->AddEpisodio(episodio1);

    testing::internal::CaptureStderr();
    serie->AddEpisodio(episodio_duplicado);
    string error_output = testing::internal::GetCapturedStderr();

    EXPECT_FALSE(error_output.empty());
    EXPECT_EQ(serie->GetDuration(), 1); // Solo debe tener 1 episodio

    delete episodio_duplicado;
}

TEST_F(SerieTest, PresentarOutput) {
    serie->Calificar(4);
    serie->AddEpisodio(episodio1);
    serie->AddEpisodio(episodio2);

    testing::internal::CaptureStdout();
    serie->Presentar();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Breaking Bad") != string::npos);
    EXPECT_TRUE(output.find("4") != string::npos); // Calificación
    EXPECT_TRUE(output.find("Drama") != string::npos);
    EXPECT_TRUE(output.find("2") != string::npos); // Número de capítulos
    EXPECT_TRUE(output.find("1 usuarios") != string::npos);
}

TEST_F(SerieTest, MostrarEpisodios) {
    serie->AddEpisodio(episodio1);
    serie->AddEpisodio(episodio2);

    testing::internal::CaptureStdout();
    serie->MostrarEpisodios();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Episodio 1") != string::npos);
    EXPECT_TRUE(output.find("Episodio 2") != string::npos);
}
