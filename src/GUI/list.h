#ifndef LIST_H
#define LIST_H

#include "GUI/GUI.h"
#include "GUI/Element.h"

namespace gui {
	//this class stores items in columns
	class GUI::List : public GUI::Element {
	protected:
		Mode orientation;

	public:
		//constructors
		List();
		List(float width, float height, uts::RGB color, Mode mode, Mode orientation);

		void updateChildSize() override;
	};
}

#endif //LIST_H