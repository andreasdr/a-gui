#pragma once

#include <agui/agui.h>
#include <agui/audio/decoder/fwd-agui.h>
#include <agui/utilities/fwd-agui.h>
#include <agui/utilities/ExceptionBase.h>

using agui::utilities::ExceptionBase;

/**
 * Audio decoder exception
 * @author Andreas Drewke
 */
class agui::audio::decoder::AudioDecoderException: public ExceptionBase
{
public:

	/**
	 * @brief Public constructor
	 * @param message message exception message
	 */
	AudioDecoderException(const string& message) throw();

};
