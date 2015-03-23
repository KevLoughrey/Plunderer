#include "Subject.h"

Subject::Subject()
{
	m_isActive = true;
}

void Subject::AddObserver(Observer* observer)
{
	m_observers.push_back(observer);
}

void Subject::RemoveObserver(Observer* observer)
{
	for (int i = 0; i < m_observers.size(); ++i) 
	{
		if (observer == m_observers.at(i))
		{
			m_observers.erase(m_observers.begin() + i);
			break;
		}
	}
}

void Subject::Notify(char* theEvent)
{
	if (m_isActive)
	{
		for (int i = 0; i < m_observers.size(); ++i)
		{
			if (m_observers.at(i)->m_type == "Achievements")
			{
				m_observers.at(i)->OnNotify(theEvent);
			}
		}
	}
}

void Subject::SetActive(bool toggle)
{
	m_isActive = toggle;
}