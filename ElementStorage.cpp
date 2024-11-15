#include "ElementStorage.h"
Position* ElementStorage::getPosition() {
	if(objectPT == nullptr) {
		objectPT = new Position();
	}
	return objectPT;
}

Velocity* ElementStorage::getVelocity() {
	if (objectV == nullptr) {
		objectV = new Velocity();
	}
	return objectV;      
}

Position* Effect::getEnd() {
	if(ptEnd == nullptr) {
		ptEnd = new Position();
	}
	return ptEnd;
}


