#include "Iglesia.h"
#include "Biblia.h"
#include "Bancos.h"

USING_NS_CC;

Scene* Iglesia::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Iglesia::create();//Almacenar la layer en el singleton (Global)
	layer->setTag(200);
	// add layer as a child to scene
	scene->addChild(layer);
	scene->setTag(300);
	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Iglesia::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{

		return false;
	}

	// add "HelloWorld" splash screen"


	std::vector<Bancos>vectorBancos;

	/*auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
			return true; // to indicate that we have consumed it.
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		this->goToPasoScene(this);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);*/

	// add the sprite as a child to this layer
	//auto sprite = Sprite::create("HelloWorld.png");
	//this->addChild(sprite, 0);

	//auto bancoi = Sprite::create("Bancos/banco.png");
	//this->addChild(bancoi);
	//bancoi->getParent()->setTag(4000);
	//CCLOG("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA %d", bancoi->getParent()->getTag());
	colocaBancos();
	//colocaPersona(0);
	return true;
}

void Iglesia::goToPasoScene(Ref *pSender) {
	auto scene = Iglesia::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, scene, Color3B::WHITE));
}

void Iglesia::onEnterTransitionDidFinish()
{
	CCLOG(" Entro en bibilia despues de transicion");
}

void Iglesia::colocaBancos()
{
	float maxHeight = Director::getInstance()->getVisibleSize().height / 2;
	float widthLimit = Director::getInstance()->getVisibleSize().width / 2;
	int mitadPasilloAncho = 40;
	float escala;
	float distfijaeny = 0.0;

	maxBancos=0;
	auto PLACEHOLDERnivel = 3;
	switch (PLACEHOLDERnivel) {
	case 1:
		maxBancos = 4;
		break;
	case 2:
		maxBancos = 6;
		break;
	case 3:
		maxBancos = 20;
		break;
	}
	String* filename = String::create("Bancos/banco.png");
	for (int i = 0; i < maxBancos; i+=2) {

		Bancos* bancoi = Bancos::Create(filename);
		Bancos* bancod = Bancos::Create(filename);
		
		float altoBanco = bancoi->getContentSize().height;
		float desplazamiento = 0;

		vectorBancos.push_back((Bancos*)bancoi);
		vectorBancos.push_back((Bancos*)bancod);
		float resta = (maxBancos - i);
		CCLOG("MAXBANCOS : %d, iterador %d, resta %d",maxBancos,i, (maxBancos - i));
		if (i == 0) {
			escala = 0.04;
			distfijaeny += bancoi->getBoundingBox().size.height*0.1 / 2;
		}
		else {
			escala = 1.0 / resta;
			distfijaeny += bancoi->getBoundingBox().size.height*escala / 2;

		}
		desplazamiento = bancoi->getBoundingBox().size.width*escala / 2;

		CCLOG("Escala %f",escala);

		bancoi->setScale(escala);
		bancod->setScale(escala);

		bancoi->setAnchorPoint(Vec2(1, 0.5));
		bancod->setAnchorPoint(Vec2(0, 0.5));
		bancod->setColor(Color3B::RED);



		bancoi->setPosition(widthLimit -desplazamiento - mitadPasilloAncho, maxHeight -distfijaeny);
		bancod->setPosition(widthLimit+desplazamiento + mitadPasilloAncho, maxHeight - distfijaeny);



		CCLOG("Banco i esta en  %f %f banco d esta en %f %f", bancoi->getPositionX(), bancoi->getPositionY(), bancod->getPositionX(), bancod->getPositionY());
		
		addChild(bancoi,1);
		addChild(bancod,1);

		//CCLOG("El padre de bancoi es %d, el padre de bancod es %d", bancoi->getParent()->getTag(), bancod->getParent()->getTag());
	}
}

void Iglesia::colocaPersona(int personasColocadas)
{
	auto feligreses = 5;
	if (personasColocadas == feligreses) return;
	auto bancorandom = random(0, maxBancos-1);
	CCLOG("BancoRandom = %d", bancorandom);
	bool personacolocada = vectorBancos[bancorandom]->colocaPersona(Sprite::create(cocos2d::String::create("Bancos/silueta.png")->getCString()));
	if (!personacolocada) {
		colocaPersona(personasColocadas);
	}
	else
		colocaPersona(personasColocadas + 1);
}

