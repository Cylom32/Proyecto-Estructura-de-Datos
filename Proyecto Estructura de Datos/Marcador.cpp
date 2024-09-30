#include "Marcador.h"
Marcador::Marcador() {
	this->tag = "";
	this->pagina = nullptr;
}
Marcador::Marcador(std::string t) {
	this->tag = t;
	this->pagina = nullptr;
}
Marcador::~Marcador() {
}
std::string Marcador::getTag() {
	return this->tag;
}
void Marcador::setTag(std::string t) {
	this->tag = t;
}
Pagina* Marcador::getPagina() {
	return this->pagina;
}
void Marcador::setPagina(Pagina* p) {
	this->pagina = p;
}
std::string Marcador::toString() {
	std::stringstream s;
	s << this->pagina->getUrl() << " - " << this->tag;
	return s.str();
}

void Marcador::serializar(std::ofstream& x)
{
	size_t tagLen = tag.size();
	x.write(reinterpret_cast<const char*>(&tagLen), sizeof(tagLen));
	x.write(tag.c_str(), tagLen);
	if (this->pagina) {
		this->pagina->serializar(x);
	}
}

bool Marcador::deserializar(std::ifstream& x)
{
	size_t tagLen;
	if (!x.read(reinterpret_cast<char*>(&tagLen), sizeof(tagLen))) return false;
	tag.resize(tagLen);
	x.read(&tag[0], tagLen);
	if (!this->pagina) {
		this->pagina = new Pagina();
	}
	this->pagina->deserializar(x);

	return true;
}