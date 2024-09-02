#include "GUI/element.h"

gui::GUI::Element::Element() :Element(Point2D(1, 1), uts::RGB(255, 255, 255), Mode::fill) {}
gui::GUI::Element::Element(Point2D size, uts::RGB color, Mode mode)
	: color(color), mode(mode) {
	clearMinMax();
	setLocation(Point2D(0, 0), size);
}
gui::GUI::Element::~Element() {
	size_t count = childs.size();
	for (size_t i = 0; i < count; i++)
		delete childs[i];
	childs.clear();
}

gui::GUI::Element* gui::GUI::Element::setLocation(Point2D newPos, Point2D newSize) {
	pos.X = newPos.X;
	pos.Y = newPos.Y;
	setSize(newSize.width, newSize.height);
	vertices[0] = pos.X;				vertices[1] = pos.Y;
	vertices[2] = pos.X + size.width;	vertices[3] = pos.Y;
	vertices[4] = pos.X + size.width;	vertices[5] = pos.Y + size.height;
	vertices[6] = pos.X;				vertices[7] = pos.Y;
	vertices[8] = pos.X;				vertices[9] = pos.Y + size.height;
	vertices[10] = pos.X + size.width;	vertices[11] = pos.Y + size.height;
	return this;
}

gui::GUI::Element* gui::GUI::Element::setSize(float width, float height) {
	//the values should not exceed the limits of min max
	size.width = std::clamp(width, min.width, max.width);
	size.height = std::clamp(height, min.height, max.height);
	return this;
}

gui::GUI::Element* gui::GUI::Element::setMinMax(float minWidth, float maxWidth, float minHeight, float maxHeight) {
	setMinWidth(minWidth);
	setMaxWidth(maxWidth);
	setMinHeight(minHeight);
	setMaxHeight(maxHeight);
	return this;
}
gui::GUI::Element* gui::GUI::Element::setMinWidth(float width) {
	if (width >= 0)
		min.width = std::min(width, max.width);
	return this;
}
gui::GUI::Element* gui::GUI::Element::setMaxWidth(float width) {
	if (width >= 0)
		max.width = std::max(width, min.width);
	return this;
}
gui::GUI::Element* gui::GUI::Element::setMinHeight(float height) {
	if (height >= 0)
		min.height = std::min(height, max.height);
	return this;
}
gui::GUI::Element* gui::GUI::Element::setMaxHeight(float height) {
	if (height >= 0)
		max.height = std::max(height, min.height);
	return this;
}
gui::GUI::Element* gui::GUI::Element::clearMinMax() {
	min.width = 0;
	max.width = std::numeric_limits<float>::infinity();
	min.height = 0;
	max.height = std::numeric_limits<float>::infinity();
	return this;
}

const float* gui::GUI::Element::getVertices() const {
	return vertices;
}
const std::vector<gui::GUI::Element*>& gui::GUI::Element::getChilds() const {
	return childs;
}
uts::RGB gui::GUI::Element::getColor() const {
	return color;
}
gui::Point2D gui::GUI::Element::getMin() const {
	return min;
}
gui::Point2D gui::GUI::Element::getMax() const {
	return max;
}
gui::GUI::Element& gui::GUI::Element::operator[](size_t index) const {
	return *childs[index];
}

void gui::GUI::Element::mouseAction(Point2D pos, MouseButton button, MouseAction action)const {
	for (auto& el : childs) {
		if (el->isInside(pos.X, pos.Y)) {
			el->mouseAction(pos, button, action);
			return;
		}
	}
}

const bool gui::GUI::Element::isInside(float x, float y) const {
	return
		x >= pos.X &&
		y >= pos.Y &&
		x <= pos.X + size.width &&
		y <= pos.Y + size.height;
}

void gui::GUI::Element::updateChildLocation() {
	for (auto& el : childs) {
		switch (el->mode) {
		case Mode::fill:
			el->setLocation(Point2D(0, 0), size);
			break;

		default:
			throw std::exception("non-existent GUI element mode");
			break;
		}
	}
}
gui::GUI::Element* gui::GUI::Element::addChild(Element* ptr_element) {
	childs.push_back(ptr_element);
	return ptr_element;
}