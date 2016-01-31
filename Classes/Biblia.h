#ifndef __BIBLIA_SCENE_H__
#define __BIBLIA_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d::experimental;


class Biblia : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void goToIglesia(Ref *pSender);

	int idSongBiblia;

	void cargaBotones();
	float stringtofloat(std::string cadena);
	virtual void onEnterTransitionDidFinish();

    // implement the "static create()" method manually
    CREATE_FUNC(Biblia);

};

#endif // __MAINMENU_SCENE_H__
