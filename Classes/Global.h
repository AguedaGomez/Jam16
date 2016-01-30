#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#include "cocos2d.h"
#include "Paso.h"

//Singleton

class Global 
{
public:
	static Global* getInstance();

	cocos2d::Scene* paso;
	cocos2d::Scene* biblia;
	cocos2d::Scene* iglesia;

	int posicionBaterias=0;

	 std::vector<std::string> BateriaAgresivas;
	 std::vector<std::string> BateriaOptimista;
	 std::vector<std::string> BateriaPesimista;


	cocos2d::Scene* getInstancePaso();
	cocos2d::Scene* getInstanceBiblia();
	cocos2d::Scene* getInstanceIglesia();

	int GetDinero();
	void SetDinero(int d);

	int GetFeligreses();
	void SetFeligreses(int f);

private:
	Global();
	~Global();
	
	int dinero = 0;
	int feligreses = 0;
	int modificadorFeligreses = 0;
	int modificadorDinero = 0;
};

#endif //ARMA

