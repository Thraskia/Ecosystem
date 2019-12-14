#include <iostream>
#include "ecosystem.h"
#include "plants.h"
#include "seedless.h"
#include "seeded.h"

using namespace std;

int main(){
	Ecosystem ecosystem(5);
	ecosystem.MapGenerator(2, 2);
	ecosystem.RunEcosystem(2);
	return 0;
}