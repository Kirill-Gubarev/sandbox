#include "GUI/list.h"

gui::GUI::List::List()
	:Element(), orientation(Mode::vertical) {

}
gui::GUI::List::List(Point2D size, uts::RGB color, Mode mode, Mode orientation)
	:Element(size, color, mode), orientation(orientation) {

}

void gui::GUI::List::updateChildLocation() {
	int numberElements = childs.size();

	Point2D elSize;
	Point2D offset;

	if (orientation == Mode::vertical) {
		offset.X = 0;
		offset.Y = size.height / static_cast<float>(numberElements);
		elSize.width = size.width;
		elSize.height = size.height / static_cast<float>(numberElements);
	}
	else {
		offset.X = size.width / static_cast<float>(numberElements);
		offset.Y = 0;
		elSize.width = size.width / static_cast<float>(numberElements);
		elSize.height = size.height;
	}
	for (size_t i = 0; i < numberElements; i++) {
		childs[i]->setLocation(offset * static_cast<float>(i) + pos, elSize);
		childs[i]->updateChildLocation();
	}
}