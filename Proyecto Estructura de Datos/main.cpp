 #include"NavegadorWeb.h"
#include"Menu.h"

/*
*************************************************************************
*          Proyecto: Navegador                                          *
*       Desarrollado por:                                               *
*     - Programador 1: Gabriel Chavarria Calero, C�dula: 118770145      *
*     - Programador 2: Rodney Morera Scott, C�dula: 402640339           *
*     - Programador 2: Andr�s Gamboa Mena , C�dula: 118800097           *
*************************************************************************
*/

int main() {

    Menu* menu = new Menu();
    menu->getNavegadorWeb()->cargarPaginasDisponibles();
    menu->menuGeneral();

    delete menu;

    return 0;
}