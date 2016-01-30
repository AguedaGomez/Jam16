#ifndef __BIBLIA_SCENE_H__
#define __BIBLIA_SCENE_H__

#include "cocos2d.h"

class Biblia : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	void goToIglesiaScene(Ref *pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(Biblia);

};

#endif // __BIBLIA_SCENE_H__
