#include "GUI/list.h"

gui::GUI::List::List()
	:Element(), orientation(Mode::vertical) {

}
gui::GUI::List::List(Point2D size, uts::RGB color, Mode mode, Mode orientation)
	:Element(size, color, mode), orientation(orientation) {

}

void gui::GUI::List::updateChildLocation() {
	if (orientation == Mode::vertical)
		updateChildLocationVertical();
	else
		updateChildLocationHorizontal();
}
void gui::GUI::List::updateChildLocationVertical() {
	
}
void gui::GUI::List::updateChildLocationHorizontal() {
	const size_t numberElements = childs.size();
	std::vector<float> newWidth(numberElements);
	typedef std::pair<float*, Element*> newWidth_and_element;
	std::vector<newWidth_and_element> sortedArr(numberElements);
	float availableWidth = size.width;

	for (size_t i = 0; i < numberElements; ++i) {
		newWidth[i] = childs[i]->getMin().width;
		availableWidth -= newWidth[i];

		sortedArr[i].first = &newWidth[i];
		sortedArr[i].second = childs[i];
	}
	std::sort(
		begin(sortedArr),
		end(sortedArr),
		[](newWidth_and_element a, newWidth_and_element b) {
			return a.second->getMax().width < b.second->getMax().width;
		});
	bool isMax = true;
	size_t start = 0;
	float countEl = 1;
	float minEl = std::numeric_limits<float>::infinity();
	float goal = std::numeric_limits<float>::infinity();
	std::cout << "available: " << availableWidth << std::endl;
	while (availableWidth > 0 && isMax) {
		isMax = false;
		minEl = std::numeric_limits<float>::infinity();
		goal = std::numeric_limits<float>::infinity();
		for (size_t i = start; i < numberElements; ++i) {
			if (minEl == sortedArr[i].first[NULL]) {
				countEl++;
			}
			else if (minEl > sortedArr[i].first[NULL]) {
				goal = minEl;
				minEl = sortedArr[i].first[NULL];
				countEl = 1;
			}
			else if (goal > sortedArr[i].first[NULL]) {
				goal = sortedArr[i].first[NULL];
			}
		}
		float distribution = availableWidth / countEl;
		float dif = 0;
		for (size_t i = start; i < numberElements; ++i) {
			if (minEl >= sortedArr[i].first[NULL]) { 
				isMax = true;
				if (goal < sortedArr[i].second->getMax().width) {
					dif = goal - sortedArr[i].first[NULL];
					if (dif > distribution)
						dif = distribution;
				}
				else {
					dif = sortedArr[i].second->getMax().width - sortedArr[i].first[NULL];
					if (dif > distribution)
						dif = distribution;
					else
						start++;
				}
				availableWidth -= dif;
				sortedArr[i].first[NULL] += dif;
			}
		}
	}
	float offset = pos.X;
	std::cout << "min\tsize\tmax" << std::endl;
	for (size_t i = 0; i < numberElements; ++i) {
		std::cout << childs[i]->getMin().width << '\t' << newWidth[i] << '\t'<<  childs[i]->getMax().width<<'\n';
		childs[i]->setLocation(Point2D(offset, pos.Y), Point2D(newWidth[i], size.height));
		childs[i]->updateChildLocation();
		offset += newWidth[i];
	}
	std::cout << "available: " << availableWidth << std::endl;
	std::cout << "===============" << std::endl;
}