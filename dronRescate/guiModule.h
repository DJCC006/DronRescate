#ifndef GUIMODULE_H
#define GUIMODULE_H

#include <QWidget>

#include <QList>
#include <QPushButton>

class guiModule : public QWidget{
    Q_OBJECT

public:
    explicit guiModule(QWidget *parent =nullptr);


public slots:
    void actualizarBotones(int indice, QString nuevoTexto);

    void actualizarPrioridad(QString newPrioridad);


private:
    QList<QPushButton*> listaBotones;

};


#endif // GUIMODULE_H
