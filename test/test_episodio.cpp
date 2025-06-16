/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */
#include <gtest/gtest.h>
#include "Episodio.h"

class EpisodioTest : public ::testing::Test {
protected:
    Episodio* episodio;

    void SetUp() override {
        episodio = new Episodio(10, "Piloto", 2700, "Drama");
    }

    void TearDown() override {
        delete episodio;
    }
};

TEST_F(EpisodioTest, ConstructorInicializaCorrectamente) {
    EXPECT_EQ(episodio->GetId(), 10);
    EXPECT_EQ(episodio->GetNombre(), "Piloto");
    EXPECT_EQ(episodio->GetDuration(), 2700);
    EXPECT_EQ(episodio->GetGenero(), "Drama");
}


TEST_F(EpisodioTest, CalificacionInicialEsCero) {
    EXPECT_DOUBLE_EQ(episodio->GetCalificacion(), 0.0);
}

TEST_F(EpisodioTest, CalificarConValorValido) {
    EXPECT_TRUE(episodio->Calificar(5));
    EXPECT_DOUBLE_EQ(episodio->GetCalificacion(), 5.0);
}

TEST_F(EpisodioTest, CalificarConValorInvalido) {
    // Capturar stderr para verificar mensaje de error
    testing::internal::CaptureStderr();
    EXPECT_FALSE(episodio->Calificar(6));
    string error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());
    EXPECT_DOUBLE_EQ(episodio->GetCalificacion(), 0.0);
}

TEST_F(EpisodioTest, CalificarConValorNegativo) {
    testing::internal::CaptureStderr();
    EXPECT_FALSE(episodio->Calificar(-1));
    string error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());
    EXPECT_DOUBLE_EQ(episodio->GetCalificacion(), 0.0);
}

TEST_F(EpisodioTest, PromedioCalificacionesMultiples) {
    episodio->Calificar(4);
    episodio->Calificar(5);
    episodio->Calificar(3);
    EXPECT_DOUBLE_EQ(episodio->GetCalificacion(), 4.0);
}

TEST_F(EpisodioTest, FormatearDuracionHoras) {
    Episodio pelicula_larga(2, "Titanic", 10800, "Drama"); // 3 horas
    EXPECT_EQ(pelicula_larga.FormatDuration(), "3:00:00 horas");
}

TEST_F(EpisodioTest, FormatearDuracionMinutos) {
    Episodio pelicula_corta(3, "Corto", 3600, "Comedia"); // 1 hora
    EXPECT_EQ(pelicula_corta.FormatDuration(), "1:00:00 horas");
}

TEST_F(EpisodioTest, FormatearDuracionSegundos) {
    Episodio pelicula_muy_corta(4, "Trailer", 45, "Trailer"); // 45 segundos
    EXPECT_EQ(pelicula_muy_corta.FormatDuration(), "45 segundos");
}

TEST_F(EpisodioTest, FormatearDuracionInvalida) {
    testing::internal::CaptureStderr();
    Episodio pelicula_invalida(5, "Invalida", 0, "Error");
    string resultado = pelicula_invalida.FormatDuration();
    string error_output = testing::internal::GetCapturedStderr();
    EXPECT_FALSE(error_output.empty());
    EXPECT_EQ(resultado, "0 segundos");
}

TEST_F(EpisodioTest, PresentarOutput) {
    episodio->Calificar(3);

    testing::internal::CaptureStdout();
    episodio->Presentar();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Piloto") != string::npos);
    EXPECT_TRUE(output.find("3") != string::npos); // Calificación
    EXPECT_TRUE(output.find("45:00 minutos") != string::npos); // Duración formateada
}
