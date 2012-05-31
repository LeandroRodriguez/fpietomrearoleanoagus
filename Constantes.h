#ifndef CONSTANTES_H_
#define CONSTANTES_H_
#include <stdint.h>

typedef uint32_t uint32;
typedef unsigned long int offset;
typedef unsigned long int cantBytes;
typedef unsigned long int tamanioBloque;
#define LONGITUD_CANT_BYTES (2*sizeof(cantBytes)) //8 Bytes
#define LONGITUD_BLOQUE_LISTA 450 //para probar los hago chicos //32768 //32kB
//#define LONGITUD_BLOQUE_NODO 32768
#define LONGITUD_BLOQUE_NODO 200
#define LONGITUD_BLOQUE_DATA 20000 //lo cambie, antes era MAIL en vez de DATA, si lo ven en algun lado cambienlo por este.
//para probar los hago chicos //32768 //32kB

#define TAMANIO_STRING_MAXIMO 100
#define VACIO 9999;

#define INDICES_EXTENSION ".idx"

#define DIR_ARCHIVO_DATOS "./Archivos/"
#define DIR_ARCHIVO_INDICES "./Indices/"

#define ARCHIVO_INDICE_PRIMARIO "PRIMARIO"
#define ARCHIVO_DATOS "ArchivoDatos.fde"
#define ARCHIVO_DATOS_LIBRES "ArchivoDatosLibres.fde"
#define ARCHIVO_ARBOL "ArchivoArbol.idx"
#define ESPACIO_TIPOS 7


#define ID_RAIZ  1

enum Resultado {
	RES_OK = 0, RES_DUPLICADO, RES_INEXISTENTE, RES_DESBORDADO
};


#endif /* CONSTANTES_H_ */
