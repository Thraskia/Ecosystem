#ifndef ANIMALS_H
#define ANIMALS_H
//class Tile;
#include <iostream>
#include <string>


using namespace std;

class Animals{
	protected:
		string name;
		int size;
		int hungerCount;
		int eatenFood;
		int eatCount;
		int x;
		int y;
		int isAlive; //???
		int isHungry;
		int inHeat;
		int speed;
		int hibernates;
		int inHibernation;
		char token;
		int growthPeriod;
		int breedingRepPeriod;


	public:
		Animals(string name,int size, int speed, int eatCount, char token, int hibernates, int inHibernation){
			this->name = name;
			this->size = size;
			this->speed = speed;
			this->eatCount = eatCount;
			this->token = token;
			this->inHeat = 0;
			this->hibernates = hibernates;
			this->inHibernation = inHibernation;
			this->isHungry = 0;
			this->isAlive = 1;
			
		}

		virtual int returnDefence();

		void killAnimal(){
			isAlive = 0;
		}

		int CheckIfDead(){
			if(isAlive == 0){
				return 1;
			}else{
				return 0 ;
			}
		}

		char returnToken(){
			return token;
		}

		int returnSize(){
			return size;
		}

		int returnSpeed(){
			return speed;
		}

		string returnName(){
			return name;
		}

		int returnInHibernation(){
			return inHibernation;
		}

		void putInHibernation(){
			inHibernation = 1;
		}

		void Place(int i, int j){
			this->x = i;
			this->y = j;
		}

		void SetGrowthPeriod(int period){
			this->growthPeriod = period;
		}

		void SetBreedingPeriod(int period1, int period2){
			if(token == 'H'){
				this->breedingRepPeriod = period1;
			}else{
				this->breedingRepPeriod = period2;
			}
		}

		virtual int Eat();
		
		virtual void Move(int terrainSize, Tile** terrain) ;

		virtual void Raise();

		void ResetHungry(){
			isHungry = 1;

		}

		int GrowthPeriod(int dayOfYear){
			if( dayOfYear%growthPeriod == 0){ //its growthPeriod
				return 1;
			}else{
				return 0;
			}
		}

		void IncreaseHunger(){
			hungerCount++;
		}

		int CheckHunger(){
			if(hungerCount >= 10){ //if must to  die
				return 1;
			}else{
				return 0;
			}
		}

		int CheckBreedingPeriod(int dayOfYear){
			if(dayOfYear%breedingRepPeriod == 0){
				return 1;
			}else{
				return 0 ;
			}
		}

		virtual ~Animals(){

		}
	
};

#endif