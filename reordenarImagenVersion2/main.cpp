

#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

//Para compilar:    g++ -Wall -o run  main.cpp `pkg-config --cflags --libs opencv`
//Para correrlo:    ./run


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//da inicio al programa. Es llamado por el main
void programa();

//crea la poblacion inicial en una matriz. Hagarra el individuo modelo y hace 16 individuos a partir de ese.
//desordenando aleatoriamente el array
void crearPoblacion(int cantidadGenes,int cantIndividuosIni, int genesIndividuo1[],Mat imgsIndiv1[], int genesIndividuoModelo[], Mat imgsIdivMod[]); //array_de_IDs_imgDesord[])

//se hace la reproduccion y la mutacion
int reproducir(int cantidadGenes,
               int cantidadIndividuos,
               int cantidadMejoresIndividuos,
               int numGeneracion,
               int poblacionMatriz[][16],
               Mat poblacionMatrizIMGS[][16],
               int individuoModeloArray[],
               Mat imgsIdivMod[]);

//compara el color pixel por pixel de 2 imagenes
int compararPixels(Mat imagenTrozo, Mat imgReferencia );

//busca el indice en donde se encuentra la imagen que busca
int buscarIndices(Mat arrayTrozos[], Mat imgReferencia);

//convertir eteros a string
std::string to_string(int i);

//recibe un array con trozos de una imagen y los une para formar una sola imagen
void crearImagen(Mat array_De_Trozos[], string, string);

//verifica orden de un array
int verificarOrden(int array[]);


















////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;
    programa();

    return 0;
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void programa() {
    int tamano = 16;
    Mat imgOriginal = imread("img1.png", 1);            //carga la imagen original
    Mat imgTrozos = imread("sliced.png", 1);            //carga la imagen

    /////////////////////////////////////////////////////////
    //////////////imagen ////////////////////////////
    int img_Width = imgOriginal.size().width;        //1000   ejm
    int img_Height = imgOriginal.size().height;      //1000   ejm

    double area_imagen = img_Width * img_Height;
    double area_trozo = area_imagen / tamano;

    double trozo_Lado = pow(area_trozo, 0.5);     //longitud del lado

    Mat array_De_imgDesord[tamano];                //crea un array para la cantidad de trozos que va a guardar
    Mat array_De_imgOriginal[tamano];              //crea un array para la cantidad de trozos que va a guardar

    int posi_X = 0;                            //posicion en la que se va a cortar los trozos
    int posi_Y = 0;

    int cant_x = img_Width / trozo_Lado;        //cantidad de trozos en el eje x
    int cant_y = img_Height / trozo_Lado;       //cantidad de trozos en el eje y

    int contador = 0;

    //for para hacer el corte de la imagen y guardar cada trozo en un array
    for (int y = 0; y < cant_y; y++) {
        //cout<<"cantidad y: "<<cant_y<<endl;
        for (int x = 0; x < cant_x; x++) {
            //cout<<"cantidad x: "<<cant_x<<endl;
            Rect myROI(posi_X, posi_Y, trozo_Lado, trozo_Lado);        //posix posiy width   height

            posi_X += trozo_Lado;                                     //aumenta en la cantidad cortada la posicion en x

            Mat trozo_imagen_orig = imgOriginal(
                    myROI);                       //corta la imagen segun el tamano y posicion del rectangulo creado
            Mat trozo_imagen_desord = imgTrozos(myROI);

            array_De_imgDesord[contador] = trozo_imagen_desord;               //guarda cada trozo en un array
            array_De_imgOriginal[contador] = trozo_imagen_orig;               //guarda cada trozo en un array
            contador++;
        }
        posi_X = 0;
        posi_Y += trozo_Lado;
    }//end for


    /////////////////////////////////////////////////////////

    //declaracion sin iniciar de arrays con los IDs
    int array_de_IDs_imgOriginal[tamano];
    int array_de_IDs_imgDesord[tamano];



    //compara los dos arrays de imagenes para agregar los IDs a las imagenes
    for (int i = 0; i < tamano; i++) { //agrega los IDs
        array_de_IDs_imgOriginal[i] = i;

        int indice = buscarIndices(array_De_imgDesord, array_De_imgOriginal[i]);
        if (indice == -1)   //si el indice da -1 (a veces sucede extranamente) entonces que se vuelva a buscar ese indice  a huevo
            i--;
        array_de_IDs_imgDesord[indice] = i;
    }




    crearPoblacion(16,16, array_de_IDs_imgDesord, array_De_imgDesord, array_de_IDs_imgOriginal, array_De_imgOriginal); //array_de_IDs_imgDesord[]){

}//end programa()

















////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//crea la poblacion inicial en una matriz. Hagarra el individuo modelo y hace 16 individuos a partir de ese.
//desordenando aleatoriamente el array
void crearPoblacion(int cantidadGenes,int cantIndividuosIni, int genesIndividuo1[],Mat imgsIndiv1[], int genesIndividuoModelo[], Mat imgsIdivMod[]){ //array_de_IDs_imgDesord[]){


    cout<<"creando poblacion"<<endl;
    srand(time(NULL));

    int genesNewPoblacion[16][16];   //16 16    matriz en donde se guardara la nueva poblacion en numeros
    Mat imgsNewPoblacion[16][16];    //16 16    matriz en donde se guardara la nueva poblacion en imagenes, mismas posiciones que los numeros

    for (int i=0; i<16; i++){                //for para creacion de cada nuevo individuo y su agregacion a la matriz poblacion

        for (int j=0; j<100; j++){                          //este for crea dos numeros aleatorios de 0 a 15 tomando en cuenta el 15 durante 100 veces, y cada vez intercambia dos datos segun dos indices dados por los dos numeros aleatorios
            int numAleatorio1= rand() % 16;
            int numAleatorio2= rand() % 16;

            //intercambio de genes
            int num1=genesIndividuo1[numAleatorio1];        //hagarra el dato del indice del num aleat 1 y lo guarda en una var1,
            int num2=genesIndividuo1[numAleatorio2];        //hagarra el dato del indice del num aleat 1 y lo guarda en una var2,

            genesIndividuo1[numAleatorio1]=num2;            //intercambia el dato del indice del numaleat1 por el dato de la var2
            genesIndividuo1[numAleatorio2]=num1;            //intercambia el dato del indice del numaleat2 por el dato de la var1

            //intercambio de imagenes  ** igual que intercambio de genes pero con las imagenes (misma posicion que cambio los genes)
            Mat img1=imgsIndiv1[numAleatorio1];
            Mat img2=imgsIndiv1[numAleatorio2];

            imgsIndiv1[numAleatorio1]=img2;
            imgsIndiv1[numAleatorio2]=img1;



        }
        for (int j=0; j<cantidadGenes; j++)
        {
            genesNewPoblacion[i][j] = genesIndividuo1[j];
            imgsNewPoblacion[i][j] = imgsIndiv1[j];
        }
        cout<<endl;
    }

    int cantidadIndividuos=16;
    int cantidadMejoresIndividuos=3;
    int numGeneracion=0;
    reproducir(cantidadGenes, cantidadIndividuos, cantidadMejoresIndividuos, numGeneracion, genesNewPoblacion,imgsNewPoblacion,genesIndividuoModelo,imgsIdivMod);


}//end crearPoblacion















////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//cantidad de genes que tiene cada individuo, cantidad de intividuos por poblacion, cantidad de los mejores individuos a elegir,
//matriz de la poblacion de individuos, array de individuo modelo, numero de generacion para esta poblacion
int reproducir(int cantidadGenes,
               int cantidadIndividuos,
               int cantidadMejoresIndividuos,
               int numGeneracion,
               int poblacionMatriz[][16],
               Mat poblacionMatrizIMGS[][16],
               int individuoModeloArray[],
                Mat imgsIdivMod[]){


    int anteriorFitness=0;
    while (true) {
        int arraydeFitness[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; //para guardar el fitnes de cada individuo

        //verifica los fitnes de cada individuo y los guarda en un array
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                if (compararPixels(poblacionMatrizIMGS[i][j], imgsIdivMod[j]) != 0) {
                    arraydeFitness[i] += 1;
                }
            }
        }

        while (verificarOrden(arraydeFitness) == 0) { //mientras el array no este ordenado


            for (int j = 0; j < 15; j++) {
                if (arraydeFitness[j] < arraydeFitness[j + 1]) {

                    //ordena el array de numeros
                    int temp = arraydeFitness[j];
                    arraydeFitness[j] = arraydeFitness[j + 1];
                    arraydeFitness[j + 1] = temp;

                    //re acomoda la poblacion
                    Mat tempArrayIndivMenor[16];
                    Mat tempArrayIndivMayor[16];
                    for (int s = 0; s < 16; s++) {
                        tempArrayIndivMenor[s] = poblacionMatrizIMGS[j][s];
                        tempArrayIndivMayor[s] = poblacionMatrizIMGS[j + 1][s];
                    }

                    for (int g = 0; g < 16; g++) {
                        poblacionMatrizIMGS[j][g] = tempArrayIndivMayor[g];
                        poblacionMatrizIMGS[j + 1][g] = tempArrayIndivMenor[g];
                    }
                }
            }
        }

        cout<<"Array de fitness ordenado, generacion: "<<numGeneracion<<endl;
        for (int p = 0; p < 16; p++) {
            cout << arraydeFitness[p] << ",";
        }

        cout<<"  ";

        //verifica cuando el maximo fitness sea 16
        if (arraydeFitness[0]==16){
            cout<<"alcanzo el maximo fitness en generacion: "<<numGeneracion<<endl;
            Mat imagen[16];
            for (int i=0; i<16; i++){
                imagen[i]=poblacionMatrizIMGS[0][i];
            }
            crearImagen(imagen, to_string(numGeneracion), to_string(16));

            return 1;
        }

        //si el fitness actual es mayor que el anterior crea un nuevo .png de una imagen del mejor fitness
        if (arraydeFitness[0]>anteriorFitness){

            cout<<"<Aumento de fitness> ";
            Mat imagen[16];
            for (int i=0; i<16; i++){
                imagen[i]=poblacionMatrizIMGS[0][i];
            }
            crearImagen(imagen, to_string(numGeneracion), "fit_"+to_string(anteriorFitness));
            anteriorFitness++;
        }



        //REPRODUCCION
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        //crear hijo
        Mat individuoHijoIMGArrayTemporal[16];
        Mat generacionMatrizIMGs[16][16];

        cantidadMejoresIndividuos=3;
        for (int i = 0; i < 16; i++) {  //16 veces porque la generacion queda de 16 individuos

            int pivote_1 = rand() % cantidadGenes;//pivote indice

            int padre_1 = rand() % cantidadMejoresIndividuos; //indice de la posicion donde estara el padre1
            int padre_2 = rand() % cantidadMejoresIndividuos;

            //verifica que el padre 2 no sea igual que el 1
            if (padre_2 != padre_1) {
                //copia la primera mitad del array de genes IMGS del padre1 a un array temporal
                for (int j = 0; j <= pivote_1; j++) {
                    individuoHijoIMGArrayTemporal[j] = poblacionMatrizIMGS[padre_1][j];
                }

                //copia la segunda mitad del array de genes IMGS del padre2 a lo que resta del array temporal
                for (int j = pivote_1+1; j < cantidadGenes; j++) {
                    individuoHijoIMGArrayTemporal[j] = poblacionMatrizIMGS[padre_2][j];
                }

                //copia el array temporal que es el nuevo individuo hijo en la matriz generacion
                for (int g = 0; g < 16; g++) {
                    generacionMatrizIMGs[i][g] = individuoHijoIMGArrayTemporal[g];
                }

            } else {
                i--;
            }
        }//end for


        //MUTACION
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        int probabilidadDeMutar=90;
        int cont=0; //bandera para que se detenga, solo hace la mutacion de la poblacion una vez. While no necesario, pereza quitarlo
        while(cont<1) {
            for (int x = 0; x < 16; x++) {
                int mutar = rand() % 100;

                if (mutar <= probabilidadDeMutar) {  //si el numero mutar aleatorio es mayor que el porcentaje de mutar entoces no muta al individuo de indice x

                    int puntoGen = rand() % 16;
                    int puntoPoblacion = rand() % 16;

                    Mat genACopiar = imgsIdivMod[rand() % 16]; //poblacionMatrizIMGS[rand() % 16][rand() % 16];//imgsIdivMod[rand() % 16];

                    while (compararPixels(genACopiar, generacionMatrizIMGs[x][puntoGen]) !=0) { //verifica que el punto seleccionado para cambiar no contenga el mismo valor que el que va a insertar
                        puntoGen = rand() % 16;
                        genACopiar = imgsIdivMod[rand() % 16]; //poblacionMatrizIMGS[rand() % 16][rand() % 16];            //imgsIdivMod[rand() % 16];
                    }//end while

                    generacionMatrizIMGs[x][puntoGen] = genACopiar;
                }//end if
            }//end for
            cont+=1;
        }//end while
        numGeneracion++;

        //la nueva generacion va a ser igual que la posterior poblacion, asi que se igualan las matrices
        for (int i = 0; i < 16; i++) {
            for (int j = 0; j < 16; j++) {
                poblacionMatrizIMGS[i][j] = generacionMatrizIMGs[i][j];
            }
        }
    }//end while true. e inicia nuevamente el proceso

}//end reproducir


























////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//verifica si un array esta ordenado correctamente de mayor a menor
int verificarOrden(int array[]){
    //int cont =0;

    for (int i=0; i<15; i++){

        //cout<<array[i]<<",";
        if(array[i]<array[i+1]){
            return false;
        }
    }
    return true;

}//end verificarOrden


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//recibe un array con trozos de una imagen y los une para formar una sola imagen y la exporta como .png
void crearImagen(Mat array_De_Trozos[], string strNumGeneracion, string strNumImagen){
    int cant_y =4;
    int cant_x=4;

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
    //columnas es la imagen ya unida totalmente

    string nombre=strNumGeneracion+"_"+strNumImagen+".png";
    imwrite( "/home/eduelem/Dropbox/Genetic-Pathfinding-Backtrack/reordenarImagenVersion2/imgs/"+nombre,  Columnas);   //guarda la parte que corto

}//end crearImagen



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


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



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//convierte enteros a string
std::string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}//end to_string

