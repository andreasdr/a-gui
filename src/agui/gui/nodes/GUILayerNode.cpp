#include <agui/gui/nodes/GUILayerNode.h>

#include <set>
#include <string>

#include <agui/agui.h>
#include <agui/gui/nodes/GUINode.h>
#include <agui/gui/nodes/GUINode_Alignments.h>
#include <agui/gui/nodes/GUINode_Border.h>
#include <agui/gui/nodes/GUINode_ComputedConstraints.h>
#include <agui/gui/nodes/GUINode_Padding.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints.h>
#include <agui/gui/nodes/GUINode_RequestedConstraints_RequestedConstraintsType.h>
#include <agui/gui/nodes/GUINode_Scale9Grid.h>
#include <agui/gui/nodes/GUINodeConditions.h>
#include <agui/gui/nodes/GUIParentNode.h>
#include <agui/gui/nodes/GUIParentNode_Overflow.h>
#include <agui/gui/nodes/GUIScreenNode.h>
#include <agui/gui/GUI.h>

using std::set;
using std::to_string;

using agui::gui::nodes::GUILayerNode;

using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUINode_Border;
using agui::gui::nodes::GUINode_ComputedConstraints;
using agui::gui::nodes::GUINode_Padding;
using agui::gui::nodes::GUINode_RequestedConstraints;
using agui::gui::nodes::GUINode_RequestedConstraints_RequestedConstraintsType;
using agui::gui::nodes::GUINode_Scale9Grid;
using agui::gui::nodes::GUINodeConditions;
using agui::gui::nodes::GUIParentNode;
using agui::gui::nodes::GUIParentNode_Overflow;
using agui::gui::nodes::GUIScreenNode;
using agui::gui::GUI;

GUILayerNode::GUILayerNode(
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
	const GUINode_Scale9Grid& backgroundImageScaleGrid,
	const GUIColor& backgroundImageEffectColorMul,
	const GUIColor& backgroundImageEffectColorAdd,
	const GUINode_Border& border,
	const GUINode_Padding& padding,
	const GUINodeConditions& showOn,
	const GUINodeConditions& hideOn,
	const string& tooltip
	) :
	GUIParentNode(screenNode, parentNode, id, flow, overflowX, overflowY, alignments, requestedConstraints, backgroundColor, backgroundImage, backgroundImageScaleGrid, backgroundImageEffectColorMul, backgroundImageEffectColorAdd, border, padding, showOn, hideOn, tooltip)
{
}

const string GUILayerNode::getNodeType()
{
	return "element";
}

bool GUILayerNode::isContentNode()
{
	return false;
}

int GUILayerNode::getContentWidth()
{
	auto width = 0;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		auto contentWidth = guiSubNode->getAutoWidth();
		if (contentWidth > width) {
			width = contentWidth;
		}
	}
	width += border.left + border.right;
	width += padding.left + padding.right;
	return width;
}

int GUILayerNode::getContentHeight()
{
	auto height = 0;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		auto contentHeight = guiSubNode->getAutoHeight();
		if (contentHeight > height) {
			height = contentHeight;
		}
	}
	height += border.top + border.bottom;
	height += padding.top + padding.bottom;
	return height;
}

void GUILayerNode::setTop(int top)
{
	if (requestedConstraints.topType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) top = requestedConstraints.top;
	GUIParentNode::setTop(top);
	top += computedConstraints.alignmentTop;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		guiSubNode->setTop(top);
	}
}

void GUILayerNode::setLeft(int left)
{
	if (requestedConstraints.leftType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) left = requestedConstraints.left;
	GUIParentNode::setLeft(left);
	left += computedConstraints.alignmentLeft;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		guiSubNode->setLeft(left);
	}
}

void GUILayerNode::layoutSubNodes()
{
	if (conditionsMet == false) return;
	GUIParentNode::layoutSubNodes();
	auto height = computedConstraints.height - border.top - border.bottom - padding.top - padding.bottom;
	auto width = computedConstraints.width - border.left - border.right - padding.left - padding.right;
	for (auto i = 0; i < subNodes.size(); i++) {
		auto guiSubNode = subNodes[i];
		if (guiSubNode->conditionsMet == false) continue;
		auto doLayoutSubNodes = false;
		if (guiSubNode->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
			guiSubNode->computedConstraints.height = height;
			doLayoutSubNodes = true;
		} else
		if (guiSubNode->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::STAR) {
			guiSubNode->computedConstraints.width = width;
			doLayoutSubNodes = true;
		}
		if (dynamic_cast<GUIParentNode*>(guiSubNode) != nullptr && doLayoutSubNodes == true) {
			(required_dynamic_cast<GUIParentNode*>(guiSubNode))->layoutSubNodes();
		}
	}
	setTop(computedConstraints.top);
	setLeft(computedConstraints.left);
	computeHorizontalChildrenAlignment();
	computeVerticalChildrenAlignment();
}

void GUILayerNode::layout()
{
	if (conditionsMet == false) return;
	if (requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
		auto subNodesHeight = requestedConstraints.height - border.top - border.bottom - padding.top - padding.bottom;
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->conditionsMet == false) continue;
			if (overflowY == GUIParentNode_Overflow::DOWNSIZE_CHILDREN && guiSubNode->requestedConstraints.heightType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL && guiSubNode->requestedConstraints.height > subNodesHeight) {
				guiSubNode->requestedConstraints.height = subNodesHeight;
			}
		}
	}
	if (requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL) {
		auto subNodesWidth = requestedConstraints.width - border.left - border.right- padding.left - padding.right;
		for (auto i = 0; i < subNodes.size(); i++) {
			auto guiSubNode = subNodes[i];
			if (guiSubNode->conditionsMet == false) continue;
			if (overflowY == GUIParentNode_Overflow::DOWNSIZE_CHILDREN && guiSubNode->requestedConstraints.widthType == GUINode_RequestedConstraints_RequestedConstraintsType::PIXEL && guiSubNode->requestedConstraints.width > subNodesWidth) {
				guiSubNode->requestedConstraints.width = subNodesWidth;
			}
		}
	}
	GUIParentNode::layout();
}
