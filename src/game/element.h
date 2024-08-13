#ifndef ELEMENT_H
#define ELEMENT_H

#include "game/GUI.h"

namespace sb {
	class GUI::Element {
	protected:
		//data
		float X, Y;
		float width, height;
		float vertices[12];
		sb::RGB color;
		Mode mode;
		std::vector<Element*> childs;
	public:
		//constructors and destructor
		Element();
		Element(float width, float height, sb::RGB color, Mode mode);
		~Element();

		//getters
		const float* getVertices() const;
		const sb::RGB getColor() const;
		const std::vector<Element*>& getChilds() const;
		Element& operator[](size_t index) const;

		virtual void mouseAction(float x, float y, MouseButton button, MouseAction action) const;
		const bool isInside(float x, float y) const;
		void setLocation(float x, float y, float width, float height);
		void addChild(Element* ptr_element);
		virtual void updateChildSize();
	};
}

#endif //ELEMENT_H