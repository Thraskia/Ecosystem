#ifndef ECOSYSTEM_H
#define ECOSYSTEM_H

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <vector>
#include "tile.h"
#include "plants.h"
#include "animals.h"
#include "herbivores.h"
#include "carnivores.h"
#include "seeded.h"
#include "seedless.h"
class Tile;
using namespace std;

class Ecosystem{
	private:
		Tile** terrain;
		int terrainSize;//platos
		int dayOfYear;
		int factor;
		string season;
	public:
		Ecosystem(int terrainSize){
			this->dayOfYear = 0;
			this->terrainSize = terrainSize;
			terrain = new Tile*[terrainSize];
			for(int i = 0; i < terrainSize; i++){
				terrain[i] = new Tile[terrainSize];
			}			

		}

		void GenerateRiver(){
			srand(time(NULL));
			int random = rand()%terrainSize; //prosoxh me to +-1
			(terrain[0][random])->placeGround("#");
			int N=1;
			while(N<terrainSize){//be careful these ++ may be out of range
				int possibility = rand()%10;
				if(possibility<=3){//one right 
					random++;
					if(random<terrainSize){
						(terrain[N][random])->placeGround("#");
						N++;
					}else{
						random--;
						
					}
					
				}else if(possibility<=6){//one left
					random--;
					if(random>=0 && random<terrainSize){
						(terrain[N][random])->placeGround("#");
						N++;
					}else{
						random++;
					}
				}else if(possibility<=9){//two right
					random +=2;
					if(random<terrainSize){
						(terrain[N][random-1])->placeGround("#");
						(terrain[N][random])->placeGround("#");
						N++;
					}else{
						random -= 2;
					}
					
				}else{//two left
					random -= 2;
					if(random>= 0 && random<terrainSize){
						(terrain[N][random+1])->placeGround("#");
						(terrain[N][random])->placeGround("#");
						N++;
					}else{
						random += 2;
					}
					
				}
			}
			for(int i =0; i< 2; i++){
				for(int j= 0; j<5; j++){
					if((terrain[i][j])->returnGround() == "#"){
						cout << "r";
					}else{
						cout << "_";
					}
				}
				cout << endl;
			}
		}

		void GenerateLake(int lakeSize){
			srand(time(NULL));
			int random_x = rand()%terrainSize;
			int random_y = rand()%terrainSize;
			cout << "lake's location is: (" << random_x << " , " << random_y << ")" << endl;
			int max_i = random_x + lakeSize - 1;
			if(max_i >= terrainSize ){
				max_i = terrainSize-1;
			}
			int max_j = random_y + lakeSize - 1;
			if(max_j >= terrainSize){
				max_j = terrainSize-1;
			}
			cout << "max_i is: " << max_i << " max_j is: " << max_j << endl;
			for(int i = random_x; i<= max_i; i++){
				for(int j = random_y; j<= max_j; j++){
					(terrain[i][j])->placeGround("#");
				}
			}
			for(int i =0; i< 2; i++){
				for(int j= 0; j<5; j++){
					if((terrain[i][j])->returnGround() == "#"){
						cout << "#";
					}else{
						cout << "_";
					}
				}
				cout << endl;
			}

		}

		void GenerateHills(int noHills=2){
			srand(time(NULL));
			int hillSize = rand()%4 + 2;
			for(int k=1; k<=noHills; k++){
				int random_x = rand()%terrainSize;
				int random_y = rand()%terrainSize;
				while((terrain[random_x][random_y])->returnGround() == "#"){
					random_x = rand()%terrainSize;
					random_y = rand()%terrainSize;
				}
				cout << "hill's location is: (" << random_x << " , " << random_y << ")" << endl;
				int max_i = random_x + hillSize - 1;
				if(max_i >= terrainSize ){
					max_i = terrainSize-1;
				}
				int max_j = random_y + hillSize - 1;
				if(max_j >= terrainSize){
					max_j = terrainSize-1;
				}
				cout << "max_i is: " << max_i << " max_j is: " << max_j << endl;
				for(int i = random_x; i<= max_i; i++){
					for(int j = random_y; j<= max_j; j++){
						if((terrain[i][j])->returnGround() != "#"){
							(terrain[i][j])->placeGround("^");
						}
					}
				}
			}	
		}

		void GenerateMeadow(){
			for (int i = 0; i < terrainSize ; i++){
				for(int j = 0; j < terrainSize; j++){
					if((terrain[i][j])->returnGround() != "#" && (terrain[i][j])->returnGround() != "^"){
						(terrain[i][j])->placeGround('"');
					}
				}
			}
		}

		void MapGenerator(int lakeSize, int noHills){
			GenerateRiver();
			GenerateLake(lakeSize);
			GenerateHills(noHills);
			GenerateMeadow();
		}

		void PlacePlants(){
			srand(time(NULL)); 
			for(int i=0; i < terrainSize; i++){
				for(int j = 0; j < terrainSize; j++){
					int random = rand()%100 + 1;
					int create = rand()%2;
					if(create == 1){//place plant in this specific tile
						if((terrain[i][j])->returnGround() == "#"){
							Seedless* algae = new Seedless("Algae", 'A', 5, 25, 25, 2, i, j);
							(terrain[i][j])->placeNewPlant(algae);
						}else if( terrain[i][j] == "^"){
							if(random%2 == 0){
								Seeded* pine = new Seeded("Pine", 'P', 15, 15, 20, 40, 20, 5, i, j);
								(terrain[i][j])->placeNewPlant(pine);
							}else{
								Seeded* maple = new Seeded("Maple", 'M', 5, 5, 10, 20, 10, 2, i, j);
								(terrain[i][j])->placeNewPlant(maple);
							}
						}else{
							if(random<=35){
								Seedless* grass =  new Seedless("Grass", 'G', 5, 15, 15, 4, i, j);
								(terrain[i][j])->placeNewPlant(grass);
							}else if(random <= 70){
								Seeded* oak = new Seeded("Oak", 'O', 20, 20, 15, 30, 15, 5, i, j);
								(terrain[i][j])->placeNewPlant(oak);
							}else{
								Seeded* maple = new Seeded("Maple", 'M', 5, 5, 10, 20, 10, 2, i, j);
								(terrain[i][j])->placeNewPlant(maple);
							}
						}
					}
					
				}
			}

		}

		void PlaceAnimals(){
			srand(time(NULL)); 
			Herbivores* Salmon;
			Herbivores* Deer;
			Herbivores* Rabbit;
			Herbivores* Groundhog;
			Carnivores* Fox;
			Carnivores* Wolf;
			Carnivores* Bear;
			for(int i=0; i < terrainSize; i++){
				for(int j = 0; j < terrainSize; j++){
					int r = rand()%10 + 1;
					for(int k=1; k<= r; k++){//k-sum of animals
						int random = rand()%100 + 1;
						if((terrain[i][j])->returnGround() == "#"){//water
							Salmon = new Herbivores("Salmon", 1, 5, 1, 0, 1, 0, 0);
							Salmon->Place(i, j);
							(terrain[i][j])->placeNewAnimal(Salmon);
						}else if( (terrain[i][j])->returnGround() == "^"){//mountain
							if(random%2 == 0){
								Bear =  new Carnivores("Bear", 10, 4, 10, 10, 10, 0, 1);
								Bear->Place(i, j);
								(terrain[i][j])->placeNewAnimal(Bear);
							}else{
								Wolf = new Carnivores("Wolf", 7, 8, 8, 8, 6, 0, 0);
								Wolf->Place(i, j);
								(terrain[i][j])->placeNewAnimal(Wolf);
							}
						}else{ //pediada
							if(random <= 20){
								Deer = new Herbivores("Deer", 5, 8, 20, 8, 0, 0);
								Deer->Place(i, j);
								(terrain[i][j])->placeNewAnimal(Deer);
							}else if(random <= 40){
								Rabbit = new Herbivores("Rabbit", 2, 6, 1, 0, 4, 0, 0);
								Rabbit->Place(i, j);
								(terrain[i][j])->placeNewAnimal(Rabbit);
							}else if(random <= 60){
								Groundhog = new Herbivores("Groundhog", 3, 5, 1, 1, 5, 1, 0);
								Groundhog->Place(i, j);
								(terrain[i][j])->placeNewAnimal(Groundhog);
							}else if(random <= 80){
								Fox = new Carnivores("Fox", 4, 6, 6, 5, 5, 0, 0);
								Fox->Place(i, j);
								(terrain[i][j])->placeNewAnimal(Fox);
							}else{
								Wolf = new Carnivores("Wolf", 7, 8, 8, 8, 6, 0, 0);
								Wolf->Place(i, j);
								(terrain[i][j])->placeNewAnimal(Wolf);
							}
						}
					}
				}
			}
		}

		void ChangeGrowthPeriod(){
			for(int i=0; i< terrainSize; i++){
				for(int j=0; j<terrainSize; j++){
					(terrain[i][j])->SetGrowthPeriod(season);

				}
			}
			
		}

		void ChangeBreedingPeriod(){
			for(int i=0; i< terrainSize; i++){
				for(int j=0; j<terrainSize; j++){
					(terrain[i][j])->SetBreedingPeriod(season);

				}
			}
		}

		void ApplySeason(){
			if(dayOfYear<=90){
				season = "winter";
			}else if(dayOfYear <= 180){
				season = "spring";
			}else if(dayOfYear <= 270){
				season = "summer";
			}else{
				season = "autumn";
			}
		}

		void DailyReset(){
			dayOfYear++;
			for(int i = 0; i<terrainSize; i++){
				for(int j = 0; j<terrainSize; j++){
					(terrain[i][j])->Reset();
				}
			}
		}

		void AnimalMovement(){
			for(int i = 0; i < terrainSize; i++){
				for(int j = 0; j < terrainSize; j++){
					(terrain[i][j])->MoveAnimals(terrain, terrainSize);
				}
			}
		}

		void AnimalEating(){
			for(int i = 0; i < terrainSize; i++){
				for(int j =0; j < terrainSize; j++){
					(terrain[i][j])->AnimalEating(terrain, terrainSize);
				}
			}
		}

		void CheckDeadEntities(){
			for(int i = 0; i < terrainSize; i++){
				for(int j =0; j <terrainSize; j++){
					(terrain[i][j])->CheckDeadEntities();
				}
			}
		}

		void AnimalBreeding(){
			for(int i = 0; i < terrainSize; i++){
				for(int j =0; j < terrainSize; j++){
					(terrain[i][j])->AnimalBreeding(dayOfYear);
				}
			}
		}

		void PlantBreeding(){
			for(int i = 0; i < terrainSize; i++){
				for(int j =0; j < terrainSize; j++){
					(terrain[i][j])->PlantBreeding(dayOfYear,terrainSize, terrain, season);
				}
			}
			
		}

		void PrintSystem(){

		}

		void PrintAnimalStatistics(){

		}

		void PrintPlantStatistics(){

		}

		void RunEcosystem(int simulationDays){
			//dayOfYear = O;
			season = "winter";
			ChangeGrowthPeriod();
			ChangeBreedingPeriod();
			while(dayOfYear <= simulationDays){
				DailyReset();
				for(int i  = 1; i <= 24; i++){
					AnimalMovement();
					AnimalEating();
				}
				CheckDeadEntities();
				AnimalBreeding();
				PlantBreeding();
				
				if(dayOfYear%90 == 0){
					ApplySeason();
					ChangeGrowthPeriod();
					ChangeBreedingPeriod();
					PrintSystem();
					PrintAnimalStatistics();
					PrintPlantStatistics();
				}
			}
			PrintSystem();
			PrintAnimalStatistics();
			PrintPlantStatistics();
		}

};

#endif