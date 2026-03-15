#ifndef VISIONMODULE_H
#define VISIONMODULE_H
using namespace std;


#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <vector>
#include <string>
#include "mapeoModule.h"


class visionModule{
private:
    cv::dnn::Net net;
    vector<string> classes;
    float confianzaMinima=0.5;


public:
    //necesario para cargar archivos
    visionModule(string cfgPath, string weightPath, string namesPath);

    vector<ObjetoDetectado> detectar(cv:: Mat& frame);

};

#endif // VISIONMODULE_H
