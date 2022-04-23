#ifndef ESTENOGRAFOLSB_H
#define ESTENOGRAFOLSB_H

#include<string>
#include<bitset>
#include<opencv4/opencv2/core/matx.hpp>
using namespace std;

class EstenografoLSB{

	public:
		static void oculta(string, string, string); 
		static void devela(string, string);
	private:
		static bool validaArchivosParaOcultar(string, string);
		static uchar modificaUltimoBit(uchar, bitset<8>, bool);

};

#endif
