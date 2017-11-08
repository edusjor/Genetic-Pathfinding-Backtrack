#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;



//Para compilar:    g++ -Wall -o run  main.cpp `pkg-config --cflags --libs opencv`
//Para correrlo:    ./run

std::string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

//recibe un array con el individuo y el individuo modelo para calcular su fitness
int calcularFitness(int individuo[], int modelo[]){
    int fitness=0;
    int tamano= 16;
    for(int i=0; i<tamano; i++){
        if (individuo[i]==modelo[i]){  
            fitness++;
        }
    }
    return fitness;
}
























//cantidadGenes=>cantidad de trozos de un solo individuo (una imagen imagen),   cantIndividuosIni=> cantidad de individuos en la poblacion inicial sin seleccionar mejores
//genesPoblacion=> matriz con todos los individuos con parametros IDs          imgsPoblacion=> Matriz con todos los individuos con parametros las imagenes
//genesIndividuoModelo=> array con IDs del individuo al cual se debe llegar a ser igual
//int seleccionar_y_reproducir(int cantidadGenes, int cantIndividuosIni, int genesPoblacion[][cantidadGenes] , Mat imgsPoblacion[][cantidadGenes] , int genesIndividuoModelo[],int numGeneracion) {


int seleccionar_y_reproducir(int cantidadGenes, int cantIndividuosIni, int genesPoblacion[][16],Mat imgsPoblacion[][16], int genesIndividuoModelo[], int numGeneracion){


    cout<<"seleccionando y reproduciendo"<<endl;

    int arrfitneses[cantIndividuosIni];

    int contador = 0;
    int mejores = 9; //numero de mayor cantidad de individuos que se seleccionaran, solo los mejores
    int mayorFitness; //el fitness mayor al cual se llego


    int arrfitnessdeMayores[mejores]; //array con los 8 numeros mas altos en fitness
    int arrIndicesDeMayores[mejores]; //array con los 8 indices de los individos con fitness mas alto

    //se guarda en el array el calculo de fitnes de cada individuo de la poblacion, cada index es el fitness de un individuo segun corresponda el index
    for (int i = 0; i < cantIndividuosIni; i++) {
        arrfitneses[i] = calcularFitness(genesPoblacion[i], genesIndividuoModelo);
        //cout<<"fitnes "<<i<<": "<<calcularFitness(genesPoblacion[i], genesIndividuoModelo)<<endl;

    }

    //busca el mayor fitness
    for (int i = 0; i < cantIndividuosIni - 1; i++) {
        if (arrfitneses[i] > arrfitneses[i + 1]) {
            if (arrfitneses[i] > mayorFitness)
                mayorFitness = arrfitneses[i];
        }
    }
    cout<<"mayor fitness: "<<mayorFitness<<endl;
    if (mayorFitness == cantidadGenes) { //verifica si ya se alcanzo el maximo fitness (cantidad de genes de un solo individuo iguales a los del original)
        //terminar aqui
        cout << "Se alcanzo el maximo fitness!. Logrado" << endl;
        return 1;
    }

    if (mayorFitness == 10) { //verifica si ya se alcanzo el maximo fitness que uno decea
        //terminar aqui
        cout << "Se alcanzo el maximo fitness establecido manualmente!. Logrado" << endl;
        return 1;
    }





    //ordena el arrfitneses
    int lon=cantidadGenes;
    int Temp;
    for (int i = 0; i < lon; i++){ 
        for (int j = 0; j < lon - 1; j++){ 
            if (arrfitneses[j] < arrfitneses[j + 1]) {// cambia "<" a ">" para cambiar la manera de ordenar
                Temp = arrfitneses[j];
                arrfitneses[j] = arrfitneses[j + 1];
                arrfitneses[j + 1] = Temp;
            }
        }
    }

    //guarda los mejores, los 9 primeros que son los 9 mayores
    for (int i = 0; i < mejores; i++){ 
        arrfitnessdeMayores[i]=arrfitneses[i];
    }




    //busca los indices en donde estan los mejores y los guarda en un array
    for (int i=0; i<mejores;i++){
        for (int j=0; j<mejores; j++){
            if (arrfitnessdeMayores[i]==arrfitneses[j]){
                arrIndicesDeMayores[i]=j;
            }
        }
    }

    //busca en la matriz de la poblacion los individuos de mas alto fitness segun los indices guardados en el array
    //y guarda esos individuos en una nueva matriz.   los individuos como IDs y como imgs
    //mejores = 9 y cantidadGenes = 16 (en un principio)
    int arrMatrMejores[mejores][cantidadGenes];
    Mat arrIMGMatrMejores[mejores][cantidadGenes];

    for(int i=0;i<mejores;i++){

        for (int j=0; j<cantidadGenes; j++){
            int indice=arrIndicesDeMayores[i];
            arrMatrMejores[i][j]=genesPoblacion[indice][j];
            arrIMGMatrMejores[i][j]=imgsPoblacion[indice][j];

        }
    }



    ////////////////////////////////////////////////
    //reproducir aqui
    srand(time(NULL));

    int arrMejorToReproducir[cantidadGenes];
    Mat arrIMGMejorToReproducir[cantidadGenes];

    Mat matGeneracion[16][16];   //la nueva poblacion/generacion

    for (int indiv=0; indiv<16; indiv++){ 

        //selecciona de la matriz dos individuos aleatorios y los guarda en un nuevo array mezclandolos mita y mitad de manera: un gen
        //del individuo 1 y el siguiente gen del individuo 2 y asi sucesivamente
        for(int i=0; i<cantidadGenes; i++){
            int aleatorio1=rand()%mejores;
            int aleatorio2=rand()%mejores;
            for(int j=0; j<cantidadGenes; j++){
                if(j%2 ==0) {
                    arrMejorToReproducir[j] = arrMatrMejores[aleatorio1][j];
                    arrIMGMejorToReproducir[j] = arrIMGMatrMejores[aleatorio1][j];

                    matGeneracion[indiv][j]=arrIMGMatrMejores[aleatorio1][j];
                }else
                {
                    arrMejorToReproducir[j] = arrMatrMejores[aleatorio2][j];
                    arrIMGMejorToReproducir[j] = arrIMGMatrMejores[aleatorio2][j];

                    matGeneracion[indiv][j]=arrIMGMatrMejores[aleatorio2][j];
                }


            }
        }


    }//end for

    

    //mutar aqui

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ///////// Mostrar generacion ///////////////////////////////////////////////////////////////////////////////////////////////////////
    

    //hagarra cada trozo de cada individuo, los une para crear al individuo completo y guarda ese individuo en un array, para crear un array
    //con toda la nueva generacion 
    Mat imgGeneracion[16];
    //Mat matGeneracion[16][16];   //la nueva poblacion/generacion
    for (int indiv=0; indiv<cantIndividuosIni; indiv++){ 

        //regenera un individuo
        Mat array_filas[4];        //array con todas las filas
        int cant_y=4;
        int cant_x=4;

        //concatena los trozos de cada fila y guarda cada fila en un array
        int cont1 = 0;
        for (int y=0; y<cant_y; y++) {
            Mat Fila=matGeneracion[indiv][cont1];
            cont1++;
            for (int x = 0; x < cant_x-1; x++) {
                if (cont1==16)
                    break;
                hconcat(Fila, matGeneracion[indiv][cont1], Fila);
                cont1+=1;
            }
            array_filas[y]=Fila;
        }

        //toma las filas guardadas en ael array y las acomoda una encima de otra para que quede la nueva imagen con el tamano de la principal original
        Mat Columnas=array_filas[0];
        for (int g=1; g<cant_y; g++){
            vconcat(Columnas, array_filas[g], Columnas);
        }

        imgGeneracion[indiv]=Columnas;
     
    }








    //hagarra todos los individuos/poblacion/nuevaGeneracion y los une en una sola imagen
    //para mostrar la nueva generacion en un mismo .png
        Mat array_filas[4];        //array con todas las filas
        int cant_y=4;
        int cant_x=4;

        //concatena los trozos de cada fila y guarda cada fila en un array
        int cont1 = 0;
        for (int y=0; y<cant_y; y++) {
            Mat Fila=imgGeneracion[cont1];
            cont1++;
            for (int x = 0; x < cant_x-1; x++) {
                if (cont1==16)
                    break;
                hconcat(Fila, imgGeneracion[cont1], Fila);
                cont1+=1;
            }
            array_filas[y]=Fila;
        }

        //toma las filas guardadas en ael array y las acomoda una encima de otra para que quede la nueva imagen con el tamano de la principal original
        Mat Columnas=array_filas[0];
        for (int g=1; g<cant_y; g++){
            vconcat(Columnas, array_filas[g], Columnas);
        }

       

    string numeroDeGeneracion= to_string(numGeneracion+1);

    imwrite( numeroDeGeneracion+" Generacion.png",  Columnas);   //guarda la parte que corto






    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //recursividad

    seleccionar_y_reproducir(cantidadGenes, cantIndividuosIni, genesPoblacion,imgsPoblacion, genesIndividuoModelo, numGeneracion+1);


        cout<<"fin aqui"<<endl;

    return 0;

}//end seleccionar_y_reproducir(parametros 5)







































//crea la poblacion inicial en una matriz. Hagarra el individuo modelo y hace 16 individuos a partir de ese.
//desordenando aleatoriamente el array
void crearPoblacion(int cantidadGenes,int cantIndividuosIni, int genesIndividuo1[],Mat imgsIndiv1[], int genesIndividuoModelo[], Mat imgsIdivMod[]){ //array_de_IDs_imgDesord[]){








    cout<<"creando poblacion"<<endl;
    srand(time(NULL));

    for (int i=0; i<16; i++){
        cout<<genesIndividuo1[i]<<endl;
    }

    //int genesNewPoblacion[cantIndividuosIni][cantidadGenes];   //16 16    matriz en donde se guardara la nueva poblacion en numeros
    //Mat imgsNewPoblacion[cantIndividuosIni][cantidadGenes];    //16 16    matriz en donde se guardara la nueva poblacion en imagenes, mismas posiciones que los numeros

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
    





    string var="";
    string var2="";
    for (int i=0; i<16; i++){

        for (int k=0; k<16; k++){
            //char *intStr = itoa(genesPoblacion[i][k]);
            //string str = string(intStr);

            var+= ","+to_string(genesNewPoblacion[i][k]);

            //var2+= ","+to_string(genesPoblacion[][k]);
            //cout<<var<<endl;
        }
        var+="\n";
        //var2+="\n";
    }
    cout<<var<<endl;
    cout<<"var2"<<endl;


    
    seleccionar_y_reproducir(16,16,genesNewPoblacion,imgsNewPoblacion,genesIndividuoModelo,0);





/*
    int poblacionNueva[2][2]={{1,2},{3,4}};
    int imgsP[2][2];
    int g[2]={1,2};
    seleccionar_y_reproducir(16,16,poblacionNueva,imgsP,g,0);   
    */
}//end crearPoblacion(parametros 6)  



















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
    int tamano = 16;
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

    //declaracion sin iniciar de arrays con los IDs
    int array_de_IDs_imgOriginal[tamano];
    int array_de_IDs_imgDesord[tamano];



    //compara los dos arrays de imagenes para agregar los IDs a las imagenes
    for(int i=0; i<tamano; i++){ //agrega los IDs
        array_de_IDs_imgOriginal[i]=i;

        int indice=buscarIndices(array_De_imgDesord,array_De_imgOriginal[i]);
        if (indice ==-1)   //si el indice da -1 (a veces sucede extranamente) entonces que se vuelva a buscar ese indice  a huevo
            i--;
        cout<<"Indice: "<<indice<<endl;
        array_de_IDs_imgDesord[indice]=i;
    }
    cout<<endl<<endl<<endl<<endl;


    for (int i=0; i<16; i++)
        cout<<array_de_IDs_imgDesord[i]<<",";

    cout<<endl<<endl<<endl;



    

    crearPoblacion(16,16, array_de_IDs_imgDesord, array_De_imgDesord, array_de_IDs_imgOriginal, array_De_imgOriginal); //array_de_IDs_imgDesord[]){
    
}//end programa()


int main() {
    std::cout << "Hello, World!" << std::endl;

    programa();
     
    
    return 0;
}



