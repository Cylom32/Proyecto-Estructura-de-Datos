#pragma once
#include"NavegadorWeb.h"
#include<windows.h>
class Menu
{
private:
	NavegadorWeb *navegador;

public:
	Menu();
	virtual ~Menu();

	NavegadorWeb* getNavegadorWeb() const;

	void setNavegadorWeb(NavegadorWeb* navegador);

	//--------------------P A R T E   D E   L O S  M E N U S -------------------------------------\\
	

	//Menu General
	void menuGeneral();
	void mostrarMenu(int);




	

	//Ir a un nuevo sitio web
	void irASitioWeb();
	bool verificarNavegadorIncializado();

	//Fin caso aparte
	void seleccionSitio();

	//Nuevos cambios
	void navegarModoIncognito(Pagina* paginaSeleccionada);

	void mostrar404Incognito();

	void navegarModoNormal(Pagina* paginaSeleccionada);

	void mostrar404Normal();
	
	//Fin nuevos cambios
	std::string mostrarSitiosDisponibles();

	void mostrarHistorialCompleto();
	void cargarAgregarGuardarHistorial(Pagina*);

	void nuevaPestania();


	void menuMarcadores(int op);
	void marcadores();

	void incognito();

	void menuBusqueda(int op);
	

	void configuracion();

	void importar();

	void exportar();
	//Filtrado  y busqueda
	void busqueda();




};

