#ifndef CARNIVORES_H
#define CARNIVORES_H
#include "animals.h"
#include "tile.h"


#include <iostream>

using namespace std;

class Carnivores: public Animals{
	private:
		int attack;
		int defence;
	public:
		Carnivores(string name,int size, int speed, int eatCount, int attack, int defence,  int hibernates, int inHibernation): Animals(name,size, speed, eatCount, 'C', hibernates, inHibernation){
			this->attack = attack;
			this->defence = defence;
		}

		int returnDefence(){
			return defence;
		}

		int Eat(Animals* food){
			if(food->CheckIfDead() == 0){//is Alive
				if(hungerCount <8){
					if(name == "Fox" && name == "Wolf"){
						if(food->returnToken() == 'H'){
							if(food->returnSize() <= size && food->returnSpeed() <= speed && food->returnName()!= "Salmon"){
								isHungry = 0;
								food->killAnimal();
								hungerCount = 0;
								return 1;
							}
						}else{
							return 0;
							/*if((food.returnSize() < size) || (food.returnSize() == size && attack > food.returnDefence())){
								isHungry = 0;
								food->killAnimal();
								hungerCount = 0;
								return 1;
							}**/
						}
					}else{//Bear
						if(food->returnName()!= "Bear" && food->returnToken() == 'H' &&  inHibernation==0){
							isHungry = 0;
							food->killAnimal();
							hungerCount = 0;
							return 1;
						}else{
							return 0;
						}
					}
				}else if(hungerCount == 8){//can it both herbivores/carnivores
					if(name == "Fox" && name == "Wolf"){
						if(food->returnToken() == 'H'){
							if(food->returnSize() <= size && food->returnSpeed() <= speed && food->returnName()!= "Salmon"){
								isHungry = 0;
								food->killAnimal();
								hungerCount = 0;
								return 1;
							}else{
								return 0;
							}
						}else{
							if((food->returnSize() < size) || (food->returnSize() == size && attack > food->returnDefence())){
								isHungry = 0;
								food->killAnimal();
								hungerCount = 0;
								return 1;
							}else{
								return 0;
							}
						}
					}else{//Bear
						if(food->returnName()!= "Bear" && inHibernation==0){
							isHungry = 0;
							food->killAnimal();
							hungerCount = 0;
							return 1;
						}else{
							return 0;
						}
					}
				}else{
					killAnimal();
					return 2;
				}
			}else{
				return 2;
			}
		
		}

		void Move(int terrainSize, Tile** terrain){
			srand(time(NULL));
			if(name=="Bear"){
				if(inHibernation==0){
					int random_x = rand()%terrainSize;
					int random_y = rand()%terrainSize;
					this->x = random_x;
					this->y = random_y; 
				}else{
					cout << "Its a hibernation period for bear" << endl;
				}
			}else{
				int random_x = rand()%terrainSize;
				int random_y = rand()%terrainSize;
				this->x = random_x;
				this->y = random_y;
			}
		}

		void Raise(){
			if(name == "Fox"){
					if(size < 4){
						size++;
					}
					if(attack < 5){
						attack++;
					}
					if(defence < 5){// be careful
						defence++;
					}
					if(speed < 6){
						speed++;
					}
					if(eatCount < 6){
						eatCount++;
					}
				}else if(name == "Bear"){
					int charCount = 2;
					while(charCount>0 && size < 10){
						size++;
						charCount--;
					}
					charCount = 2;
					while(charCount>0 && attack < 10){
						attack++;
						charCount--;
					}
					charCount = 2;
					while(charCount>0 && defence < 10){// be careful
						defence++;
						charCount--;
					}
					charCount = 2;
					while(charCount>0 && eatCount < 10){
						eatCount++;
						charCount--;
					}
				}else if(name == "Wolf"){
					if(size < 7){
						size++;
					}
					int charCount = 2;
					while(charCount>0 && attack < 8){
						attack++;
						charCount--;
					}
					charCount = 2;
					while(charCount>0 && defence < 6){// be careful
						defence++;
						charCount--;
					}
					charCount = 2;
					if(charCount>0 && speed < 8){
						speed++;
						charCount--;
					}
					charCount = 2;
					while(charCount>0 && eatCount < 8){
						eatCount++;
						charCount--;
					}
				}
		}
};

#endif