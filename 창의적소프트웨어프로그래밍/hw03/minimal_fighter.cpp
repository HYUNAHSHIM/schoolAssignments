#include <iostream>
#include "minimal_fighter.h"

using namespace std;

MinimalFighter::MinimalFighter(){
	mHp =0;
	mPower =0;
	mStatus = Invalid;
}
MinimalFighter::MinimalFighter(int _hp, int _power){
	mHp =_hp;
	mPower=_power;
	if(_hp<=0){
		mStatus =Dead;
	}else if(_hp>0){
		mStatus =Alive;}
}
int MinimalFighter::hp() const{
	return this->mHp;}
int MinimalFighter::power() const{
	return this->mPower;}
FighterStatus MinimalFighter::status() const{
	return this->mStatus;}
void MinimalFighter::setHp(int _hp){
	mHp -= _hp;
	if(mHp<=0){
		mStatus = Dead;}
}
void MinimalFighter::hit(MinimalFighter *_enemy){
	mHp -= _enemy->power();
	enemy->setHp(mPower);
	if(mHp <=0){
		mStatus = Dead;}
}
void MinimalFighter::attack(MinimalFighter *_target){
	_target->setHp(mPower);
	mPower =0;}
void MinimalFighter::fight(MinimalFighter *_enemy){
	while(1){
		mHp -= _enemy->power();
		(*_enemy).setHp(mPower);
		if(mHp <=0||_enemy->status()==Dead){
			if(mHp<=0){
				mStatus=Dead;}
			return;
		}
	}
}

