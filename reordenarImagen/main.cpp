#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;



//Para compilar:    g++ -Wall -o run  main.cpp `pkg-config --cflags --libs opencv`
//Para correrlo:    ./run


//recibe un array con el individuo y el individuo modelo para calcular su fitness
int calcularFitness(int individuo[], int modelo[]){
    int fitness=0;
    int tamano= (sizeof(individuo))/4;
    for(int i=0; i<tamano; i++){
        if (individuo[i]==modelo[i])
            fitness++;
    }
    return fitness;
}


//cantidadGenes=>cantidad de trozos de imagen   cantIndividuosIni=> cantidad de individuos en la poblacion inicial sin seleccionar mejores
//genesPoblacion=> matriz con todos los individuos con parametros IDs          imgsPoblacion=> Matriz con todos los individuos con parametros las imagenes
//genesIndividuoModelo=> array con IDs del individuo al cual se debe llegar a ser igual
void seleccionar_y_reproducir(int cantidadGenes, int cantIndividuosIni, int genesPoblacion[][16], Mat imgsPoblacion[][16], int genesIndividuoModelo[]) {
    int arrfitneses[cantIndividuosIni];

    int contador = 0;
    int mejores = 8; //numero de mayor cantidad de individuos que se seleccionaran, solo los mejores
    int mayorFitness; //el fitness mayor al cual se llego


    int arrfitnessdeMayores[8]; //array con los 8 numeros mas altos en fitness
    int arrIndicesDeMayores[8]; //array con los 8 indices de los individos con fitness mas alto

    //se guarda en el array el calculo de fitnes de cada individuo de la poblacion, cada index es el fitness de un individuo segun corresponda el index
    for (int i = 0; i < cantIndividuosIni; i++) {
        arrfitneses[i] = calcularFitness(genesPoblacion[i], genesIndividuoModelo);
    }

    //busca el mayor fitness
    for (int i = 0; i < cantIndividuosIni - 1; i++) {
        if (arrfitneses[i] > arrfitneses[i + 1]) {
            if (arrfitneses[i] > mayorFitness)
                mayorFitness = arrfitneses[i];
        }
    }
    if (mayorFitness == 16) { //verifica si ya se alcanzo el maximo fitness
        //terminar aqui
        cout << "Se alcanzo el maximo fitness!, logrado" << endl;
    }


    //ordena el arrfitneses
    int lon=16;
    int Temp;
    for (int i = 0; i < lon; i++)
        for (int j = 0; j < lon - 1; j++)
            if (arrfitneses[j] < arrfitneses[j + 1]) {// cambia "<" a ">" para cambiar la manera de ordenar
                Temp = arrfitneses[j];
                arrfitneses[j] = arrfitneses[j + 1];
                arrfitneses[j + 1] = Temp;
            }

    //guarda los 8 primeros que son los 8 mayores
    for (int i = 0; i < mejores; i++)
        arrfitnessdeMayores[i]=arrfitneses[i];




    //busca los indices en donde estan los mejores y los guarda en un array
    for (int i=0; i<8;i++){
        for (int j=0; j<8; j++){
            if (arrfitnessdeMayores[i]==arrfitneses[j]){
                arrIndicesDeMayores[i]=j;
            }

        }
    }

    //busca en la mtriz de la poblacion los individuos de mas alto fitness segun los indices guardados en el array
    //y guarda esos individuos en una nueva matriz   los individuos como IDs y como imgs
    int arrMatrMejores[8][16];
    Mat arrIMGMatrMejores[8][16];

    for(int i=0;i<8;i++){

        for (int j=0; j<16; j++){
            int indice=arrIndicesDeMayores[i];
            arrMatrMejores[i][j]=genesPoblacion[indice][j];
            arrIMGMatrMejores[i][j]=imgsPoblacion[indice][j];

        }
    }

    ////////////////////////////////////////////////
    //reproducir aqui


    //mutar aqui



    //recursividad


}











//crea la poblacion inicial en una matriz. Hagarra el individuo modelo y hace 16 individuos a partir de ese.
//desordenando aleatoriamente el array
void crearPoblacion(int cantidadGenes,int cantIndividuosIni, int genesIndividuo1[],Mat imgsIndiv1[], int genesIndividuoModelo[], Mat imgsIdivMod[]){ //array_de_IDs_imgDesord[]){

    int genesPoblacion[cantidadGenes][16];

    Mat imgsPoblacion[cantIndividuosIni][16];

    for (int i=0;i<cantIndividuosIni;i++) {

        int genesIndividuo1_nuevo[cantidadGenes];
        Mat imgIndividuo1_nuevo[cantidadGenes];

        bool usado[cantidadGenes];

        for (int i = 0; i < cantidadGenes; i++)
            usado[i] = false;

        srand(time(NULL));
        int index = 0;

        for (int i = 0; i < cantidadGenes; i++) {
            do {
                index = (rand() % cantidadGenes);
            } while (usado[index]);

            genesIndividuo1_nuevo[i] = genesIndividuo1[index];
            imgIndividuo1_nuevo[i]= imgsIndiv1[index];
            usado[index] = true;
        }
        for (int j=0; j<16;j++) {
            genesPoblacion[i][j] = genesIndividuo1_nuevo[j];
            imgsPoblacion[i][j] = imgIndividuo1_nuevo[j];
        }
    }



    seleccionar_y_reproducir(cantidadGenes,cantIndividuosIni,genesPoblacion,imgsPoblacion,genesIndividuoModelo);

}















/*
//Se hace el proceso del algoritmo genetico
void genetic_Algorithm(Mat array_De_imgOriginal[],int array_de_IDs_imgOriginal[],  Mat array_De_imgDesord[],int array_de_IDs_imgDesord[]){


}//end genetic_Algorithm(parameters 4)


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


}//end programa()


int main() {
    std::cout << "Hello, World!" << std::endl;

    programa();
    return 0;
}



*/