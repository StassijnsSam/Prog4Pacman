#pragma once
namespace dae {
	class ServiceLocator final
	{
    public:
        ServiceLocator(const ServiceLocator& other) = delete;
        ServiceLocator(ServiceLocator&& other) = delete;
        ServiceLocator& operator=(const ServiceLocator& other) = delete;
        ServiceLocator& operator=(ServiceLocator&& other) = delete;

        //static void Initialize();
        //static void Provide();
        //static ISound* GetSoundService();

    private:
        ServiceLocator() = default;
        ~ServiceLocator() = default;
	};
}

