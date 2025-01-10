#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/elements/fwd-agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>
#include <agui/gui/nodes/GUIElementController.h>
#include <agui/utilities/MutableString.h>

using std::string;

// namespaces
namespace agui {
namespace gui {
namespace elements {
	using ::agui::gui::events::GUIKeyboardEvent;
	using ::agui::gui::events::GUIMouseEvent;
	using ::agui::gui::nodes::GUIElementController;
	using ::agui::gui::nodes::GUINode;
	using ::agui::gui::nodes::GUIParentNode;
	using ::agui::utilities::MutableString;
}
}
}

/**
 * GUI grid item controller
 * @author Andreas Drewke
 */
class agui::gui::elements::GUIGridItemController: public GUIElementController
{
	friend class GUIGridItem;
	friend class GUIGridController;

protected:
	GUIParentNode* gridNode { nullptr };

private:
	STATIC_DLL_IMPEXT static string CONDITION_SELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_UNSELECTED;
	STATIC_DLL_IMPEXT static string CONDITION_FOCUSSED;
	STATIC_DLL_IMPEXT static string CONDITION_UNFOCUSSED;
	STATIC_DLL_IMPEXT static string CONDITION_DISABLED;
	STATIC_DLL_IMPEXT static string CONDITION_ENABLED;
	bool initialPostLayout;
	bool selected;
	bool focussed;
	MutableString value;

	// forbid class copy
	FORBID_CLASS_COPY(GUIGridItemController)

	/**
	 * Private constructor
	 * @param node node
	 */
	GUIGridItemController(GUINode* node);

	/**
	 * @return is selected
	 */
	inline bool isSelected() {
		return selected;
	}

	/**
	 * Select
	 */
	void select();

	/**
	 * Unselect
	 */
	void unselect();

	/**
	 * Toggle selection
	 */
	void toggle();

	/**
	 * @return is focussed
	 */
	inline bool isFocussed() {
		return focussed;
	}

	/**
	 * Focus
	 */
	void focus();

	/**
	 * Unfocus
	 */
	void unfocus();

public:
	// overridden methods
	void setDisabled(bool disabled) override;
	void initialize() override;
	void dispose() override;
	void postLayout() override;
	void handleMouseEvent(GUINode* node, GUIMouseEvent* event) override;
	void handleKeyboardEvent(GUIKeyboardEvent* event) override;
	void onFocusGained() override;
	void onFocusLost() override;
	bool hasValue() override;
	const MutableString& getValue() override;
	void setValue(const MutableString& value) override;

};
