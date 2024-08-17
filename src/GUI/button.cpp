#include "GUI/button.h"

gui::GUI::Button::Button()
	:Element() {
	clearFunctions();
}
gui::GUI::Button::Button(Point2D size, uts::RGB color, Mode mode)
	:Element(size, color, mode) {
	clearFunctions();
}

void gui::GUI::Button::clearFunctions() {
	LPress = nullptr;
	LRelease = nullptr;
	RPress = nullptr;
	RRelease = nullptr;
}

void gui::GUI::Button::mouseAction(Point2D pos, MouseButton button, MouseAction action) const {
	Element::mouseAction(pos, button, action);
	if (action == MouseAction::press)
		switch (button) {
		case MouseButton::left:
			if (LPress)LPress();
			break;
		case MouseButton::right:
			if (LPress)RPress();
			break;
		}
	else if (action == MouseAction::release)
		switch (button) {
		case MouseButton::left:
			if (LPress)LRelease();
			break;
		case MouseButton::right:
			if (LPress)RRelease();
			break;
		}
}

void gui::GUI::Button::setLPress(void(*func)()) {
	LPress = func;
}
void gui::GUI::Button::setLRelease(void(*func)()) {
	LRelease = func;
}
void gui::GUI::Button::setRPress(void(*func)()) {
	RPress = func;
}
void gui::GUI::Button::setRRelease(void(*func)()) {
	RRelease = func;
}