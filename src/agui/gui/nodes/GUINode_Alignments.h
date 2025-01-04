#pragma once

#include <agui/agui.h>
#include <agui/gui/nodes/fwd-agui.h>

using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_AlignmentHorizontal;
using agui::gui::nodes::GUINode_AlignmentVertical;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Flow;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;

/**
 * GUI node alignments
 * @author Andreas Drewke
 */
struct agui::gui::nodes::GUINode_Alignments
{
	GUINode_AlignmentHorizontal* horizontal { nullptr };
	GUINode_AlignmentVertical* vertical { nullptr };
};
