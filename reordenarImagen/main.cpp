#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

//Se hace el proceso del algoritmo genetico
void genetic_Algorithm(Mat array_De_imgOriginal[],int array_de_IDs_imgOriginal[],  Mat array_De_imgDesord[],int array_de_IDs_imgDesord[]){


}


//compara el color pixel por pixel de 2 imagenes
int compararPixels(Mat imagenTrozo, Mat imgReferencia ){
    for (int y = 0; y < imgReferencia.rows; y++) {
        for (int x = 0; x < imgReferencia.cols; x++) {

            // get pixel of img referencia
            Vec3b colorRef = imgReferencia.at<Vec3b>(Point(x, y));
            // get pixel of img trozo
            Vec3b colorTrozo = imagenTrozo.at<Vec3b>(Point(x, y));
            //verif if los pixeles son iguales si no entonces hace break y sigue con la siguiente imagen del array
            if (colorTrozo!=colorRef)
                return false;
        }
    }
    return true;
}//end compararPixels

//busca el indice en donde se encuentra la imagen que busca
int buscarIndices(Mat arrayTrozos[], Mat imgReferencia){
    int cant_trozos;//hacer el lenght
    for (int i=0; i<cant_trozos; i++) {
        Mat imagenTrozo = arrayTrozos[i];

        if (compararPixels(imagenTrozo,imgReferencia)==true){
            return i; //retorna el indice
        }
    }
    return -1;
}//end buscarIndices


void programa(){
    int tamano = 25;
    Mat imgOriginal=imread("img1.png",1);            //carga la imagen
    Mat imgTrozos=imread("sliced.png",1);            //carga la imagen


    /////////////////////////////////////////////////////////
    //////////////imagen ////////////////////////////
    int img_Width = imgOriginal.size().width;        //1000   ejm
    int img_Height = imgOriginal.size().height;      //1000   ejm

    double area_imagen=img_Width*img_Height;
    double area_trozo=area_imagen/tamano;

    double trozo_Lado=pow(area_trozo,0.5);     //longitud del lado

    Mat array_De_imgDesord[tamano];              //crea un array para la cantidad de trozos que va a guardar
    Mat array_De_imgOriginal[tamano];              //crea un array para la cantidad de trozos que va a guardar

    int posi_X=0;                            //posicion en la que se va a cortar los trozos
    int posi_Y=0;

    int cant_x=img_Width/trozo_Lado;        //cantidad de trozos en el eje x
    int cant_y=img_Height/trozo_Lado;       //cantidad de trozos en el eje y

    int contador=0;

    //for para hacer el corte de la imagen y guardar cada trozo en un array
    for (int y=0; y<cant_y; y++) {
        //cout<<"cantidad y: "<<cant_y<<endl;
        for (int x = 0; x < cant_x; x++) {
            //cout<<"cantidad x: "<<cant_x<<endl;
            Rect myROI(posi_X, posi_Y, trozo_Lado, trozo_Lado);        //posix posiy width   height

            posi_X += trozo_Lado;                                     //aumenta en la cantidad cortada la posicion en x

            Mat trozo_imagen_orig = imgOriginal(myROI);                       //corta la imagen segun el tamano y posicion del rectangulo creado
            Mat trozo_imagen_desord= imgTrozos(myROI);

            array_De_imgDesord[contador] = trozo_imagen_orig;               //guarda cada trozo en un array
            array_De_imgOriginal[contador] = trozo_imagen_desord;               //guarda cada trozo en un array
            contador++;
        }
        posi_X=0;
        posi_Y+=trozo_Lado;
    }//end for
    /////////////////////////////////////////////////////////


    //arrays con los IDs
    int array_de_IDs_imgOriginal[tamano];
    int array_de_IDs_imgDesord[tamano];


    for(int i=0; i<tamano; i++){ //agrega los IDs
        array_de_IDs_imgOriginal[i]=i;

        int indice=buscarIndices(array_De_imgDesord,array_De_imgOriginal[i]);
        array_de_IDs_imgDesord[indice]=i;
        cout<<"indice: "<<indice<<endl;
        if(indice ==-1) {
            namedWindow("Display window", WINDOW_AUTOSIZE);// Create a window for display.
            //imshow("Display window", array_De_imgOriginal[i]);                   // Show our image inside it.
            imshow("Display window", array_De_imgDesord[i]);
            waitKey(0);
        }

    }

    //el array IDs imgDesord debe quedar igual a la otra

    genetic_Algorithm(array_De_imgOriginal,array_de_IDs_imgOriginal,  array_De_imgDesord,array_de_IDs_imgDesord);


}


int main() {
    std::cout << "Hello, World!" << std::endl;
    programa();
    return 0;
}





/*
//parte una imagen en trozos y los guarda en una array, y lo retorna en forma de referencia
Mat partirImagen(Mat imagen, int tamano, int i ,int j){
    int img_Width = imagen.size().width;        //1000   ejm
    int img_Height = imagen.size().height;      //1000   ejm

    double area_imagen=img_Width*img_Height;
    double area_trozo=area_imagen/tamano;

    double trozo_Lado=pow(area_trozo,0.5);     //longitud del lado

    Mat array_De_Trozos[tamano];              //crea un array para la cantidad de trozos que va a guardar


    int posi_X=0;                            //posicion en la que se va a cortar los trozos
    int posi_Y=0;

    int cant_x=img_Width/trozo_Lado;        //cantidad de trozos en el eje x
    int cant_y=img_Height/trozo_Lado;       //cantidad de trozos en el eje y

    int contador=0;

    //for para hacer el corte de la imagen y guardar cada trozo en un array
    for (int y=0; y<cant_y; y++) {
        for (int x = 0; x < cant_x; x++) {
            Rect myROI(posi_X, posi_Y, trozo_Lado, trozo_Lado);        //posix posiy width   height

            posi_X += trozo_Lado;                                     //aumenta en la cantidad cortada la posicion en x

            Mat trozo_imagen = imagen(myROI);                       //corta la imagen segun el tamano y posicion del rectangulo creado
            array_De_Trozos[contador] = trozo_imagen;               //guarda cada trozo en un array
            contador++;
        }
        posi_X=0;
        posi_Y+=trozo_Lado;
    }//end for


}//end partirImagen
*/
