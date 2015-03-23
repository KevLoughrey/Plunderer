#include <Room.h>

Room::Room() 
{
	m_blockPositions = std::vector<b2Vec2>();
	m_blockTypes = std::vector<int>();
	m_backBlockPositions = std::vector<b2Vec2>();
	m_backBlockTypes = std::vector<int>();
	m_blockHeights = std::vector<int>();
}


Room::~Room()
{
}

void Room::addHealthPos(b2Vec2 pos)
{
	m_healthPos = pos;
}

void Room::addSpawnPoint(b2Vec2 pos)
{
	m_spawnPoint = pos;
}

void Room::addSwitchPos(b2Vec2 pos)
{
	m_switchPos = pos;
}

b2Vec2 Room::getHealthPos()
{
	return m_healthPos;
}

b2Vec2 Room::getSwitchPos()
{
	return m_switchPos;
}

void Room::addHeight(int height)
{
	m_blockHeights.push_back(height);
}

void Room::addPosition(b2Vec2 pos)
{
	m_blockPositions.push_back(pos);
}

void Room::addType(int type)
{
	m_blockTypes.push_back(type);
}

void Room::addBackPosition(b2Vec2 position)
{
	m_backBlockPositions.push_back(position);
}

void Room::addBackType(int type)
{
	m_backBlockTypes.push_back(type);
}

std::vector<int> Room::getBlockHeights()
{
	return m_blockHeights;
}

std::vector<b2Vec2> Room::getBlockPositions()
{
	return m_blockPositions;
}

std::vector<int> Room::getBlockTypes()
{
	return m_blockTypes;
}

b2Vec2 Room::getSpawnPoint()
{
	return m_spawnPoint;
}

std::vector<b2Vec2> Room::getBackBlockPositions()
{
	return m_backBlockPositions; 
}

std::vector<int> Room::getBackBlockTypes()
{
	return m_backBlockTypes;
}