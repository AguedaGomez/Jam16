#include "Bancos.h"

USING_NS_CC;

Bancos* Bancos::Create(cocos2d::String * cadena)
{
	Bancos* banco = new Bancos();
	auto texture = Director::getInstance()->getTextureCache()->addImage(cadena->getCString());
	banco->initWithTexture(texture);
	banco->retain();
	return banco;
}

Bancos::Bancos()
{
	for (int i = 0; i < 5; i++) {
		vectorPosiciones.push_back(-1);
	}
	Sprite* banco_txtr = Sprite::create("images/Bancos/banco.png");
	addChild(banco_txtr,4);
	banco_txtr->setPosition(banco_txtr->getContentSize().width / 2+30,banco_txtr->getContentSize().height/2);
}

Bancos::~Bancos()
{
}

bool Bancos::colocaPersona(Sprite* silueta)
{

	if (numpersonas >= maxpersonas) {
		return false;
	}
	else {
		int posicion = asignaPosicion();
		silueta->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(silueta,1);
		silueta->setPosition(silueta->getPositionX() + (this->getContentSize().width/5)*posicion,silueta->getPositionY()+silueta->getContentSize().height/2);
		silueta->setScale((this->getContentSize().width / 5) / silueta->getContentSize().width);
		vectorPosiciones[posicion - 1] = 1;
		numpersonas++;
		return true;
	}
	CCLOG("numeropersonas = %d", numpersonas);
	for (int i = 0; i < 5; i++) {
		CCLOG("slot %d = %d", i, vectorPosiciones[i]);
	}
}

int Bancos::asignaPosicion()
{
	auto posicion = random(0,4 );
	if (vectorPosiciones[posicion] == 1) {
		asignaPosicion();
	}
	else return posicion+1;
}
