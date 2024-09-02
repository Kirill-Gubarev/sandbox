#include "GUI/list.h"

gui::GUI::List::List()
	:Element(), orientation(Mode::vertical) {

}
gui::GUI::List::List(Point2D size, uts::RGB color, Mode mode, Mode orientation)
	:Element(size, color, mode), orientation(orientation) {

}

void gui::GUI::List::updateChildLocation() {
	const size_t numberElements = childs.size();
	
	//declaring an array for new sizes
	std::vector<float> arrNewSizes(numberElements);
	//declaring an array to sort
	std::vector<std::pair<float*, Element*>> sortedArr(numberElements);

	//the variable for distribution
	float availableSize = 0;

	//lambda functions
	float (*lam_getMin)(const Element* const element);
	float (*lam_getMax)(const Element* const element);

	if (orientation == Mode::vertical) {
		availableSize = size.height;
		lam_getMin = [](const Element* const element)->float {return element->getMin().height; };
		lam_getMax = [](const Element* const element)->float {return element->getMax().height; };
	}
	else {
		availableSize = size.width;
		lam_getMin = [](const Element* const element)->float {return element->getMin().width; };
		lam_getMax = [](const Element* const element)->float {return element->getMax().width; };
	}

	for (size_t i = 0; i < numberElements; ++i) {
		//the size cannot be less than the minimum value
		arrNewSizes[i] = lam_getMin(childs[i]);
		//reduce the available size
		availableSize -= arrNewSizes[i];

		//first is a pointer to the size
		sortedArr[i].first = &arrNewSizes[i];
		//second is a pointer to the element
		sortedArr[i].second = childs[i];
	}
	//sorting by a maximum values
	std::sort(begin(sortedArr), end(sortedArr),
		[&lam_getMax](std::pair<float*, Element*> a, std::pair<float*, Element*> b) {
			return lam_getMax(a.second) < lam_getMax(b.second);
		});

	//are there any elements that are not filled to the maximum
	bool filledMax = false;
	//the starting value of the cycles
	size_t start = 0;
	//the elements counter for distribution
	uint32_t countEl = 1;
	//the minimum value of an element in the array
	float minSize = std::numeric_limits<float>::infinity();
	//target value to fill in
	float targetSize = std::numeric_limits<float>::infinity();

	//===OUTPUT===
	std::cout << "available: " << availableSize << std::endl;

	while (availableSize > 0 && !filledMax) {
		//update variables
		filledMax = true;
		minSize = std::numeric_limits<float>::infinity();
		targetSize = std::numeric_limits<float>::infinity();

		//finding the minimum size and target
		for (size_t i = start; i < numberElements; ++i) {
			const float newSize = sortedArr[i].first[NULL];
			if (newSize < minSize) {
				//the minimum value is always assigned in target
				targetSize = minSize;
				minSize = newSize;
				//update the element counter, it cannot be less than 1
				countEl = 1;
			}
			else if (newSize == minSize)
				countEl++;
			else if (newSize < targetSize)
				targetSize = newSize;
		}

		//distribution 
		float portion = availableSize / countEl;

		for (size_t i = start; i < numberElements; ++i) {
			float newSize = sortedArr[i].first[NULL];
			if (minSize >= newSize) {
				//update "filledMax"
				filledMax = false;
				float maxSize = lam_getMax(sortedArr[i].second);
				float dif = 0;

				//calculating the difference
				if (targetSize < maxSize) {
					dif = targetSize - newSize;
					if (dif > portion)
						dif = portion;
				}
				else {
					dif = maxSize - newSize;
					if (dif > portion)
						dif = portion;
					else
						start++;
				}

				availableSize -= dif;
				sortedArr[i].first[NULL] += dif;
			}
		}
	}

	//===OUTPUT===
	std::cout << "min\tsize\tmax" << std::endl;

	float offset = pos.X;
	if(orientation == Mode::vertical)
		for (size_t i = 0; i < numberElements; ++i) {

			//===OUTPUT===
			std::cout << lam_getMin(childs[i]) << '\t' << arrNewSizes[i] << '\t' << lam_getMax(childs[i]) << '\n';

			childs[i]->setLocation(Point2D(pos.X, offset), Point2D(size.width, arrNewSizes[i]));
			childs[i]->updateChildLocation();
			offset += arrNewSizes[i];
		}
	else
		for (size_t i = 0; i < numberElements; ++i) {

			//===OUTPUT===
			std::cout << lam_getMin(childs[i]) << '\t' << arrNewSizes[i] << '\t' << lam_getMax(childs[i]) << '\n';

			childs[i]->setLocation(Point2D(offset, pos.Y), Point2D(arrNewSizes[i], size.height));
			childs[i]->updateChildLocation();
			offset += arrNewSizes[i];
		}
		

	//===OUTPUT===
	std::cout << "available: " << availableSize << std::endl;

	//===OUTPUT===
	std::cout << "===============" << std::endl;

}