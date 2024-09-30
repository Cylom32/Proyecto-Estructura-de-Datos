#pragma once

#include "Pagina.h"
#include <iostream>
#include <fstream>
#include <sstream>


class Marcador
{
private:
	std::string tag;
	Pagina* pagina;
public:
	Marcador();
	Marcador(std::string);
	~Marcador();
	std::string getTag();
	void setTag(std::string);
	Pagina* getPagina();
	void setPagina(Pagina*);
	std::string toString();
	void serializar(std::ofstream& x);
	bool deserializar(std::ifstream&);
};