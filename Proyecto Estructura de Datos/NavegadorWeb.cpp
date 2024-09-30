#include "NavegadorWeb.h"

NavegadorWeb::NavegadorWeb(std::string csv) : csv(csv) {
    this->incognito = false;
    pestanias = new std::vector<Pestanias*>();
    pestaniaActual = new Pestanias();
    pestanias->push_back(pestaniaActual);
    paginasDisponibles = new std::vector<Pagina*>();
    marcadores = new std::vector<Marcador*>();

    incognitas = new std::vector<Pestanias*>(); 
    incognitaActual = new Pestanias(); 
    incognitas->push_back(incognitaActual);

    limite= 10; 
    maxTiempo = 60;

}

NavegadorWeb::~NavegadorWeb()
{
    for (int i = 0; i < paginasDisponibles->size(); i++) {
        if ((*paginasDisponibles)[i] != nullptr) {
            delete (*paginasDisponibles)[i]; // Si se borran aqui, se borran de todos los demás vectores, puesto que estas son las paginas origen
        }
    }
    delete paginasDisponibles;

    for (int i = 0; i < pestanias->size(); i++) {
        if ((*pestanias)[i] != nullptr) {
            delete (*pestanias)[i];
        }
    }
    delete pestanias;

    for (int i = 0; i < marcadores->size(); i++) {
        if ((*marcadores)[i] != nullptr) {
            delete (*marcadores)[i];
        }
    }
    delete marcadores;
    delete incognitas;
}


void NavegadorWeb::cargarPaginasDisponibles() {
    std::ifstream archivo(csv);
    if (!archivo.is_open()) {
        throw std::runtime_error("Error al abrir el archivo: " + csv);
    }
    std::string linea;
    std::getline(archivo, linea); 


    while (std::getline(archivo, linea)) {
        std::istringstream ss(linea);
        std::string url, dominio, titulo;

        if (!std::getline(ss, url, ',') || !std::getline(ss, dominio, ',') || !std::getline(ss, titulo)) {
            throw std::runtime_error("Error al procesar la linea del archivo CSV.");
        }

        paginasDisponibles->push_back(new Pagina(url, dominio, titulo));
    }

    archivo.close();
}

std::vector <Pagina*>* NavegadorWeb::getPaginasDisponibles() {
    return paginasDisponibles;
}

std::vector <Marcador*>* NavegadorWeb::getMarcadores() {
    return marcadores;
}

Pestanias* NavegadorWeb::getPestaniaActual() {
    return pestaniaActual;
}

std::vector<Pestanias*>* NavegadorWeb::getPestanias() {
    return pestanias;
}

void NavegadorWeb::setPestanias(std::vector<Pestanias*>* x)
{
    pestanias = x;
}

std::string NavegadorWeb::toString() {
   std::stringstream s;
    for (int i = 0; i < pestanias->size(); i++) {
        s << (*pestanias)[i]->toStringHistorial() << "\n";
    }

    return s.str();
}

std::string NavegadorWeb::irASitio() {
    std::stringstream s;
    s<<"------------------------ Selecciona el sitio web al que quieres ir ------------------------\n";
    for (int i = 0; i < pestanias->size(); i++) {
        s << "URL: " << (*pestanias)[i]->toString() <<"\n";
    }
    return s.str();
}

Pagina* NavegadorWeb::buscarPagina(const std::string& nomS)
{
    for (Pagina* pagina : *paginasDisponibles) {
        if (pagina->getTitulo() == nomS) {
            return pagina;
        }
    }
    return nullptr;
}



void NavegadorWeb::crearNuevaPestania() {
    if (pestanias->size() >= limite) {
        std::cout << "No se puede crear una pestania. Limite maximo de " << limite << "pestanias alcanzado. " << std::endl;
        return;
    }

    Pestanias* nuevaPestania = new Pestanias();

    pestanias->push_back(nuevaPestania);

    pestaniaActual = nuevaPestania;

    if (this->leerContadorPestanias() < this->getPestanias()->size()) {
        actualizarContadorPestanias();      // Actualizar el contador en el archivo
    }
    //std::cout << "Nueva pestania creada y seleccionada." << std::endl;
}


int NavegadorWeb::indexPestania(Pestanias* pestania) {

    auto it = std::find(pestanias->begin(), pestanias->end(), pestania);

    if (it != pestanias->end()) {

        return std::distance(pestanias->begin(), it);

    }

    else {

        return 0;

    }

}


void NavegadorWeb::setPestaniaActual(Pestanias* nuevaPestania) {
    pestaniaActual = nuevaPestania;  
}


void NavegadorWeb::pestaniaAnterior() {
    int indiceActual = indexPestania( getPestaniaActual());
    if (indiceActual > 0) {
        setPestaniaActual((*pestanias)[indiceActual - 1]);
    }
}
void NavegadorWeb::pestaniaSiguiente() {
    int indiceActual = indexPestania(getPestaniaActual());
    if (indiceActual < pestanias->size() - 1) {
        setPestaniaActual((*pestanias)[indiceActual + 1]);  // Cambiar a la pestaña siguiente
    }
}

bool NavegadorWeb::agregarMarcador(Marcador* marc) {
    for (Marcador* m : *marcadores) {
        if (m->getPagina() == marc->getPagina()) {
            return false;
        }
    }
    marcadores->push_back(marc);
    return true;
}

void NavegadorWeb::actualizarContadorPestanias()
{
    std::ofstream outFile("cantH.bin", std::ios::binary);
    if (outFile.is_open()) {
        size_t cantidad = pestanias->size(); // Obtener el tamaño actual
        outFile.write(reinterpret_cast<const char*>(&cantidad), sizeof(cantidad));
        outFile.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo para actualizar el contador." << std::endl;
    }
}

void NavegadorWeb::setContadorPestanias(size_t numeroEspecifico)
{
    std::ofstream outFile("cantH.bin", std::ios::binary);
    if (outFile.is_open()) {
        outFile.write(reinterpret_cast<const char*>(&numeroEspecifico), sizeof(numeroEspecifico));
        outFile.close();
    }
    else {
        std::cerr << "No se pudo abrir el archivo para actualizar el contador." << std::endl;
    }
}

size_t NavegadorWeb::leerContadorPestanias()
{
    std::ifstream inFile("cantH.bin", std::ios::binary);
    size_t cantidad = 0;
    if (inFile.is_open()) {
        inFile.read(reinterpret_cast<char*>(&cantidad), sizeof(cantidad));
        inFile.close();
    }
    else {
     
    }
    return cantidad;
}

std::string NavegadorWeb::toStringMarcadores() {
    std::stringstream s;

    if (marcadores->empty()) {
        s << "No existen marcadores...\n";
        return s.str();
    }

    for (int i = 0; i < marcadores->size(); i++) {
        if ((*marcadores)[i] != nullptr) {
            s << (*marcadores)[i]->toString() << "\n";
        }
    }

    return s.str();
}

bool NavegadorWeb::modoIncognito() {
    return incognito;
}
void NavegadorWeb::setIncognito(bool x) {
    incognito = x;
}




void NavegadorWeb::guardarMarcadores(const std::string& nom)
{
    if (marcadores->empty()) {
        std::cerr << "Los marcadores estan vacios, no se guardara nada." << std::endl;
        return;
    }

    std::ofstream outFile(nom, std::ios::binary | std::ios::trunc);
    if (outFile.is_open()) {
        for (Marcador* marcador : *marcadores) {
            if (marcador != nullptr) {
                marcador->serializar(outFile);
            }
        }
        outFile.close();
        std::cout << "Marcadores guardados exitosamente en " << nom << std::endl;
    }
    else {
        std::cerr << "No se pudo abrir el archivo " << nom << " para guardar." << std::endl;
    }
}

void NavegadorWeb::cargarMarcadores(const std::string& nom) {
    std::ifstream inFile(nom, std::ios::binary);
    if (!inFile.is_open()) {
        return;
    }

    marcadores->clear();

    while (true) {
        Marcador* marcador = new Marcador();
        if (marcador->deserializar(inFile)) {
            marcadores->push_back(marcador);
        }
        else {
            delete marcador;
            break;
        }
    }

    inFile.close();
}


int NavegadorWeb::indexIncognita(Pestanias* pestania) {

    auto it = std::find(incognitas->begin(), incognitas->end(), pestania);

    if (it != incognitas->end()) {

        return std::distance(incognitas->begin(), it);

    }

    else {

        return 0;

    }

}


void NavegadorWeb::incognitaAnterior() {
    int indiceActual = indexIncognita(getIncognitaActual());
    if (indiceActual > 0) {
        setIncognitaActual((*incognitas)[indiceActual - 1]);
    }
}
void NavegadorWeb::incognitaSiguiente() {
    int indiceActual = indexIncognita(getIncognitaActual());
    if (indiceActual < incognitas->size() - 1) {
        setIncognitaActual((*incognitas)[indiceActual + 1]); 
    }
}


void NavegadorWeb::setIncognitaActual(Pestanias* nuevaPestania) {
    incognitaActual = nuevaPestania;
}
void NavegadorWeb::crearNuevaIncognita() {

    Pestanias* nuevaPestania = new Pestanias();
    incognitas->push_back(nuevaPestania);
    incognitaActual = nuevaPestania;

    std::cout << "Nueva pestania Incognita creada y seleccionada." << std::endl;
}


Pestanias* NavegadorWeb::getIncognitaActual() {
    return incognitaActual;
}
std::vector<Pestanias*>* NavegadorWeb::getIncognitas() {
    return incognitas;
}



std::string NavegadorWeb::toStringIncognitas() {
    std::stringstream s;
    for (int i = 0; i < incognitas->size(); i++) {
        s << (*incognitas)[i]->toStringHistorial() << "\n";
    }

    return s.str();
}


int NavegadorWeb::getlimite() {
    return limite;
}


void NavegadorWeb::setLimite(int x) {
    limite = x;
}


void NavegadorWeb::setMaxTiempo(int x)
{
    this->maxTiempo = x;
}

void NavegadorWeb::inicalizarTiempoDeBorrado()
{

    std::thread([this]() {
        std::this_thread::sleep_for(std::chrono::minutes(maxTiempo));
        limpiarDespuesDelTiempo();
        }).detach();
}

void NavegadorWeb::limpiarDespuesDelTiempo()
{
    pestanias->clear();
    Pestanias* pNueva = new Pestanias();
    this->setPestaniaActual(pNueva);
    this->pestanias->push_back(pNueva);
    std::cout << "El vector de pestanias ha sido vaciado despues de " << maxTiempo << " minutos.\n";
}


void NavegadorWeb::buscarPorTitulo(const std::string& tituloBuscado, std::vector<Pestanias*>* vec, Pestanias* pActual) {
    if (vec == nullptr || vec->empty()) {
        std::cout << "No hay pestanias abiertas actualmente." << std::endl;
        return;
    }

    bool encontrado = false;
         
    for (const auto& pagina : *pActual->getHistorial()) {
        if (pagina != nullptr) {
                  
            if (pagina->getTitulo() == tituloBuscado) {
                std::cout << "Pagina encontrada con el titulo '" << tituloBuscado << "': " << std::endl;
                std::cout << "URL: " << pagina->getUrl() << std::endl;

                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron paginas con el titulo '" << tituloBuscado << "'." << std::endl;
    }
}


void NavegadorWeb::filtrarPorPalabraClave(const std::string& palabraClave, std::vector<Pestanias*>* vec, Pestanias* pActual) {
    if (vec == nullptr || vec->empty()) {
        std::cout << "No hay pestanias abiertas actualmente." << std::endl;
        return;
    }

    bool encontrado = false;
    
    for (const auto& pagina : *pActual->getHistorial()) {
        if (pagina != nullptr) {
                  
            if (pagina->getTitulo().find(palabraClave) != std::string::npos) {
                std::cout << "Pagina encontrada con la palabra clave '" << palabraClave << "': " << std::endl;
                std::cout << "URL: " << pagina->getUrl() << std::endl;
                encontrado = true;
            }
        }
    }

    if (!encontrado) {
        std::cout << "No se encontraron paginas con la palabra clave '" << palabraClave << "'." << std::endl;
    }
}


