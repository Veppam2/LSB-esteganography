#include <iostream>
#include <bitset>
#include <string>
#include <vector>
#include <experimental/filesystem>
#include <opencv2/opencv.hpp>
#include "EstenografoLSB.h"
//#include <opencv4/opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

namespace fs = std::experimental::filesystem;

void imprimirUso(){
	cout << "Uso: [exe] -h [dir ImagenEntrada] [dir ArchivoAOcultar] [dir Imagen Salida]" << endl
	     << "ó" << endl
	     << "Uso: [exe] -u [dir ImagenEntrada] [dir ArchivoSalida]" << endl;
	return;
}


int main(int argc, char **argv){

	/**
	 * Verificar que se hayan pasado valores por parámetros correctamente:
	 * -> Al menos 3 y posiblemente un cuarto que son:
	 *  1) -h o -u para saber qué acción realizar. Se almacenará en la variable "bandera".
	 *  2) Dir de la imagen en formato png. Se almacenará en "dirImagen".
	 *  3) Dir del archivo de techo donde se obtiene o manda el mensaje. Se almacenará en "dirEntrada".
	 *  4) En caso de que se pase -h como bandera, debe especificarse una ruta para la imagen de salida. Se almacenará en "dirSalida".
	 * */

	if(argc <4){
		imprimirUso();
		return 0;
	}

	string bandera = *(argv+1);
	string dirImagen = *(argv+2);
	string dirTexto = *(argv+3);
	string dirSalida;

	/**
	 * Verificar que la bandera haya sido -h o -u.
	 * En caso de que no sea ninguna, termina el proceso
	 * En caso de que sea -h o -u se asigna la acción a realizar en la variable "ocultaTexto" donde va a ser verdadera sólo si se pasa -h (ocultar) 
	 * */
	if( !(bandera.compare("-h")==0) &&  !(bandera.compare("-u")==0) ){
		imprimirUso();
		return 0;
	}
	
	bool ocultaTexto = (bandera.compare("-h") == 0);

	if(ocultaTexto){
		if(argc >= 5)
			dirSalida = *(argv+4);
		else{
			imprimirUso();
			return 1;
		}
	}

	
	/**
	 * Verificar directorios de imagen y archivo de texto:
	 * -> Siempre debe de existir la imagen en la ruta dada en "dirImagen"
	 * -> El archivo con el texto debe de existir si se pide ocultar el texto ie si "ocultaTexto" es true. En otro caso se puede crear o sobreescribir el contendio del archivo. Suponemos que el usuario sabe lo que hace.
	 * * */
	
	if(!fs::exists(dirImagen)){
		cout << "Error en la lectura de: "<<dirImagen << endl;
		return 1;
	}

	if( ocultaTexto &&  !fs::exists(dirTexto) ){
		cerr << "Error en la lectura de: " << dirTexto<< endl;
		return 1;
	}
	/**
	 * Finalmente ocultamos o develamos
	 * */

	if(ocultaTexto)
		EstenografoLSB::oculta(dirImagen, dirTexto, dirSalida);
	else
		EstenografoLSB::devela(dirImagen, dirTexto);


	return 0;
}
