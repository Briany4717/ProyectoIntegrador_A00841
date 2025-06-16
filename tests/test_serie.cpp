//
// Created by Brian Roberto Gómez Martínez on 15/06/25.
//

#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

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
    EXPECT_EQ(serie->getId(), 100);
    EXPECT_EQ(serie->getNombre(), "Breaking Bad");
    EXPECT_EQ(serie->getDuration(), 0); // Inicia con 0 episodios
    EXPECT_EQ(serie->getGenero(), "Drama");
}

TEST_F(SerieTest, AgregarEpisodioIncrementa) {
    serie->addEpisodio(episodio1);
    EXPECT_EQ(serie->getDuration(), 1); // Ahora tiene 1 episodio

    vector<Video*> episodios = serie->getEpisodios();
    EXPECT_EQ(episodios.size(), 1);
    EXPECT_EQ(episodios[0]->getId(), 101);
}

TEST_F(SerieTest, AgregarMultiplesEpisodios) {
    serie->addEpisodio(episodio1);
    serie->addEpisodio(episodio2);

    EXPECT_EQ(serie->getDuration(), 2);
    vector<Video*> episodios = serie->getEpisodios();
    EXPECT_EQ(episodios.size(), 2);
}

TEST_F(SerieTest, AgregarEpisodioConIdDuplicado) {
    Video* episodio_duplicado = new Episodio(101, "Episodio Duplicado", 3000, "Drama");

    serie->addEpisodio(episodio1);

    testing::internal::CaptureStderr();
    serie->addEpisodio(episodio_duplicado);
    string error_output = testing::internal::GetCapturedStderr();

    EXPECT_FALSE(error_output.empty());
    EXPECT_EQ(serie->getDuration(), 1); // Solo debe tener 1 episodio

    delete episodio_duplicado;
}

TEST_F(SerieTest, PresentarOutput) {
    serie->calificar(4);
    serie->addEpisodio(episodio1);
    serie->addEpisodio(episodio2);

    testing::internal::CaptureStdout();
    serie->presentar();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Breaking Bad") != string::npos);
    EXPECT_TRUE(output.find("4") != string::npos); // Calificación
    EXPECT_TRUE(output.find("Drama") != string::npos);
    EXPECT_TRUE(output.find("2") != string::npos); // Número de capítulos
    EXPECT_TRUE(output.find("1 usuarios") != string::npos);
}

TEST_F(SerieTest, MostrarEpisodios) {
    serie->addEpisodio(episodio1);
    serie->addEpisodio(episodio2);

    testing::internal::CaptureStdout();
    serie->mostrarEpisodios();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Episodio 1") != string::npos);
    EXPECT_TRUE(output.find("Episodio 2") != string::npos);
}