#ifndef GUI_H
#define GUI_H


#include "common.h"
#include "utilities/rgb.h"
#include "utilities/vec2d.hpp"

namespace sb {
	class GUI {
	public:
		enum class Mode : std::uint32_t {
			fill = 0,
			vertical,
			horizontal
		};
		class Element {
		public:
			float x, y;
			float width, height;
			float vertices[12];
			sb::RGB color;
			std::vector<Element*> childs;
			Mode mode;
			Element();
			Element(float width, float height, sb::RGB color, Mode mode);
			~Element();
			void setLocation(float x, float y, float width, float height);
			virtual void updateChildSize();
		};
		class List : public Element {
		public:
			Mode orientation;
			List(float width, float height, sb::RGB color, Mode mode, Mode orientation);
			void updateChildSize() override;
		}; 
		class DockPanel : public Element {

		};
		class Button : public Element {

		};
		static Element* ptr_element;

		//an object of this class cannot be created
		GUI() = delete;
		GUI(const GUI&) = delete;
		void operator =(const GUI&) = delete;

		//managing this class
		static void init();
		static void terminate();

		static void updateElementsSize();
	};
}


#endif //GUI_H