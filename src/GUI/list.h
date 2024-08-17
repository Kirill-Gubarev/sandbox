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
		List(Point2D size, uts::RGB color, Mode mode, Mode orientation);

		void updateChildLocation() override;
	};
}

#endif //LIST_H