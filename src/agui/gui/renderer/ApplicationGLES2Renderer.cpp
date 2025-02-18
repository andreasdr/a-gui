#include <agui/gui/renderer/ApplicationGLES2Renderer.h>

#if defined(_MSC_VER)
	// this suppresses a warning redefinition of APIENTRY macro
	#define NOMINMAX
	#include <windows.h>
#endif
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

#include <agui/agui.h>
#include <agui/gui/renderer/GUIShader.h>
#include <agui/gui/GUI.h>

using std::string;

using agui::gui::renderer::ApplicationGLES2Renderer;

ApplicationGLES2Renderer::ApplicationGLES2Renderer()
{
}

bool ApplicationGLES2Renderer::prepareWindowSystemRendererContext(int tryIdx) {
	if (tryIdx > 0) return false;
	glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
	glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	return true;
}

bool ApplicationGLES2Renderer::initializeWindowSystemRendererContext(GLFWwindow* glfwWindow) {
	glfwMakeContextCurrent(glfwWindow);
	if (glfwGetCurrentContext() == nullptr) {
		Console::printLine("ApplicationGLES2Renderer::initializeWindowSystemRendererContext(): glfwMakeContextCurrent(): Error: No window attached to context");
		return false;
	}
	return true;
}

void ApplicationGLES2Renderer::onBindTexture(int contextIdx, int32_t textureId)
{
	GUI::getShader()->bindTexture(textureId);
}

void ApplicationGLES2Renderer::onUpdateTextureMatrix(int contextIdx)
{
	GUI::getShader()->updateTextureMatrix();
}

void ApplicationGLES2Renderer::onUpdateEffect(int contextIdx)
{
	GUI::getShader()->updateEffect();
}
