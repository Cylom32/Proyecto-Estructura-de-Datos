#pragma once
#include"Pestanias.h"
#include"Marcador.h"
#include<iostream>
#include<windows.h>
#include<vector>
#include <fstream>
#include<string>
#include<sstream>
#include <chrono>
#include <thread>


class NavegadorWeb
{

private:
	std::string csv;
	std::vector <Pagina*>* paginasDisponibles;//Vector de paginas
	std::vector <Marcador*>* marcadores;
	std::vector <Pestanias*>* pestanias;//Vector de pestañas
	Pestanias* pestaniaActual;
	bool incognito;

	std::vector <Pestanias*>* incognitas;//Vector de pestañas
	Pestanias* incognitaActual;

	//Politicas de configuracion
	int limite;
	int maxTiempo;





public:

	NavegadorWeb(std::string = 0);
	~NavegadorWeb();





	void cargarPaginasDisponibles();

	std::vector <Pagina*>* getPaginasDisponibles();
	std::vector <Marcador*>* getMarcadores();
	Pestanias* getPestaniaActual();
	std::vector<Pestanias*>* getPestanias();
	void setPestanias(std::vector<Pestanias*>*);
	std::string toString();
	std::string irASitio();
	Pagina* buscarPagina(const std::string&);

	void crearNuevaPestania();
	int indexPestania( Pestanias* pestania);

	void pestaniaAnterior();
	void pestaniaSiguiente();
	void setPestaniaActual(Pestanias* nuevaPestania);

	

	std::string toStringMarcadores();
	bool agregarMarcador(Marcador* marc);

	void actualizarContadorPestanias();
	void setContadorPestanias(size_t);
	size_t leerContadorPestanias();



	void guardarMarcadores(const std::string& nom);

	void cargarMarcadores(const std::string& nom);




	//Modo incognito

	bool modoIncognito();
	void setIncognito(bool);
	void incognitaAnterior();
	void incognitaSiguiente();
	void setIncognitaActual(Pestanias* nuevaPestania);
	void crearNuevaIncognita();
	int indexIncognita(Pestanias* pestania);
	Pestanias* getIncognitaActual();
	std::vector<Pestanias*>* getIncognitas();


	std::string toStringIncognitas();

	//Politicas de configuracion
	int getlimite();
	void setLimite(int x);
	
	void setMaxTiempo(int);
	void inicalizarTiempoDeBorrado();
	void limpiarDespuesDelTiempo();

	//Busqueda Y filtrado
	void buscarPorTitulo(const std::string& titulo, std::vector<Pestanias*>* vec, Pestanias* pActual);

	void filtrarPorPalabraClave(const std::string& palabraClave, std::vector<Pestanias*>* vec, Pestanias* pActual);

	
};

