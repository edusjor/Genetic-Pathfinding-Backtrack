

#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;


////////////////////////////////////////////////////////////////////////
//se hace la reproduccion y la mutacion
int reproducir(int cantidadGenes,
               int cantidadIndividuos,
               int cantidadMejoresIndividuos,
               int numGeneracion,
               int poblacionMatriz[][16],
               int individuoModeloArray[]);

//recibe un array con un individuo y el individuo modelo para calcular y retornar su fitness
int calcularFitness(int individuo[], int modelo[],int cantidadGenes);

///////////////////////////////////////////////////////////////////////
int main() {
    srand(time(NULL));
    std::cout << "Hello, World!" << std::endl;

    int cantidadGenes=16;
    int cantidadIndividuos=16;
    int cantidadMejoresIndividuos=3;

    int numGeneracion =0;
    int individuoModeloArray[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};

    int poblacionMatriz[16][16]={{10,15,12,14,3,8,9,11,2,5,13,1,6,4,0,7},
                                {13,5,14,12,0,11,3,15,7,10,9,4,2,6,8,1},
                                {9,7,13,8,15,0,14,6,2,11,4,3,12,1,10,5},
                                {14,10,7,11,6,2,4,1,8,0,3,15,9,12,13,5},
                                {1,4,15,6,2,14,7,11,0,8,3,5,10,9,12,13},
                                {10,11,5,7,12,0,4,3,13,8,14,9,15,1,6,2},
                                {9,7,4,6,0,13,15,2,3,11,1,14,12,8,10,5},
                                {8,5,4,2,0,3,7,15,9,12,1,11,13,6,14,10},
                                {7,6,15,10,3,1,11,0,8,12,5,4,13,9,14,2},
                                {14,6,8,7,1,3,5,0,13,2,4,15,10,9,12,11},
                                {5,3,7,6,0,15,4,12,11,10,2,13,8,1,14,9},
                                {13,5,3,14,2,9,1,15,10,7,8,11,4,12,6,0},
                                {12,2,8,6,5,4,1,11,10,13,9,0,3,15,7,14},
                                {12,11,13,6,3,10,4,15,8,2,1,5,14,7,0,9},
                                {11,2,5,7,10,14,9,1,3,12,6,13,15,0,8,4},
                                {6,2,7,5,9,3,1,8,11,4,15,10,12,0,14,13}};


    reproducir(cantidadGenes, cantidadIndividuos, cantidadMejoresIndividuos, numGeneracion, poblacionMatriz,individuoModeloArray);


    return 0;
}


//cantidad de genes que tiene cada individuo, cantidad de intividuos por poblacion, cantidad de los mejores individuos a elegir,
//matriz de la poblacion de individuos, array de individuo modelo, numero de generacion para esta poblacion
int reproducir(int cantidadGenes,
               int cantidadIndividuos,
               int cantidadMejoresIndividuos,
               int numGeneracion,
               int poblacionMatriz[][16],
               int individuoModeloArray[]){

    cout<<"Reproduciendo"<<endl;

    //array con los fitnes de cada individuo de la poblacion en el mismo indice respectivo
    int fitnessArray[16];

    //array con los fitnessArray ordenados de mayor a menor, (solo importa saber cuales numero defitnes son mayores sin importar el indice, aun)
    int fitnessArrayOrdenados[16];

    //array con los n (cantidadMejoresIndividuos) mejores numeros de fitness
    //con estos fitness se buscan en fitness array los indices respectivos a estos mejores fitness, con esos indices se seleccionan los individuos
    int fitnessArrayMejores[cantidadMejoresIndividuos];

    //array con los n indices en donde se encuentran los n mejores fitness de "fitnessArrray"
    int indicesArrayMejoresFitness[cantidadMejoresIndividuos];

    //array con los mejores individuos de la poblacion, que se ubican segun los indices del array "indicesArrayMejoresFitness"
    int individuosMejoresArray[cantidadMejoresIndividuos][cantidadGenes];

    //array con los genes del nuevo hijo, temporal porque cada vez que este se guarde en la matriz generacion se vuelve a reutilizar
    int individuoHijoArrayTemporal[cantidadGenes];

    //matriz con cada nuevo hijo
    int generacionMatriz[16][16];

    //Se guarda aqui el indice con mayor indice
    int indiceConMayorFitness=0;

    //Se guarda el numero mayor que sera el fitness mayor
    int mayorFitness=0;

    //Probabilidad porcentual de cada individuo mutar
    int probabilidadDeMutar=70;


    //teniendo el array con los mejores individuos que pueden ser 3 empieza la fiesta. y se generan 16 hijos que sera la siguiente generacion


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //busca el fitnes de todos los individuos y los guarda en un array "fitnessArray"
    for (int i=0; i<cantidadIndividuos; i++){
        int calculoDeFitness= calcularFitness(poblacionMatriz[i],individuoModeloArray,cantidadGenes);
        fitnessArray[i]= calculoDeFitness;
        if (calculoDeFitness==16){
            indiceConMayorFitness=i;
        }
        //prueba
        //cout<<"fitness: "<< calculoDeFitness<<endl;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //ordena el "fitnessArray" pero guarda el ordenamiento en otro array "fitnessArrayOrdenados"

    for(int i=0; i<cantidadGenes; i++){//crea la copia para ordenar el fitnessArray
        fitnessArrayOrdenados[i]=fitnessArray[i];
    }
    int Temp;
    for (int i = 0; i < cantidadGenes; i++){
        for (int j = 0; j < cantidadGenes - 1; j++){
            if (fitnessArrayOrdenados[j] < fitnessArrayOrdenados[j + 1]) {// cambia "<" a ">" para cambiar la manera de ordenar
                Temp = fitnessArrayOrdenados[j];
                fitnessArrayOrdenados[j] = fitnessArrayOrdenados[j + 1];
                fitnessArrayOrdenados[j + 1] = Temp;
            }
        }
    }

    //define el mayor fitness
    //muestra el individuo con mayor fitness
    mayorFitness=fitnessArrayOrdenados[0];
    cout<<"Fitness mayor: "<<mayorFitness<<endl;
    if(mayorFitness==16){
        cout<<"Se alcanzo el maximo fitness en generacion "<<numGeneracion-1<<endl;
        cout<<"individuo con mayor fitnes: "<<endl;
        for (int k=0; k<16; k++) {
            cout<<","<<poblacionMatriz[indiceConMayorFitness][k];
        }
        return 1;
    }



    //prueba del ordenamiento
    //muestra el array del fitnessArray ordenado de mayor a menor
    cout<<"fitnessArray Ordenado: ";
    for (int i=0; i<cantidadGenes; i++){
        cout<<fitnessArrayOrdenados[i]<<",";
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //guarda los n (cantidadMejoresIndividuos) mejores en un array
    for (int i=0; i<cantidadMejoresIndividuos; i++){
        fitnessArrayMejores[i]=fitnessArrayOrdenados[i];
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //buscar los indices de los fitness de fitnessArrayMejores en fitnessArray y guardarlos en indicesArrayMejoresFitness
    int indiceAnterior=-1; //para que no repita los indices
    for (int i=0; i<cantidadMejoresIndividuos; i++){
        for (int j=0; j<16; j++){
            if (fitnessArrayMejores[i]==fitnessArray[j]){
                if (indiceAnterior<j) {
                    indicesArrayMejoresFitness[i] = j;

                    break;
                }
            }
        }indiceAnterior=-1;
    }

    //prueba
    for (int i=0; i<cantidadMejoresIndividuos; i++){
        cout<<"EL indice de: "<< fitnessArrayMejores[i]<<" es: "<<indicesArrayMejoresFitness[i]<< endl;
    }


    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //copia a la matriz individuosMejoresArray los individuos escogidos con mayor fitness
    for (int i=0; i<cantidadMejoresIndividuos; i++) {
        for (int j=0; j<cantidadGenes; j++) {
            individuosMejoresArray[i][j] = poblacionMatriz[indicesArrayMejoresFitness[i]][j];
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //crear hijo

    for(int i=0; i<16; i++){  //16 veces

        int pivote_1=rand()%cantidadGenes;
        //cout<<"\npiv: "<<pivote_1<<endl;
        int padre_1=rand()%cantidadMejoresIndividuos;
        int padre_2=rand()%cantidadMejoresIndividuos;
        //verificar que el padre 2 no sea igual que el 1***************

        if (padre_2!=padre_1) {
            for (int j = 0; j <= pivote_1; j++) {

                individuoHijoArrayTemporal[j] = individuosMejoresArray[padre_1][j];

            }
            for (int j = pivote_1 + 1; j < cantidadGenes; j++) {
                individuoHijoArrayTemporal[j] = individuosMejoresArray[padre_2][j];

            }

            for (int g = 0; g < 16; g++) {
                //cout<<","<<individuoHijoArrayTemporal[g];
                generacionMatriz[i][g] = individuoHijoArrayTemporal[g];
            }

        }else{
            i--;
        }

    }//end for



    //mutar
    //para cada individuo de la poblacion crea un numero random <100. Si ese numero es <= la probabilidad de mutar entonces muta
    //selecciona un punto al azar
    for(int x=0; x<16; x++){
        int mutar=rand()%100;
        if (mutar<=probabilidadDeMutar) {

            int punto = rand() % 16;
            int nuevoPunto = rand() % 16;

            while (nuevoPunto == generacionMatriz[x][punto]) {
                nuevoPunto = rand() % 16;
            }
            generacionMatriz[x][punto] = nuevoPunto;
        }

    }




    //prueba, muestra cada nueva generacion con su mutacion
    cout<<"Nueva generacion. Generacion: "<<numGeneracion<<endl;
    for(int r=0; r<16; r++){
        cout<<endl;
        for(int s=0; s<16;s++){
            cout<<","<<generacionMatriz[r][s];
        }
    }cout<<endl;







    reproducir(cantidadGenes, cantidadIndividuos, cantidadMejoresIndividuos, numGeneracion+=1, generacionMatriz,individuoModeloArray);

    return 0;

}//end reproducir



//recibe un array con un individuo y el individuo modelo para calcular y retornar su fitness
int calcularFitness(int individuo[], int modelo[],int cantidadGenes){
    int fitness=0;
    for(int i=0; i<cantidadGenes; i++){
        if (individuo[i]==modelo[i]){
            fitness++;
        }
    }
    return fitness;
}//end calcularFitness


