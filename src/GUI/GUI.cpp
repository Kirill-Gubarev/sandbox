#include "GUI/GUI.h"
#include "GUI/element.h"
#include "GUI/list.h"
#include "GUI/button.h"
#include "game/sbWindow.h"

gui::GUI::Element* gui::GUI::ptr_element;

//managing this class
void gui::GUI::init() {
	ptr_element = new List(
		static_cast<float>(sb::SBWindow::getWidth()),
		static_cast<float>(sb::SBWindow::getHeight()),
		uts::RGB(0, 255, 0),
		Mode::fill,
		Mode::horizontal
	);
	ptr_element->addChild(new Element(50, 50, uts::RGB(255, 0, 0), Mode::fill));
	ptr_element->addChild(new List(50, 100, uts::RGB(0, 0, 255), Mode::fill, Mode::vertical));
	ptr_element->addChild(new Element(40, 100, uts::RGB(255, 255, 0), Mode::fill));

	Button* button = new Button(40, 100, uts::RGB(255, 0, 155), Mode::fill);
	button->setLPress([]() {std::cout << "Left press" << std::endl; });
	button->setLRelease([]() {std::cout << "Left release" << std::endl; });
	button->setRPress([]() {std::cout << "Right press" << std::endl; });
	button->setRRelease([]() {std::cout << "Right release" << std::endl; });
	(*ptr_element)[1].addChild(button);
	(*ptr_element)[1].addChild(new Element(40, 100, uts::RGB(0, 155, 255), Mode::fill));
	(*ptr_element)[1].addChild(new Element(40, 100, uts::RGB(129, 120, 255), Mode::fill));
	(*ptr_element)[1].addChild(new Element(40, 100, uts::RGB(255, 140, 135), Mode::fill));
	updateElementsSize();
}
void gui::GUI::terminate() {
	delete ptr_element;
}

void gui::GUI::updateElementsSize() {
	ptr_element->setLocation(0, 0,
		static_cast<float>(sb::SBWindow::getWidth()),
		static_cast<float>(sb::SBWindow::getHeight())
	);
	ptr_element->updateChildSize();
}
