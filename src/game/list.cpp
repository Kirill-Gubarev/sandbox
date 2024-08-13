#include "game/list.h"

sb::GUI::List::List()
	:Element(), orientation(Mode::vertical) {

}
sb::GUI::List::List(float width, float height, sb::RGB color, Mode mode, Mode orientation)
	:Element(width, height, color, mode), orientation(orientation) {

}

void sb::GUI::List::updateChildSize() {
	int numberElements = childs.size();
	float elementsWidth;
	float elementsHeight;
	float offsetX;
	float offsetY;
	if (orientation == Mode::vertical) {
		offsetX = 0;
		offsetY = height / numberElements;
		elementsWidth = width;
		elementsHeight = height / numberElements;
	}
	else {
		offsetX = width / numberElements;
		offsetY = 0;
		elementsWidth = width / numberElements;
		elementsHeight = height;
	}
	for (size_t i = 0; i < numberElements; i++) {
		childs[i]->setLocation(
			static_cast<float>(i) * offsetX + X,
			static_cast<float>(i) * offsetY + Y,
			elementsWidth, elementsHeight
		);
		childs[i]->updateChildSize();
	}
}