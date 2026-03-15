#include "guiModule.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>


QLabel *principalCuadrante =nullptr;



guiModule::guiModule(QWidget *parent){
    setWindowTitle("PANEL RECONOCIMEINTO");
    resize(900,600);

    //Layout contenedor de todo
    QVBoxLayout *layoutPrincipal = new QVBoxLayout();

    //agregado de titulo
    QLabel *tituloPrincipal = new QLabel("PANEL DE IDENTIFICACIONA", this);
    tituloPrincipal->setAlignment(Qt::AlignCenter);
    tituloPrincipal->setStyleSheet("font-size: 25px; font-weight: bold;");
    layoutPrincipal->addWidget(tituloPrincipal);


    layoutPrincipal->addSpacing(20);

    QHBoxLayout *centerLayout = new QHBoxLayout();
    centerLayout->addStretch();

    int tamanioBtt=210;

    QGridLayout *gridLayout = new QGridLayout();

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            QPushButton *btt = new QPushButton(QString("0"));

            btt->setFixedSize(tamanioBtt, tamanioBtt);

            btt->setStyleSheet(
                "QPushButton {"
                "border: 2px solid #00ff41;"
                "font=family: 'Courier New';"
                "font-size: 18px;"
                "font-weight: bold;"
                "}"
                );


            gridLayout->addWidget(btt, i, j);

            listaBotones.append(btt);
        }
    }

    centerLayout->addLayout(gridLayout);

    centerLayout->addStretch();

    layoutPrincipal->addLayout(centerLayout);
    layoutPrincipal->addStretch();

    principalCuadrante= new QLabel("CUADRANTE PRIORIDAD: ", this);
    principalCuadrante->setAlignment(Qt::AlignCenter);
    principalCuadrante->setStyleSheet("font-size: 18px; font-weight: bold;");
    layoutPrincipal->addWidget(principalCuadrante);

    layoutPrincipal->addStretch();

    setLayout(layoutPrincipal);

}
