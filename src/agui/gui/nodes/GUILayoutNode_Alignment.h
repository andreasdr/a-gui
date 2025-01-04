#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/utilities/Enum.h>

using std::string;

using agui::gui::nodes::GUILayoutNode;
using agui::gui::nodes::GUILayoutNode_Alignment;
using agui::utilities::Enum;

/**
 * GUI layout node alignment enum
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUILayoutNode_Alignment final: public Enum
{
public:
	STATIC_DLL_IMPEXT static GUILayoutNode_Alignment* VERTICAL;
	STATIC_DLL_IMPEXT static GUILayoutNode_Alignment* HORIZONTAL;
	STATIC_DLL_IMPEXT static GUILayoutNode_Alignment* NONE;

	/**
	 * Public constructor
	 * @param name name
	 * @param ordinal ordinal
	 */
	GUILayoutNode_Alignment(const string& name, int ordinal);

	/**
	 * Returns enum object given by name
	 * @param name name
	 * @return enum object
	 */
	static GUILayoutNode_Alignment* valueOf(const string& name);
};
