#include "Bancos.h"

USING_NS_CC;

Bancos* Bancos::Create(cocos2d::String * cadena)
{
	Bancos* banco = new Bancos();
	auto texture = Director::getInstance()->getTextureCache()->addImage(cadena->getCString());
	banco->initWithTexture(texture);
	return banco;
}

Bancos::Bancos()
{
	for (int i = 0; i < 5; i++) {
		vectorPosiciones.push_back(-1);
	}
}

Bancos::~Bancos()
{
}

bool Bancos::colocaPersona(Sprite* silueta)
{
	if (numpersonas == maxpersonas) {
		return false;
	}

	int posicion = asignaPosicion();
	silueta->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(silueta);
	silueta->setPosition(this->getContentSize().width*this->getScale() / posicion, this->getContentSize().height*this->getScale() / 2);
	vectorPosiciones[posicion - 1] = 1;
	numpersonas++;
	return true;

}

int Bancos::asignaPosicion()
{
	auto posicion = random(0,4 );
	if (vectorPosiciones[posicion] == 1) {
		asignaPosicion();
	}
	else return posicion+1;
}
