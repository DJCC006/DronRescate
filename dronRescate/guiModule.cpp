#include "guiModule.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>


QLabel *principalCuadrante =nullptr;



guiModule::guiModule(QWidget *parent){
    setWindowTitle("PANEL RECONOCIMIENTO");
    resize(900,600);


    //layout contenedor de todo
    QVBoxLayout *layoutPrincipal = new QVBoxLayout();



    //agregado de titulo
    QLabel *tituloPrincipal = new QLabel("PANEL DE IDENTIFICACION", this);
    tituloPrincipal->setAlignment(Qt::AlignCenter);
    tituloPrincipal->setStyleSheet("font-size: 25px; font-weight: bold;");
    layoutPrincipal->addWidget(tituloPrincipal);



    //agrega espacio
    layoutPrincipal->addSpacing(20);


    //creacion de layout para grid layout, y espaciados a lo largo
    QHBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addStretch();

    int tamanioBtt =210;

    QGridLayout *gridLayout = new QGridLayout();
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            QPushButton *btt = new QPushButton(QString("0"));

            btt->setFixedSize(tamanioBtt, tamanioBtt);




            btt->setStyleSheet(
                "QPushButton {"
                "border: 2px solid #00ff41;"
                "font-family: 'Courier New';"
                "font-size: 18px;"
                "font-weight: bold;"
                "}"
                );

            gridLayout->addWidget(btt, i, j);

            //guardamos el nuevo boton en la lista de botones
            listaBotones.append(btt);


        }
    }

    centerLayout->addLayout(gridLayout);

    //agrega espacio
    centerLayout->addStretch();

    layoutPrincipal->addLayout(centerLayout);
    layoutPrincipal->addStretch();




    //texto con cuadrante con mayor cantidad
    principalCuadrante = new QLabel("CAUDRANTE PRIORIDAD: ", this);
    principalCuadrante->setAlignment(Qt::AlignCenter);
    principalCuadrante->setStyleSheet("font-size: 18px; font-weight: bold;");
    layoutPrincipal->addWidget(principalCuadrante);

    //espacio para juntar todo
    layoutPrincipal->addStretch();

    setLayout(layoutPrincipal);

}


void guiModule::actualizarBotones(int indice, QString nuevoTexto){
    if(indice >=0 && indice <listaBotones.size()){
        //funcion principal para establecer texto
        listaBotones[indice]->setText(nuevoTexto);

        listaBotones[indice]->setStyleSheet(
            "QPushButton {"
            "border: 2px solid #00ff41;"
            "font-family: 'Courier New';"
            "font-size: 18px;"
            "font-weight: bold;"
            "}"
            );
    }
}

void guiModule::actualizarPrioridad(QString newPrioridad){
    principalCuadrante->setText("CUADRANTE PRIORIDAD: "+newPrioridad);
    // principalCuadrante->setAlignment(Qt::AlignCenter);
    principalCuadrante->setStyleSheet("font-size: 18px; font-weight: bold;");
}
