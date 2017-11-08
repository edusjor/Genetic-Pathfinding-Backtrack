#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;



#include <opencv2/photo.hpp>
#include <opencv2/highgui.hpp>


using namespace cv;




//Para compilar:    g++ -Wall -o run  main.cpp `pkg-config --cflags --libs opencv`
//Para correrlo:    ./run

std::string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

/*
std::string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}
*/


int random(int cantidadGenes){
	srand(time(NULL));
	 return (rand() % cantidadGenes);
}
void crearPoblacion(int cantidadGenes,int cantIndividuosIni, int genesIndividuo1[],int modelo[]){ //array_de_IDs_imgDesord[]){
	
	


	//int modelo[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	//int genesIndividuo1[16]={0,15,2,3,14,11,6,7,8,9,10,5,12,13,4,1};
	srand(time(NULL));


	int genesPoblacion[16][16];
	//Mat imgsPoblacion[16][16];

	for (int i=0; i<16; i++){

		for (int j=0; j<100; j++){
			int numAleatorio1= rand() % 16;
			int numAleatorio2= rand() % 16;

			int num1=genesIndividuo1[numAleatorio1];
			int num2=genesIndividuo1[numAleatorio2];

			genesIndividuo1[numAleatorio1]=num2;
			genesIndividuo1[numAleatorio2]=num1;



		}
		for (int j=0; j<16; j++)
		{
			genesPoblacion[i][j] = genesIndividuo1[j];
			//cout<<","+to_string(genesIndividuo1[i]);
		}
		cout<<endl;
	}
	

    string var="";
    string var2="";
    for (int i=0; i<16; i++){

        for (int k=0; k<16; k++){
        	//char *intStr = itoa(genesPoblacion[i][k]);
			//string str = string(intStr);

            var+= ","+to_string(genesPoblacion[i][k]);

            //var2+= ","+to_string(genesPoblacion[][k]);
            //cout<<var<<endl;
        }
        var+="\n";
        //var2+="\n";
    }
    cout<<var<<endl;
    //cout<<var2<<endl;
    
    
	









/*




    cout<<"creando poblacion"<<endl;
    int genesPoblacion[cantidadGenes][16];

    //Mat imgsPoblacion[cantIndividuosIni][16];

    for (int i=0;i<cantIndividuosIni;i++) {

        int genesIndividuo1_nuevo[cantidadGenes];
        //Mat imgIndividuo1_nuevo[cantidadGenes];

        bool usado[cantidadGenes];

        for (int i = 0; i < cantidadGenes; i++)
            usado[i] = false;

        
        int index = 0;

        for (int i = 0; i < cantidadGenes; i++) {
            do {
            	//srand(time(NULL));
                index = random(cantidadGenes);
                
            } while (usado[index]);

            genesIndividuo1_nuevo[i] = genesIndividuo1[index];
            //imgIndividuo1_nuevo[i]= imgsIndiv1[index];
            usado[index] = true;
        }
        for (int j=0; j<16;j++) {
            genesPoblacion[i][j] = genesIndividuo1_nuevo[j];
            //imgsPoblacion[i][j] = imgIndividuo1_nuevo[j];
        }
    }


    string var="";
    string var2="";
    for (int i=0; i<16; i++){

        for (int k=0; k<16; k++){
        	//char *intStr = itoa(genesPoblacion[i][k]);
			//string str = string(intStr);

            var+= ","+to_string(genesPoblacion[0][k]);

            var2+= ","+to_string(genesPoblacion[5][k]);
            //cout<<var<<endl;
        }
        var+="\n";
        var2+="\n";
    }
    cout<<var<<endl;
    cout<<var2<<endl;
    
    */

}//end crearPoblacion(parametros 6)  


int main()	{
	int modelo[16]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int individuo1[16]={0,15,2,3,14,11,6,7,8,9,10,5,12,13,4,1};
	crearPoblacion(16,16,individuo1,modelo);
	/*int array[16]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int estalibre[16];
	int desordenado[16];
	int i,pos;
	time_t t;

	//semilla para el rand
	srand((unsigned) time(&t));

	//inicializacion de los arrays
	for(i=0;i<16;i++)	{
		array[i]=i;
		estalibre[i]=1;//1 -> libre, 0 -> ocupado
	}

	for(i=0;i<16;i++)	{
		pos=rand()%16;
		//este bucle evita que dos elementos sean guardados en la misma posicion
		while (estalibre[pos]==0)
			pos=rand()%16;
		desordenado[pos]=array[i];
		estalibre[pos]=0;
	}

	for (int i=0; i<16; i++){
		cout<<desordenado[i]<<endl;
	}*/

	return 0;
}