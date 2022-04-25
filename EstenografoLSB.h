#ifndef ESTENOGRAFOLSB_H
#define ESTENOGRAFOLSB_H

#include<string>
#include<bitset>
#include<opencv4/opencv2/core/matx.hpp>
using namespace std;
using namespace cv;

class EstenografoLSB{

	public:
		static void oculta(string, string, string); 
		static void devela(string, string);
	private:
		
		static bool validaArchivosParaOcultar(string, string);
		static bool validaDireccionImagen(string);
		static bool validaDireccionArchivoTexto(string);
		static uchar modificaUltimoBit(uchar, bitset<8>, bool);
		static Mat_<Vec4b> marcarFinDeArchivoEnImagen(int, int, Mat_<Vec4b>);

};

#endif
