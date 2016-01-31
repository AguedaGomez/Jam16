#include "Biblia.h"
#include "Global.h"
#include "AudioEngine.h"
#include "ui/CocosGUI.h"


using namespace cocos2d::experimental;

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("images/Biblia/biblia.png");
	sprite->setPosition(1280/2,720/2);
	addChild(sprite, 0);

    return true;
}

void Biblia::goToIglesia(Ref * pSender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f,Global::getInstance()->getInstanceIglesia(),Color3B::WHITE));
}




void Biblia::cargaBotones()
{
	auto tamañoletra = 20;
	auto lector = Global::getInstance()->lector;


	auto buttonagresiva = cocos2d::ui::Button::create("images/Bancos/banco_senuelo.png", "images/Bancos/banco_senuelo.png", "images/Bancos/banco_senuelo.png");

	buttonagresiva->setTitleText(lector.leeCampo(Global::getInstance()->BateriaAgresivas[Global::getInstance()->agresivaDeTurno], 1));
	buttonagresiva->setTitleFontName("Arial");
	buttonagresiva->setTitleFontSize(tamañoletra);
	Global::getInstance()->bateriaEscogida = 0;

	buttonagresiva->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto stringfeli = lector.leeCampo(Global::getInstance()->BateriaAgresivas[Global::getInstance()->agresivaDeTurno], 2);
		auto stringDinero = lector.leeCampo(Global::getInstance()->BateriaAgresivas[Global::getInstance()->agresivaDeTurno], 3);
		auto stringFrase = lector.leeCampo(Global::getInstance()->BateriaAgresivas[Global::getInstance()->agresivaDeTurno],0);
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			Global::getInstance()->multiplicadorFeligreses = stringtofloat(stringfeli);

			Global::getInstance()->multiplicadorDinero = stringtofloat(stringDinero);
			Global::getInstance()->FrasePaso = stringFrase;

			CCLOG("multiplicador d %f multiplicador f %f", Global::getInstance()->multiplicadorDinero, Global::getInstance()->multiplicadorFeligreses);
			goToIglesia(this);
			break;
		default:
			break;
		}
	});

	auto buttonopt = cocos2d::ui::Button::create("images/Bancos/banco_senuelo.png", "images/Bancos/banco_senuelo.png", "images/Bancos/banco_senuelo.png");

	buttonopt->setTitleText(lector.leeCampo(Global::getInstance()->BateriaOptimista[Global::getInstance()->optimistaDeTurno], 1));
	buttonopt->setTitleFontName("Arial");
	buttonopt->setTitleFontSize(tamañoletra);
	Global::getInstance()->bateriaEscogida = 1;

	buttonopt->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto stringfeli = lector.leeCampo(Global::getInstance()->BateriaOptimista[Global::getInstance()->optimistaDeTurno], 2);
		auto stringDinero = lector.leeCampo(Global::getInstance()->BateriaOptimista[Global::getInstance()->optimistaDeTurno], 3);
		auto stringFrase = lector.leeCampo(Global::getInstance()->BateriaOptimista[Global::getInstance()->optimistaDeTurno],0);
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			Global::getInstance()->multiplicadorFeligreses = stringtofloat(stringfeli);

			Global::getInstance()->multiplicadorDinero = stringtofloat(stringDinero);
			Global::getInstance()->FrasePaso = stringFrase;

			CCLOG("multiplicador d %f multiplicador f %f", Global::getInstance()->multiplicadorDinero, Global::getInstance()->multiplicadorFeligreses);
			goToIglesia(this);
			break;
		default:
			break;
		}
	});

	auto buttonpes = cocos2d::ui::Button::create("images/Bancos/banco_senuelo.png", "images/Bancos/banco_senuelo.png", "images/Bancos/banco_senuelo.png");

	buttonpes->setTitleText(lector.leeCampo(Global::getInstance()->BateriaPesimista[Global::getInstance()->pesimistaDeTurno], 1));

	buttonpes->setTitleFontName("Arial");
	buttonpes->setTitleFontSize(tamañoletra);

	Global::getInstance()->bateriaEscogida = 2;
	buttonpes->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type) {
		auto stringfeli = lector.leeCampo(Global::getInstance()->BateriaPesimista[Global::getInstance()->pesimistaDeTurno], 2);
		auto stringDinero = lector.leeCampo(Global::getInstance()->BateriaPesimista[Global::getInstance()->pesimistaDeTurno], 3);
		auto stringFrase = lector.leeCampo(Global::getInstance()->BateriaPesimista[Global::getInstance()->pesimistaDeTurno],0);

		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:

			Global::getInstance()->multiplicadorFeligreses = stringtofloat(stringfeli);
			Global::getInstance()->multiplicadorDinero = stringtofloat(stringDinero);
			Global::getInstance()->FrasePaso = stringFrase;

			CCLOG("multiplicador d %f multiplicador f %f", Global::getInstance()->multiplicadorDinero, Global::getInstance()->multiplicadorFeligreses);
			goToIglesia(this);
			break;
		default:
			break;
		}
	});

	this->addChild(buttonagresiva);
	this->addChild(buttonpes);
	this->addChild(buttonopt);
	auto arriba = Vec2(1280 / 2, 720 / 2 + 50);
	auto medio = Vec2(1280 / 2, 720 / 2 - 50);
	auto abajo = Vec2(1280 / 2, 720 / 2 - 150);

	auto configuracion = random(1, 3);

	if (configuracion == 1) {
		buttonagresiva->setPosition(arriba);
		buttonpes->setPosition(medio);
		buttonopt->setPosition(abajo);
	}
	else if (configuracion == 2) {
		buttonagresiva->setPosition(abajo);
		buttonpes->setPosition(arriba);
		buttonopt->setPosition(medio);
	}
	else {
		buttonagresiva->setPosition(medio);
		buttonpes->setPosition(abajo);
		buttonopt->setPosition(arriba);
	}
}

float Biblia::stringtofloat(std::string cadena)
{
	int decenas = 0;
	int unidades = 0;
	for (int i = 0; i < cadena.size(); i++) {
		auto caracter = cadena[i];
		auto numero = 0;
		if (caracter == '0') { numero = 0; }
		else if (caracter == '1') { numero = 1; }
		else if (caracter == '2') { numero = 2; }
		else if (caracter == '3') { numero = 3; }
		else if (caracter == '4') { numero = 4; }
		else if (caracter == '5') { numero = 5; }
		else if (caracter == '6') { numero = 6; }
		else if (caracter == '7') { numero = 7; }
		else if (caracter == '8') { numero = 8; }
		else if (caracter == '9') { numero = 9; }

		if (i == 0) decenas = numero * 10;
		if (i == 2)unidades = numero;

	}
	auto numero = (decenas + unidades) / 10.0;
	return numero;
}

void Biblia::onEnterTransitionDidFinish()
{
	removeAllChildren();
	Global::getInstance()->generaFrasesAleatorias();
	cargaBotones();

}

