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
#include "Pelicula.h"
using namespace std;

TEST(SimpleTest, BasicAssertion) {
    EXPECT_EQ(2 + 2, 4);
    EXPECT_TRUE(true);
}


class PeliculaTest : public ::testing::Test {
protected:
    Pelicula* pelicula;

    void SetUp() override {
        pelicula = new Pelicula(1, "Avatar", 9000, "Accion");
    }

    void TearDown() override {
        delete pelicula;
    }
};

TEST_F(PeliculaTest, ConstructorInicializaCorrectamente) {
    EXPECT_EQ(pelicula->GetId(), 1);
    EXPECT_EQ(pelicula->GetNombre(), "Avatar");
    EXPECT_EQ(pelicula->GetDuration(), 9000);
    EXPECT_EQ(pelicula->GetGenero(), "Accion");
}

TEST_F(PeliculaTest, CalificacionInicialEsCero) {
    EXPECT_DOUBLE_EQ(pelicula->GetCalificacion(), 0.0);
}

TEST_F(PeliculaTest, CalificarConValorValido) {
    EXPECT_TRUE(pelicula->Calificar(5));
    EXPECT_DOUBLE_EQ(pelicula->GetCalificacion(), 5.0);
}

TEST_F(PeliculaTest, CalificarConValorInvalido) {
    // Capturar stderr para verificar mensaje de error
    testing::internal::CaptureStderr();
    EXPECT_FALSE(pelicula->Calificar(6));
    string error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());
    EXPECT_DOUBLE_EQ(pelicula->GetCalificacion(), 0.0);
}

TEST_F(PeliculaTest, CalificarConValorNegativo) {
    testing::internal::CaptureStderr();
    EXPECT_FALSE(pelicula->Calificar(-1));
    string error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());
    EXPECT_DOUBLE_EQ(pelicula->GetCalificacion(), 0.0);
}

TEST_F(PeliculaTest, PromedioCalificacionesMultiples) {
    pelicula->Calificar(4);
    pelicula->Calificar(5);
    pelicula->Calificar(3);
    EXPECT_DOUBLE_EQ(pelicula->GetCalificacion(), 4.0);
}

TEST_F(PeliculaTest, FormatearDuracionHoras) {
    Pelicula pelicula_larga(2, "Titanic", 10800, "Drama"); // 3 horas
    EXPECT_EQ(pelicula_larga.FormatDuration(), "3:00:00 horas");
}

TEST_F(PeliculaTest, FormatearDuracionMinutos) {
    Pelicula pelicula_corta(3, "Corto", 3600, "Comedia"); // 1 hora
    EXPECT_EQ(pelicula_corta.FormatDuration(), "1:00:00 horas");
}

TEST_F(PeliculaTest, FormatearDuracionSegundos) {
    Pelicula pelicula_muy_corta(4, "Trailer", 45, "Trailer"); // 45 segundos
    EXPECT_EQ(pelicula_muy_corta.FormatDuration(), "45 segundos");
}

TEST_F(PeliculaTest, FormatearDuracionInvalida) {
    testing::internal::CaptureStderr();
    Pelicula pelicula_invalida(5, "Invalida", 0, "Error");
    string resultado = pelicula_invalida.FormatDuration();
    string error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());
    EXPECT_EQ(resultado, "0 segundos");
}

TEST_F(PeliculaTest, PresentarOutput) {
    pelicula->Calificar(4);
    pelicula->Calificar(5);

    testing::internal::CaptureStdout();
    pelicula->Presentar();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Avatar") != string::npos);
    EXPECT_TRUE(output.find("4.5") != string::npos); // Promedio de calificaciones
    EXPECT_TRUE(output.find("Accion") != string::npos);
    EXPECT_TRUE(output.find("2 usuarios") != string::npos);
}
