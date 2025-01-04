#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Alignments;
using agui::gui::nodes::GUINode_AlignmentHorizontal;
using agui::gui::nodes::GUINode_AlignmentVertical;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_Flow;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;

/**
 * GUI node computed constraints
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_ComputedConstraints
{
	int left { 0 };
	int top { 0 };
	int width { 0 };
	int height { 0 };
	int alignmentLeft { 0 };
	int alignmentTop { 0 };
	int contentAlignmentLeft { 0 };
	int contentAlignmentTop { 0 };
	int additionalAlignmentLeft { 0 };
	int additionalAlignmentTop { 0 };
};
