#include "Achievements.h"


Achievements::Achievements(Subject* subject, SDL_Renderer* renderer)
	:m_subject(subject)
{
	m_subject->AddObserver(this);
	m_type = "Achievements";

	m_achievements.push_back(new Achievement("Ka-Ching", renderer));
	m_achievements.push_back(new Achievement("Kaboom", renderer));
	m_achievements.push_back(new Achievement("Instant Replay", renderer));
	m_achievements.push_back(new Achievement("Bat out of Hell", renderer));
	m_achievements.push_back(new Achievement("More Bandages", renderer));
	m_achievements.push_back(new Achievement("Hiss Off", renderer));
	m_achievements.push_back(new Achievement("Whiplash", renderer));
	m_achievements.push_back(new Achievement("Heartifact", renderer));
	m_achievements.push_back(new Achievement("Bullseye", renderer));
}


Achievements::~Achievements()
{
}

void Achievements::OnNotify(char* theEvent)
{
	if (theEvent == "gem destroyed")
	{
		Unlock("Ka-Ching");
	}
	else if (theEvent == "player bomb exploded")
	{
		Unlock("Kaboom");
	}
	else if (theEvent == "rewinding")
	{
		Unlock("Instant Replay");
	}
	else if (theEvent == "bat destroyed")
	{
		Unlock("Bat out of Hell");
	}
	else if (theEvent == "mummy destroyed")
	{
		Unlock("More Bandages");
	}
	else if (theEvent == "snake destroyed")
	{
		Unlock("Hiss Off");
	}
	else if (theEvent == "player whipped")
	{
		Unlock("Whiplash");
	}
	else if (theEvent == "life destroyed")
	{
		Unlock("Heartifact");
	}
	else if (theEvent == "player shot with arrow")
	{
		Unlock("Bullseye");
	}
}

void Achievements::Unlock(char* achievementName)
{
	for (int i = 0; i < m_achievements.size(); ++i) 
	{
		if (m_achievements.at(i)->GetName() == achievementName && !m_achievements.at(i)->GetIsUnlocked())
		{
			m_achievements.at(i)->Unlock();
		}
	}
}

void Achievements::Render()
{
	for (int i = 0; i < m_achievements.size(); ++i) 
	{
		if (m_achievements.at(i)->GetIsUnlocked() && m_achievements.at(i)->GetIsAlive())
		{
			m_achievements.at(i)->Render();
		}
		if (!m_achievements.at(i)->GetIsAlive()) 
		{
			delete m_achievements.at(i);
			m_achievements.erase(m_achievements.begin() + i);
		}
	}
}