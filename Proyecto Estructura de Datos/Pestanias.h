#pragma once
#include<vector>
#include "Pagina.h"
#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <chrono>

class Pestanias
{
private:
    Pagina* paginaActual;
    std::vector<Pagina*>* historial;
    int maxEntradasHistorial;

public:
    Pestanias();
    ~Pestanias();

    std::vector<Pagina*>* getHistorial();
    Pagina* getPaginaActual();
    void setPaginaActual(Pagina* pag);

    Pagina* obtenerPagina(std::string nombre);  
    std::string toString();
    std::string toStringHistorial();
 


    int indexPagina(Pagina* pagina);
    void paginaAnterior();
    void paginaSiguiente();
    void agregar(Pagina* pag);

    void agregarIncognita(Pagina* pag);

    bool hayPaginas() const;

    void guardarHistorial(const std::string&);
    void cargarHistorial(const std::string&);

    void guardarHistorialNuevaSecion(const std::string&);
    void cargarHistorialNuevaSecion(const std::string&);
    
    //Para las politicas del navegador
    void limitarHistorial();
    void limitarTiempoHistorial(int minutos);
    void setMaxEntradasHistorial(int max);

    void eliminarHistorialeDeMas(std::string);

    std::string buscar(std::string);

   
};

