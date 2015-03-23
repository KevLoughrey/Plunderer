#include <Memento.h>

Memento::Memento()
{
}


Memento::~Memento()
{
}

void Memento::PushToPositionsList(b2Vec2 position)
{
	if (m_positionsList.size() > 600)
	{
		m_positionsList.erase(m_positionsList.begin());
	}
	m_positionsList.push_back(position);
}

b2Vec2 Memento::PopFromPositionsList()
{
	if (m_positionsList.size() > 1)
	{
		b2Vec2 v = m_positionsList.back();
		m_positionsList.pop_back();
		return v;
	}
	else
	{
		return m_positionsList.at(0);
	}
}