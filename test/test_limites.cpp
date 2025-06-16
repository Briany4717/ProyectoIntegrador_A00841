/*
* Proyecto Integrador TC1013B - A00841404
 * Copyright (C) Instituto Tecnológico de Estudios Superiores de Monterrey
 * http://tec.mx/
 *
 */

#include <gtest/gtest.h>
#include "Pelicula.h"

class EdgeCaseTest : public ::testing::Test {};

TEST_F(EdgeCaseTest, DuracionCero) {
    testing::internal::CaptureStderr();
    Pelicula pelicula_cero(1, "Test", 0, "Test");
    string resultado = pelicula_cero.FormatDuration();
    string error_output = testing::internal::GetCapturedStderr();

    EXPECT_FALSE(error_output.empty());
    EXPECT_EQ(resultado, "0 segundos");
}

TEST_F(EdgeCaseTest, DuracionNegativa) {
    testing::internal::CaptureStderr();
    Pelicula pelicula_negativa(1, "Test", -100, "Test");
    string resultado = pelicula_negativa.FormatDuration();
    string error_output = testing::internal::GetCapturedStderr();

    EXPECT_FALSE(error_output.empty());
    EXPECT_EQ(resultado, "0 segundos");
}

TEST_F(EdgeCaseTest, NombreVacio) {
    Pelicula pelicula_sin_nombre(1, "", 3600, "Test");
    EXPECT_EQ(pelicula_sin_nombre.GetNombre(), "");
}

TEST_F(EdgeCaseTest, GeneroVacio) {
    Pelicula pelicula_sin_genero(1, "Test", 3600, "");
    EXPECT_EQ(pelicula_sin_genero.GetGenero(), "");
}

TEST_F(EdgeCaseTest, CalificacionLimiteSuperior) {
    Pelicula pelicula(1, "Test", 3600, "Test");
    EXPECT_TRUE(pelicula.Calificar(5));
    EXPECT_DOUBLE_EQ(pelicula.GetCalificacion(), 5.0);
}

TEST_F(EdgeCaseTest, CalificacionLimiteInferior) {
    Pelicula pelicula(1, "Test", 3600, "Test");
    EXPECT_TRUE(pelicula.Calificar(0));
    EXPECT_DOUBLE_EQ(pelicula.GetCalificacion(), 0.0);
}
