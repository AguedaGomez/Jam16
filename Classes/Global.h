#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "cocos2d.h"
#include "Paso.h"
#include "LeerArchivo.h"


//Singleton

class Global 
{
public:
	static Global* getInstance();

	int feligresesAñadidos;
	int dineroAñadidos;

	cocos2d::Scene* paso;
	cocos2d::Scene* biblia;
	cocos2d::Scene* iglesia;

	int posicionBaterias=0;

	LeerArchivo lector;

	 std::vector<std::string> BateriaAgresivas;
	 std::vector<std::string> BateriaOptimista;
	 std::vector<std::string> BateriaPesimista;

	 std::string FrasePaso;

	 int agresivaDeTurno;
	 int pesimistaDeTurno;
	 int optimistaDeTurno;

	 float multiplicadorFeligreses;
	 float multiplicadorDinero;
	 int bateriaEscogida;


	cocos2d::Scene* getInstancePaso();
	cocos2d::Scene* getInstanceBiblia();
	cocos2d::Scene* getInstanceIglesia();

	int GetDinero();
	void SetDinero(int d);
	void setNivel(int nivel);

	int GetFeligreses();
	void SetFeligreses(int f);
	void multiplicaFeligreses(float m);
	void modificaNivel();
	void generaFrasesAleatorias();
	int getNivel();

private:
	Global();
	~Global();
	
	int dinero = 0;
	int feligreses = 0;
	int nivel = 1;

};

#endif //ARMA

