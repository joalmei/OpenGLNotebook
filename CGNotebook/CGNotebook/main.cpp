#include "Window.h"
#include "TriangleRenderer.h"

int main()
{
	Window w;
	auto r = new TriangleRenderer();
	auto renderFunction = [r](GLFWwindow* w) { r->Render(w); };

	w.SubscribeOnRender(renderFunction);

	w.RenderLoop();

	delete r;

	return 0;
}