#ifndef GUIMODULE_H
#define GUIMODULE_H

#include <QWidget>

#include <QList>
#include <QPushButton>

class guiModule : public QWidget{
    Q_OBJECT

public:
    explicit guiModule(QWidget *parent =nullptr);

private:
    QList<QPushButton*> listaBotones;

};


#endif // GUIMODULE_H
