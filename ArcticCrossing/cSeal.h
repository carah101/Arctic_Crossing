/*
== == == == == == == == =
cRocket.h
- Header file for class definition - SPECIFICATION
- Header file for the Rocket class which is a child of cSprite class
== == == == == == == == =
*/
#ifndef _CSEAL_H
#define _CSEAL_H
#include "cSprite.h"

class cRocket : public cSprite
{
private:
	SDL_Point sealMotion;

	
public:
	void initialise();
	void render();		// Default render function
	void update(float deltaTime);		// Seal update method
	void setSealMotion(SDL_Point sealMotion);   //sets the distance moved by the seal
	SDL_Point getSealMotion();				 // sets the distance moved by the seal
};
#endif