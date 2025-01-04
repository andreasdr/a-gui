#pragma once

#include <string>
#include <unordered_map>

#include <agui/agui.h>
#include <agui/audio/fwd-agui.h>

using std::string;
using std::unordered_map;

using agui::audio::AudioBufferManager_AudioBufferManaged;

/**
 * Audio buffer manager
 * @author Andreas Drewke
 */
class agui::audio::AudioBufferManager final
{
	friend class AudioBufferManager_AudioBufferManaged;
	friend class Audio;
	friend class Sound;

private:
	unordered_map<string, AudioBufferManager_AudioBufferManaged*> audioBuffers;

	// forbid class copy
	FORBID_CLASS_COPY(AudioBufferManager)

	/**
	 * Private constructor
	 */
	inline AudioBufferManager() {}

	/**
	 * Adds a audio buffer to manager / open al stack
	 * @param id id
	 * @return audio buffer managed
	 */
	AudioBufferManager_AudioBufferManaged* addAudioBuffer(const string& id);

	/**
	 * Removes a texture from manager / open gl stack
	 * @param id id
	 * @return true if caller has to remove the audio buffer from open AL
	 */
	bool removeAudioBuffer(const string& id);

};
