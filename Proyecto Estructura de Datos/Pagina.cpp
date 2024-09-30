#include "Pagina.h"

Pagina::Pagina(std::string url, std::string dominio, std::string titulo):url(url),dominio(dominio),titulo(titulo)
{
	setTiempoVisita();
}

Pagina::~Pagina()
{
}

std::string Pagina::getUrl()
{
	return url;
}

std::string Pagina::getDominio()
{
	return dominio;
}

std::string Pagina::getTitulo()
{
	return titulo;
}

void Pagina::setUrl(std::string x)
{
	this->url = x;
}

void Pagina::setDominio(std::string x)
{
	this->dominio = x;
}

void Pagina::setTitulo(std::string x)
{
	this->titulo = x;
}

void Pagina::serializar(std::ofstream& x)
{
	size_t urlLen = url.size();
	size_t dominioLen = dominio.size();
	size_t tituloLen = titulo.size();
	x.write(reinterpret_cast<const char*>(&urlLen), sizeof(urlLen));
	x.write(url.c_str(), urlLen);
	x.write(reinterpret_cast<const char*>(&dominioLen), sizeof(dominioLen));
	x.write(dominio.c_str(), dominioLen);
	x.write(reinterpret_cast<const char*>(&tituloLen), sizeof(tituloLen));
	x.write(titulo.c_str(), tituloLen);
}

bool Pagina::deserializar(std::ifstream& x)
{
	size_t urlLen, dominioLen, tituloLen;
	if (!x.read(reinterpret_cast<char*>(&urlLen), sizeof(urlLen))) return false;
	url.resize(urlLen);
	x.read(&url[0], urlLen);
	if (!x.read(reinterpret_cast<char*>(&dominioLen), sizeof(dominioLen))) return false;
	dominio.resize(dominioLen);
	x.read(&dominio[0], dominioLen);
	if (!x.read(reinterpret_cast<char*>(&tituloLen), sizeof(tituloLen))) return false;
	titulo.resize(tituloLen);
	x.read(&titulo[0], tituloLen);
	return true;
}



void Pagina::setTiempoVisita() {
	tiempoVisita = std::chrono::system_clock::now();
}



std::chrono::time_point<std::chrono::system_clock> Pagina::getTiempoVisita() {
	return tiempoVisita;
}