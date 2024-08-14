#ifndef RGB_H
#define RGB_H

#include <memory>

namespace uts {
	/// this class stores the color
	struct RGB {
		std::uint8_t R, G, B;
		RGB();
		RGB(std::uint8_t r, std::uint8_t g, std::uint8_t b);
	};
}

#endif //RGB_H