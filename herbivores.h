#ifndef HERBIVORES_H
#define HERBIVORES_H
#include "animals.h"
#include "carnivores.h"
#include "plants.h"
#include "seeded.h"
#include "seedless.h"
#include "tile.h"

class Plants;

#include <iostream>

using namespace std;

class Herbivores: public Animals{
	private:
		int canClimb;
		int neededFood;
		int count;
		int var; //be careful__ i had it STATIC

	public:
		Herbivores(string name,int size, int speed, int eatCount, int canClimb, int neededFood, int hibernates, int inHibernation): Animals(name,size, speed, eatCount, 'H', hibernates, inHibernation) {
			this->canClimb = canClimb;
			this->neededFood = neededFood;
			this->count = 1;
			this->var = 1;
			
		}
		

		int Eat(Plants& food){ // be careful here
			if(var >=7){//have to eat for 7 days
				if(food.CheckLife() == 0){
					if(name == "Deer"){
						if(food.returnToken() == 'G' || food.returnToken() == 'A'){
							int temp = 1;
							while(neededFood < eatenFood && temp <= eatCount){
								eatenFood ++;
								temp++;
							}
							food.Eaten(temp, canClimb);
							if(neededFood == eatenFood){
								var =1;
								isHungry = 0;
							}
							return 1;
						}else if(size >= food.returnSize() && size < (food.returnSize() +4)){
							int temp = 1;
							while(neededFood < eatenFood && temp <= eatCount){
								eatenFood ++;
								temp++;
							}
							food.Eaten(temp, canClimb);
							if(neededFood == eatenFood){
								var =1;
								isHungry =0;
							}
							return 1;
						}
						return 0;
					}else if(name == "Rabbit"){
						if(food.returnToken() == 'G' ){// dont eat algae
							int temp = 1;
							while(neededFood < eatenFood && temp <= eatCount){
								eatenFood ++;
								temp++;
							}
							food.Eaten(temp, canClimb);
							if(neededFood == eatenFood){
								var =1;
								isHungry = 0;
							}
							return 1;
						}else if(size >= food.returnSize()){
							int temp = 1;
							while(neededFood < eatenFood && temp <= eatCount){
								eatenFood ++;
								temp++;
							}
							food.Eaten(temp, canClimb);
							if(neededFood == eatenFood){
								var =1;
								isHungry = 0;
							}
							return 1;
						}
						return 0;
					}else if(name == "Grounghog"){
						if(food.returnToken() == 'G' ){// dont eat algae
							int temp = 1;
							while(neededFood < eatenFood && temp <= eatCount){
								eatenFood ++;
								temp++;
							}
							food.Eaten(temp, canClimb);
							if(neededFood == eatenFood){
								var =1;
								isHungry = 0;
							}
							return 1;
						}else if(size >= food.returnSize()){
							int temp = 1;
							while(neededFood < eatenFood && temp <= eatCount){
								eatenFood ++;
								temp++;
							}
							food.Eaten(temp, canClimb);
							if(neededFood == eatenFood){
								var =1;
								isHungry =0;
							}
							return 1;
						}
						return 0;
					}else{//Salmon
						if(food.returnToken() == 'A' ){//eat only algae
							int temp = 1;
							while(neededFood < eatenFood && temp <= eatCount){
								eatenFood ++;
								temp++;
							}
							food.Eaten(temp, canClimb);
							if(neededFood == eatenFood){
								var =1;
								isHungry =0;
							}
							return 1;
						}
						return 0;
					}
				}else{
					return 2;
				}
				hungerCount++;
			}else{
				var++;
				if(var == 10){
					killAnimal();
				}else if(var > 7){
					isHungry = 1;
				}
				return 1;
			}

			
		}

		void Move(int terrainSize, Tile** terrain){
			srand(time(NULL));
			int random_x = rand()%terrainSize;
			int random_y = rand()%terrainSize;
			if(name == "Deer"){
				this->x = random_x;
				this->y = random_y; 
			}else if(name == "Rabbit"){
				while((terrain[random_x][random_y]).returnGround() == '^'){
					random_x = rand()%terrainSize;
					random_y = rand()%terrainSize;
				}
				this->x = random_x;
				this->y = random_y;
			}else if(name == "Grounghog"){
				if(inHibernation == 0){//is not a hibernation period
					while((terrain[random_x][random_y]).returnGround() == '#'){
						random_x = rand()%terrainSize;
						random_y = rand()%terrainSize;
					}
					this->x = random_x;
					this->y = random_y;
				}
				
			}else{//salmon
				while((terrain[random_x][random_y]).returnGround() != '#'){
					random_x = rand()%terrainSize;
					random_y = rand()%terrainSize;
				}
				this->x = random_x;
				this->y = random_y;
			}
		}

		void Raise(){
			if(name == "Deer"){
					int charCount = 2;
					if(size < 5){
						size++;
					}
					while(charCount>0 && speed < 8){
						speed++;
						charCount--;
					}
					charCount = 2;
					while(charCount>0 && neededFood < 8){
						neededFood++;
						charCount--;
					}

				}else if( name == "Rabbit"){
					int charCount = 2;
					if(size < 2){
						size++;
					}
					while(charCount>0 && speed < 6){
						speed++;
						charCount--;
					}
					if(neededFood < 4){
						neededFood++;
					}
				}else if(name == "Grounghog"){
					if(size < 3){
						size++;
					}
					if(speed < 5){
						speed++;
					}
					if(neededFood < 5){
						neededFood++;
					}
				}
		}

};


#endif