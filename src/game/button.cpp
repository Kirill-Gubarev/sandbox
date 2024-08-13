#include "game/button.h"

sb::GUI::Button::Button()
	:Element() {
	clearFunctions();
}
sb::GUI::Button::Button(float width, float height, sb::RGB color, Mode mode)
	:Element(width, height, color, mode) {
	clearFunctions();
}

void sb::GUI::Button::clearFunctions() {
	LPress = nullptr;
	LRelease = nullptr;
	RPress = nullptr;
	RRelease = nullptr;
}

void sb::GUI::Button::mouseAction(float x, float y, MouseButton button, MouseAction action) const {
	Element::mouseAction(x, y, button, action);
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

void sb::GUI::Button::setLPress(void(*func)()) {
	LPress = func;
}
void sb::GUI::Button::setLRelease(void(*func)()) {
	LRelease = func;
}
void sb::GUI::Button::setRPress(void(*func)()) {
	RPress = func;
}
void sb::GUI::Button::setRRelease(void(*func)()) {
	RRelease = func;
}