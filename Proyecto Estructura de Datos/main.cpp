 #include"NavegadorWeb.h"
#include"Menu.h"

/*
*************************************************************************
*          Proyecto: Navegador                                          *
*       Desarrollado por:                                               *
*     - Programador 1: Gabriel Chavarria Calero, Cédula: 118770145      *
*     - Programador 2: Rodney Morera Scott, Cédula: 402640339           *
*     - Programador 2: Andrés Gamboa Mena , Cédula: 118800097           *
*************************************************************************
*/

int main() {

    Menu* menu = new Menu();
    menu->getNavegadorWeb()->cargarPaginasDisponibles();
    menu->menuGeneral();

    delete menu;

    return 0;
}