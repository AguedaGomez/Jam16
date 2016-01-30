#include "Global.h"

USING_NS_CC;


static Global* global = nullptr;

Global::Global() {
	//inicializar escenas a null
	paso = nullptr;
	iglesia = nullptr;
	biblia = nullptr;

	BateriaAgresivas.push_back("muerteydestruccion/");
}

Global* Global::getInstance(){

	if (!global){
		global = new Global();
	}

	return global;
}

cocos2d::Scene * Global::getInstancePaso()
{
	if (paso == nullptr) {
		paso = Paso::createScene();
		paso->retain();
	}
	return paso;

}

cocos2d::Scene * Global::getInstanceBiblia()
{
	if (biblia == nullptr) {
		//biblia = Paso::createScene();
		biblia->retain();
	}
	return biblia;
}

int Global::GetDinero()
{
	return dinero;
}

void Global::SetDinero(int d)
{
	dinero += d;
}

int Global::GetFeligreses()
{
	return feligreses;
}

void Global::SetFeligreses(int f)
{
	feligreses += f;
}



