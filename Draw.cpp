#include "Draw.h"

#include <cassert>

#include "Element.h"

#include <cassert>
#include "bird.h"




void Draw::drawAll(){
	for (tuple<drawMethod, Element*> element : elementsToDraw) {
		get<0>(element)(get<1>(element));
	}
	elementsToDraw.clear();
}

void Draw::add(drawMethod method, Element* element) {
	elementsToDraw.emplace_back(method, element);
}





