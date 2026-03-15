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

QString mapeoModule::generarTexto(int id){
    int fila = id/3;
    int columna = id %3;

    int valor = cuadrante[fila][columna];

    // string txtAAA= to_string(valor);

    QString finaltxt = QString("[%1][%2]\nVAL: %3").arg(fila+1).arg(columna+1).arg(valor);

    return finaltxt;
}

void mapeoModule::actualizarGUI(){
    for(int id=0; id<9; ++id){
        QString txtSend = generarTexto(id);

        emit datoCambiado(id, txtSend);
    }
}

string mapeoModule::obtMainCuadrante(){
    int maximo = cuadrante[0][0];
    int maxFila=0;
    int maxColumna=0;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(cuadrante[i][j]>maximo){
                maximo=cuadrante[i][j];
                maxFila=i+1;
                maxColumna=j+1;
            }
        }
    }



    string maxCuadrante = "["+to_string(maxFila)+"]["+to_string(maxColumna)+"]";
    return maxCuadrante;
}


void mapeoModule::actualizarMainCuadrante(){
    //se usa el fromStdString para convertir un string normal a qstring
    QString mainCuadrante = QString::fromStdString(obtMainCuadrante());

    //mandamos senial de label cambiado
    emit labelCambiado(mainCuadrante);
}
