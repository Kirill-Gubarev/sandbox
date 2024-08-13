#include "element.h"

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
void sb::GUI::Element::setLocation(float x, float y, float width, float height) {
	this->X = x;
	this->Y = y;
	this->width = width;
	this->height = height;
	vertices[0] = x;				vertices[1] = y;
	vertices[2] = x + width;		vertices[3] = y;
	vertices[4] = x + width;		vertices[5] = y + height;
	vertices[6] = x;				vertices[7] = y;
	vertices[8] = x;				vertices[9] = y + height;
	vertices[10] = x + width;		vertices[11] = y + height;
}

const float* sb::GUI::Element::getVertices() const {
	return vertices;
}
const sb::RGB sb::GUI::Element::getColor() const {
	return color;
}
const std::vector<sb::GUI::Element*>& sb::GUI::Element::getChilds() const {
	return childs;
}
sb::GUI::Element& sb::GUI::Element::operator[](size_t index) const {
	return *childs[index];
}

void sb::GUI::Element::mouseAction(float x, float y, MouseButton button, MouseAction action)const {
	for (auto& el : childs) {
		if (el->isInside(x, y)) {
			el->mouseAction(x, y, button, action);
			return;
		}
	}
}

const bool sb::GUI::Element::isInside(float x, float y) const {
	return (x >= X && y >= Y) && (x < X + width && y < Y + height);
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
void sb::GUI::Element::addChild(Element* ptr_element) {
	childs.push_back(ptr_element);
}