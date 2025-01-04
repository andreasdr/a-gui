#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Alignments;
using agui::gui::nodes::GUINode_AlignmentHorizontal;
using agui::gui::nodes::GUINode_AlignmentVertical;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Flow;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;

/**
 * GUI node requested constraints entity
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_RequestedConstraints
{
	GUINode_RequestedConstraints_RequestedConstraintsType* leftType { nullptr };
	int left { 0 };
	GUINode_RequestedConstraints_RequestedConstraintsType* topType { nullptr };
	int top { 0 };
	GUINode_RequestedConstraints_RequestedConstraintsType* widthType { nullptr };
	int width { 0 };
	GUINode_RequestedConstraints_RequestedConstraintsType* heightType { nullptr };
	int height { 0 };
};
