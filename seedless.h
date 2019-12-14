#ifndef SEEDLESS_H
#define SEEDLESS_H
#include "plants.h"
#include "tile.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

class Seedless: public Plants{

	public:
		Seedless(string name, char token, int life, int breedingProb, int illnessProb, int lifeFactor, int x, int y): Plants(name, token, life, breedingProb, illnessProb, lifeFactor, x, y){
		}

		void Eaten(int LoseLife, int canClimb){
			while(life>0 && LoseLife>0){
				life--;
				LoseLife--;
			}
			cout << "The plant was eaten by an animal. New life is: " << life << endl;
		}

		void changeLifeFactor(){
			srand(time(NULL));
			int random = rand()%101;
			if(random <= illnessProb){
				if(life-lifeFactor > 0){
					life -= lifeFactor;
				}else{
					life = 0;
				}
				cout << "The plant cannot grow up due to illness. New life is: " << life << endl;
			}else{
				life += lifeFactor;
				cout << "The plant grows up. New life is: " << life << endl;
			}
		}

		int breeding(){
			srand(time(NULL));
			int random = random%101;
			if(random <= breedingProb){
				life -= lifeFactor;
				cout << "The plant cannot be reproduced due to illness. New life is: " << life << endl;
				return 0;
			}else{
				life += lifeFactor;
				cout << "The plant reproduced. New life is: " << life << endl;
				return 1;
			}
		}

};

#endif 