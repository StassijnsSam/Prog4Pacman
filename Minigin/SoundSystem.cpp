#include "SoundSystem.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "ResourceManager.h"
#include <SDL_mixer.h>

namespace dae {
	class SoundSystem::SoundSystemImpl : public ISound{
	public:
		SoundSystemImpl();
        ~SoundSystemImpl();

        // Thread for processing sound requests
        std::thread soundThread = std::thread(&SoundSystem::SoundSystemImpl::soundThreadFunction, this);

        void Play(const std::string& soundName, const float volume){
            //Create sound
            std::string soundPath = ResourceManager::GetInstance().GetFullSoundPath(soundName);
            Mix_Chunk* sound = Mix_LoadWAV(soundPath.c_str());

            //Put it on the eventQueue
            std::unique_lock<std::mutex> lock(eventQueueMutex);
            eventQueue.push(SoundRequest{ sound, volume });
            eventQueueNotEmpty.notify_one();
        };

        void soundThreadFunction() {
            while (true) {
                // Wait for event queue to have a sound request
                std::unique_lock<std::mutex> lock(eventQueueMutex);
                eventQueueNotEmpty.wait(lock, [this]() { return !eventQueue.empty(); });

                // Get next sound request
                SoundRequest request = eventQueue.front();
                eventQueue.pop();
                lock.unlock();

                // Play sound
                Mix_VolumeChunk(request.sound, request.volume);
                Mix_PlayChannel(-1, request.sound, 0);
            }
        }

        void Stop() {
            Mix_CloseAudio();
            Mix_Quit();
        }

    private:
        struct SoundRequest
        {
            Mix_Chunk* sound;
            float volume;
        };

        // Event queue
        std::queue<SoundRequest> eventQueue{};
        std::mutex eventQueueMutex{};
        std::condition_variable eventQueueNotEmpty{};
	};
    SoundSystem::SoundSystemImpl::SoundSystemImpl()
    {
        // Initialize SDL_mixer
        Mix_Init(MIX_INIT_OGG);
        Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024);
    }
    SoundSystem::SoundSystemImpl::~SoundSystemImpl()
    {
        // Clean up SDL_mixer
        Mix_CloseAudio();
        Mix_Quit();
    }
}

dae::SoundSystem::SoundSystem()
{
    pImpl = std::make_unique<SoundSystemImpl>();
}

dae::SoundSystem::~SoundSystem()
{
}

void dae::SoundSystem::Play(const std::string& soundName, const float volume)
{
    pImpl->Play(soundName, volume);
}

void dae::SoundSystem::Stop()
{
    pImpl->Stop();
}

