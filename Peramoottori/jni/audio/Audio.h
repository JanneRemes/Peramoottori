#ifndef AUDIO_H
#define AUDIO_H

#include "audio\AudioPlayer.h"
#include "resources\ResourceReader.h"
#include "system\PMassert.h"
#include "System\PMdebug.h"

#include <string>
#include <vector>

namespace pm
{
	class Audio
	{
	public:

		Audio(std::string fileName);
		~Audio();

		void Play();
		void Stop();
		
		void SetLooping(bool isEnabled);

	private:
	
		AudioPlayer* player;
	};
}
#endif //AUDIO_H