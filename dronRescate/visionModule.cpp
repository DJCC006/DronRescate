#include "visionModule.h"
#include <fstream>
#include <iostream>
using namespace std;


visionModule::visionModule(string cfgPath, string weightPath, string namesPath){

    cout<<"Cargando modelo YOLO...."<<endl;

    net = cv::dnn::readNetFromDarknet(cfgPath, weightPath);

    if(net.empty()){
        cout<<"ERROR FATAL. No se pudieron cargar los archivos YOLO"<<endl;
        cout<<"CFG: "<<cfgPath<<endl;
        cout<<"WEIGHTS: "<<weightPath<<endl;
        exit(-1);
    }

    cout<<"archivos cargados exitosamente"<<endl;

    net.setPreferableBackend(cv::dnn::DNN_BACKEND_OPENCV);
    net.setPreferableTarget(cv::dnn::DNN_TARGET_CPU);

    ifstream ifs(namesPath);

    if(!ifs.is_open()){
        cout<<"ERROR: No se pudo abrir"<<namesPath<<endl;
        exit(-1);
    }

    string line;

    while(getline(ifs, line)){
        classes.push_back(line);
    }

    cout<<"Classes cargadas: "<<classes.size()<<endl;

}


vector<ObjetoDetectado> visionModule::detectar(cv::Mat &frame){
    vector<ObjetoDetectado> resultados;

    cv::Mat blob;

    cv::dnn::blobFromImage(
        frame,
        blob,
        1.0/255.0,
        cv::Size(416,416),
        cv::Scalar(0,0,0),
        true,
        false
        );

    net.setInput(blob);

    vector<cv::String> names = net.getUnconnectedOutLayersNames();
    vector<cv::Mat> outs;

    net.forward(outs,names);

    cout<<"Capas de salida YOLO: "<<outs.size()<<endl;
    for(const auto& output: outs){
        for(int i=0; i<output.rows; i++){
            float *data = (float*)output.ptr(i);
            float objectness = data[4];

            if(objectness<0.01)
                continue;

            int numClasses = output.cols -5;

            int bestClass = -1;
            float bestScore =0;

            for(int c =0; c < numClasses; c++){
                float score = data[5+c];

                if(score>bestScore){
                    bestScore =score;
                    bestClass=c;
                }
            }


            float confidence = objectness * bestScore;

            if(isnan(confidence) || isinf(confidence))
                continue;

            cout<<"Confianza detectada: "<<confidence<<endl;

            if(confidence >0.25){
                int centerX = (int)(data[0] * frame.cols);
                int centerY = (int)(data[1] * frame.rows);

                int width = (int)(data[2] *frame.cols);
                int height = (int)(data[3] * frame.rows);

                if(bestClass >= classes.size())
                    continue;

                string clase = classes[bestClass];

                cout<<"Clase detectada: "<<clase<<endl;

                if(clase== "person"){
                    resultados.push_back({centerX,centerY, "Persona"});
                }
            }
        }
    }

    return resultados;
}
