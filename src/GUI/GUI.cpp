#include "GUI/GUI.h"
#include "GUI/element.h"
#include "GUI/list.h"
#include "GUI/button.h"
#include "game/sbWindow.h"

gui::GUI::Element* gui::GUI::ptr_element;

//managing this class
void gui::GUI::init() {
	ptr_element = new List(
		Point2D(
			static_cast<float>(sb::SBWindow::getWidth()),
			static_cast<float>(sb::SBWindow::getHeight())),
		uts::RGB(0, 255, 0),
		Mode::fill,
		Mode::horizontal
	);
	ptr_element->addChild(new Element(
		Point2D(50, 50),
		uts::RGB(255, 0, 0),
		Mode::fill
	));
	Button* button = new Button(
		Point2D(40, 100),
		uts::RGB(255, 0, 255),
		Mode::fill
	);
	button->setLPress([]() {std::cout << "Left press" << std::endl; });
	button->setLRelease([]() {std::cout << "Left release" << std::endl; });
	button->setRPress([]() {std::cout << "Right press" << std::endl; });
	button->setRRelease([]() {std::cout << "Right release" << std::endl; });
	ptr_element->addChild(button->setMin(300, 300)->setMax(300, 300));
	ptr_element->addChild(
		new Element(
			Point2D(40, 100), 
			uts::RGB(255, 255, 0), 
			Mode::fill
		));
	updateElementsSize();
}
void gui::GUI::terminate() {
	delete ptr_element;
}

void gui::GUI::updateElementsSize() {
	ptr_element->setLocation(Point2D(0, 0),
		Point2D(
			static_cast<float>(sb::SBWindow::getWidth()),
			static_cast<float>(sb::SBWindow::getHeight())
		));
	ptr_element->updateChildLocation();
}