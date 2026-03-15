#ifndef MAPEOMODULE_H
#define MAPEOMODULE_H
#include <string>
#include <QObject>
using namespace std;


struct ObjetoDetectado{
    int x;
    int y;
    string tipo;
};



class mapeoModule: public QObject{
    Q_OBJECT



private:
    int cuadrante[3][3];
    int totalDetectado;


public:
    mapeoModule();

    void reset();

    void traducirCordenadas(int x, int y, int screenWidth, int screenHeight);

    int getObjetosCuadrante(int fila, int columna);

    int getTotal();

    void printTableroConsole();

};




#endif // MAPEOMODULE_H
