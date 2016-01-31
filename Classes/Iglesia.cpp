#include "Iglesia.h"
#include "Biblia.h"
#include "Bancos.h"
#include "Global.h"
#include "AudioEngine.h"


USING_NS_CC;
using namespace cocos2d::experimental;


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


	/*std::vector<Bancos>vectorBancos;

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
			return true; // to indicate that we have consumed it.
	};

	listener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		this->goToPasoScene(this);
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 30);



	auto istener = EventListenerKeyboard::create();
	istener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {

		Vec2 loc = event->getCurrentTarget()->getPosition();
		switch (keyCode) {

		case EventKeyboard::KeyCode::KEY_F:
			Global::getInstance()->feligresesAñadidos += 5;
			break;
		case EventKeyboard::KeyCode::KEY_D:
			Global::getInstance()->feligresesAñadidos -= 5;
			break;
		}
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(istener, this);*/
	
	

	auto dinero = Global::getInstance()->GetDinero();


	fondo = Sprite::create("images/Paso/fondo.png");
	fondo->retain();
	this->addChild(fondo);
	fondo->setPosition(640,360);
	Sacerdote = Sprite::create("images/Persona/cura.png");
	Sacerdote->retain();
	Sacerdote->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2+30);
	colocaSacerdote();
	colocaRiquezas();
	transicionAMinijuego();
	amen=Label::create("Ameeeeeen, JO-DER","Arial",30);
	amen->setPosition(200, 700);
	this -> addChild(amen);
	listenerToque = EventListenerTouchOneByOne::create();
	listenerToque->onTouchBegan = [&](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		if (amen->getBoundingBox().containsPoint(touch->getLocation())) {
			return true; // to indicate that we have consumed it.
		}
		return false;
	};

	listenerToque->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event* event)
	{
		amen->runAction(Sequence::create(ScaleTo::create(0.2f, 0.8f), ScaleTo::create(0.2, 1.0f), NULL));
		listenerToque->setEnabled(false);
		Iglesia::goToPasoScene(this);
	};
	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listenerToque, 30);

	return true;
}

void Iglesia::goToPasoScene(Ref *pSender) {
	feligreses_labl->removeFromParent();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Global::getInstance()->getInstancePaso(), Color3B::WHITE));
}

void Iglesia::onEnterTransitionDidFinish()
{

	colocaBancos();
	colocaPersona(0);
	Global::getInstance()->multiplicaFeligreses(Global::getInstance()->multiplicadorFeligreses);
	Global::getInstance()->SetFeligreses(Global::getInstance()->feligresesAñadidos);
	Global::getInstance()->SetDinero(Global::getInstance()->dineroAñadidos);
	Global::getInstance()->feligresesAñadidos = 0;
	Global::getInstance()->dineroAñadidos = 0;

	eleccion = Global::getInstance()->eleccion;
	log("eleccion = %c",eleccion);
	auto feligreses = Global::getInstance()->GetFeligreses();
	auto dinero = Global::getInstance()->GetDinero();
	if (feligreses <= 0 || dinero == 0) {
		//gotoGameOver();
	}
	else if (feligreses <= 50) {
		Global::getInstance()->setNivel(1);
	}
	else if (feligreses > 50 && feligreses <= 70) {
		Global::getInstance()->setNivel(2);
	}
	else 	Global::getInstance()->setNivel(3);
	listenerToque->setEnabled(true);

	feligreses_labl = Label::create(String::createWithFormat("Feligreses %d", Global::getInstance()->GetFeligreses())->getCString(),"Arial",30);
	this->addChild(feligreses_labl);
	feligreses_labl->setPosition(200, 500);

	idSongIglesiaAmbiente = AudioEngine::play2d("sounds/Background.mp3");
	AudioEngine::setVolume(idSongIglesiaAmbiente, 0.01);

	
	auto reaccionSonido = Sprite::create();
	this->addChild(reaccionSonido);
	reaccionSonido->runAction(Sequence::create(DelayTime::create(2.0f), CallFuncN::create(CC_CALLBACK_1(Iglesia::reproduceReaccion,this,eleccion)), NULL));
	reaccionSonido->runAction(Sequence::create(DelayTime::create(4.0f), CallFuncN::create(CC_CALLBACK_1(Iglesia::reproduceRecolecta, this,eleccion)), NULL));
}

void Iglesia::reproduceReaccion(Node *pSender, char elec)
{
	int Sonidoreaccion;
	switch (elec)
	{
	case 'o':
		if (random(0, 1) < 0.5) {
			Sonidoreaccion = AudioEngine::play2d("sounds/Ovacion1.mp3");
		}
		else
		{
			Sonidoreaccion = AudioEngine::play2d("sounds/Ovacion2.mp3");
		}
		AudioEngine::setVolume(Sonidoreaccion, 0.05);
		

		break;
	case 'p':
			Sonidoreaccion = AudioEngine::play2d("sounds/Toses.mp3");
		AudioEngine::setVolume(Sonidoreaccion, 0.05);
		break;
	case 'a':
		if (random(0, 1) < 0.5) {
			Sonidoreaccion = AudioEngine::play2d("sounds/Silencio1.mp3");
		}
		else {
			Sonidoreaccion = AudioEngine::play2d("sounds/Silencio2.mp3");
		}
		AudioEngine::setVolume(Sonidoreaccion, 0.05);

		break;

	default:
		break;
	}

}

void Iglesia::reproduceRecolecta(Node * pSender, char elec)
{
	int sonidoMonedas;
	switch (elec)
	{
	case 'o':
		sonidoMonedas = AudioEngine::play2d("sounds/monedas.mp3");
		break;
	case 'p':
		sonidoMonedas = AudioEngine::play2d("sounds/monedasIntermedio.mp3");
		break;
	case 'a':
		sonidoMonedas = AudioEngine::play2d("sounds/monedasLargo.mp3");
		break;

	default:
		break;
	}
}



void Iglesia::colocaBancos()
{
	float maxHeight = Director::getInstance()->getVisibleSize().height / 2;
	float widthLimit = Director::getInstance()->getVisibleSize().width*0.49;
	int mitadPasilloAncho = 40;
	float escala;
	float distfijaeny = 0.0;

	maxBancos=0;
	auto nivel = Global::getInstance()->getNivel();
	switch (nivel) {
	case 1:
		maxBancos = 10;
		break;
	case 2:
		maxBancos = 14;
		break;
	case 3:
		maxBancos = 16;
		break;
	}
	String* filename = String::create("images/Bancos/banco_senuelo.png");
	for (int i = 0; i < maxBancos; i+=2) {

		Bancos* bancoi = Bancos::Create(filename);
		Bancos* bancod = Bancos::Create(filename);
		
		float altoBanco = bancoi->getContentSize().height;
		float desplazamiento = 0;

		vectorBancos.push_back((Bancos*)bancoi);
		vectorBancos.push_back((Bancos*)bancod);
		float resta = (maxBancos - i);

		if (i == 0) {
			escala = 1.0/resta;
			distfijaeny += bancoi->getBoundingBox().size.height*escala / 2;
		}
		else {
			escala = 1.0 / resta;
			distfijaeny += bancoi->getBoundingBox().size.height*escala / 2;

		}
		desplazamiento = bancoi->getBoundingBox().size.width*escala / 2;


		bancoi->setScale(escala);
		bancod->setScale(escala);

		bancoi->setAnchorPoint(Vec2(1, 0.5));
		bancod->setAnchorPoint(Vec2(0, 0.5));
		bancod->setColor(Color3B::RED);



		bancoi->setPosition(widthLimit -desplazamiento - mitadPasilloAncho, maxHeight -distfijaeny);
		bancod->setPosition(widthLimit+desplazamiento + mitadPasilloAncho, maxHeight - distfijaeny);

		
		addChild(bancoi,i/2);
		addChild(bancod,i/2);

	}
}

void Iglesia::colocaPersona(int personasColocadas)
{
	auto feligreses = Global::getInstance()->GetFeligreses();
	CCLOG("feligreses = %d", feligreses);
	for (int i = 0; i < feligreses; i++) {
		auto bancorandom = random(0, maxBancos - 1);
		bool personacolocada = vectorBancos[bancorandom]->colocaPersona(Sprite::create(cocos2d::String::createWithFormat("images/Bancos/silueta%i.png",random(1,5))->getCString()));
		while (!personacolocada) {
			bancorandom = random(0, maxBancos - 1);
			personacolocada = vectorBancos[bancorandom]->colocaPersona(Sprite::create(cocos2d::String::createWithFormat("images/Bancos/silueta%i.png", random(1, 5))->getCString()));
		}
	}
}

void Iglesia::colocaSacerdote()
{
	Sacerdote->removeFromParent();
	this->addChild(Sacerdote, 2);
	Sacerdote->setScale(0.2/Global::getInstance()->getNivel());
}

void Iglesia::colocaRiquezas()
{
}

void Iglesia::transicionAMinijuego()
{

}

