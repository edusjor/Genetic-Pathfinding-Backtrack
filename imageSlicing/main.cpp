#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;


int main (){
    Mat imagen=imread("img1.png",1);            //carga la imagen

    int cantidad=25;                            //cantidad de partes en cortar siempre debe ser un numero con raiz

    int img_Width = imagen.size().width;        //1000   ejm
    int img_Height = imagen.size().height;      //1000   ejm


    double area_imagen=img_Width*img_Height;
    double area_trozo=area_imagen/cantidad;

    double trozo_Lado=pow(area_trozo,0.5);

    Mat array_De_Trozos[cantidad];              //crea un array para la cantidad de trozos que va a guardar


    int posi_X=0;                            //posicion en la que se va a cortar los trozos
    int posi_Y=0;

    int cant_x=img_Width/trozo_Lado;
    int cant_y=img_Height/trozo_Lado;

    int contador=0;
    for (int y=0; y<cant_y; y++) {
        for (int x = 0; x < cant_x; x++) {
            Rect myROI(posi_X, posi_Y, trozo_Lado, trozo_Lado);        //posix posiy width   height

            posi_X += trozo_Lado;                                     //aumenta en la cantidad cortada la posicion en x

            Mat trozo_imagen = imagen(myROI);                       //corta la imagen segun el tamano y posicion del rectangulo creado
            array_De_Trozos[contador] = trozo_imagen;
            contador++;
        }
        posi_X=0;
        posi_Y+=trozo_Lado;
    }


    Mat array_filas[cant_y];

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

    Mat Columnas=array_filas[0];
    for (int g=1; g<cant_y; g++){
        vconcat(Columnas, array_filas[g], Columnas);
    }


    imwrite( "sliced.png",  Columnas);   //guarda la parte que corto


    waitKey();
    return 1;

}
























