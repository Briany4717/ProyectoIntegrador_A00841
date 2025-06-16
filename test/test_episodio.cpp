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

TEST_F(EpisodioTest, PresentarOutput) {
    episodio->Calificar(3);

    testing::internal::CaptureStdout();
    episodio->Presentar();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Piloto") != string::npos);
    EXPECT_TRUE(output.find("3") != string::npos); // Calificación
    EXPECT_TRUE(output.find("45:00 minutos") != string::npos); // Duración formateada
}
