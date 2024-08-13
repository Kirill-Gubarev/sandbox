#ifndef LIST_H
#define LIST_H

#include "game/GUI.h"
#include "game/Element.h"

namespace sb {
	//this class stores items in columns
	class GUI::List : public GUI::Element {
	protected:
		Mode orientation;

	public:
		//constructors
		List();
		List(float width, float height, sb::RGB color, Mode mode, Mode orientation);

		void updateChildSize() override;
	};
}

#endif //LIST_H