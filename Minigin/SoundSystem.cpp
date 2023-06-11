#include "SoundSystem.h"
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <vector>
#include "ResourceManager.h"
#include <SDL_mixer.h>
#include <iostream>
#include <unordered_map>

namespace dae {
	class SoundSystem::SoundSystemImpl : public ISound{
	public:
		SoundSystemImpl();
        ~SoundSystemImpl();

        void Play(const std::string& soundName, const int volume){
            //Put it on the eventQueue
            std::unique_lock<std::mutex> lock(eventQueueMutex);
            eventQueue.push(SoundRequest{ soundName, volume });
            eventQueueNotEmpty.notify_one();
        };

        void SoundThreadFunction() {
            while (m_IsRunning) {
                // Wait for event queue to have a sound request
                std::unique_lock lock(eventQueueMutex);
                eventQueueNotEmpty.wait(lock, [this]() { return !m_IsRunning || !eventQueue.empty(); });

                if (!eventQueue.empty()) {
                    // Get next sound request
                    SoundRequest request = eventQueue.front();
                    eventQueue.pop();
                    lock.unlock();

                    Mix_Chunk* pSound;
                    // Check if you have already loaded this sound before
                    if (m_pLoadedSounds.contains(request.soundName)) {
                        pSound = m_pLoadedSounds.at(request.soundName);
                    }
                    else {
                        //Create sound
                        std::string soundPath = ResourceManager::GetInstance().GetFullSoundPath(request.soundName);
                        pSound = Mix_LoadWAV(soundPath.c_str());
                        m_pLoadedSounds.insert(std::pair(soundPath, pSound));
                    }


                    // Play sound
                    Mix_VolumeChunk(pSound, request.volume);
                    Mix_PlayChannel(-1, pSound, 0);
                }   
            }
        }

        void Stop() {

            m_IsRunning = false;

            //Clean up the loaded sounds
            for (auto soundPair : m_pLoadedSounds)
            {
                Mix_FreeChunk(soundPair.second);
                soundPair.second = nullptr;
            }

            Mix_CloseAudio();
            Mix_Quit();
        }

    private:
        struct SoundRequest
        {
            std::string soundName;
            int volume;
            //bool isLooping;
        };

        // Event queue
        std::queue<SoundRequest> eventQueue{};
        std::mutex eventQueueMutex{};
        std::condition_variable eventQueueNotEmpty{};

        // Thread
        std::jthread m_SoundThread;

        bool m_IsRunning{ true };

        // Already loaded sounds
        std::unordered_map<std::string, Mix_Chunk*> m_pLoadedSounds{};
	};

    SoundSystem::SoundSystemImpl::SoundSystemImpl()
    {
        // Initialize SDL_mixer
        Mix_Init(MIX_INIT_OGG);
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
            std::cout << "SDL_mixer initialization failed" << std::endl;
            return;
        }

        //Create sound thread
        m_SoundThread = std::jthread(&SoundSystemImpl::SoundThreadFunction, this);
    }

    SoundSystem::SoundSystemImpl::~SoundSystemImpl()
    {
        m_IsRunning = false;
        eventQueueNotEmpty.notify_one();

        //Clean up the loaded sounds
        for (auto soundPair : m_pLoadedSounds)
        {
            Mix_FreeChunk(soundPair.second);
            soundPair.second = nullptr;
        }

        // Clean up SDL_mixer
        Mix_CloseAudio();
        Mix_Quit();
    }
}

dae::SoundSystem::SoundSystem()
{
    pImpl = new SoundSystemImpl();
}

dae::SoundSystem::~SoundSystem()
{
    delete pImpl;
    pImpl = nullptr;
}

void dae::SoundSystem::Play(const std::string& soundName, const int volume)
{
    pImpl->Play(soundName, volume);
}

void dae::SoundSystem::Stop()
{
    pImpl->Stop();
}

