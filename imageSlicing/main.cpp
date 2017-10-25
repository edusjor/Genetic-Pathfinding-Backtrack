#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Para compilar:    g++ -Wall -o run  main.cpp `pkg-config --cflags --libs opencv`
//Para correrlo:    ./run





int main (){
    Mat imagen=imread("img1.png",1);            //carga la imagen

    int cantidad=25;                            //cantidad de partes en cortar siempre debe ser un numero con raiz

    int img_Width = imagen.size().width;        //1000   ejm
    int img_Height = imagen.size().height;      //1000   ejm


    double area_imagen=img_Width*img_Height;
    double area_trozo=area_imagen/cantidad;    //calcula el area que deberia medir cada trozo

    double trozo_Lado=pow(area_trozo,0.5);      //saca la raiz cuadrada para calcular el lado de cada trozo

    Mat array_De_Trozos[cantidad];              //crea un array para la cantidad de trozos que va a guardar




    int posi_X=0;                               //posicion x en la que se va a cortar los trozos
    int posi_Y=0;                               //posicion y en la que se va a cortar los trozos

    int cant_x=img_Width/trozo_Lado;            //cantidad de filas que debe tener la nueva imangen
    int cant_y=img_Height/trozo_Lado;           //cantidad de columnas

    int contador=0;
    for (int y=0; y<cant_y; y++) {
        for (int x = 0; x < cant_x; x++) {
            Rect myROI(posi_X, posi_Y, trozo_Lado, trozo_Lado);        //posix posiy width   height          crea el rectangulo/cuadrado con las medidas y la posicion para copiar de la u

            posi_X += trozo_Lado;                                     //aumenta en la cantidad cortada la posicion en x

            Mat trozo_imagen = imagen(myROI);                       //corta la imagen segun el tamano y posicion del rectangulo creado
            array_De_Trozos[contador] = trozo_imagen;               //guarda cada nuevo trozo en un array con todos los trozos
            contador++;
        }
        posi_X=0;
        posi_Y+=trozo_Lado;
    }






    //desordena el array
    Mat desordenado[cantidad];
    bool usado[cantidad];


    for(int i=0; i<cantidad;i++){
        usado[i]= false;
    }
    int index=0;
    for (int i=0; i<cantidad;i++){
        srand (time(NULL));
        do{

            index =(rand() % cantidad);
        }while (usado[index]);
        desordenado[i]=array_De_Trozos[index];
        usado[index]=true;
    }
    for (int i =0;i<cantidad;i++){
        array_De_Trozos[i]=desordenado[i];
    }









    Mat array_filas[cant_y];        //array con todas las filas


    //concatena los trozos de cada fila y guarda cada fila en un array
    int cont1 = 0;
    for (int y=0; y<cant_y; y++) {
        Mat Fila=array_De_Trozos[cont1];
        cont1++;
        for (int x = 0; x < cant_x-1; x++) {
            if (cont1==25)
                break;
            hconcat(Fila, array_De_Trozos[cont1], Fila);
            cont1+=1;
        }
        array_filas[y]=Fila;
    }

    //toma las filas guardadas en ael array y las acomoda una encima de otra para que quede la nueva imagen con el tamano de la principal original
    Mat Columnas=array_filas[0];
    for (int g=1; g<cant_y; g++){
        vconcat(Columnas, array_filas[g], Columnas);
    }


    imwrite( "sliced.png",  Columnas);   //guarda la parte que corto


    waitKey();
    return 1;

}
























