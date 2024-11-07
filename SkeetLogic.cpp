#include "SkeetLogic.h"

#include "Interface.h"
#include "Storage.h"

SkeetLogic::SkeetLogic(Interface* skeetInterface) {
	SkeetInterface = skeetInterface;
	SkeetStorage = new Storage();
}
