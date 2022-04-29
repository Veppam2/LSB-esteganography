#include <iostream>
#include <string>
#include <experimental/filesystem>

#include <bitset>
#include <opencv2/opencv.hpp>
#include <fstream>

#include "EstenografoLSB.h"

using namespace std;
using namespace cv;

namespace fs = std::experimental::filesystem;

/**
 * Método que realiza el proceso de ocultar un texto en una imagen
 * DirImg -- ruta de la imagen  
 * DirTxt -- ruta del texto  
 * DirSalida -- ruta de salida
 */
void EstenografoLSB::oculta(string dirImg, string dirTxt, string dirSalida){
	
	cout << "ocultando: " << dirTxt << " dentro de: " << dirTxt << endl;

	if( !validaArchivosParaOcultar(dirImg, dirTxt) ){
		return;
	}

	
	Mat_<Vec4b> image = imread(dirImg, IMREAD_UNCHANGED);
	ifstream file(dirTxt);	
	
	int cont = 0;
	char c;
	file.get(c);

	bool todoElArchivoOculto = file.eof();

	bitset<8> charBits (c); 

	int bit_actual = 0;
	
	int i = 0;
	int j = 0;
	for(i = 0;i<image.rows && !todoElArchivoOculto ; i++){
		for(j = 0;j<image.cols && !todoElArchivoOculto; j++){

			Vec4b pixel= image(i,j);
			//Modifica pixel
			
			for(int indice = 0; indice<4; indice++){
				pixel[indice] = modificaUltimoBit(
						pixel[indice],
					       	(charBits>>bit_actual),
						charBits[bit_actual]
					);
				bit_actual++;
			}
			//Actualiza pixel
			image.at<Vec4b>(i,j) = pixel;


			if(bit_actual == 8){
				//Lee otro caracter
				file.get(c);
				charBits = bitset<8>(c);
				todoElArchivoOculto = file.eof();	
				//Nueva cuenta
				bit_actual =0;
			}

			if(todoElArchivoOculto)
				image = marcarFinDeArchivoEnImagen(i, j, image );
		}
	}
	

	file.close();

	try{
		imwrite(dirSalida, image);

		cout << "Archivo: "<< dirTxt <<" oculto en " << dirSalida<<endl;
	}catch(Exception e){
	
		cout << "El archivo: " << dirSalida << " no es un formato aceptable. Tiene que ser formato png" << endl;
	}

	return;
}
/**
 * Método que realiza el proceso de develar el texto que fue oculto en una imagen
 * DirImg -- ruta de la imagen  
 * DirTxt -- ruta del texto
 */
void EstenografoLSB::devela(string dirImg, string dirTxt){
	cout << "devela: " << dirImg << " : " << dirTxt << endl;
	
	if( !validaDireccionImagen(dirImg) )
		return;

	Mat_<Vec4b> image = imread(dirImg, IMREAD_UNCHANGED);
	ofstream file(dirTxt);

	char c;
	bitset<8> charBits (string ("00000000") );
	bool lecturaCompleta = false;
	int bit_count = 0;

	for(int i = 0;i<image.rows && !lecturaCompleta ; i++){
		for(int j = 0;j<image.cols && !lecturaCompleta; j++){
			
			
			Vec4b v = image(i,j);

			for(int index = 0; index < 4; index++){
				bitset<8> bitRGB (v[index] );
				charBits[bit_count] = bitRGB[0];
				bit_count++;
			}

			if(bit_count == 8){
				c = (char) charBits.to_ulong();


				bit_count = 0;

				if(c == '\0'){
					lecturaCompleta = true;
				}else
					file << c;
			}


		}
	}

}
/**
 * Coloca un caracter para marcar el final del texto
 * image -- imagen que se uso para ocultar el texto
 */
Mat_<Vec4b> EstenografoLSB::marcarFinDeArchivoEnImagen(int i, int j, Mat_<Vec4b> image){
	
	/*
	 * Dejar un caracter de final de archivo \0
	 * */

	j++;

	int bit_actual = 0;
	char c = '\0';
	bitset<8> charBits(c);

	bool termina = false;


	for(i = i;i<image.rows && !termina ; i++){
		for(j = j;j<image.cols && !termina; j++){

			Vec4b pixel = image(i,j);
	
			for(int indice = 0; indice<4; indice++){
				pixel[indice] = modificaUltimoBit(
						pixel[indice],
					       	(charBits>>bit_actual),
						charBits[bit_actual]
					);
				bit_actual++;
			}
			//Actualiza pixel
			image.at<Vec4b>(i,j) = pixel;

			if(bit_actual == 8)
				termina = true;
		}
	}

	return image;
	
}
/**
* Enciende/apaga el ultimo bit de la imagen dependiendo de como se encuentre el bit 
* origunal -- caracter original
* bits -- bits que se prenden/apagan
* bitPrendido -- representa si el bit se encuentra prendido o apagado
**/
uchar EstenografoLSB::modificaUltimoBit(uchar original, bitset<8> bits, bool bitPrendido){
	

	bitset<8> mascaraAND (string("00000001") );
	bitset<8> mascaraOR (string("11111110") );

	bitset<8> bitsetOriginal = bitset<8>(original);

	bitset<8> salida;

	if(bitPrendido)
		salida = (bitsetOriginal |= (bits &= mascaraAND) ); 
	else
		salida = (bitsetOriginal &= (bits |= mascaraOR) );

	return (uchar) salida.to_ulong();
}
/**
 * Verifica que la ruta del texto a ocultar sea la correcta para su lectura
 * dirTxt -- ruta de la imagen 
 */
bool EstenografoLSB::validaDireccionArchivoTexto(string dirTxt){
	/*
	 * Verificar que se pueda leer el archivo de texto a partir de la ruta del archivo
	 * */

	ifstream file(dirTxt);
	if( !file.is_open() ){
		cout << "No se pudo obtener el texto del archivo" << endl;
		return false;
	}

	return true;
}
/**
 * Verifica que la ruta de la imagen sea la correcta
 * dirImg -- ruta de la imagen 
 */
bool EstenografoLSB::validaDireccionImagen(string dirImg){
	
	/*
	 * Checar que se pueda obtener el objeto Mat_ a partir de la ruta a la imagen
	 * */
	Mat_<Vec4b> image = imread(dirImg, IMREAD_UNCHANGED);
	if(image.empty() ){
		cout << "No se pudo obtener información de la imagen"<< endl;
		return false;
	}	

	return true;
}
/**
 * Verifica que el archivo de texto se halla ocultado correctamente
 * dirImg -- ruta de la imagen
 * dirTxt -- ruta del texto
 */
bool EstenografoLSB::validaArchivosParaOcultar( string dirImg, string dirTxt){

	if( !validaDireccionImagen(dirImg) )
		return false;

	if( !validaDireccionArchivoTexto(dirTxt) )
		return false;

	/**
	 * La imagen debe de tener al menos 2 bytes por cada caracter del archivo de texto para poder esconder el texto completo dentro del archivo. Dos bytes adicionales para poder poner el signo de fin de archivo '\0':
	 * */
	
	Mat_<Vec4b> image = imread(dirImg, IMREAD_UNCHANGED);
	uintmax_t tamanoDirTxt = fs::file_size(dirTxt);
	uintmax_t tamanoDirImg = (uintmax_t)((image.rows * image.cols)/2);

	if(tamanoDirImg < tamanoDirTxt){
		//cout << tamanoDirImg << " : " << tamanoDirTxt << endl;
		cout << "La imagen es muy pequeña para esconder el texto completo" << endl;
		return false;
	}

	return true;
}


