#include "MainMenuScene.h"
#include "Global.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;

USING_NS_CC;

Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
	auto botonPlay = MenuItemImage::create("images/MainMenuScene/start_btn.png", "images/MainMenuScene/start_btn.png",
		CC_CALLBACK_1(MainMenu::goToBiblia, this));


	auto menu = Menu::create(botonPlay, NULL);
	menu->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	addChild(menu, 0);

	idSongMainMenu=AudioEngine::play2d("sounds/Guadalquivir.mp3",true,0.7);
    return true;
}

void MainMenu::goToBiblia(Ref *pSender)
{
	AudioEngine::stopAll();
	Director::getInstance()->pushScene(Global::getInstance()->getInstancePaso()); 
}

