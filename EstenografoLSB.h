#ifndef ESTENOGRAFOLSB_H
#define ESTENOGRAFOLSB_H

#include<string>
#include<bitset>
#include<opencv2/core/matx.hpp>
using namespace std;
using namespace cv;
/**
 * Crea funciones a implementarse para ocultar un texto y develar un texto, asi como verificar 
 */
class EstenografoLSB{

	public:
		/**
 		* Método que realiza el proceso de ocultar un texto en una imagen
 		*/
		static void oculta(string, string, string); 
		/**
 		* Método que realiza el proceso de develar el texto que fue oculto en una imagen
 		*/
		static void devela(string, string);
	private:
		/**
 		* Verifica que el archivo de texto se halla ocultado correctamente
 		*/ 
		static bool validaArchivosParaOcultar(string, string);
		/**
 		* Verifica que la ruta de la imagen sea la correcta
 		*/ 
		static bool validaDireccionImagen(string);
		/**
 		* Verifica que la ruta del texto a ocultar sea la correcta para su lectura
 		*/ 
		static bool validaDireccionArchivoTexto(string);
		/**
		 * Enciende/apaga el ultimo bit de la imagen dependiendo de como se encuentre el bit  
		 */
		static uchar modificaUltimoBit(uchar, bitset<8>, bool);
		/**
		 * Coloca un caracter para marcar el final del texto
		 */
		static Mat_<Vec4b> marcarFinDeArchivoEnImagen(int, int, Mat_<Vec4b>);

};

#endif
