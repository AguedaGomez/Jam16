#ifndef __IGLESIA_SCENE_H__
#define __IGLESIA_SCENE_H__

#include "cocos2d.h"
#include "Bancos.h"

class Iglesia : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	int maxBancos;
	virtual bool init();

	void goToPasoScene(Ref *pSender);
	virtual void onEnterTransitionDidFinish();

	void colocaBancos();
	void colocaPersona(int personasColocadas);

	std::vector<Bancos*>vectorBancos;

	// implement the "static create()" method manually
	CREATE_FUNC(Iglesia);

};

#endif // __BIBLIA_SCENE_H__
