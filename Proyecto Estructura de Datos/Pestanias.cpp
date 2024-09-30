#include "Pestanias.h"

Pestanias::Pestanias(){
	historial = new std::vector<Pagina*>();
	this->paginaActual = nullptr;
	this->maxEntradasHistorial = 100;
}



Pestanias::~Pestanias()
{
	delete historial;
}


Pagina* Pestanias::obtenerPagina(std::string nombre)
{
	for (Pagina* pagina : *historial) {
		if (pagina->getTitulo() == nombre) 
		{
			return pagina;
		}
	}


	return nullptr;
}

std::string Pestanias::toString()
{
	std::stringstream s;

	for (Pagina* pagina : *historial) {
		s << pagina->getUrl();
	}
	return s.str();
}

Pagina* Pestanias::getPaginaActual() {
	return paginaActual;
}

void Pestanias::setPaginaActual(Pagina* pag) {
	paginaActual = pag;
}

std::string Pestanias::toStringHistorial() {
	std::stringstream s;

	if (historial->empty()) {
		s << "El historial esta vacio.\n";
		return s.str();
	}

	for (int i = 0; i < historial->size(); i++) {
		if ((*historial)[i] != nullptr) {
			s << "URL: " << (*historial)[i]->getUrl() << "\t"
				<< "DOM: " << (*historial)[i]->getDominio() << "\t"
				<< "Titulo: " << (*historial)[i]->getTitulo() << "\n";
		}
	}

	return s.str();
}


int Pestanias::indexPagina(Pagina* pagina) {
	// Buscar la pagina en el historial
	auto it = std::find(historial->begin(), historial->end(), pagina);

	// Si la página fue encontrada
	if (it != historial->end()) {
		return std::distance(historial->begin(), it);
	}
	else {
		// Pagina no encontrada, devolver un valor especial
		return -1;
	}
}


void Pestanias::paginaAnterior() {
	int indiceActual = indexPagina(getPaginaActual());
	if (indiceActual > 0) {
		setPaginaActual((*historial)[indiceActual - 1]);
	}
}
void Pestanias::paginaSiguiente() {
	int indiceActual = indexPagina(getPaginaActual());
	if (indiceActual < historial->size() - 1) {
		setPaginaActual((*historial)[indiceActual + 1]);
	}
}


void Pestanias::agregar(Pagina* pag) {

	if (pag == nullptr) 
		pag = new Pagina("Error", "Error", "404 Not Found");

	historial->push_back(pag);
	setPaginaActual(pag);  
	limitarHistorial();
	limitarTiempoHistorial(60);

}

void Pestanias::agregarIncognita(Pagina* pag) {
	if (pag == nullptr)
		pag = new Pagina("Error", "Error", "404 Not Found");

	historial->push_back(pag);
	setPaginaActual(pag);
}

bool Pestanias::hayPaginas() const {
	return !historial->empty();
}

//----------------------------------------------------------------------------------------------------------------
//Continuar sesion
void Pestanias::guardarHistorial(const std::string& nom)
{
	if (historial->empty()) {
		std::cerr << "El historial esta vacio, no se guardara nada." << std::endl;
		return;
	}

	std::ofstream outFile(nom, std::ios::binary | std::ios::trunc);
	if (outFile.is_open()) {
		for (Pagina* pagina : *historial) {
			if (pagina != nullptr) {
				pagina->serializar(outFile);
			}
		}
		outFile.close();
		std::cout << "Historial guardado exitosamente en " << nom << std::endl;
	}
	else {
		std::cerr << "No se pudo abrir el archivo " << nom << " para guardar." << std::endl;
	}
}


void Pestanias::cargarHistorial(const std::string& nom)
{
	std::ifstream inFile(nom, std::ios::binary);
	if (!inFile.is_open()) {
		return;
	}

	historial->clear();

	while (true) {
		Pagina* pagina = new Pagina();
		if (pagina->deserializar(inFile)) {
			historial->push_back(pagina);
		}
		else {
			delete pagina;
			break;
		}
	}

	inFile.close();
}

//----------------------------------------------------------------------------------------------------------------
//Nueva secion

void Pestanias::guardarHistorialNuevaSecion(const std::string& nom)
{
	if (historial->empty()) {
		if (std::remove(nom.c_str()) == 0) {
			std::cout << "Archivo vacío eliminado: " << nom << std::endl;
		}
		return;
	}

	std::ofstream outFile(nom, std::ios::binary);
	if (outFile.is_open()) {
		for (Pagina* pagina : *historial) {
			if (pagina != nullptr) {
				pagina->serializar(outFile);
			}
		}
		outFile.close();
	}
	else {
		std::cerr << "No se pudo abrir el archivo " << nom << " para guardar." << std::endl;
	}
}


void Pestanias::cargarHistorialNuevaSecion(const std::string& nom)
{
	if (historial->empty()) {
		if (std::remove(nom.c_str()) == 0) {
			std::cout << "Archivo vacio eliminado: " << nom << std::endl;
		}
		return;
	}

	std::ofstream outFile(nom, std::ios::binary | std::ios::app);
	if (outFile.is_open()) {
		for (Pagina* pagina : *historial) {
			if (pagina != nullptr) {
				pagina->serializar(outFile);
			}
		}
		outFile.close();
	}
	else {
		std::cerr << "No se pudo abrir el archivo " << nom << " para guardar." << std::endl;
	}
}
//----------------------------------------------------------------------------------------------------------------

//Para la privacidad
void Pestanias::limitarHistorial() {
	if (historial->size() > maxEntradasHistorial) {
	
		historial->erase(historial->begin(), historial->begin() + (historial->size() - maxEntradasHistorial));
	}
}



void Pestanias::limitarTiempoHistorial(int minutos) {
	auto now = std::chrono::system_clock::now();

	historial->erase(
		std::remove_if(historial->begin(), historial->end(), [&](Pagina* pag) {
			auto tiempoVisita = pag->getTiempoVisita();
			auto duracion = std::chrono::duration_cast<std::chrono::minutes>(now - tiempoVisita);
			return duracion.count() > minutos;
			}),
		historial->end()
	);
}


void Pestanias::setMaxEntradasHistorial(int max) {
	maxEntradasHistorial = max;
}

void Pestanias::eliminarHistorialeDeMas(std::string nom)
{
	std::remove(nom.c_str());
}



std::vector<Pagina*>* Pestanias::getHistorial() {
	return historial;
}



std::string Pestanias::buscar(std::string titulo)
{
	std::stringstream s; 
	if (historial != nullptr) { 
		for (Pagina* page : *historial) {  
			if (page->getTitulo() == titulo) { 
				s << page->getTitulo() << std::endl; 
			}
		}
	}
	if (s.str().empty()) { 
		s << "No se encontro la pagina con el titulo: " << titulo; 
	}
	return s.str(); 
}