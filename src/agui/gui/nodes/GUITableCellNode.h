#pragma once

#include <set>
#include <string>

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUILayoutNode.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints.h>

using std::set;
using std::string;

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUILayoutNode;
using agui::gui::nodes::GUILayoutNode_Alignment;
using agui::gui::nodes::GUINode_Alignments;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_Flow;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIParentNode_Overflow;
using agui::gui::nodes::GUIScreenNode;

/**
 * GUI panel node
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUITableCellNode final
	: public GUILayoutNode
{
	friend class agui::gui::GUIParser;

protected:
	// forbid class copy
	FORBID_CLASS_COPY(GUITableCellNode)

	/**
	 * Constructor
	 * @param screenNode screen node
	 * @param parentNode parent node
	 * @param id id
	 * @param flow flow
	 * @param overflowX overflow x
	 * @param overflowY overflow y
	 * @param alignments alignments
	 * @param requestedConstraints requested constraints
	 * @param backgroundColor background color
	 * @param backgroundImage background image
	 * @param backgroundImageScale9Grid background image scale 9 grid
	 * @param backgroundImageEffectColorMul background image effect color mul
	 * @param backgroundImageEffectColorAdd background image effect color add
	 * @param border border
	 * @param padding padding
	 * @param showOn show on
	 * @param hideOn hide on
	 * @param tooltip tooltip
	 * @param alignment alignment
	 */
	GUITableCellNode(
		GUIScreenNode* screenNode,
		GUIParentNode* parentNode,
		const string& id,
		GUINode_Flow* flow,
		GUIParentNode_Overflow* overflowX,
		GUIParentNode_Overflow* overflowY,
		const GUINode_Alignments& alignments,
		const GUINode_RequestedConstraints& requestedConstraints,
		const GUIColor& backgroundColor,
		const string& backgroundImage,
		const GUINode_Scale9Grid& backgroundImageScale9Grid,
		const GUIColor& backgroundImageEffectColorMul,
		const GUIColor& backgroundImageEffectColorAdd,
		const GUINode_Border& border,
		const GUINode_Padding& padding,
		const GUINodeConditions& showOn,
		const GUINodeConditions& hideOn,
		const string& tooltip,
		GUILayoutNode_Alignment* alignment
	);

	// overridden methods
	const string getNodeType() override;

public:
	/**
	 * Create requested constraints
	 * @param left left
	 * @param top top
	 * @param width width
	 * @param height height
	 * @param factor factor
	 * @return requested constraints
	 */
	static GUINode_RequestedConstraints createRequestedConstraints(const string& left, const string& top, const string& width, const string& height, int factor);

};
