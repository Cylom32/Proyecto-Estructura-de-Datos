
#include "Menu.h"
#include <limits>
#include <conio.h> // Para usar _getch()
#include <windows.h> // Para usar Sleep()



Menu::Menu() : navegador(new NavegadorWeb("Paginas.csv")) {};

Menu::~Menu() {
    if (navegador != nullptr) {
        delete navegador;
    }
}

NavegadorWeb* Menu::getNavegadorWeb() const {
    return navegador;
}

void Menu::setNavegadorWeb(NavegadorWeb* navegador) {
    this->navegador = navegador;
}

void Menu::menuGeneral() {
    int op = 1;
    bool salir = false;

    while (!salir) {
        system("cls"); 
        mostrarMenu(op); 

        std::cout << "Seleccione una opcion (1-9): " << std::endl;

        char tecla = _getch();

        if (tecla >= '1' && tecla <= '9') {
            op = tecla - '0'; // Convertir el carácter numérico a número y seleccionar opción
        }
        else {
            switch (tecla) {
            case 72: // Flecha arriba
                if (navegador->modoIncognito() && navegador->getIncognitaActual() != nullptr && navegador->getIncognitaActual()->hayPaginas()) {
                    navegador->getIncognitaActual()->paginaAnterior();
                }
                else if (navegador->getPestaniaActual() != nullptr && navegador->getPestaniaActual()->hayPaginas()) {
                    navegador->getPestaniaActual()->paginaAnterior();
                }
                break;

            case 80: // Flecha abajo
                if (navegador->modoIncognito() && navegador->getIncognitaActual() != nullptr && navegador->getIncognitaActual()->hayPaginas()) {
                    navegador->getIncognitaActual()->paginaSiguiente();
                }
                else if (navegador->getPestaniaActual() != nullptr && navegador->getPestaniaActual()->hayPaginas()) {
                    navegador->getPestaniaActual()->paginaSiguiente();
                }
                break;

            case 75: // Flecha izquierda
                if (navegador->modoIncognito() && navegador->getIncognitas()->size() > 1) {
                    navegador->incognitaAnterior();
                }
                else if (navegador->getPestanias()->size() > 1) {
                    navegador->pestaniaAnterior();
                }
                break;

            case 77: // Flecha derecha
                if (navegador->modoIncognito() && navegador->getIncognitas()->size() > 1) {
                    navegador->incognitaSiguiente();
                }
                else if (navegador->getPestanias()->size() > 1) {
                    navegador->pestaniaSiguiente();
                }
                break;

            case 13: // Enter
                switch (op) {
                case 1:
                    irASitioWeb();
                    break;
                case 2:
                    if (navegador->modoIncognito()) {
                        navegador->crearNuevaIncognita();
                    }
                    else {
                        nuevaPestania();
                        system("pause");
                    }
                    break;
                    break;
                case 3:
                    if (!navegador->modoIncognito()) {
                        marcadores();
                    }
                    else {
                        system("cls");
                        std::cout << "No se pueden acceder a los marcadores desde el modo incognito..." << std::endl;
                        system("pause");
                    }
                    break;
                case 4:
                    incognito();
                    break;
                case 5:
                    busqueda();
                    break;
                case 6:
                    configuracion();
                    break;
                case 7:
                    importar();
                    break;
                case 8:
                    exportar();
                    break;
                case 9:
                    std::cout << "Saliendo del navegador web ..." << std::endl;
                    system("pause");
                    salir = true;
                    break;
                }
                break;

            default:
                // Ignorar otras teclas no utilizadas
                break;
            }
        }

        Sleep(100); // Pequeño retraso para evitar sobrecargar el CPU
    }
}

void Menu::mostrarMenu(int op) {
    std::cout << "------------ Navegador Web ------------" << std::endl;
    if (navegador->modoIncognito())
    {
        std::cout << "[Modo Incognito]" << std::endl;
        std::cout << "\t   ___  " << std::endl;
        std::cout << "\t  //_\\\\" << std::endl;  
        std::cout << "\t (-o.o-)" << std::endl;
        std::cout << "\t   ~~~ " << std::endl;
        std::cout << "Pestania actual: " << navegador->indexIncognita(navegador->getIncognitaActual()) + 1 << std::endl; 
        std::cout << "Sitio Actual: " << (navegador->getIncognitaActual() == nullptr || navegador->getIncognitaActual()->getPaginaActual() == nullptr ? "Ninguno" : navegador->getIncognitaActual()->getPaginaActual()->getTitulo()) << std::endl;
    }
    else {
        std::cout << "Pestania actual: " << navegador->indexPestania(navegador->getPestaniaActual()) + 1 << std::endl; 
        std::cout << "Sitio Actual: " << (navegador->getPestaniaActual() == nullptr || navegador->getPestaniaActual()->getPaginaActual() == nullptr ? "Ninguno" : navegador->getPestaniaActual()->getPaginaActual()->getTitulo()) << std::endl; 
    }

   
    for (int i = 1; i <= 9; ++i) {
        std::cout << (op == i ? "> " : "  ") << i << ") ";
        switch (i) {
        case 1: std::cout << "Ir a un sitio web." << std::endl; break;
        case 2: std::cout << "Nueva pestaniaa." << std::endl; break;
        case 3: std::cout << "Marcadores" << std::endl; break;
        case 4: std::cout << "Modo incognito." << std::endl; break;
        case 5: std::cout << "Busqueda." << std::endl; break;
        case 6: std::cout << "Configuracion." << std::endl; break;
        case 7: std::cout << "Importacion." << std::endl; break;
        case 8: std::cout << "Exportacion." << std::endl; break;
        case 9: std::cout << "Salir." << std::endl; break;
        }
    }
}

// ------------------------I N I C I O       M E N U    I R      A       S I T I O------------------------\\

void Menu::irASitioWeb()
{
    system("cls");

    if (!verificarNavegadorIncializado()) {
        return;
    }

    std::cout << mostrarSitiosDisponibles();
    seleccionSitio();
}

bool Menu::verificarNavegadorIncializado() {
    if (navegador == nullptr) {
        std::cout << "Error: Navegador no inicializado." << std::endl;
        system("pause");
        return false;
    }
    return true;

}


void Menu::navegarModoIncognito(Pagina* paginaSeleccionada) {
    system("cls");
    std::cout << "Navegando a: " << paginaSeleccionada->getUrl() << " - " << paginaSeleccionada->getTitulo() << std::endl;

    // No guardamos en el historial en modo incógnito
    navegador->getIncognitaActual()->setPaginaActual(paginaSeleccionada);
    navegador->getIncognitaActual()->agregarIncognita(paginaSeleccionada);

}

void Menu::mostrar404Incognito() {
    system("cls");
    std::cout << "404 NOT FOUND - La pagina ingresada no existe." << std::endl;

    Pagina* pagina404 = new Pagina("404", "Not Found", "404 NOT FOUND");
    navegador->getIncognitaActual()->setPaginaActual(pagina404);
    navegador->getIncognitaActual()->agregarIncognita(pagina404);
}

void Menu::navegarModoNormal(Pagina* paginaSeleccionada) {
    system("cls");
    std::cout << "Navegando a: " << paginaSeleccionada->getUrl() << " - " << paginaSeleccionada->getTitulo() << std::endl;

    // Guardamos en el historial en modo normal
    this->cargarAgregarGuardarHistorial(paginaSeleccionada);
    navegador->getPestaniaActual()->setPaginaActual(paginaSeleccionada);
}

void Menu::mostrar404Normal() {
    system("cls");
    std::cout << "404 NOT FOUND - La pagina ingresada no existe." << std::endl;

    Pagina* pagina404 = new Pagina("404", "Not Found", "404 NOT FOUND");
    navegador->getPestaniaActual()->setPaginaActual(pagina404);
    this->cargarAgregarGuardarHistorial(pagina404);
}


void Menu::seleccionSitio() {
    std::string titulo;

    std::cout << "Ingrese el titulo del sitio web (case sensitive): ";
    std::cin >> titulo;

    Pagina* paginaSeleccionada = nullptr;
    for (Pagina* pagina : *navegador->getPaginasDisponibles()) {
        if (pagina->getTitulo() == titulo) {
            paginaSeleccionada = pagina;
            break;
        }
    }

    if (paginaSeleccionada != nullptr) {
        if (navegador->modoIncognito()) {
            navegarModoIncognito(paginaSeleccionada);
        }
        else {
            navegarModoNormal(paginaSeleccionada);
        }
    }
    else {
        if (navegador->modoIncognito()) {
            mostrar404Incognito();
        }
        else {
            mostrar404Normal();
        }
    }
    system("pause");
}



//Fin cambios en el seleccion sitio


std::string Menu::mostrarSitiosDisponibles()
{
    std::stringstream s;
    system("cls");
    s << "------------------------ Selecciona el sitio web al que quieres ir ------------------------\n";
    navegador->irASitio();
    std::vector<Pagina*>* paginas = navegador->getPaginasDisponibles();

    for (int i = 0; i < paginas->size(); i++) {
        s << i + 1 << ")" << (*paginas)[i]->getTitulo() << "\n";
    }
    return s.str();
}


void Menu::mostrarHistorialCompleto()

{

    size_t contadorDeseado = navegador->leerContadorPestanias();

    while (navegador->getPestanias()->size() < contadorDeseado) {

        navegador->crearNuevaPestania();

    }

    for (int i = 0; i < navegador->getPestanias()->size(); ++i) {

        Pestanias* pestania = navegador->getPestanias()->at(i);

        if (pestania != nullptr) {

            std::string fileName = "Historial_" + std::to_string(i + 1) + ".bin";

            std::cout << "Historial " << (i + 1) << ":\n";

            pestania->cargarHistorial(fileName);

            std::cout << pestania->toStringHistorial() << std::endl;

        }

    }

}




void Menu::cargarAgregarGuardarHistorial(Pagina* pag)
{
    if (!navegador->modoIncognito())
        navegador->getPestaniaActual()->agregar(pag);
    else
        navegador->getIncognitaActual()->agregarIncognita(pag);

}


// ------------------------     F I N      M E N U    I R      A       S I T I O    ------------------------\\



void Menu::nuevaPestania() {
    if (!verificarNavegadorIncializado()) {
        return;
    }
    navegador->crearNuevaPestania();
}


void Menu::menuMarcadores(int op) {
    std::cout << "------------ Menu Marcadores ------------" << std::endl;
    for (int i = 1; i <= 4; ++i) {
        std::cout << (op == i ? "> " : "  ") << i << ") ";
        switch (i) {
            case 1: std::cout << "Agregar pagina actual a marcadores." << std::endl; break;
            case 2: std::cout << "Listar marcadores." << std::endl; break;
            case 3: std::cout << "Buscar marcador" << std::endl; break;
            case 4: std::cout << "Volver" << std::endl; break;
        }
    }
}

void Menu::marcadores() {
    int op = 1;
    bool salir = false;

    while(!salir){
        system("cls");
        menuMarcadores(op);

        char tecla = _getch(); // Captura la tecla presionada

        if (tecla >= '1' && tecla <= '4') {
            op = tecla - '0'; // Convertir el carácter numérico a número y seleccionar opción
        }
        else {
            switch (tecla)
            {
            case 13: // Enter
                system("cls");
                switch (op) {
                case 1: {
                    std::cout << "------------ Menu Marcadores ------------" << std::endl;
                    if(navegador->getPestaniaActual()->getPaginaActual() == nullptr){
                        std::cout << "No se encuentra en ninguna pagina actualmente..." << std::endl;
                    }
                    else {
                        std::string tag;
                        std::cout << "Agregue un comentario o tag para este marcador: ";
                        std::cin.ignore();
                        std::getline(std::cin, tag);
                        Marcador* marcador = new Marcador(tag);
                        marcador->setPagina(navegador->getPestaniaActual()->getPaginaActual());
                        if (navegador->agregarMarcador(marcador)) {
                            std::cout << "Se ha agregado un marcador exitosamente!" << std::endl;
                        }
                        else {
                            std::cout << "Ya existe un marcador para esta pagina..." << std::endl;
                        }
                    }
                    system("pause");
                        break;
                    }
                case 2:
                    std::cout << "------------ Menu Marcadores ------------" << std::endl;
                    if (!navegador->getMarcadores()->empty()) {
                        std:: cout << navegador->toStringMarcadores() << std::endl;
                    }
                    else {
                        std::cout << "No hay marcadores registrados..." << std::endl;
                    }
                    system("pause");
                    break;
                case 3: {
                    std::cout << "------------ Menu Marcadores ------------" << std::endl;
                    if (navegador->getMarcadores()->empty()) {
                        std::cout << "No hay marcadores registrados..." << std::endl;
                    } else {
                        std::cout << navegador->toStringMarcadores();
                        std::string titulo;

                        std::cout << "Ingrese el titulo del sitio web (case sensitive): ";
                        std::cin >> titulo;

                        Marcador* marcadorSeleccionado = nullptr;
                        for (Marcador* marcador : (*navegador->getMarcadores())) {
                            if (marcador->getPagina()->getTitulo() == titulo) {
                                marcadorSeleccionado = marcador;
                                break;
                            }
                        }

                        if (marcadorSeleccionado != nullptr) {
                            system("cls");
                            std::cout << "Navegando a: " << marcadorSeleccionado->toString() << std::endl;

                            if (!navegador->modoIncognito()) {
                                this->cargarAgregarGuardarHistorial(marcadorSeleccionado->getPagina());
                            }
                            navegador->getPestaniaActual()->setPaginaActual(marcadorSeleccionado->getPagina());
                        }
                    }
                    system("pause");
                    break;
                }
                case 4:
                    salir = true;
                    break;
                }
                break;

            default:
                break;
            }
        }
    }
}

void Menu::incognito() {
    system("cls");
    if (navegador->modoIncognito()) {
        std::cout << "Modo incognito desactivado. " << std::endl;
        navegador->setIncognito(false);
        if (!navegador->getPestaniaActual()->getHistorial()->empty()) {
            navegador->getPestaniaActual()->setPaginaActual((*navegador->getPestaniaActual()->getHistorial())[0]);
        }
        else {
            navegador->getPestaniaActual()->setPaginaActual(nullptr);
        }
    }
    else {
        std::cout << "Modo incognito activado." << std::endl;
        navegador->setIncognito(true);
        navegador->getPestaniaActual()->setPaginaActual(nullptr);
    }
    system("pause");
}

void Menu::menuBusqueda(int op)
{
    std::cout << "------------ Menu Busqueda ------------" << std::endl;
    for (int i = 1; i <= 3; ++i) {
        std::cout << (op == i ? "> " : "  ") << i << ") ";
        switch (i) {
        case 1: std::cout << "Filtrado." << std::endl; break;
        case 2: std::cout << "Busqueda." << std::endl; break;
        case 3: std::cout << "Salir." << std::endl; break;
        }
    }
}

void Menu::busqueda() {
    int opcion;

    do {
    system("cls");
    std::cout << "1. Buscar por titulo exacto" << std::endl;
    std::cout << "2. Filtrar por palabra clave" << std::endl;
    std::cout << "Seleccione una opcion: ";

    std::cin >> opcion; if (std::cin.fail()) { std::cin.clear(); std::cin.ignore(); }
    } while (std::cin.fail() || opcion < 1 || opcion > 2);

    std::string criterioBusqueda;
    switch (opcion) {
    case 1:
        std::cout << "Ingrese el titulo exacto: ";
        std::cin.ignore();
        std::getline(std::cin, criterioBusqueda);
        if (navegador->modoIncognito()) {
            navegador->buscarPorTitulo(criterioBusqueda, navegador->getIncognitas(), navegador->getIncognitaActual());
        }
        else {
            navegador->buscarPorTitulo(criterioBusqueda, navegador->getPestanias(), navegador->getPestaniaActual());
        }
        break;
    case 2:
        std::cout << "Ingrese la palabra clave: ";
        std::cin.ignore();
        std::getline(std::cin, criterioBusqueda);
        if (navegador->modoIncognito()) {
            navegador->filtrarPorPalabraClave(criterioBusqueda, navegador->getIncognitas(), navegador->getIncognitaActual());
        }
        else {
            navegador->filtrarPorPalabraClave(criterioBusqueda, navegador->getPestanias(), navegador->getPestaniaActual());
        }
        break;
    default:
        std::cout << "Opcion no valida" << std::endl;
    }

    system("pause");
    std::cin.clear();
}



void Menu::configuracion() {
    system("cls");
    if (navegador->modoIncognito()) {
        std::cout << "La configuracion no esta disponible en el modo incognito." << std::endl;
        system("pause");
        return;
    }

    int opcion;
    std::cout << "Configuracion del navegador" << std::endl;
    std::cout << " 1. Cambiar limite de pestanias (actual: " << navegador->getlimite() << " )" << std::endl;
    std::cout << " 2. Cambiar el tiempo de vida del historial: " << std::endl;
    std::cout << " 3. Volver: " << std::endl;
    std::cout << "Seleccione una opcion: " << std::endl;
    std::cin >> opcion;

    switch (opcion) {
    case 1: {
        int nuevoLimite;
        std::cout << "Ingrese el nuevo limite de pestanias: ";
        std::cin >> nuevoLimite;
        while (nuevoLimite < navegador->getPestanias()->size()) {
            std::cout << "Error: Debe ser mayor o igual a las pestañas actuales: " << navegador->getPestanias()->size() << std::endl;
            std::cout << "Ingrese el nuevo limite de pestanias: ";
            std::cin >> nuevoLimite;
        }
        navegador->setLimite(nuevoLimite);
        std::cout << "Nuevo limite de pestanias establecido: " << nuevoLimite << std::endl;
        system("pause");
        break;
    }
    case 2:
        int tiempoVida;
        std::cout << "Ingresa el tiempo de vida del historial (en minutos): ";
        std::cin >> tiempoVida;  

        navegador->setMaxTiempo(tiempoVida);  
        navegador->inicalizarTiempoDeBorrado();  
        return;
    case 3:
        return;
    default:
        std::cout << "Opcion no valida." << std::endl;
        break;
    }

 
    std::cout << "Configuracion actualizada.\n";
}

void Menu::importar() {
    system("cls");
    //--------------------------------------------------------------
    if (navegador->modoIncognito()) {
        system("cls");
        std::cout << "No se puede cargar una sesion anterior desde el modo incognito..." << std::endl;
        system("pause");
        return;
    }
    system("cls");
    std::string op = "";
    std::cout << "Sesion pasada:" << std::endl;

    size_t contadorDeseado = navegador->leerContadorPestanias();
    while (navegador->getPestanias()->size() < contadorDeseado) {
        navegador->crearNuevaPestania();
    }

    // Cargar marcadores
    navegador->cargarMarcadores("Marcadores.bin");

    // Cargar los historiales
    for (int i = 0; i < navegador->getPestanias()->size(); ++i) {
        Pestanias* pestania = navegador->getPestanias()->at(i);
        if (pestania != nullptr) {
            std::string fileName = "Historial_" + std::to_string(i + 1) + ".bin";
            std::cout << "Pestania " << (i + 1) << ":\n";
            pestania->cargarHistorial(fileName);
            std::cout << pestania->toStringHistorial() << std::endl;
            if (pestania->getHistorial()->empty()) {
                pestania->setPaginaActual(nullptr);
            }
            else {
                pestania->setPaginaActual((*pestania->getHistorial())[0]);
            }
        }
    }


    if (op == "Y" || op == "y") {
        navegador->cargarMarcadores("Marcadores.bin");
        for (int i = 0; i < navegador->getPestanias()->size(); i++) {
            (*navegador->getPestanias())[i]->setPaginaActual((*(*navegador->getPestanias())[i]->getHistorial())[0]);
        }
    }
    //--------------------------------------------------------------
    std::cout << "Importacion realizada correctamente." << std::endl;
    system("pause");
}

void Menu::exportar() {
    system("cls");
    int i = 1, j = 1;
    size_t tam = navegador->getPestanias()->size();
    if (navegador->modoIncognito()) {
        std::cout << "La exportacion no esta disponible en el modo incognito." << std::endl;
        system("pause");
        return;
    }    
 
    // Guardar marcadores
    navegador->guardarMarcadores("Marcadores.bin");

    if(navegador->getPestanias()->size() < navegador->leerContadorPestanias()){
    std::vector <Pestanias*>* p = new std::vector<Pestanias*>();
    NavegadorWeb* n = new NavegadorWeb("Paginas.csv");
    n->setPestanias(p);
    for (int i = 0; i < navegador->leerContadorPestanias(); i++) {
        n->crearNuevaPestania();
    }
    for (Pestanias* pe : *p) {
        if (pe) {
            if (j > navegador->getPestanias()->size())
                pe->eliminarHistorialeDeMas("Historial_" + std::to_string(j) + ".bin");
            j++;
        }
        for (Pestanias* pesta : *navegador->getPestanias()) {
            if (pesta) { // Verificar que el puntero no sea nulo
                pesta->guardarHistorialNuevaSecion("Historial_" + std::to_string(i++) + ".bin"); // Llama al método en cada objeto
            }
        }
    }
    navegador->setContadorPestanias(tam);
    }
    else {
        for (Pestanias* pesta : *navegador->getPestanias()) {
            if (pesta) { // Verificar que el puntero no sea nulo
                pesta->guardarHistorialNuevaSecion("Historial_" + std::to_string(i++) + ".bin"); // Llama al método en cada objeto
            }
        }
    }
    std::cout << "Exportacion realizada correctamente." << std::endl;
    system("pause");
}

