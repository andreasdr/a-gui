#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/Enum.h>

using std::string;

using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Alignments;
using agui::gui::nodes::GUINode_AlignmentHorizontal;
using agui::gui::nodes::GUINode_AlignmentVertical;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Flow;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::utilities::Enum;

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
