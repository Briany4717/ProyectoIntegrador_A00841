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
    Episodio* episodio3;
    Episodio* episodio4;
    Episodio* episodio5;
    Video* episodio6;

    void SetUp() override {
        serie = new Serie(100, "Breaking Bad", "Drama");
        episodio1 = new Episodio(101, "Episodio 1", 2700, "Drama");
        episodio2 = new Episodio(102, "Episodio 2", 2800, "Drama");
        episodio3 = new Episodio(103, "Episodio 3", 2700, "Drama");
        episodio4 = new Episodio(104, "Episodio 4", 2800, "Drama");
        episodio5 = new Episodio(105, "Episodio 5", 2700, "Drama");
        episodio6 = new Episodio(106, "Episodio 6", 2800, "Drama");
    }

    void TearDown() override {
        delete serie;
        delete episodio1;
        delete episodio2;
        delete episodio3;
        delete episodio4;
        delete episodio5;
        delete episodio6;
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
    serie->AddEpisodio(episodio3);
    serie->AddEpisodio(episodio4);
    serie->AddEpisodio(episodio5);

    EXPECT_EQ(serie->GetDuration(), 5);
    vector<Video*> episodios = serie->GetEpisodios();
    EXPECT_EQ(episodios.size(), 5);
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

TEST_F(SerieTest, AgregarEpisodioConIdDuplicado2) {
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
    serie->AddEpisodio(episodio3);
    serie->AddEpisodio(episodio4);
    serie->AddEpisodio(episodio5);

    testing::internal::CaptureStdout();
    serie->MostrarEpisodios();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Episodio 1") != string::npos);
    EXPECT_TRUE(output.find("Episodio 2") != string::npos);
    EXPECT_TRUE(output.find("Episodio 3") != string::npos);
    EXPECT_TRUE(output.find("Episodio 4") != string::npos);
    EXPECT_TRUE(output.find("Episodio 5") != string::npos);
}
