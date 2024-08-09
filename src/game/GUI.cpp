#include "game/GUI.h"
#include "game/sbWindow.h"


sb::GUI::Element* sb::GUI::ptr_element;

sb::GUI::Element::Element() :Element(1, 1, sb::RGB(255, 255, 255), Mode::fill) {}
sb::GUI::Element::Element(float width, float height, sb::RGB color, Mode mode)
	: color(color), mode(mode) {
	setLocation(0, 0, width, height);
}
sb::GUI::Element::~Element() {
	size_t count = childs.size();
	for (size_t i = 0; i < count; i++)
		delete childs[i];
}
sb::GUI::List::List(float width, float height, sb::RGB color, Mode mode, Mode orientation)
	:Element(width, height, color, mode), orientation(orientation) {}
void sb::GUI::Element::setLocation(float x, float y, float width, float height) {
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	vertices[0] = x;				vertices[1] = y;
	vertices[2] = x + width;		vertices[3] = y;
	vertices[4] = x + width;		vertices[5] = y + height;
	vertices[6] = x;				vertices[7] = y;
	vertices[8] = x;				vertices[9] = y + height;
	vertices[10] = x + width;		vertices[11] = y + height;
}
void sb::GUI::Element::updateChildSize() {
	for (auto& el : childs) {
		switch (el->mode) {
		case Mode::fill:
			el->setLocation(0, 0, width, height);
			break;

		default:
			throw std::exception("non-existent GUI element mode");
			break;
		}
	}
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
				static_cast<float>(i) * offsetX + x,
				static_cast<float>(i) * offsetY + y,
				elementsWidth, elementsHeight
			);
			childs[i]->updateChildSize();
	}
}


//managing this class
void sb::GUI::init() {
	ptr_element = new List(
		static_cast<float>(sb::SBWindow::getWidth()),
		static_cast<float>(sb::SBWindow::getHeight()),
		sb::RGB(0, 255, 0),
		Mode::fill,
		Mode::horizontal
	);
	ptr_element->childs.push_back(new Element(50, 50, sb::RGB(255, 0, 0), Mode::fill));
	ptr_element->childs.push_back(new List(50, 100, sb::RGB(0, 0, 255), Mode::fill, Mode::vertical));
	ptr_element->childs.push_back(new Element(40, 100, sb::RGB(255, 255, 0), Mode::fill));

	ptr_element->childs[1]->childs.push_back(new Element(40, 100, sb::RGB(255, 0, 155), Mode::fill));
	ptr_element->childs[1]->childs.push_back(new Element(40, 100, sb::RGB(0, 155, 255), Mode::fill));
	ptr_element->childs[1]->childs.push_back(new Element(40, 100, sb::RGB(129, 120, 255), Mode::fill));
	ptr_element->childs[1]->childs.push_back(new Element(40, 100, sb::RGB(255, 140, 135), Mode::fill));
	updateElementsSize();
}
void sb::GUI::terminate() {
	delete ptr_element;
}

void sb::GUI::updateElementsSize() {
	ptr_element->setLocation(0, 0,
		static_cast<float>(sb::SBWindow::getWidth()),
		static_cast<float>(sb::SBWindow::getHeight())
	);
	ptr_element->updateChildSize();
}
