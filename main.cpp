#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Video.h"
#include "Serie.h"
#include "Pelicula.h"

vector<Video*> db;

void cargarArchivo(const string& file) {
    try {
        ifstream archivo(file);
        if (!archivo.is_open()) {
            cerr << "No se pudo abrir el archivo: " << file << endl;
            return;
        }

        string linea;
        getline(archivo, linea); // Saltar el encabezado

        vector<Serie*> series;  // Vector para mantener las referencias a las series
        vector<Pelicula*> peliculas;

        while (getline(archivo, linea)) {
            stringstream ss(linea);
            string tipo, id, titulo, duracion, genero, id_serie;

            if (getline(ss, tipo, ',') &&
                getline(ss, id, ',') &&
                getline(ss, titulo, ',') &&
                getline(ss, duracion, ',') &&
                getline(ss, genero, ',') &&
                getline(ss, id_serie)) {

                try {
                    int idNum = stoi(id);
                    int duracionNum = stoi(duracion);
                    
                    if (tipo == "Serie") {
                        auto* nuevaSerie = new Serie(idNum, titulo, genero);
                        series.push_back(nuevaSerie);
                    }
                    else if (tipo == "Pelicula") {
                        auto* nuevaPelicula = new Pelicula(idNum, titulo, duracionNum, genero);
                        peliculas.push_back(nuevaPelicula);
                    }
                    else if (tipo == "Episodio") {
                        int idSerieNum = stoi(id_serie);
                        // Buscar la serie correspondiente
                        Serie* seriePadre = nullptr;
                        for (Serie* serie : series) {
                            if (serie->GetId() == idSerieNum) {
                                seriePadre = serie;
                                break;
                            }
                        }
                        
                        if (seriePadre != nullptr) {
                            Video* nuevoEpisodio = new Pelicula(idNum, titulo, duracionNum, genero);
                            seriePadre->AddEpisodio(nuevoEpisodio);
                        }
                    }
                    else {
                        throw invalid_argument("Tipo de video invalido. Debe ser Serie, Pelicula o Episodio.");
                    }
                } catch (const invalid_argument& e) {
                    cerr << "Error al convertir números: " << e.what() << endl;
                } catch (const out_of_range& e) {
                    cerr << "Número fuera de rango: " << e.what() << endl;
                }
            }
        }
        for (auto* serie : series) {
            db.push_back(serie);
        }
        for (auto* pelicula : peliculas) {
            db.push_back(pelicula);
        }
        archivo.close();
        cout << "Archivo cargado correctamente." << endl;
    } catch (const exception& e) {
        cerr << "Error general: " << e.what() << endl;
    }
}

string askFilter(const string& text) {
    cout << text;
    string response = "-";
    getline(cin, response);
    if (response.empty()) return "-";
    return response;
}

void filtrarVideos(const vector<Video*> videos,const string &tipof,const string &genf,const string &nombref,string &califf) {
    for (Video* v : videos) {
        bool pasa = true;
        const string tipo = dynamic_cast<Serie*>(v) ? "serie" :
                          dynamic_cast<Pelicula*>(v) ? "pelicula" : "otro";
        if (tipo != tipof && tipof != "-") pasa = false;
        if (v->GetGenero() != genf && genf != "-") pasa = false;
        if (v->GetNombre() != nombref && nombref != "-") pasa = false;
        if (califf != "-") {
            if (!isdigit(califf[0]) && califf.size() >= 2 && califf[1] == '=') {
            } else if (califf[0] == '<' || califf[0] == '>' || califf[0] == '=') {
            } else {
                califf = "=" + califf;
            }

            double cal = v->GetCalificacion();
            size_t start = (califf[1] == '=') ? 2 : 1;
            double val = stod(califf.substr(start));
            string cmp = califf.substr(0, start);

            if (cmp == "<" && !(cal < val)) pasa = false;
            else if (cmp == "<=" && !(cal <= val)) pasa = false;
            else if (cmp == ">" && !(cal > val)) pasa = false;
            else if (cmp == ">=" && !(cal >= val)) pasa = false;
            else if (cmp == "=" && !(cal == val)) pasa = false;

        }
        if (pasa) v->Presentar();
    }
}

int main() {

    int op = 10;
    while (op != 0) {
        cout << "---------- Menú ----------" << endl;
        cout << "1. Cargar archivo de datos" << endl;
        cout << "2. Mostrar todo" << endl;
        cout << "3. Filtrar todo por..." << endl;
        cout << "4. Filtrar episodios de una serie" << endl;
        cout << "5. Calificar" << endl;
        cout << "0. Salir" << endl;
        try {
            cout << "-> ";
            cin >> op;
            if (op < 0 || op > 6) throw invalid_argument("Opción invalida. Intente de nuevo.");

            switch (op) {
                case 1: {
                    cout << "Ingrese el nombre del archivo (.csv en la carpeta donde se ->ejecute<- este programa [.exe,.sh,etc..]):\n-> ";
                    cin.ignore();
                    string file;
                    getline(cin, file);
                    cargarArchivo(file);
                    break;
                }
                case 2: {
                    for(auto* video : db) {
                        video->Presentar();
                    }
                    cout << "Presiona Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 3: {
                    cout << "Filtrar por..." << endl;
                    cout << "Escriba - para omitir el filtro" << endl;
                    cin.ignore();
                    string nombref = askFilter("Nombre = ");
                    string tipof = askFilter("Tipo de video (serie,pelicula) = ");
                    string genf = askFilter("Genero = ");
                    string califf = askFilter("Califiación (Use =, <, > o <=, >= dependiendo lo que busque): ");

                    filtrarVideos(db,tipof,genf,nombref,califf);
                    cout << "Presiona Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    break;
                }
                case 4: {
                    cout << "Id o nombre de la serie = ";
                    bool finded = false;
                    string response;
                    cin.ignore(); // Limpia el salto de línea anterior
                    getline(cin, response); // Toma toda la línea, incluyendo espacios

                    Serie* serieSelected = nullptr;
                    for (Video* v : db) {
                        if (std::isdigit(response[0])) {
                            if (dynamic_cast<Serie*>(v) && dynamic_cast<Serie*>(v)->GetId() == stoi(response)) {
                                cout << "----|" << v->GetNombre() << "|----" << endl;
                                dynamic_cast<Serie*>(v)->MostrarEpisodios();
                                cout << "Filtrar? [s/n]" << endl;
                                char fyn;
                                cin >> fyn;
                                if (fyn == 's') {
                                    cin.ignore();
                                    if (dynamic_cast<Serie*>(v) != nullptr) {
                                        Serie* serie = dynamic_cast<Serie*>(v);
                                        vector<Video*> episodios = serie->GetEpisodios();
                                        string nombref = askFilter("Nombre = ");
                                        string califf = askFilter("Califiación (Use =, <, > o <=, >= dependiendo lo que busque): ");

                                        filtrarVideos(episodios,"-","-",nombref,califf);
                                    } else {
                                        throw invalid_argument("No se encontró la serie seleccionada.");
                                    }
                                }
                                finded = true;
                                break;
                            }
                        }else {
                            if (string nombre = dynamic_cast<Serie*>(v)->GetNombre(); dynamic_cast<Serie*>(v) && nombre == response) {
                                dynamic_cast<Serie*>(v)->MostrarEpisodios();
                                cout << "Filtrar? [s/n]" << endl;
                                char fyn;
                                cin >> fyn;
                                if (fyn == 's') {
                                    cin.ignore();
                                    if (dynamic_cast<Serie*>(v) != nullptr) {
                                        Serie* serie = dynamic_cast<Serie*>(v);
                                        vector<Video*> episodios = serie->GetEpisodios();
                                        string nombref = askFilter("Nombre = ");
                                        string califf = askFilter("Califiación (Use =, <, > o <=, >= dependiendo lo que busque): ");

                                        filtrarVideos(episodios,"-","-",nombref,califf);
                                    } else {
                                        throw invalid_argument("No se encontró la serie seleccionada.");
                                    }
                                }
                                finded = true;
                                break;
                            }
                        }
                    }
                    if (!finded) throw invalid_argument("El id o nombre de la serie que busca no existe.");
                    cout << "Presiona Enter para continuar...";
                    cin.ignore();
                    cin.get();
                    break;
                }
                    case 5: {
                    cin.ignore();
                    cout << "Id o nombre del video = ";
                    string response;
                    getline(cin, response);
                    Video* videoSelected = nullptr;
                    for (Video* v : db) {
                        if ((std::isdigit(response[0]) && v->GetId() == stoi(response))||v->GetNombre() == response) videoSelected = v;
                    }
                    if (videoSelected == nullptr) throw invalid_argument("El id o nombre del video no existe.");
                    cout << "Qué calificación desea otorgarle a " << videoSelected->GetNombre() << "?\n-> ";
                    cin >> response;
                        if (videoSelected->Calificar(stoi(response))) {} else throw invalid_argument("La respuesta debe ser un valor entero.");
                    }
                default: ;
            }
        }catch (exception& e) {
            cerr << e.what() << endl;
            cerr << "Presiona Enter para continuar...";
            cin.ignore();
            cin.get();
        }
    }

    return 0;
}