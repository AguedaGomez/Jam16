#include "Biblia.h"
#include "Iglesia.h"

USING_NS_CC;

Scene* Biblia::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = Biblia::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Biblia::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");


    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}

void Biblia::goToIglesiaScene(Ref *pSender) {
	auto scene = Iglesia::createScene();
	Director::getInstance()->replaceScene(scene);
}
