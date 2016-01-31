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
	cocos2d::Label* letraActual_label;
	cocos2d::Vector<cocos2d::String*>  bateriaGritos;
	std::vector<std::string> personasEspaldas;
	std::vector<std::string> personasCara;


	void prepara();
	void creaLabelfinal(Node* n);


private:
	int fallos = 0;
	int idSongPaso;

	void meneito(Node* n);
	virtual void onEnterTransitionDidFinish();


	cocos2d::Sprite* señuelo;
	void spawnLetras(int &indice);
	void spawnPersonas(Node* n);
	void eliminaPersona(Node* p);

	
	void goToBiblia(Node* sender);

	cocos2d::EventListenerKeyboard* listener;
	
	// implement the "static create()" method manually
	CREATE_FUNC(Paso);
};

#endif // __PASO_SCENE_H__
