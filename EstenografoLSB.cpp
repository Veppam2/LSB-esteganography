#include <iostream>
#include <string>
#include <experimental/filesystem>

#include <bitset>
#include <opencv4/opencv2/opencv.hpp>
#include <fstream>

#include "EstenografoLSB.h"

using namespace std;
using namespace cv;

namespace fs = std::experimental::filesystem;

void EstenografoLSB::oculta(string dirImg, string dirTxt, string dirSalida){
	
	cout << "ocultando: " << dirTxt << " dentro de: " << dirTxt << endl;

	if( !validaArchivosParaOcultar(dirImg, dirTxt) ){
		return;
	}

	
	Mat_<Vec4b> image = imread(dirImg, IMREAD_UNCHANGED);
	ifstream file(dirTxt);	

	/*
	Vec4b x = image(0,0);
	cout << x << endl;
	cout << bitset<8> ('A')[0] << endl;
	cout << bitset<8> ('A') << endl;
	*/
	
	int cont = 0;
	//while( !file.eof() &&  file.get(c) ){
	char c;
	file.get(c);
	//cout << bitset<8>( string("10001111") );

	/*
	while( file.get(c) ){
		cout << c << " :' " << (char)bitset<8>(c) << cont++  <<endl;
	}
	*/
	/*
	cout << image(0,0) << endl;
	cout << image(0,0)[0] << endl;
	cout << bitset<8>(image(0,0)[0]) << endl;
	*/

	bool todoElArchivoOculto = file.eof();

	bitset<8> charBits (c); 

	int bit_actual = 0;
	
	Vec4b x = image(0,0);
	cout << x << endl;
	for(int i = 0;i<image.rows && !todoElArchivoOculto ; ++i){
		for(int j = 0;j<image.cols && !todoElArchivoOculto; ++j){

			Vec4b pixel= image(i,j);
			//Modifica pixel con los 4 bits de 8

			for(int i = 0; i<4; i++){
				cout <<c <<": " << charBits << endl;
				//cout << "bts >>" << bit_actual << endl;
				pixel[i] = modificaUltimoBit(
						pixel[i],
					       	(charBits>>bit_actual),
						charBits[bit_actual]
					);
				bit_actual++;
			}

			if(bit_actual == 8){
				//Lee otro caracter
				file.get(c);
				charBits = bitset<8>(c);
				todoElArchivoOculto = file.eof();	
				//Nueva cuenta
				bit_actual =0;
			}

			/*
			Vec4b pixelOriginal = image(i,j);
			//cout << y << endl;

			Vec4b& pixelModificado = image2.at<Vec4b>(i,j);
			pixelModificado[0] = pixelOriginal[2]/2;
			pixelModificado[1] = pixelOriginal[0]/2;
			pixelModificado[2] = pixelOriginal[1]/2;
			pixelModificado[3] = pixelOriginal[3];
			*/

		}
	}

	file.close();

	imwrite(dirSalida, image);

	cout << "Archivo: "<< dirTxt <<" oculto en " << dirSalida<<endl;

	return;
}

void EstenografoLSB::devela(string dirImg, string dirTxt){
	cout << "devela: " << dirImg << " : " << dirTxt << endl;
}

uchar EstenografoLSB::modificaUltimoBit(uchar original, bitset<8> bits, bool bitPrendido){
	

	bitset<8> mascaraAND (string("00000001") );
	bitset<8> mascaraOR (string("11111110") );

	bitset<8> bitsetOriginal = bitset<8>(original);
	//cout << "numeroRGB: " << bitsetOriginal  << endl;
	//cout << "trianguloP: " << bits << endl;

	bitset<8> salida;
	if(bitPrendido)
		salida = (bitsetOriginal |= (bits &= mascaraAND) ); 
	else
		salida = (bitsetOriginal &= (bits |= mascaraOR) );

	//cout << "salida: " << salida << endl;
	//cout << endl;

	return (uchar) salida.to_ulong();
}

bool EstenografoLSB::validaArchivosParaOcultar( string dirImg, string dirTxt){

	/*
	 * Checar que se pueda obtener el objeto Mat_ a partir de la ruta a la imagen
	 * */
	Mat_<Vec4b> image = imread(dirImg, IMREAD_UNCHANGED);
	if(image.empty() ){
		cout << "No se pudo obtener información de la imagen"<< endl;
		return false;
	}	

	/*
	 * Verificar que se pueda leer el archivo de texto a partir de la ruta del archivo
	 * */
	ifstream file(dirTxt);
	if( !file.is_open() ){
		cout << "No se pudo obtener el texto del archivo" << endl;
		return false;
	}

	/**
	 * La imagen debe de tener al menos 2 bytes por cada caracter del archivo de texto para poder esconder el texto completo dentro del archivo. Dos bytes adicionales para poder poner el signo de fin de archivo '\0':
	 * */
	uintmax_t tamanoDirTxt = fs::file_size(dirTxt);
	uintmax_t tamanoDirImg = (uintmax_t)((image.rows * image.cols)/2);

	if(tamanoDirImg < tamanoDirTxt){
		//cout << tamanoDirImg << " : " << tamanoDirTxt << endl;
		cout << "La imagen es muy pequeña para esconder el texto completo" << endl;
		return false;
	}

	return true;
}


