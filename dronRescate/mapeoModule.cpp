#include "mapeoModule.h"
#include <iostream>
#include <string>
using namespace std;

mapeoModule::mapeoModule(){
    reset();
}

void mapeoModule::reset(){
    totalDetectado=0;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cuadrante[i][j]=0;
        }
    }
}

void mapeoModule::traducirCordenadas(int x, int y, int screenWidth, int screenHeight){
    int fila = y / (screenHeight/3);
    int columna = x /(screenWidth/3);

    if(fila <3 && columna<3 ){
        cuadrante[fila][columna]++;
    }

    totalDetectado++;
}

int mapeoModule::getObjetosCuadrante(int fila, int columna){
    return cuadrante[fila][columna];
}

int mapeoModule::getTotal(){
    return totalDetectado;
}

void mapeoModule::printTableroConsole(){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cout<<" | "<<cuadrante[i][j]<<" | ";
        }
        cout<<endl;
    }
}
