#include "mainwindow.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "visionModule.h"
#include "mapeoModule.h"
#include <QApplication>

using namespace std;

void dibujarInterfaz(cv::Mat& frame, mapeoModule& mapa, const vector<ObjetoDetectado>& detecciones);

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();

     visionModule vision(
         "model/yolov4-tiny.cfg",
         "model/yolov4-tiny.weights",
         "model/coco.names"
    );

     mapeoModule mapa;


     cv::VideoCapture cap(0);

     if(!cap.isOpened()){
         cerr <<"ERROR: No se pudo abrir la camara."<<endl;
         return -1;
     }

     cv::Mat frame;

     cout<<"Sistema de camara iniciando..."<<endl;


     while(true){
         cap>> frame;

         if(frame.empty()) break;

         mapa.reset();

         vector<ObjetoDetectado> detecciones = vision.detectar(frame);

         for(const auto& obj : detecciones){
             mapa.traducirCordenadas(obj.x, obj.y, frame.cols, frame.rows);

         }

         dibujarInterfaz(frame, mapa, detecciones);

         cv::imshow("CAMARA DE CONTROL - TESTEO", frame);

         if(cv::waitKey(1) == 27) break;
     }

     cap.release();

     cv::destroyAllWindows();

     return 0;
}

void dibujarInterfaz(cv::Mat& frame, mapeoModule& mapa, const vector<ObjetoDetectado>& detecciones){
    int weight= frame.cols;
    int height = frame.rows;

    //dibujado de cuadrado alrededor de objeto detectado
    for(const auto& obj: detecciones){
        if(obj.tipo == "Persona"){
            int box_width =100;
            int box_height =150;

            cv::Point top_left(obj.x - box_width/2, obj.y- box_height/2);
            cv::Point bottom_right(obj.x+box_width/2, obj.y+box_height/2);

            //dibujar rectangulo
            cv::rectangle(frame, top_left, bottom_right, cv::Scalar(0,255,0),2);

            //poner etiqueta encima del rectangulo
            cv::putText(frame, obj.tipo,
                        cv::Point(top_left.x, top_left.y-10),
                        cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(0,255,0),1);
        }
    }


    //Dibujado de grid con objetos detectados
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            cv::Rect rect(j * (weight/3), i*(height/3), weight/3, height/3);
            cv::rectangle(frame, rect, cv::Scalar(200,200,200),1);


            int conteo = mapa.getObjetosCuadrante(i,j);

            if(conteo>0){
                cv::rectangle(frame, rect, cv::Scalar(0,0,255),2);

                string texto = "Personas: "+to_string(conteo);
                cv::putText(frame, texto,
                            cv::Point(j*(weight/3)+10, i*(height/3)+30),
                            cv::FONT_HERSHEY_COMPLEX, 0.7, cv::Scalar(0,0,255),2);
            }
        }
    }
}
