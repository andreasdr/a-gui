#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/Enum.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace nodes {
	using ::agui::utilities::Enum;
}
}
}

/**
 * GUI node horizontal alignment enum
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUINode_AlignmentHorizontal final: public Enum
{
public:
	STATIC_DLL_IMPEXT static GUINode_AlignmentHorizontal* NONE;
	STATIC_DLL_IMPEXT static GUINode_AlignmentHorizontal* LEFT;
	STATIC_DLL_IMPEXT static GUINode_AlignmentHorizontal* CENTER;
	STATIC_DLL_IMPEXT static GUINode_AlignmentHorizontal* RIGHT;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUINode_AlignmentHorizontal(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @return enum object
	 */
	static GUINode_AlignmentHorizontal* valueOf(const string& name);
};
