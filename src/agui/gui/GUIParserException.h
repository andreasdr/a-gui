#pragma once

#include <string>

#include <agui/agui.h>
#include <agui/gui/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/ExceptionBase.h>

using std::string;

using agui::utilities::ExceptionBase;

/**
 * GUI parser exception
 * @author Andreas Drewke
 */
class agui::gui::GUIParserException final: public ExceptionBase
{
public:
	/**
	 * Public constructor
	 */
	GUIParserException(const string& message);
};
