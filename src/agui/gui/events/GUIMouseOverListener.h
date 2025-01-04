#pragma once

#include <agui/agui.h>
#include <agui/gui/events/fwd-agui.h>
#include <agui/gui/nodes/fwd-agui.h>

using agui::gui::nodes::GUIElementNode;

/**
 * GUI mouse over listener
 * @author Andreas Drewke
 */
struct agui::gui::events::GUIMouseOverListener
{
	/**
	 * Destructor
	 */
	virtual ~GUIMouseOverListener() {}

	/**
	 * On mouse over
	 * @param node node
	 */
	virtual void onMouseOver(GUIElementNode* node) = 0;
};
