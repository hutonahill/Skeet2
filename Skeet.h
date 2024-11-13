/***********************************************************************
* Header File:
 *    SKEET
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The game class
 ************************************************************************/

#pragma once

#include "position.h"
#include "uiInteract.h"
#include "bird.h"

#include "time.h"

#include "Interface.h"
#include "InterfaceLogicFactory.h"
#include "SkeetLogic.h"

#include <list>

/*************************************************************************
 * Skeet2
 * The game class
 *************************************************************************/
class Skeet
{
public:
	Skeet(Position & dimensions) : dimensions(dimensions) 
	{
		Interface* inter = new Interface();
		SkeetLogic* skeetLogic = new SkeetLogic();

		interface = InterfaceLogicFactory::create(inter, skeetLogic);

	}

	// handle all user input
	void interact(const UserInput& ui);

	// move the gameplay by one unit of time
	void animate();

	// output everything on the screen
	void drawLevel()  const;    // output the game
	void drawStatus() const;    // output the status information

	// is the game currently playing right now?
	bool isPlaying() const { return interface->isPlaying();  }
private:

	Interface* interface;
	Position dimensions;           // size of the screen
};
