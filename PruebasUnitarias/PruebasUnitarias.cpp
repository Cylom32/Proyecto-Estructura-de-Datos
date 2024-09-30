#include "pch.h"
#include "CppUnitTest.h"
#include"../Proyecto Estructura de Datos/NavegadorWeb.cpp"
#include"../Proyecto Estructura de Datos/Pestanias.cpp"
#include"../Proyecto Estructura de Datos/Pagina.cpp"
#include"../Proyecto Estructura de Datos/Marcador.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PruebasUnitarias
{
	TEST_CLASS(PruebasUnitarias)
	{
	public:
		
        TEST_METHOD(ConstructorDestructorTest)
        {
            NavegadorWeb* navegador = new NavegadorWeb("test.csv");

        
            Assert::IsNotNull(navegador->getPestanias()); 
            Assert::IsTrue(navegador->getPestanias()->size() == 1); 
            Assert::IsNotNull(navegador->getMarcadores()); 
            Assert::IsTrue(navegador->getMarcadores()->empty()); 
            Assert::IsNotNull(navegador->getPaginasDisponibles());
            Assert::IsTrue(navegador->getPaginasDisponibles()->empty()); 

           
            Assert::IsFalse(navegador->modoIncognito()); 
            Assert::AreEqual(navegador->getlimite(), 10); 
           

            delete navegador;
        }


        TEST_METHOD(CargarPaginasDisponiblesTest)
        {
  
            std::ofstream testFile("test.csv");
            testFile << "url,dominio,titulo\n"; 
            testFile << "http://example.com,example.com,Example Title\n";
            testFile << "http://test.com,test.com,Test Title\n";
            testFile.close();
            NavegadorWeb* navegador = new NavegadorWeb("test.csv");
            navegador->cargarPaginasDisponibles();
            Assert::IsNotNull(navegador->getPaginasDisponibles());
            Assert::IsTrue(navegador->getPaginasDisponibles()->size() == 2);
            Pagina* pagina1 = navegador->getPaginasDisponibles()->at(0);
            Assert::AreEqual(std::string("http://example.com"), pagina1->getUrl()); 
            Assert::AreEqual(std::string("example.com"), pagina1->getDominio());
            Assert::AreEqual(std::string("Example Title"), pagina1->getTitulo());
            Pagina* pagina2 = navegador->getPaginasDisponibles()->at(1);
            Assert::AreEqual(std::string("http://test.com"), pagina2->getUrl());
            Assert::AreEqual(std::string("test.com"), pagina2->getDominio());
            Assert::AreEqual(std::string("Test Title"), pagina2->getTitulo());
            delete navegador;
            std::remove("test.csv");
        }


        TEST_METHOD(BuscarPaginaTest)
        {
            std::ofstream testFile("test.csv");
            testFile << "url,dominio,titulo\n"; 
            testFile << "http://example.com,example.com,Example Title\n";
            testFile << "http://test.com,test.com,Test Title\n";
            testFile.close();
            NavegadorWeb* navegador = new NavegadorWeb("test.csv");
            navegador->cargarPaginasDisponibles();
            Pagina* paginaEncontrada = navegador->buscarPagina("Example Title");
            Assert::IsNotNull(paginaEncontrada);
            Assert::AreEqual(std::string("http://example.com"), paginaEncontrada->getUrl());
            Pagina* paginaNoEncontrada = navegador->buscarPagina("Nonexistent Title");
            Assert::IsNull(paginaNoEncontrada); 
            delete navegador;
            std::remove("test.csv");
        }



        TEST_METHOD(CrearNuevaPestaniaTest)
        {
            std::ofstream testFile("test.csv");
            testFile << "url,dominio,titulo\n"; 
            testFile.close();
            NavegadorWeb* navegador = new NavegadorWeb("test.csv");
            navegador->cargarPaginasDisponibles();
            navegador->setLimite(3);
            for (int i = 1; i < 3; ++i) {
                navegador->crearNuevaPestania();
                std::cout << "Cantidad de pestañas después de crear: " << navegador->getPestanias()->size() << std::endl;
                Assert::AreEqual(i + 1, static_cast<int>(navegador->getPestanias()->size()), L"La cantidad de pestañas no es correcta.");
            }
            std::ostringstream out;
            std::streambuf* originalCout = std::cout.rdbuf(out.rdbuf()); 
            navegador->crearNuevaPestania();
            std::cout.rdbuf(originalCout); 
            Assert::IsTrue(out.str().find("No se puede crear una pestania.") != std::string::npos, L"No se mostró el mensaje correcto al intentar exceder el límite.");
            delete navegador;
            std::remove("test.csv");
        }



        TEST_METHOD(AgregarMarcadorTest)
        {
            std::ofstream testFile("test.csv");
            testFile << "url,dominio,titulo\n"; 
            testFile.close();
            NavegadorWeb* navegador = new NavegadorWeb("test.csv");
            navegador->cargarPaginasDisponibles(); 
            Pagina* pagina1 = new Pagina("http://ejemplo.com", "ejemplo.com", "Ejemplo");
            Marcador* marcador1 = new Marcador(pagina1->getTitulo());
            Assert::IsTrue(navegador->agregarMarcador(marcador1), L"El marcador debería haberse agregado exitosamente.");
            Assert::IsFalse(navegador->agregarMarcador(marcador1), L"El marcador duplicado no debería haberse agregado.");
            Assert::AreEqual(1, static_cast<int>(navegador->getMarcadores()->size()), L"El tamaño del marcador debería ser 1.");
            delete navegador;
            std::remove("test.csv");
        }


        TEST_METHOD(GestionarMarcadoresTest)
        {
            std::ofstream testFile("test.csv");
            testFile << "url,dominio,titulo\n"; 
            testFile.close();
            NavegadorWeb* navegador = new NavegadorWeb("test.csv");
            navegador->cargarPaginasDisponibles(); 
            Pagina* pagina1 = new Pagina("http://ejemplo.com", "ejemplo.com", "Ejemplo");
            Marcador* marcador1 = new Marcador(pagina1->getTitulo());
            navegador->agregarMarcador(marcador1);
            std::string nombreArchivo = "marcadores_test.bin";
            navegador->guardarMarcadores(nombreArchivo);
            std::ifstream checkFile(nombreArchivo, std::ios::binary);
            Assert::IsTrue(checkFile.is_open(), L"El archivo de marcadores no se creó correctamente.");
            checkFile.close();
            navegador->cargarMarcadores(nombreArchivo); 
            Assert::AreEqual(1, static_cast<int>(navegador->getMarcadores()->size()), L"El número de marcadores no coincide después de cargar.");
            delete navegador;
            std::remove("test.csv");
            std::remove(nombreArchivo.c_str());
        }


        TEST_METHOD(CrearNuevaIncognitaTest)
        {
            std::ofstream testFile("test.csv");
            testFile << "url,dominio,titulo\n";
            testFile.close();
            NavegadorWeb* navegador = new NavegadorWeb("test.csv");
            navegador->cargarPaginasDisponibles(); 
            for (int i = 1; i < 3; ++i) { 
                navegador->crearNuevaIncognita();
                std::cout << "Cantidad de incógnitas después de crear: " << navegador->getIncognitas()->size() << std::endl;
                Assert::AreEqual(i + 1, static_cast<int>(navegador->getIncognitas()->size()), L"La cantidad de incógnitas no es correcta.");
            }

            delete navegador;

            std::remove("test.csv");
        }

    };
	
}
