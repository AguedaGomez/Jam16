#include "LeerArchivo.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <utility>
#include "cocos2d.h"


using namespace std;

LeerArchivo::LeerArchivo()
{
	return;
}

/*
LeerArchivo::~LeerArchivo()
{
}*/


//RECIBE RUTA DONDE COLOCAR
/*
std::vector< std::vector< std::string>> LeerArchivo::extraer(std::string ruta) {

	ifstream entrada;
	entrada.open(ruta);
	int i = 0;
	vector<vector<string>> vec(50);
	string aux, aux2="";
	const char* salto = "\n";
	const char* tab = "\t";

	if (entrada)
		while (!entrada.eof()) {
			getline(entrada, aux); 
			//Separación de la linea en 4 campos
			for (int j=0; j<aux.size();j++) {//4 es el num de campos
				aux2 = "";
				
				while (!strcmp((const char *)aux.at(j),salto) && !strcmp((const char *)aux.at(j), tab)) {
					aux2+=aux.at(j);
					j++;
				}
				vec[i].push_back(aux2);
			}
			i++;
		}
	entrada.close();
	return vec;
}
*/
vector<string> LeerArchivo::Extraer(string ruta)
{
	ifstream entrada;
	entrada.open(ruta);
	int i = 0;
	vector<string> vec(50);
	string aux, aux2 = "";

	if (entrada)
		while (!entrada.eof()) {
			getline(entrada, vec[i]);
			/*//Separación de la linea en 4 campos
			for (int j = 0; j<aux.size(); j++) {//4 es el num de campos
				aux2 = "";

				while (!strcmp((const char *)aux.at(j), salto) && !strcmp((const char *)aux.at(j), tab)) {
					aux2 += aux.at(j);
					j++;
				}
				vec[i].push_back(aux2);
			}*/
			i++;
		}
	entrada.close();
	return vec;
}


string LeerArchivo::leeCampo(std::string cad, int pos) {
	std::string aux = "";
	std::string final = "";
	int contador = 0;
	int iterador = 0;

	while (iterador < cad.size()) {
		if (cad[iterador] != '#') {
			aux += cad[iterador];
		}
		else {
			contador++;
			if (contador - 1 == pos) {
				final=aux;
			}
			aux = "";
		}
		iterador++;
	}
	return final;
}
