#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>

using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Alignments;
using agui::gui::nodes::GUINode_AlignmentHorizontal;
using agui::gui::nodes::GUINode_AlignmentVertical;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Flow;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;

/**
 * GUI node border entity
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_Border
{

	GUIColor leftColor;
	GUIColor topColor;
	GUIColor rightColor;
	GUIColor bottomColor;
	int left { 0 };
	int top { 0 };
	int right { 0 };
	int bottom { 0 };
};
