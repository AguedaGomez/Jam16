#include "Paso.h"
#include "Global.h"
#include "AudioEngine.h"

using namespace cocos2d::experimental;

USING_NS_CC;

Scene* Paso::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Paso::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Paso::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	bateriaGritos.pushBack(cocos2d::String::create("sounds/gritopenoso1.mp3"));
	bateriaGritos.pushBack(cocos2d::String::create("sounds/gritopenoso2.mp3"));
	bateriaGritos.pushBack(cocos2d::String::create("sounds/gritopenoso3.mp3"));

	//prepara();
	return true;
}

void Paso::prepara()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	idSongPaso = AudioEngine::play2d("sounds/Saeta.mp3");

	señuelo = Sprite::create();
	addChild(señuelo);
	int n_letra = 0;
	letraActual = NULL;
	pasito = Sprite::create("images/Paso/Paso.png");
	this->addChild(pasito, 1);
	pasito->setPosition(visibleSize.width / 2 - pasito->getBoundingBox().size.width / 2, visibleSize.height / 2);
	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode key, Event* event) {
		if ((int)key == letraActual + 27) {
			CCLOG("BIEN");
			auto label = Label::create("VERY GOOD", "Arial", 40);
			label->setColor(Color3B::GREEN);
			this->addChild(label);
			label->setPosition(400, 400);
			label->runAction(FadeOut::create(0.5));
			pasito->setColor(Color3B::GREEN);
		}
		else {
			CCLOG("MAL");
			int r = random(0, 2);
			auto s = bateriaGritos.at(r)->getCString();
			AudioEngine::play2d(s, false, 0.7);

			auto label = Label::create("TOO BAD", "Arial", 40);
			label->setColor(Color3B::RED);
			this->addChild(label);
			label->setPosition(400, 400);
			label->runAction(FadeOut::create(0.5));
			pasito->setColor(Color3B::RED);
			pasito->runAction(Sequence::create(RotateBy::create(0.1, 25), RotateBy::create(0.1, -50), RotateBy::create(0.1, 25), NULL));
		}
		pasito->setColor(Color3B::WHITE);
		listener->setEnabled(false);
		//CCLOG("b: %d",(int)cadena[0]);
		//CCLOG("key %d", (int)key);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->runAction(RepeatForever::create(Sequence::create(CallFuncN::create(CC_CALLBACK_1(Paso::spawnPersonas, this)), DelayTime::create(0.5f), NULL)));
	señuelo->runAction(RepeatForever::create(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Paso::spawnLetras, this, n_letra)), DelayTime::create(0.9f), NULL)));

}

void Paso::onEnterTransitionDidFinish()
{
	prepara();

}

void Paso::spawnLetras(int &indice)
{
	std::string frase = Global::getInstance()->BateriaAgresivas[Global::getInstance()->posicionBaterias];
	listener->setEnabled(true);
		auto letra = Label::create();
		if (indice <= frase.length()) 
		{
			letra->setString(frase.substr(indice, 1));
			indice++;
			letraActual = (int)letra->getString()[0];
			letra->setSystemFontSize(100.0f);
			letra->setPosition(Point(1280 / 2, 720 / 2));
			if (letra->getString() == "/") {
				auto c = this->getChildren();
				for (int j = 0; j < this->getChildrenCount(); j++)
					c.at(j)->stopAllActions();
				stopAllActions();
				pasito->runAction(Sequence::create(MoveTo::create(0.3, Vec2(Director::getInstance()->getVisibleSize().width + pasito->getBoundingBox().size.width, pasito->getPositionY())),CallFuncN::create(CC_CALLBACK_1(Paso::goToBiblia,this)), NULL));
				AudioEngine::stopAll();
				AudioEngine::play2d("sounds/Aplausos_mixdown.mp3",false,0.5);
				listener->setEnabled(false);

			}
			else {
				addChild(letra, 4);
				letra->runAction(Sequence::create(FadeIn::create(0.1f), DelayTime::create(0.1f), FadeOut::create(0.1f), NULL));

			}
		}
		
}

void Paso::spawnPersonas(Node* n)
{
	auto personaDelante = cocos2d::Sprite::create("images/Persona/back_btn.png");
	personaDelante->setPosition(Point(1300,720/3));
	addChild(personaDelante, 2);

	auto personaDetras = cocos2d::Sprite::create("images/Persona/back_btn.png");
	personaDetras->setPosition(Point(1350, 720*2 / 3));
	addChild(personaDetras, 0);

	
	personaDelante->runAction(Sequence::create(MoveBy::create(12,Point(-1400,0)),
		CallFuncN::create(CC_CALLBACK_1(Paso::eliminaPersona,this)) ,NULL));

	personaDetras->runAction(Sequence::create(MoveBy::create(15, Point(-1400, 0)),
		CallFuncN::create(CC_CALLBACK_1(Paso::eliminaPersona, this)), NULL));
}

void Paso::eliminaPersona(Node *p)
{
	p->stopAllActions();
	p = nullptr;
	removeChild(p);
}

void Paso::goToBiblia(Node* sender)
{
	removeAllChildren();
	Director::getInstance()->popScene();
	//Director::getInstance()->replaceScene(Global::getInstance()->getInstanceBiblia());
}
