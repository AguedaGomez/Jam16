#ifndef __PASO_SCENE_H__
#define __PASO_SCENE_H__

#include "cocos2d.h"

class Paso : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	int letraActual;
	cocos2d::Sprite* pasito;
	virtual bool init();


private:
	int fallos = 0;

	cocos2d::Sprite* señuelo;
	void spawnLetras(int &indice);
	void spawnPersonas(Node* n);
	void eliminaPersona(Node* p);

	bool compruebaTeclaAcertada();
	void goToBiblia(Node* sender);

	cocos2d::EventListenerKeyboard* listener;
	
	// implement the "static create()" method manually
	CREATE_FUNC(Paso);
};

#endif // __PASO_SCENE_H__
