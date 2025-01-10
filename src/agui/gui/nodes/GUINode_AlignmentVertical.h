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
 * GUI node vertical alignment enum
 */
class agui::gui::nodes::GUINode_AlignmentVertical final: public Enum
{
public:
	STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* NONE;
	STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* TOP;
	STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* CENTER;
	STATIC_DLL_IMPEXT static GUINode_AlignmentVertical* BOTTOM;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUINode_AlignmentVertical(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @return enum object
	 */
	static GUINode_AlignmentVertical* valueOf(const string& name);
};
