#include <memory>
#include <string>

#include <agui/agui.h>
#include <agui/application/Application.h>
#include <agui/gui/GUI.h>
#include <agui/gui/GUIParser.h>
#include <agui/gui/GUIVersion.h>
#include <agui/gui/renderer/GUIRenderer.h>
#include <agui/os/filesystem/FileSystem.h>
#include <agui/os/filesystem/FileSystemInterface.h>
#include <agui/utilities/Console.h>

using std::make_unique;
using std::string;
using std::unique_ptr;

using agui::application::Application;
using agui::gui::GUI;
using agui::gui::GUIParser;
using agui::gui::GUIVersion;
using agui::gui::renderer::GUIRenderer;
using agui::os::filesystem::FileSystem;
using agui::os::filesystem::FileSystemInterface;
using agui::utilities::Console;

/**
 * TDME editor
 * @author andreas.drewke
 */
class AGUI final
	: public Application
{
public:
	// forbid class copy
	FORBID_CLASS_COPY(AGUI)

	/**
	 * Public constructor
	 */
	AGUI(const string& screenFileName): Application(), screenFileName(screenFileName) {
	}

	/**
	 * Destructor
	 */
	~AGUI() {
	}

	/**
	 * Initialize
	 */
	void initialize() {
		//
		guiRenderer = make_unique<GUIRenderer>(Application::getRenderer());
		gui = make_unique<GUI>(guiRenderer.get(), getWindowWidth(), getWindowHeight());
		//
		auto screenNode = GUIParser::parse(
			FileSystem::getStandardFileSystem()->getPathName(screenFileName),
			FileSystem::getStandardFileSystem()->getFileName(screenFileName)
		);
		gui->addScreen(
			screenNode->getId(),
			screenNode
		);
	}

	/**
	 * Dispose
	 */
	void dispose() {
		gui->dispose();
		guiRenderer->dispose();
		GUIParser::dispose();
	}

	/**
	 * Resize
	 * @param width width
	 * @param height height
	 */
	void reshape(int width, int height) {
	}

	/**
	 * Display
	 */
	void display() {
		gui->handleEvents();
		//
		Application::getRenderer()->initializeFrame();
		gui->render();
		Application::getRenderer()->finishFrame();
	}

private:
	string screenFileName;
	unique_ptr<GUI> gui;
	unique_ptr<GUIRenderer> guiRenderer;
};

int main(int argc, char** argv)
{
	Console::printLine(string("A-GUI ") + GUIVersion::getVersion());
	Console::printLine(GUIVersion::getCopyright());
	Console::printLine();

	//
	if (argc != 2) {
		Console::printLine("Usage: agui pathtoscreen.xml");
		Application::exit(1);
	}

	auto screenFileName = string(argv[1]);
	auto agui = new AGUI(screenFileName);
	return agui->run(argc, argv, "A-GUI", nullptr, Application::WINDOW_HINT_MAXIMIZED);

	//
	return Application::EXITCODE_SUCCESS;
}
