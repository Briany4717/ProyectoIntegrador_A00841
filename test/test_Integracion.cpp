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
    EXPECT_EQ(encontrado->GetId(), 2);
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

class ComprehensiveVideoTest : public ::testing::Test {
protected:
    Pelicula* pelicula;
    Serie* serie;
    Episodio* episodio;

    void SetUp() override {
        pelicula = new Pelicula(1, "Test Movie", 7200, "Drama");
        serie = new Serie(2, "Test Series", "Comedy");
        episodio = new Episodio(3, "Test Episode", 1800, "Comedy");
    }

    void TearDown() override {
        delete pelicula;
        delete serie;
        delete episodio;
    }
};

TEST_F(ComprehensiveVideoTest, CalificarTodosLosValoresValidos) {
    for (int i = 0; i <= 5; ++i) {
        Pelicula p(i, "Test", 3600, "Test");
        EXPECT_TRUE(p.Calificar(i));
        EXPECT_DOUBLE_EQ(p.GetCalificacion(), i);
    }
}

TEST_F(ComprehensiveVideoTest, CalificarTodosLosValoresInvalidos) {
    vector<int> valores_invalidos = {-10, -1, 6, 10, 100};

    for (int valor : valores_invalidos) {
        testing::internal::CaptureStderr();
        EXPECT_FALSE(pelicula->Calificar(valor));
        string error_output = testing::internal::GetCapturedStderr();
        EXPECT_FALSE(error_output.empty());
        EXPECT_DOUBLE_EQ(pelicula->GetCalificacion(), 0.0);
    }
}

TEST_F(ComprehensiveVideoTest, PromedioCalificacionesComplejo) {
    pelicula->Calificar(1);
    pelicula->Calificar(2);
    pelicula->Calificar(3);
    pelicula->Calificar(4);
    pelicula->Calificar(5);
    EXPECT_DOUBLE_EQ(pelicula->GetCalificacion(), 3.0);
}

TEST_F(ComprehensiveVideoTest, PromedioCalificacionesDecimales) {
    pelicula->Calificar(2);
    pelicula->Calificar(3);
    EXPECT_DOUBLE_EQ(pelicula->GetCalificacion(), 2.5);
}

TEST_F(ComprehensiveVideoTest, FormatearDuracionTodasLasRamas) {
    // Probar todas las ramas del formatDuration

    // Caso: exactamente 1 hora
    Pelicula p1(1, "Test1", 3600, "Test");
    EXPECT_EQ(p1.FormatDuration(), "1:00:00 horas");

    // Caso: menos de 1 minuto
    Pelicula p2(2, "Test2", 30, "Test");
    EXPECT_EQ(p2.FormatDuration(), "30 segundos");

    // Caso: exactamente 1 minuto
    Pelicula p3(3, "Test3", 60, "Test");
    EXPECT_EQ(p3.FormatDuration(), "01:00 minutos");

    // Caso: horas con minutos < 10
    Pelicula p4(4, "Test4", 3900, "Test"); // 1:05:00
    EXPECT_EQ(p4.FormatDuration(), "1:05:00 horas");

    // Caso: horas con segundos < 10
    Pelicula p5(5, "Test5", 3605, "Test"); // 1:00:05
    EXPECT_EQ(p5.FormatDuration(), "1:00:05 horas");

    // Caso: minutos con segundos < 10
    Pelicula p6(6, "Test6", 65, "Test"); // 1:05
    EXPECT_EQ(p6.FormatDuration(), "01:05 minutos");
}

TEST_F(ComprehensiveVideoTest, FormatearDuracionCasosLimite) {
    // Duración = 0 (caso límite)
    testing::internal::CaptureStderr();
    Pelicula p_zero(1, "Zero", 0, "Test");
    string result = p_zero.FormatDuration();
    string error = testing::internal::GetCapturedStderr();
    EXPECT_EQ(result, "0 segundos");
    EXPECT_FALSE(error.empty());

    // Duración negativa
    testing::internal::CaptureStderr();
    Pelicula p_neg(2, "Negative", -1, "Test");
    result = p_neg.FormatDuration();
    error = testing::internal::GetCapturedStderr();
    EXPECT_EQ(result, "0 segundos");
    EXPECT_FALSE(error.empty());
}

// Tests específicos para Serie con más cobertura
TEST_F(ComprehensiveVideoTest, SerieAgregarEpisodiosMultiples) {
    // Agregar muchos episodios
    for (int i = 1; i <= 10; ++i) {
        Episodio* ep = new Episodio(100 + i, "Episode " + to_string(i), 1800, "Comedy");
        serie->AddEpisodio(ep);
    }

    EXPECT_EQ(serie->GetDuration(), 10);
    EXPECT_EQ(serie->GetEpisodios().size(), 10);
}

TEST_F(ComprehensiveVideoTest, SerieIntentarAgregarEpisodiosDuplicados) {
    Episodio* ep1 = new Episodio(101, "Episode 1", 1800, "Comedy");
    Episodio* ep2 = new Episodio(101, "Episode 1 Duplicate", 2000, "Comedy");

    serie->AddEpisodio(ep1);

    testing::internal::CaptureStderr();
    serie->AddEpisodio(ep2);
    string error = testing::internal::GetCapturedStderr();

    EXPECT_FALSE(error.empty());
    EXPECT_EQ(serie->GetDuration(), 1);
    EXPECT_EQ(serie->GetEpisodios().size(), 1);

    delete ep2; // ep1 será eliminado por serie
}

TEST_F(ComprehensiveVideoTest, SerieCalificacionConEpisodios) {
    Episodio* ep1 = new Episodio(101, "Episode 1", 1800, "Comedy");
    serie->AddEpisodio(ep1);

    // Calificar la serie
    serie->Calificar(4);
    serie->Calificar(5);

    EXPECT_DOUBLE_EQ(serie->GetCalificacion(), 4.5);
    EXPECT_EQ(serie->GetDuration(), 1); // Un episodio
}

TEST_F(ComprehensiveVideoTest, EpisodioTodasLasFunciones) {
    // Probar todas las funciones del episodio
    EXPECT_EQ(episodio->GetId(), 3);
    EXPECT_EQ(episodio->GetNombre(), "Test Episode");
    EXPECT_EQ(episodio->GetDuration(), 1800);
    EXPECT_EQ(episodio->GetGenero(), "Comedy");

    episodio->Calificar(3);
    EXPECT_DOUBLE_EQ(episodio->GetCalificacion(), 3.0);
}

// Tests de presentación con verificación de output completo
TEST_F(ComprehensiveVideoTest, PeliculaPresentarOutputCompleto) {
    pelicula->Calificar(4);
    pelicula->Calificar(5);
    pelicula->Calificar(3);

    testing::internal::CaptureStdout();
    pelicula->Presentar();
    string output = testing::internal::GetCapturedStdout();

    // Verificar que todos los elementos están presentes
    EXPECT_TRUE(output.find("1.-") != string::npos); // ID
    EXPECT_TRUE(output.find("Test Movie") != string::npos); // Nombre
    EXPECT_TRUE(output.find("4") != string::npos); // Calificación (4.0)
    EXPECT_TRUE(output.find("2:00:00 horas") != string::npos); // Duración
    EXPECT_TRUE(output.find("Drama") != string::npos); // Género
    EXPECT_TRUE(output.find("3 usuarios") != string::npos); // Número de calificaciones
}

TEST_F(ComprehensiveVideoTest, SeriePresentarOutputCompleto) {
    Episodio* ep1 = new Episodio(101, "Episode 1", 1800, "Comedy");
    Episodio* ep2 = new Episodio(102, "Episode 2", 1900, "Comedy");
    serie->AddEpisodio(ep1);
    serie->AddEpisodio(ep2);

    serie->Calificar(5);

    testing::internal::CaptureStdout();
    serie->Presentar();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("2.-") != string::npos); // ID
    EXPECT_TRUE(output.find("Test Series") != string::npos); // Nombre
    EXPECT_TRUE(output.find("5") != string::npos); // Calificación
    EXPECT_TRUE(output.find("Capítulos: 2") != string::npos); // Número de episodios
    EXPECT_TRUE(output.find("Comedy") != string::npos); // Género
    EXPECT_TRUE(output.find("1 usuarios") != string::npos); // Número de calificaciones
}

TEST_F(ComprehensiveVideoTest, EpisodiopresentarOutputCompleto) {
    episodio->Calificar(2);

    testing::internal::CaptureStdout();
    episodio->Presentar();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("3.-") != string::npos); // ID
    EXPECT_TRUE(output.find("Test Episode") != string::npos); // Título
    EXPECT_TRUE(output.find("30:00 minutos") != string::npos); // Duración
    EXPECT_TRUE(output.find("2") != string::npos); // Calificación
}

TEST_F(ComprehensiveVideoTest, SerieMostrarEpisodiosVacio) {
    // Mostrar episodios cuando no hay ninguno
    testing::internal::CaptureStdout();
    serie->MostrarEpisodios();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.empty()); // No debe mostrar nada
}

TEST_F(ComprehensiveVideoTest, SerieMostrarEpisodiosConContenido) {
    Episodio* ep1 = new Episodio(101, "Episode 1", 1800, "Comedy");
    Episodio* ep2 = new Episodio(102, "Episode 2", 1900, "Comedy");
    serie->AddEpisodio(ep1);
    serie->AddEpisodio(ep2);

    testing::internal::CaptureStdout();
    serie->MostrarEpisodios();
    string output = testing::internal::GetCapturedStdout();

    EXPECT_TRUE(output.find("Episode 1") != string::npos);
    EXPECT_TRUE(output.find("Episode 2") != string::npos);
}

// Tests para constructores con move semantics
TEST_F(ComprehensiveVideoTest, ConstructorConMoveSemantics) {
    string nombre = "Movie Test";
    string genero = "Action";

    Pelicula p(10, std::move(nombre), 7200, std::move(genero));

    EXPECT_EQ(p.GetNombre(), "Movie Test");
    EXPECT_EQ(p.GetGenero(), "Action");
    // nombre y genero deberían estar vacíos después del move, pero no podemos verificarlo aquí
}

// Tests para casos de strings vacíos y especiales
TEST_F(ComprehensiveVideoTest, StringsVaciosYEspeciales) {
    Pelicula p1(1, "", 3600, "");
    EXPECT_EQ(p1.GetNombre(), "");
    EXPECT_EQ(p1.GetGenero(), "");

    Pelicula p2(2, "   ", 3600, "   ");
    EXPECT_EQ(p2.GetNombre(), "   ");
    EXPECT_EQ(p2.GetGenero(), "   ");

    // Strings con caracteres especiales
    Pelicula p3(3, "Película Ñoña", 3600, "Comedia & Drama");
    EXPECT_EQ(p3.GetNombre(), "Película Ñoña");
    EXPECT_EQ(p3.GetGenero(), "Comedia & Drama");
}

// Tests para verificar que los destructores se llamen
TEST_F(ComprehensiveVideoTest, DestructoresVirtuales) {
    // Crear objetos polimórficos
    Video* videos[] = {
        new Pelicula(1, "Test1", 3600, "Test"),
        new Episodio(2, "Test2", 1800, "Test")
    };

    // Eliminar a través del puntero base
    for (Video* v : videos) {
        delete v; // Debe llamar al destructor correcto
    }

    // Si llegamos aquí sin crash, los destructores virtuales funcionan
    SUCCEED();
}
