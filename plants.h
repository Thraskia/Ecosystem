#ifndef PLANTS_H
#define PLANTS_H

#include <iostream>
#include <string>
#include "tile.h"
using namespace std;

class Plants{
	protected:
		string name;
		int x;
		int y;
		char token;
		int breedingProb; 
		int illnessProb;
		int life;
		int lifeFactor;
		int growthPeriod;
		int breedingRepPeriod;
	public:
		Plants(string name, char token, int life, int breedingProb, int illnessProb, int lifeFactor, int x, int y){
			this->name = name;
			this->token = token;
			this->life = life;
			this->breedingProb = breedingProb;
			this->illnessProb = illnessProb;
			this->lifeFactor = lifeFactor;
			this->x = x;
			this->y = y;
		}

		int getx(){
			return x;
		}

		int gety(){
			return y;
		}
		virtual int returnSize();
		virtual void Eaten(int LoseLife, int canClimb) ;
		virtual int breeding();
		virtual void changeLifeFactor();
		
		char returnToken(){
			return token;
		}

		string returnName(){
			return name;
		}

		void SetGrowthPeriod(int period){
			this->growthPeriod = period;
		}

		void SetBreedingPeriod(int period){
			this->breedingRepPeriod = period;
		}

		int GrowthPeriod(int dayOfYear){
			if(growthPeriod!=0 && dayOfYear%growthPeriod == 0){//its growthPeriod
				return 1;
			}else{
				return 0;
			}
		}

		int CheckLife(){
			if(life == 0){//it is dead;
				return 1;
			}else{
				return 0;
			}
		}

		int CheckBreedingPeriod(int dayOfYear){
			if(breedingRepPeriod != 0 && dayOfYear%breedingRepPeriod == 0){
				return 1;
			}else{
				return 0 ;
			}
		}
};

#endif