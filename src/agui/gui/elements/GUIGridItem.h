#pragma once

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/elements/GUIElement.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/utilities/fwd-agui.h>

using std::string;
using std::unordered_map;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUINodeController;
	using ::agui::gui::nodes::GUIScreenNode;
	using ::agui::os::filesystem::FileSystemException;
}
}
}

/**
 * GUI grid item element
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIGridItem final: public GUIElement
{

private:
	STATIC_DLL_IMPEXT static string NAME;

public:
	// forbid class copy
	FORBID_CLASS_COPY(GUIGridItem)

	/**
	 * Public constructor
	 */
	GUIGridItem();

	// overridden methods
	const string& getName() override;
	const string getTemplate(const string& applicationPathName, const string& applicationSubPathName, const string& fileName = string()) override;
	unordered_map<string, string> getAttributes(GUIScreenNode* screenNode) override;
	GUINodeController* createController(GUINode* node) override;

};
