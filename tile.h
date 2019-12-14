#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <vector>
#include <string>
#include "plants.h"
#include "seeded.h"
#include "seedless.h"
#include "animals.h"
#include "herbivores.h"
#include "carnivores.h"

using namespace std;

class Tile{
	private:
		vector<Animals*> animals;
		Plants* plant;
		int placePlant;
		char ground;
	public:
		Tile(){
			placePlant = 0;
		}

		Plants* returnPlant(){
			return plant;
		}

		int returnplacePlant(){
			if(placePlant == 1){
				return 1;
			}else{
				return 0;
			}
		}

		char returnGround(){
			return ground;
		}

		void placeGround(char ground){
			this->ground = ground;
		}

		void placeNewPlant(Plants* p){
			this->plant = p;
			placePlant = 1;
		}

		void placeNewAnimal(Animals* anim){
			animals.push_back(anim);
		}

		void SetGrowthPeriod(string season){
			if(season == "winter"){
				for(int i=0; i< animals.size(); i++){
					(animals[i])->SetGrowthPeriod(30);
				}
				if(placePlant == 1){
					plant->SetGrowthPeriod(10);
				}
			}else if(season == "spring"){
				for(int i=0; i< animals.size(); i++){
					(animals[i])->SetGrowthPeriod(20);
				}
				if(placePlant == 1){
					plant->SetGrowthPeriod(5);
				}
			}else if(season == "summer"){
				for(int i=0; i< animals.size(); i++){
					(animals[i])->SetGrowthPeriod(30);
				}
				if(placePlant == 1){
					plant->SetGrowthPeriod(10);
				}
			}else{
				for(int i=0; i< animals.size(); i++){
					(animals[i])->SetGrowthPeriod(15);
				}
				if(placePlant == 1){
					plant->SetGrowthPeriod(0);
				}
			}
		}

		void SetBreedingPeriod(string season){
			if(season == "winter"){
				for(int i=0; i< animals.size(); i++){
					(animals[i])->SetBreedingPeriod(18, 10);
				}
				if(placePlant == 1){
					plant->SetBreedingPeriod(0);
				}
			}else if(season == "spring"){
				for(int i=0; i< animals.size(); i++){
					(animals[i])->SetBreedingPeriod(12, 11);
				}
				if(placePlant == 1){
					plant->SetBreedingPeriod(10);
				}
			}else if(season == "summer"){
				for(int i=0; i< animals.size(); i++){
					(animals[i])->SetBreedingPeriod(8, 9);
				}
				if(placePlant == 1){
					plant->SetBreedingPeriod(10);
				}
			}else{
				for(int i=0; i< animals.size(); i++){
					(animals[i])->SetBreedingPeriod(5, 9);
				}
				if(placePlant == 1){
					plant->SetBreedingPeriod(20);
				}
			}
		}

		void Reset(int dayOfYear){
			for(int i = 0; i < animals.size(); i++){
				animals[i]->ResetHungry();
				if((animals[i])->GrowthPeriod(dayOfYear) == 1){
					(animals[i])->Raise();
				}
			}
			if(placePlant == 1){
				if(plant->GrowthPeriod(dayOfYear) == 1){
					plant->changeLifeFactor();//plant is growing
				}
			}
		}

		void MoveAnimals(Tile** terrain, int terrainSize){
			for(int i=0; i< animals.size(); i++){
				animals[i]->Move(terrainSize, terrain);
			}
		}

		void AnimalEating(Tile** terrain, int terrainSize){
			for(int i=0; i< animals.size(); i++){
				if(animals[i]->CheckIfDead() == 0){
					if(animals[i]->returnToken() == 'H'){//herbivore
						if(placePlant == 1 && animals[i]->Eat(plant) != 1){//dead plant or non-type of food that can eat
							//pairnw 1 otan faei or otan var==7
							for(int k = 0; k < terrainSize; k++){
								for(int l = 0; l < terrainSize; l++){
									if(placePlant == 1 && animals[i]->Eat(terrain[k][l]->returnPlant()) == 1){//have eat
										terrain[k][l]->placeNewAnimal(animals[i]);
										animals[i]->Place(k,l);
										animals.erase(i);
										break;
									}
								}
							}
							//look for food
						}
					}else{//carnivore
						int j=0;
						int keep;
						while(i!=j && j<animals.size() && (keep = animals[i]->Eat(animals[j])) == 0){
							j++;
						}
						if(j == animals.size() && keep ==0){
							animals[i]->IncreaseHunger();
						}
					}
				}
				
			}
		}

		void CheckDeadEntities(){
			int i=0;
			while(i < animals.size()){
				if((animals[i])->CheckHunger() == 1 || ((animals[i])->CheckIfDead()) == 1){
					animals.erase(i);
				}else{
					i++;
				}
			}
			if(placePlant == 1){
				if(plant->CheckLife() == 1){
					placePlant = 0;
					delete plant;
				}
			}
		}

		void AnimalBreeding(int dayOfYear){
			for(int i=0; i< animals.size(); i++){
				if((animals[i])->CheckBreedingPeriod(dayOfYear) == 1){ //SPECIFIC OBJECT
					if((animals[i])->returnToken() == 'H'){
						if((animals[i])->returnName() == "Deer"){
							Herbivores* new_animal = new Herbivores("Deer", 2, 4, 2, 0, 4, 0, 0);
							animals.push_back(new_animal);
						}else if((animals[i])->returnName() == "Rabbit"){
							Herbivores* new_animal = new Herbivores("Rabbit", 1, 2, 1, 0, 2, 0, 0);
							animals.push_back(new_animal);
						}else if((animals[i])->returnName() == "Groundhog" && (animals[i])->returnInHibernation() == 0){
							Herbivores* new_animal = new Herbivores("Groundhog", 2, 3, 1, 1, 3, 1, 0);
							animals.push_back(new_animal);
						}else{//salmon
							Herbivores* new_animal = new Herbivores("Salmon", 1, 5, 1, 0, 1, 0, 0);
							animals.push_back(new_animal);
						}
						
					}else{
						if((animals[i])->returnName() == "Fox"){
							Carnivores* new_animal = new Carnivores("Fox", 1, 1, 2, 1, 1, 0, 0);
							animals.push_back(new_animal);
						}else if((animals[i])->returnName() == "Wolf"){
							Carnivores* new_animal = new Carnivores("Wolf", 1, 2, 2, 2, 2, 0, 0);
							animals.push_back(new_animal);
						}else{//Bear
							if((animals[i])->returnInHibernation() == 0){
								Carnivores* new_animal = new Carnivores("Bear", 3, 4, 5, 6, 6, 1, 0);
								animals.push_back(new_animal);
							}
						}
						
					}
				}
			}
		}

		void PlantBreeding(int dayOfYear, int terrainSize, Tile** terrain, string season){
			srand(time(NULL));
			if(placePlant == 1){
				if(plant->CheckBreedingPeriod(dayOfYear) == 1){
					if(season != "winter"){
						int random_x = rand()%terrainSize;
						int random_y = rand()%terrainSize;
						if((terrain[random_x][random_y]).returnplacePlant() == 0){//there isnt a plant in this specific tile
							if(plant->returnName() == "Grass"){
								if(((terrain[random_x][random_y]).returnGround() == '"') && (plant->breeding() == 1)){
									Seedless* newplant = new Seedless("Grass", 'G', 5, 15, 15, 4, random_x, random_y);
									(terrain[random_x][random_y])->placeNewPlant(newplant);
								}
							}else if(plant->returnName() == "Algae"){
								if(((terrain[random_x][random_y])->returnGround() == '#') && (plant->breeding() == 1)){
									Seedless* newplant = new Seedless("Algae", 'A', 5, 25, 25, 2, random_x, random_y);
									(terrain[random_x][random_y])->placeNewPlant(newplant);
								}
							}else if(plant->returnName() == "Maple"){
								if(((terrain[random_x][random_y])->returnGround() == '"') || ((terrain[random_x][random_y])->returnGround() == '^')) && (plant->breeding() == 1){
									Seeded* newplant = new Seeded("Maple", 'M', 5, 5, 10, 20, 10, 2, random_x, random_y);
									(terrain[random_x][random_y])->placeNewPlant(newplant);
								}
							}else if(plant->returnName() == "Oak"){
								if(((terrain[random_x][random_y])->returnGround() == '"') && (plant->breeding() == 1)){
									Seeded* newplant = new Seeded("Oak", 'O', 20, 20, 15, 30, 15, 5, random_x, random_y);
									(terrain[random_x][random_y]).placeNewPlant(newplant);
								}
							}else{//pine
								if(((terrain[random_x][random_y])->returnGround() == '^') && (plant->breeding() == 1)){
									Seeded* newplant = new Seeded("Pine", 'P', 15, 15, 20, 40, 20, 5, random_x, random_y);
									(terrain[random_x][random_y])->placeNewPlant(newplant);
								}
							}
						}	
					}
				}
			}
		}
};

#endif