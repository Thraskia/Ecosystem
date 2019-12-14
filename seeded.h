#ifndef SEEDED_H
#define SEEDED_H
#include "plants.h"
#include "tile.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

class Seeded: public Plants{
	private:
		int foliage;
		int seeds;
		int size;

	public:
		Seeded(string name, char token, int breedingProb, int illnessProb, int lifeFactor, int foliage, int seeds, int size, int x, int y): Plants(name, token, foliage, breedingProb, illnessProb, lifeFactor, x, y){
			this->foliage = foliage;
			this->seeds = seeds;
			this->size = size;
			
		}

		int returnSize(){
			return size;
		}

		void Eaten(int LoseLife, int canClimb){
			if(canClimb == 1){
				while(seeds>0 && LoseLife>0){
					seeds--;
					LoseLife--;
				}
				if(LoseLife>0){
					while(foliage>0 && LoseLife>0){
						foliage--;
						LoseLife--;
						life--;
					}
				}
			}else{
				while(foliage>0 && LoseLife>0){
					foliage--;
					LoseLife--;
					life--;
				}
			}
			cout << "The plant was eaten by an animal. New life is: " << life << " foliage is: " << foliage << " seeds are: " << seeds << endl;
		}

		void changeLifeFactor(){
			srand(time(NULL));
			int random = rand()%101;
			if(random <= illnessProb){
				foliage -= lifeFactor;
				life -= lifeFactor;
				seeds = seeds - (2*lifeFactor);
				if(size > 0){
					size--;
				}
				cout << "The plant cannot grow up due to illness. New life is: " << life << endl;
			}else{
				foliage += lifeFactor;
				life += lifeFactor;
				seeds = seeds + (2*lifeFactor);
				size++;
				cout << "The plant grows up. New life is: " << life << endl;
			}
		}

		int breeding(){
			srand(time(NULL));
			int random = random%101;
			if(random <= breedingProb){
				seeds = 0;
				if(foliage-lifeFactor > 0){
					foliage -= lifeFactor;
					life -= lifeFactor;
				}else{
					foliage = 0;
					life = 0;
				}
				if(size>0){
					size--;
				}
				cout << "The plant cannot be reproduced due to illness. New life is: " << life << endl;
				return 0;
			}else{
				foliage += lifeFactor;
				size++;
				life += lifeFactor;
				cout << "The plant reproduced. New life is: " << life << endl;
				return 1;
			}
		}

};

#endif