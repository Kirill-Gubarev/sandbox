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
		enum class MouseButton : std::uint32_t {
			left = 0,
			right,
			middle
		};
		enum class MouseAction : std::uint32_t {
			release = 0,
			press
		};
		class Element;
		class List;
		class Button;
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