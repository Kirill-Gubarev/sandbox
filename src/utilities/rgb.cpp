#include "utilities/rgb.h"
uts::RGB::RGB() : R(0), G(0), B(0) {

}
uts::RGB::RGB(std::uint8_t r, std::uint8_t g, std::uint8_t b)
	: R(r), G(g), B(b) {

}
uts::RGB uts::RGB::random() {
	return RGB(rand() % 256, rand() % 256, rand() % 256);
}