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

	personasEspaldas.push_back("images/Persona/hombre.png");
	personasEspaldas.push_back("images/Persona/nina.png");
	personasEspaldas.push_back("images/Persona/vieja1.png");
	personasEspaldas.push_back("images/Persona/vieja2.png");
	personasEspaldas.push_back("images/Persona/vieja3.png");

	personasCara.push_back("images/Persona/cofradeMuj.png");
	personasCara.push_back("images/Persona/cofradeHombr.png");
	personasCara.push_back("images/Persona/ninoRata.png");
	personasCara.push_back("images/Persona/Seniorito.png");

	//prepara();
	return true;
}

void Paso::prepara()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto background = cocos2d::Sprite::create("images/Paso/fondo.png");
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	addChild(background);
	auto rectangle = cocos2d::Sprite::create("images/Paso/black.png");
	addChild(rectangle, 5);
	rectangle->setScale(15, 0.75);
	rectangle->setPositionY(0);

	idSongPaso = AudioEngine::play2d("sounds/Saeta.mp3");

	señuelo = Sprite::create();
	addChild(señuelo);
	int n_letra = 0;
	letraActual = NULL;
	pasito = Sprite::create("images/Trono/tronoEntero.png");
	pasito->setScale(-0.5,0.5);

	this->addChild(pasito, 1);
	pasito->setPosition(0, visibleSize.height / 2-50); //visibleSize.width / 2 - pasito->getBoundingBox().size.width / 2
	pasito->runAction(Sequence::create(MoveBy::create(3.0f, Point(visibleSize.width / 2 ,0)), CallFuncN::create(CC_CALLBACK_1(Paso::meneito, this)),NULL));

	listener = EventListenerKeyboard::create();
	listener->onKeyPressed = [&](EventKeyboard::KeyCode key, Event* event) {
		if ((int)key == letraActual + 27) {

			letraActual_label->setColor(Color3B::WHITE);
		}
		else {
			int r = random(0, 2);
			auto s = bateriaGritos.at(r)->getCString();
			AudioEngine::play2d(s, false, 0.7);

			auto label = Label::create("TOO BAD", "Trajan Pro 3", 40);
			letraActual_label->setColor(Color3B(48,48,48));
			pasito->runAction(Sequence::create(RotateBy::create(0.1, 15), RotateBy::create(0.1, -30), RotateBy::create(0.1, 15), NULL));
		}
		pasito->setColor(Color3B::WHITE);
		listener->setEnabled(false);
		//CCLOG("b: %d",(int)cadena[0]);
		//CCLOG("key %d", (int)key);
	};
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->runAction(RepeatForever::create(Sequence::create(CallFuncN::create(CC_CALLBACK_1(Paso::spawnPersonas, this)), DelayTime::create(1.3f), NULL)));
	señuelo->runAction(RepeatForever::create(Sequence::create(CallFuncN::create(CC_CALLBACK_0(Paso::spawnLetras, this, n_letra)), 
		DelayTime::create(2.0f), NULL)));

}

void Paso::meneito(Node*n)
{
	pasito->runAction(RepeatForever::create(Sequence::create(MoveBy::create(1.5f, Point(-3, 10)), MoveBy::create(1.5f, Point(3, -10)), NULL)));
}


void Paso::onEnterTransitionDidFinish()
{
	prepara();

}

void Paso::spawnLetras(int &indice)
{
	//std::string frase = Global::getInstance()->BateriaAgresivas[Global::getInstance()->posicionBaterias];
	std::string frase=Global::getInstance()->FrasePaso;
	//agresiva 0  opt 1 pes 2

	listener->setEnabled(true);
		auto letra = Label::create();
		letraActual_label = letra;
		if (indice <= frase.length()) 
		{
			letra->setString(frase.substr(indice, 1));
			indice++;
			letraActual = (int)letra->getString()[0];
			letra->setSystemFontSize(100.0f);
			letra->setPosition(Point(0, 80));
			letra->setColor(Color3B(126, 126, 126));
			//if (letra->getString() == "/") {
			if (indice == frase.length()) {
				auto c = this->getChildren();
				for (int j = 0; j < this->getChildrenCount(); j++)
					c.at(j)->stopAllActions();
				stopAllActions();
				pasito->runAction(Sequence::create(MoveTo::create(4.0, Vec2(Director::getInstance()->getVisibleSize().width + pasito->getBoundingBox().size.width, pasito->getPositionY())),
					 CallFuncN::create(CC_CALLBACK_1(Paso::creaLabelfinal,this)), NULL));
				AudioEngine::stopAll();
				AudioEngine::play2d("sounds/Aplausos_mixdown.mp3",false,0.5);
				listener->setEnabled(false);

			}
			else {
				addChild(letra,6);
				letra->runAction(Sequence::create(FadeIn::create(0.1f), MoveBy::create(1.5,Point(1270,0)), FadeOut::create(0.1f), NULL));
			}
		}
}

void Paso::spawnPersonas(Node* n)
{
	int rDelante = random(0, 4);
	int rDetras = random(0,3);

	int escala = random(0, 1);

	std::string sDelante = personasEspaldas[rDelante];
	std::string sDetras = personasCara[rDetras];

	auto personaDelante = cocos2d::Sprite::create();
	personaDelante->initWithFile(sDelante);

	personaDelante->setPosition(Point(1350,720/3-personaDelante->getContentSize().height/3));
	escala == 0 ? personaDelante->setScaleX(-1) : personaDelante->setScaleX(1);
	addChild(personaDelante, 2);

	auto personaDetras = cocos2d::Sprite::create();
	personaDetras->initWithFile(sDetras);
	personaDetras->setPosition(Point(1350, 720*2 / 3-personaDetras->getContentSize().height/2));
	escala == 1 ? personaDetras->setScaleX(-1) : personaDetras->setScaleX(1);

	addChild(personaDetras, 0);

	
	personaDelante->runAction(Sequence::create(MoveBy::create(17,Point(-1400,0)),
		CallFuncN::create(CC_CALLBACK_1(Paso::eliminaPersona,this)) ,NULL));

	personaDetras->runAction(Sequence::create(MoveBy::create(25, Point(-1500, 0)),
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
void Paso::creaLabelfinal(Node * n)
{
	CCLOG("holi");
	//auto texto = cocos2d::Label::create();

	auto texto = cocos2d::Label::createWithSystemFont("Fin de la procesion", "Times New Roman", 20,
		Size(300, 100), TextHAlignment::CENTER, TextVAlignment::CENTER);
	//texto->setString("Fin de la procesion");
	texto->setColor(Color3B::BLACK);
	texto->setScale(5);
	addChild(texto, 8);
	texto->setPosition(1280 / 2,50);
	texto->runAction(Sequence::create(FadeIn::create(0.5),MoveBy::create(5.0,Point(0,720)),FadeOut::create(0.5), 
		CallFuncN::create(CC_CALLBACK_1(Paso::goToBiblia, this)), NULL));

}