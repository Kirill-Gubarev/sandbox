#include "game/GUI.h"
#include "game/element.h"
#include "game/list.h"
#include "game/button.h"
#include "game/sbWindow.h"

sb::GUI::Element* sb::GUI::ptr_element;

//managing this class
void sb::GUI::init() {
	ptr_element = new List(
		static_cast<float>(sb::SBWindow::getWidth()),
		static_cast<float>(sb::SBWindow::getHeight()),
		sb::RGB(0, 255, 0),
		Mode::fill,
		Mode::horizontal
	);
	ptr_element->addChild(new Element(50, 50, sb::RGB(255, 0, 0), Mode::fill));
	ptr_element->addChild(new List(50, 100, sb::RGB(0, 0, 255), Mode::fill, Mode::vertical));
	ptr_element->addChild(new Element(40, 100, sb::RGB(255, 255, 0), Mode::fill));

	Button* button = new Button(40, 100, sb::RGB(255, 0, 155), Mode::fill);
	button->setLPress([]() {std::cout << "Left press" << std::endl; });
	button->setLRelease([]() {std::cout << "Left release" << std::endl; });
	button->setRPress([]() {std::cout << "Right press" << std::endl; });
	button->setRRelease([]() {std::cout << "Right release" << std::endl; });
	(*ptr_element)[1].addChild(button);
	(*ptr_element)[1].addChild(new Element(40, 100, sb::RGB(0, 155, 255), Mode::fill));
	(*ptr_element)[1].addChild(new Element(40, 100, sb::RGB(129, 120, 255), Mode::fill));
	(*ptr_element)[1].addChild(new Element(40, 100, sb::RGB(255, 140, 135), Mode::fill));
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
