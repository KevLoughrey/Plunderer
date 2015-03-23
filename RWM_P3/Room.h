#pragma once

#include <Box2D\Box2D.h>
#include <vector>

class Room
{
public:
	Room();
	~Room(void);
	void addPosition(b2Vec2 position);
	void addType(int type);
	void addBackPosition(b2Vec2 position);
	void addBackType(int type);
	void addHeight(int height);
	void addSpawnPoint(b2Vec2 position);
	void addSwitchPos(b2Vec2 pos);
	void addHealthPos(b2Vec2 pos);
	std::vector<b2Vec2> getBlockPositions();
	std::vector<int> getBlockTypes();
	std::vector<b2Vec2> getBackBlockPositions();
	std::vector<int> getBackBlockTypes();
	std::vector<int> getBlockHeights();
	b2Vec2 getSpawnPoint();
	b2Vec2 getSwitchPos();
	b2Vec2 getHealthPos();

protected:
	std::vector<b2Vec2> m_blockPositions;
	std::vector<int> m_blockTypes;
	std::vector<int> m_blockHeights;
	std::vector<b2Vec2> m_backBlockPositions;
	std::vector<int> m_backBlockTypes;
	b2Vec2 m_spawnPoint;
	b2Vec2 m_switchPos;
	b2Vec2 m_healthPos;
};

