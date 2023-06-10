#include "Keyboard.h"

dae::Keyboard::Keyboard()
    :m_CurrentState(SDL_NUM_SCANCODES, 0),
    m_PreviousState(SDL_NUM_SCANCODES, 0),
    m_ButtonsPressedThisFrame(SDL_NUM_SCANCODES, 0),
    m_ButtonsReleasedThisFrame(SDL_NUM_SCANCODES, 0)
{
}

void dae::Keyboard::Update()
{
    SDL_PumpEvents();

    //Save the previous State
    m_PreviousState = m_CurrentState;

    //Get all the current keystates
    int numKeys{};
    const Uint8* pKeysState = SDL_GetKeyboardState(&numKeys);

    for (int i = 0; i < numKeys; ++i){
        m_CurrentState[i] = pKeysState[i];
    }
}

bool dae::Keyboard::IsButtonPressedThisFrame(SDL_Scancode key) const
{
    //Only if previously not pressed, and now pressed
    return m_CurrentState[key] && !m_PreviousState[key];
}

bool dae::Keyboard::IsButtonReleasedThisFrame(SDL_Scancode key) const
{
    //Only if previously pressed, and now not pressed
    return !m_CurrentState[key] && m_PreviousState[key];
}

bool dae::Keyboard::IsButtonPressed(SDL_Scancode key) const
{
    return m_CurrentState[key];
}
