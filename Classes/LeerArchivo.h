#ifndef __LEERARCHIVO_H__
#define __LEERARCHIVO_H__

#include <vector>
#include <string>
using namespace std;

class LeerArchivo
{
public:

	LeerArchivo();

	/*~LeerArchivo();*/
	 //std::vector< std::vector< std::string>> extraer(std::string ruta);

	std::vector<string> Extraer(string ruta);

	string leeCampo(string, int);
};
#endif
