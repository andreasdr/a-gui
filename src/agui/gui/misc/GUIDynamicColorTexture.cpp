#include <agui/gui/misc/GUIDynamicColorTexture.h>

#include <string>

#include <agui/agui.h>
#include <agui/application/Application.h>
#include <agui/gui/textures/GUITexture.h>
#include <agui/gui/renderer/GUIRendererBackend.h>
#include <agui/utilities/ByteBuffer.h>

using agui::application::Application;
using agui::gui::textures::GUITexture;
using agui::gui::renderer::GUIRendererBackend;
using agui::gui::misc::GUIDynamicColorTexture;
using agui::utilities::ByteBuffer;

uint32_t GUIDynamicColorTexture::counter = 0;

void GUIDynamicColorTexture::initialize()
{
	colorBufferTextureId = Application::getRenderer()->createColorBufferTexture(width, height, Application::getRenderer()->ID_NONE, Application::getRenderer()->ID_NONE);
	texture = new GUITexture(
		"dynamic-color-texture:" + to_string(GUIDynamicColorTexture::counter++),
		GUITexture::TEXTUREDEPTH_RGBA,
		GUITexture::TEXTUREFORMAT_RGBA,
		width, height,
		width, height,
		GUITexture::TEXTUREFORMAT_RGBA,
		ByteBuffer(width * height * 4)
	);
	texture->acquireReference();
	texture->setUseCompression(false);
	texture->setUseMipMap(false);
	texture->setRepeat(false);
}

void GUIDynamicColorTexture::reshape(int32_t width, int32_t height)
{
	texture->releaseReference();
	texture = new GUITexture(
		"dynamic-color-texture:" + to_string(GUIDynamicColorTexture::counter++),
		GUITexture::TEXTUREDEPTH_RGBA,
		GUITexture::TEXTUREFORMAT_RGBA,
		width, height,
		width, height,
		GUITexture::TEXTUREFORMAT_RGBA,
		ByteBuffer(width * height * 4)
	);
	texture->acquireReference();
	texture->setUseCompression(false);
	texture->setUseMipMap(false);
	texture->setRepeat(false);
	Application::getRenderer()->resizeColorBufferTexture(colorBufferTextureId, width, height);
	this->width = width;
	this->height = height;
}

void GUIDynamicColorTexture::dispose()
{
	Application::getRenderer()->disposeTexture(colorBufferTextureId);
	texture->releaseReference();
}

void GUIDynamicColorTexture::update()
{
	Application::getRenderer()->bindTexture(Application::getRenderer()->CONTEXTINDEX_DEFAULT, colorBufferTextureId);
	Application::getRenderer()->uploadTexture(Application::getRenderer()->CONTEXTINDEX_DEFAULT, texture);
	Application::getRenderer()->bindTexture(Application::getRenderer()->CONTEXTINDEX_DEFAULT, Application::getRenderer()->ID_NONE);
}
