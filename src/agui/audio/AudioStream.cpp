#include <agui/audio/AudioStream.h>

#if defined(__APPLE__)
	#define AL_SILENCE_DEPRECATION
	#include <OpenAL/al.h>
#elif defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__linux__) || defined(_WIN32) || defined(__HAIKU__)
	#include <AL/al.h>
#endif

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <agui/agui.h>
#include <agui/audio/Audio.h>
#include <agui/math/Vector3.h>
#include <agui/os/filesystem/FileSystemException.h>
#include <agui/utilities/ByteBuffer.h>
#include <agui/utilities/Console.h>

using agui::audio::AudioStream;

using std::array;
using std::string;
using std::to_string;
using std::unique_ptr;
using std::vector;

using agui::audio::Audio;
using agui::math::Vector3;
using agui::utilities::ByteBuffer;
using agui::utilities::Console;

void AudioStream::setParameters(uint32_t sampleRate, uint8_t channels, const int64_t bufferSize) {
	this->sampleRate = sampleRate;
	this->channels = channels;
	this->data = unique_ptr<ByteBuffer>(ByteBuffer::allocate(bufferSize));
}

bool AudioStream::isPlayingBuffers() {
	ALint state;
	alGetSourcei(alSourceId, AL_SOURCE_STATE, &state);
	return state == AL_PLAYING;
}

bool AudioStream::isPlaying()
{
	return isPlayingBuffers() == true || playing == true;
}

void AudioStream::rewind()
{
}

void AudioStream::play()
{
	if (initiated == false)
		return;

	//
	stop();

	// update AL properties
	updateProperties();
	ALsizei buffersToPlay = 0;
	for (auto i = 0; i < alBufferIds.size(); i++) {
		data->clear();
		fillBuffer(data.get());
		// skip if no more data is available
		if (data->getPosition() == 0) break;
		// otherwise upload
		alBufferData(alBufferIds[i], format, data->getBuffer(), data->getPosition(), sampleRate);
		//
		if (alGetError() != AL_NO_ERROR) {
			Console::printLine(string("AudioStream::play(): '"+ id + "': Could not upload buffer"));
		}
		buffersToPlay++;
	}

	alSourceQueueBuffers(alSourceId, buffersToPlay, alBufferIds.data());
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::play(): '" + id + "': Could not queue buffers"));
	}
	alSourcePlay(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::play(): '"+ id + "': Could not play source"));
	}

	//
	playing = true;
}

void AudioStream::pause()
{
	if (initiated == false)
		return;

	alSourcePause(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::pause(): '" + id + "': Could not pause"));
	}
}

void AudioStream::stop()
{
	if (initiated == false)
		return;

	alSourceStop(alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::stop(): '" + id + "': Could not stop"));
	}
	// determine queued buffers
	ALint queuedBuffers;
	alGetSourcei(alSourceId, AL_BUFFERS_QUEUED, &queuedBuffers);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::stop(): '" + id + "': Could not determine queued buffers"));
	}
	// unqueue buffers
	if (queuedBuffers > 0) {
		vector<uint32_t> removedBuffers;
		removedBuffers.resize(queuedBuffers);
		alSourceUnqueueBuffers(alSourceId, queuedBuffers, removedBuffers.data());
		if (alGetError() != AL_NO_ERROR) {
			Console::printLine(string("AudioStream::stop(): '" + id + "': Could not unqueue buffers"));
		}
	}

	//
	playing = false;
}

bool AudioStream::initialize()
{
	switch (channels) {
		case(1): format = AL_FORMAT_MONO16; break;
		case(2): format = AL_FORMAT_STEREO16; break;
		default:
			Console::printLine(string("AudioStream::initialize(): '" + id + "': Unsupported number of channels"));
	}

	alGenBuffers(alBufferIds.size(), alBufferIds.data());
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::initialize(): '" + id + "': Could not generate buffer"));
		return false;
	}
	// create source
	alGenSources(1, &alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::initialize(): '" + id + "': Could not generate source"));
		dispose();
		return false;
	}
	// initiate sound properties
	updateProperties();
	initiated = true;
	return true;
}

void AudioStream::update()
{
	if (initiated == false)
		return;

	// determine processed buffers
	int32_t processedBuffers;
	alGetSourcei(alSourceId, AL_BUFFERS_PROCESSED, &processedBuffers);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::update(): '" + id + "': Could not determine processed buffers"));
	}
	if (isPlayingBuffers() == false && playing == true) {
		play();
	} else {
		while (processedBuffers > 0) {
			// get a processed buffer id and unqueue it
			uint32_t processedBufferId;
			alSourceUnqueueBuffers(alSourceId, 1, &processedBufferId);
			if (alGetError() != AL_NO_ERROR) {
				Console::printLine(string("AudioStream::update(): '" + id + "': Could not unqueue buffers"));
			}
			// fill processed buffer again
			data->clear();
			fillBuffer(data.get());
			// stop buffer if not filled
			if (data->getPosition() == 0) {
				playing = false;
			} else {
				// upload buffer data
				alBufferData(processedBufferId, format, data->getBuffer(), data->getPosition(), sampleRate);
				if (alGetError() != AL_NO_ERROR) {
					Console::printLine(string("AudioStream::update(): '" + id + "': Could not upload buffer"));
				}
				// queue it
				alSourceQueueBuffers(alSourceId, 1, &processedBufferId);
				if (alGetError() != AL_NO_ERROR) {
					Console::printLine(string("AudioStream::update(): '" + id + "': Could not queue buffer"));
				}
				// stop buffer if not filled completely
				if (data->getPosition() < data->getCapacity()) {
					playing = false;
				}
			}
			// processed it
			processedBuffers--;
		}
	}
	// update AL properties
	updateProperties();
}

void AudioStream::updateProperties()
{
	// update sound properties
	alSourcef(alSourceId, AL_PITCH, pitch);
	alSourcef(alSourceId, AL_GAIN, gain);
	alSourcefv(alSourceId, AL_POSITION, sourcePosition.getArray().data());
	alSourcefv(alSourceId, AL_DIRECTION, sourceDirection.getArray().data());
	alSourcefv(alSourceId, AL_VELOCITY, sourceVelocity.getArray().data());
	if (fixed == true) {
		alSourcef(alSourceId, AL_ROLLOFF_FACTOR, 0.0f);
		alSourcei(alSourceId, AL_SOURCE_RELATIVE, AL_TRUE);
	} else {
		alSourcef(alSourceId, AL_ROLLOFF_FACTOR, 1.0f);
		alSourcei(alSourceId, AL_SOURCE_RELATIVE, AL_FALSE);
	}
}

void AudioStream::dispose()
{
	if (initiated == false)
		return;
	//
	alDeleteSources(1, &alSourceId);
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::dispose(): '" + id + "': Could not delete source"));
	}
	alSourceId = Audio::ALSOURCEID_NONE;
	//
	alDeleteBuffers(alBufferIds.size(), alBufferIds.data());
	if (alGetError() != AL_NO_ERROR) {
		Console::printLine(string("AudioStream::dispose(): '" + id + "': Could not delete buffers"));
	}
	alBufferIds.fill(Audio::ALBUFFERID_NONE);
	//
	data = nullptr;
	//
	initiated = false;
}
