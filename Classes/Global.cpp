#include "Global.h"
#include "Biblia.h"
#include "LeerArchivo.h"
#include "Iglesia.h"


USING_NS_CC;


static Global* global = nullptr;

Global::Global() {
	//inicializar escenas a null
	paso = nullptr;
	iglesia = nullptr;
	biblia = nullptr;

	feligreses = 10;
	dinero = 10;
	dineroAñadidos = 0;
	feligresesAñadidos = 0;
	bateriaEscogida = 0;
	multiplicadorDinero = 1;
	multiplicadorFeligreses = 1;
	BateriaAgresivas = lector.Extraer("Databases/bateriaAgr.tsv");
	BateriaOptimista = lector.Extraer("Databases/bateriaOpt.tsv");
	BateriaPesimista = lector.Extraer("Databases/bateriaPes.tsv");

	//BateriaAgresivas.push_back("muerteydestruccion/");

	
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
		biblia = Biblia::createScene();
		biblia->retain();
	}
	return biblia;
}

cocos2d::Scene * Global::getInstanceIglesia()
{
	if (iglesia == nullptr) {
		iglesia = Iglesia::createScene();
		iglesia->retain();
	}
	return iglesia;
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
	CCLOG("feligreses en global tras sumar = %d", feligreses);

	if (feligreses >= 80)feligreses = 80;
	if (feligreses <= 0)feligreses = 0;
}

void Global::setNivel(int nivel)
{
	this->nivel = nivel;
}

void Global::multiplicaFeligreses(float m)
{
	feligreses *= m;
	CCLOG("feligreses en global tras multiplicar = %d", feligreses);
	if (feligreses >= 80)feligreses = 80;
	if (feligreses <= 0)feligreses = 0;
}

void Global::modificaNivel()
{
	nivel++;
}

void Global::generaFrasesAleatorias()
{
	agresivaDeTurno = random(0, 13);
	optimistaDeTurno = random(0, 14);
	pesimistaDeTurno = random(0, 11);
}

int Global::getNivel()
{
	return nivel;
}