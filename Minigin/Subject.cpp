#include "Subject.h"
#include "Observer.h"

void dae::Subject::AddObserver(Observer* pObserver)
{
	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(Observer* pObserver)
{
	m_pObservers.erase(std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver), m_pObservers.end());
}

void dae::Subject::Notify(GameObject* actor, int event)
{
	for (auto pObserver : m_pObservers) {
		pObserver->Notify(actor, event);
	}
}
