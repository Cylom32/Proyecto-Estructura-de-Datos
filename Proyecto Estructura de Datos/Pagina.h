#pragma once
#include <iostream>
#include <fstream>
#include<chrono>
#include<iostream>
#include<sstream>


class Pagina
{
private:
	std::string url;
	std::string dominio;
	std::string titulo;
	std::chrono::time_point<std::chrono::system_clock>tiempoVisita;

public:

	Pagina(std::string = "", std::string = "", std::string = "");
	~Pagina();

	std::string getUrl();
	std::string getDominio();
	std::string getTitulo();

	void setUrl(std::string);
	void setDominio(std::string);
	void setTitulo(std::string);

	void serializar(std::ofstream&);
	bool deserializar(std::ifstream&);

	std::chrono::time_point<std::chrono::system_clock> getTiempoVisita();
	void setTiempoVisita();



};


