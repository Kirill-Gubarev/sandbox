#include "render.h"
#include "game/area.h"
#include "sbWindow.h"


void sb::Render::update() {
	glClear(GL_COLOR_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_COLOR_ARRAY);

	drawTiles();
	drawArea();

	//glEnableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glfwSwapBuffers(ptr_sbWindow->getGLFWwindow());
}
void sb::Render::drawArea() {
	glLineWidth(2);
	glColor3ub(150, 150, 150);
	glVertexPointer(2,GL_FLOAT,0, &areaVertices);
	glDrawArrays(GL_LINE_LOOP,0,4);
}
void sb::Render::drawTiles() {

	int areaWidth = ptr_area->getWidth();
	int areaHeight = ptr_area->getHeight();

	for (int x = 0; x < areaWidth; x++) {
		for (int y = areaHeight - 1; y >= 0; y--) {
			sb::Tile& tile = ptr_area->getTile(x, y);
			if (tile.isNotEmpty())
				continue;

			glBegin(GL_TRIANGLE_FAN);

			sb::Render::setColor(tile.getColor());
			glVertex2f(1 + x, 1 + y);
			glVertex2f(1 + x, 0 + y);
			glVertex2f(0 + x, 0 + y);
			glVertex2f(0 + x, 1 + y);
			glEnd();
		}
	}
}
void sb::Render::setColor(sb::RGB color) {
	glColor3ub(color.r, color.g, color.b);
}

//singleton pattern
sb::Render* sb::ptr_render = nullptr;
std::unique_ptr<sb::Render> sb::Render::ptr_instance;
sb::Render::Render() {
	int areaWidth = ptr_area->getWidth();
	int areaHeight = ptr_area->getHeight();

	areaVertices[0] = 0;			areaVertices[1] = 0;
	areaVertices[2] = areaWidth;	areaVertices[3] = 0;
	areaVertices[4] = areaWidth;	areaVertices[5] = areaHeight;
	areaVertices[6] = 0;			areaVertices[7] = areaHeight;
}

sb::Render* sb::Render::getInstance(){
	return ptr_instance.get();
}
sb::Render* sb::Render::createInstance() {
	if (ptr_instance == nullptr){
		ptr_instance.reset(new Render());
		ptr_render = ptr_instance.get();
	}
	return ptr_instance.get();
}
