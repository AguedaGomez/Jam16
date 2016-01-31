#ifndef __BANCOS_SCENE_H__
#define __BANCOS_SCENE_H__

#include "cocos2d.h"



class Bancos : public cocos2d::Sprite
{
public:
	static Bancos* Create(cocos2d::String* cadena);
	Bancos();
	~Bancos();

	bool colocaPersona(Sprite* silueta);
	int asignaPosicion();
private:
	int maxpersonas = 5;
	int numpersonas=0;
	std::vector<int> vectorPosiciones;

};

#endif // __BIBLIA_SCENE_H__
