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
		Button(float width, float height, uts::RGB color, Mode mode);

		void clearFunctions();

		void mouseAction(float x, float y, MouseButton button, MouseAction action) const override;

		//setters
		void setLPress(void(*func)());
		void setLRelease(void(*func)());
		void setRPress(void(*func)());
		void setRRelease(void(*func)());
	};
}

#endif //BUTTON_H