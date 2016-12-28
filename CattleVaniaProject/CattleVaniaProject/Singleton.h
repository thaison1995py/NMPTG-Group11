#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "CTexture.h"
#include "CEnum.h"

class Singleton
{
private:
	CTexture* simon;
	CTexture* simonDeath;

	//enemy
	CTexture* blackKnight;
	CTexture* dragonSkullCannon;
	CTexture* vampireBat;
	CTexture* medusa;
	CTexture* flyingblock;
	CTexture* skeleton;
	CTexture* monkeyevil;
	CTexture* blackraven;
	//ground
	CTexture *brokenbrick;
	CTexture* candle;
	CTexture* movingPlatform;
	CTexture* openDoor;
	CTexture* stupidDoor;
	CTexture* spiketrap;
	//weapon
	CTexture* morningStar;
	CTexture* fireBomb;
	CTexture* dagger;
	CTexture* boomerang;
	CTexture* axe;
	//item
	CTexture *goldchest;
	CTexture *crown;
	CTexture *doubleshot;
	CTexture *food;
	CTexture* largeHeartItem;
	CTexture* smallHeartItem;
	CTexture* moneyBagItem;
	CTexture* crossItem;
	CTexture* morningStarItem;
	CTexture* fireBombItem;
	CTexture* daggerItem;
	CTexture* boomerangItem;
	CTexture* axeItem;
	CTexture* watchItem;

	CTexture* magicalCrystal;
	//boss
	CTexture* phantombat;
	CTexture* queenMedusa;
	CTexture* littleSnake;
	//other
	CTexture* fireDie;
	CTexture* fireBall;
	CTexture* skeletal;
	CTexture* bgMenu;
	//IntroScene
	CTexture* helicopter;
	CTexture* bat;
	CTexture* introBackground;

	CTexture* gameScore;
	CTexture* hp;

	CTexture* fallingCastle;
	CTexture* simonInCastle;

	static Singleton *single;
	Singleton();

public:
	static Singleton* getInstance();
	~Singleton();
	CTexture* getTexture(EnumID id);
};

#endif