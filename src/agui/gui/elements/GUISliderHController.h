#pragma once

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/utilities/MutableString.h>

using agui::gui::events::GUIKeyboardEvent;
using agui::gui::events::GUIMouseEvent;
using agui::gui::nodes::GUIElementController;
using agui::gui::nodes::GUINode;
using agui::gui::nodes::GUIParentNode;
using agui::utilities::MutableString;

/**
 * GUI horizontal slider controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUISliderHController final: public GUIElementController
{
	friend class GUISliderH;

private:
	GUINode* sliderNode { nullptr };
	GUIParentNode* sliderParentNode { nullptr };
	bool disabled { false };
	float valueFloat { 0.0f };
	MutableString value { };

	// forbid class copy
	FORBID_CLASS_COPY(GUISliderHController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUISliderHController(GUINode* node);

	/**
	 * Update slider
	 */
	void updateSlider();

public:
	// overridden methods
	bool isDisabled() override;
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;
	void tick() override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;

};
