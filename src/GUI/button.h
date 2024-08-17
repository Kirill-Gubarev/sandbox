#ifndef BUTTON_H
#define BUTTON_H

#include "GUI/GUI.h"
#include "GUI/Element.h"

namespace gui {
	//this class can perform actions
	class GUI::Button : public GUI::Element {
	protected:
		//functions
		void(*LPress)();
		void(*LRelease)();
		void(*RPress)();
		void(*RRelease)();

	public:
		//constructors
		Button();
		Button(Point2D size, uts::RGB color, Mode mode);

		void clearFunctions();

		void mouseAction(Point2D pos, MouseButton button, MouseAction action) const override;

		//setters
		void setLPress(void(*func)());
		void setLRelease(void(*func)());
		void setRPress(void(*func)());
		void setRRelease(void(*func)());
	};
}

#endif //BUTTON_H