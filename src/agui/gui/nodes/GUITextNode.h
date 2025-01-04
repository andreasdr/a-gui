#pragma once

#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIColor.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/renderer/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/Exception.h>
#include <agui/utilities/MutableString.h>

using std::string;
using std::vector;

using agui::gui::nodes::GUIColor;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Alignments;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_Flow;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::renderer::GUIFont;
using agui::gui::renderer::GUIRenderer;
using agui::utilities::Exception;
using agui::utilities::MutableString;

/**
 * GUI text node
 * @author Andreas Drewke
 */
class agui::gui::nodes::GUITextNode final
	: public GUINode
{
	friend class agui::gui::GUIParser;

private:
	GUIFont* font { nullptr };
	GUIColor color;
	MutableString text;

protected:
	// forbid class copy
	FORBID_CLASS_COPY(GUITextNode)

	/**
	 * Constructor
	 * @param screenNode screen node
	 * @param parentNode parent node
	 * @param id id
	 * @param flow flow
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
	 * @param font font
	 * @param size size
	 * @param color color
	 * @param text text
	 * @throws agui::gui::GUIParserException
	 */
	GUITextNode(
		GUIScreenNode* screenNode,
		GUIParentNode* parentNode,
		const string& id,
		GUINode_Flow* flow,
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
		const string& font,
		int size,
		const string& color,
		const MutableString& text
	);

	// overridden methods
	const string getNodeType() override;
	bool isContentNode() override;

public:
	// overridden methods
	int getContentWidth() override;
	int getContentHeight() override;

	/**
	 * @return text
	 */
	inline const MutableString& getText() const {
		return text;
	}

	/**
	 * Set text
	 * @param text text
	 */
	void setText(const MutableString& text);

	// overridden methods
	void dispose() override;
	void render(GUIRenderer* guiRenderer) override;
};
