#ifndef ELEMENT_H
#define ELEMENT_H

#include "GUI/GUI.h"

namespace gui {
	//base class
	class GUI::Element {
	protected:
		//data
		Point2D pos, size;
		Point2D min, max;
		float vertices[12];
		uts::RGB color;
		Mode mode;
		std::vector<Element*> childs;

	public:
		//constructors and destructor
		Element();
		Element(Point2D size, uts::RGB color, Mode mode);
		~Element();

		//getters
		const float* getVertices() const;
		const std::vector<Element*>& getChilds() const;
		uts::RGB getColor() const;
		Point2D getMin() const;
		Point2D getMax() const;
		Element& operator[](size_t index) const;

		//setters
		Element* setLocation(Point2D newPos, Point2D newSize);
		Element* setMin(float width, float height);
		Element* setMax(float width, float height);
		Element* setSize(float width, float height);

		virtual void mouseAction(Point2D pos, MouseButton button, MouseAction action) const;
		const bool isInside(float x, float y) const;

		Element* addChild(Element* ptr_element);
		virtual void updateChildLocation();
	};
}

#endif //ELEMENT_H