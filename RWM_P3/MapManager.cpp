#include <MapManager.h>


MapManager::MapManager(int level, 
					   SDL_Renderer* renderer) 
					   : m_level(level), 
					   m_renderer(renderer),
					   m_completedLevels(-1),
					   m_numBombs(5),
					   m_health(CONSTANTS::PLAYER_STARTING_HEALTH),
					   m_goldAmount(0),
					   m_alive(true),
					   healthPosAssinged(false)
{
	m_bgPositions = std::vector<b2Vec2>();
	m_backTypes = std::vector<int>();
	m_blockHeights = std::vector<int>();

	m_levelBlockPositions = std::vector<b2Vec2>();
	m_backPositions = std::vector<b2Vec2>();
	m_backPositionsOnes = std::vector<b2Vec2>();
	m_blockTypes = std::vector<int>();
	m_blockTypesOnes = std::vector<int>();
	/*
	m_bgPositions.reserve(5000);
	m_backTypes.reserve(5000);
	m_blockHeights.reserve(5000);
	m_levelBlockPositions.reserve(5000);
	m_backPositions.reserve(6000);
	m_backPositionsOnes.reserve(5000);
	m_blockTypes.reserve(5000);
	m_blockTypesOnes.reserve(5000);
	*/
	m_type0Rooms = std::vector<Room*>();
	m_type1Rooms = std::vector<Room*>();
	m_type2Rooms = std::vector<Room*>();
	m_type3Rooms = std::vector<Room*>();
	
	m_type0Paths = std::vector<std::string>();
	m_type1Paths = std::vector<std::string>();
	m_type2Paths = std::vector<std::string>();
	m_type3Paths = std::vector<std::string>();

	m_type0Paths.push_back("levels/type0/Spelunky1.tmx");
	m_type0Paths.push_back("levels/type0/Spelunky2.tmx");
	m_type0Paths.push_back("levels/type0/Spelunky3.tmx");
	m_type0Paths.push_back("levels/type0/Spelunky4.tmx");
	m_type0Paths.push_back("levels/type0/Spelunky5.tmx");
	m_type0Paths.push_back("levels/type0/Spelunky6.tmx");
	m_type0Paths.push_back("levels/type0/Spelunky7.tmx");
	m_type0Paths.push_back("levels/type0/Spelunky8.tmx");

	m_type1Paths.push_back("levels/type1/Spelunky1.tmx");
	m_type1Paths.push_back("levels/type1/Spelunky2.tmx");
	m_type1Paths.push_back("levels/type1/Spelunky3.tmx");
	m_type1Paths.push_back("levels/type1/Spelunky4.tmx");
	m_type1Paths.push_back("levels/type1/Spelunky5.tmx");
	m_type1Paths.push_back("levels/type1/Spelunky6.tmx");
	m_type1Paths.push_back("levels/type1/Spelunky7.tmx");
	m_type1Paths.push_back("levels/type1/Spelunky8.tmx");

	m_type2Paths.push_back("levels/type2/Spelunky1.tmx");
	m_type2Paths.push_back("levels/type2/Spelunky2.tmx");
	m_type2Paths.push_back("levels/type2/Spelunky3.tmx");
	m_type2Paths.push_back("levels/type2/Spelunky4.tmx");
	m_type2Paths.push_back("levels/type2/Spelunky5.tmx");
	m_type2Paths.push_back("levels/type2/Spelunky6.tmx");
	m_type2Paths.push_back("levels/type2/Spelunky7.tmx");
	m_type2Paths.push_back("levels/type2/Spelunky8.tmx");

	m_type3Paths.push_back("levels/type3/Spelunky1.tmx");
	m_type3Paths.push_back("levels/type3/Spelunky2.tmx");
	m_type3Paths.push_back("levels/type3/Spelunky3.tmx");
	m_type3Paths.push_back("levels/type3/Spelunky4.tmx");
	m_type3Paths.push_back("levels/type3/Spelunky5.tmx");
	m_type3Paths.push_back("levels/type3/Spelunky6.tmx");
	m_type3Paths.push_back("levels/type3/Spelunky7.tmx");

	AddToVectors();

	LoadObjects(m_type0Paths, &m_type0Rooms);
	LoadObjects(m_type1Paths, &m_type1Rooms);
	LoadObjects(m_type2Paths, &m_type2Rooms);
	LoadObjects(m_type3Paths, &m_type3Rooms);
	
}
int MapManager::GetCompletedLevels()
{
	return m_completedLevels;
}

void MapManager::AddLevel()
{
	m_level++;
}

int  MapManager::GetLevel()
{
	return m_level;
}

void MapManager::ResetLevel()
{
	m_level = -1;
}

void MapManager::AddToVectors()
{
	++m_completedLevels;
	m_levelBlockPositions.clear();
	m_backPositions.clear();
	m_backPositionsOnes.clear();
	m_blockTypes.clear();
	m_blockTypesOnes.clear();

	m_row0Offsets = std::vector<b2Vec2>();
	m_row1Offsets = std::vector<b2Vec2>();
	m_row2Offsets = std::vector<b2Vec2>();
	m_row3Offsets = std::vector<b2Vec2>();

	m_row0Offsets.push_back(b2Vec2(100, 50));
	m_row0Offsets.push_back(b2Vec2(700, 50));
	m_row0Offsets.push_back(b2Vec2(1300, 50));
	m_row0Offsets.push_back(b2Vec2(1900, 50));

	m_row1Offsets.push_back(b2Vec2(100, 450));
	m_row1Offsets.push_back(b2Vec2(700, 450));
	m_row1Offsets.push_back(b2Vec2(1300, 450));
	m_row1Offsets.push_back(b2Vec2(1900, 450));

	m_row2Offsets.push_back(b2Vec2(100, 850));
	m_row2Offsets.push_back(b2Vec2(700, 850));
	m_row2Offsets.push_back(b2Vec2(1300, 850));
	m_row2Offsets.push_back(b2Vec2(1900, 850));

	m_row3Offsets.push_back(b2Vec2(100, 1250));
	m_row3Offsets.push_back(b2Vec2(700, 1250));
	m_row3Offsets.push_back(b2Vec2(1300, 1250));
	m_row3Offsets.push_back(b2Vec2(1900, 1250));
}
MapManager::~MapManager()
{
	for(int i =0; i < m_type0Rooms.size(); ++i)
	{
		delete m_type0Rooms.at(i);
	}
	for(int i =0; i < m_type1Rooms.size(); ++i)
	{
		delete m_type1Rooms.at(i);
	}
	for(int i =0; i < m_type2Rooms.size(); ++i)
	{
		delete m_type2Rooms.at(i);
	}
	for(int i =0; i < m_type3Rooms.size(); ++i)
	{
		delete m_type3Rooms.at(i);
	}
	
}

void MapManager::LoadObjects(std::vector<std::string> paths, 
							 std::vector<Room*> *rooms)
{
	for (std::vector<std::string>::iterator iter = paths.begin(); iter != paths.end(); ++iter)	
	{
		m_map = new Tmx::Map();
		m_map->ParseFile(*iter);

		rooms->push_back(new Room());

		for (int i = 0; i < m_map->GetNumObjectGroups(); ++i)
		{
			if (0 == m_map->GetObjectGroup(i)->GetName().compare("dirt"))
			{
				const Tmx::ObjectGroup* walls = m_map->GetObjectGroup(0);
				std::vector<Tmx::Object*> wallArray = walls->GetObjects();
				for (std::vector<Tmx::Object*>::iterator it = wallArray.begin(); it != wallArray.end(); ++it)
				{
					b2Vec2 pos;
					pos.x = (*it)->GetX();
					pos.y = (*it)->GetY();
					int type = std::stoi((*it)->GetType());
					int height = (*it)->GetHeight();
					if(type == 50)
					{
						rooms->at(rooms->size()-1)->addSpawnPoint(pos);
					}
					else if (type == 70)
					{
						rooms->at(rooms->size()-1)->addSwitchPos(pos);
					}
					else if (type == 6)
					{
						rooms->at(rooms->size()-1)->addHealthPos(pos);
					}
					else
					{
						rooms->at(rooms->size()-1)->addPosition(pos);
						rooms->at(rooms->size()-1)->addType(type);
						rooms->at(rooms->size()-1)->addHeight(height);
					}
				}
			}

			if (0 == m_map->GetObjectGroup(i)->GetName().compare("bg"))
			{
				const Tmx::ObjectGroup* bg = m_map->GetObjectGroup(1);
				std::vector<Tmx::Object*> bgArray = bg->GetObjects();
				for (std::vector<Tmx::Object*>::iterator it = bgArray.begin(); it != bgArray.end(); ++it)
				{
					b2Vec2 pos;
					pos.x = (*it)->GetX();
					pos.y = (*it)->GetY();
					int type = std::stoi((*it)->GetType());
					rooms->at(rooms->size()-1)->addBackPosition(pos);
					rooms->at(rooms->size()-1)->addBackType(type);
				}
			}

		}
	}	
	
	LoadWorldBorder();
}
void MapManager::LoadWorldBorder()
{
	m_map = new Tmx::Map();
	m_map->ParseFile("levels/worldborder.tmx");

	for (int i = 0; i < m_map->GetNumObjectGroups(); ++i)
	{
		if (0 == m_map->GetObjectGroup(i)->GetName().compare("dirt"))
		{
			const Tmx::ObjectGroup* walls =m_map->GetObjectGroup(0);
			std::vector<Tmx::Object*> wallArray = walls->GetObjects();
			for (std::vector<Tmx::Object*>::iterator it = wallArray.begin(); it != wallArray.end(); ++it)
			{
				b2Vec2 pos;
				pos.x = (*it)->GetX();
				pos.y = (*it)->GetY();
				pos.y -= 50;
				int type = std::stoi((*it)->GetType());
				int height = (*it)->GetHeight();
				if (type == 0)
				{
					m_levelBlockPositions.push_back(pos);
					m_blockTypes.push_back(type);
					m_blockHeights.push_back(height);
				}
				else if (type == 60)
				{
					m_levelBlockPositions.push_back(pos);
					m_blockTypes.push_back(type);
					m_blockHeights.push_back(height);
				}
				else if(type == 2 || type == 3 || type == 4 || type == 5 || type == 6 || type == 7 || type == 8 || type == 9 )
				{
					m_backPositionsOnes.push_back(pos);
					m_blockTypesOnes.push_back(type);
				}
			}
		}
	}
}
void MapManager::Render(b2Vec2 offset)
{
	//for(std::vector<Tile*>::iterator it = tiles.begin(); it != tiles.end(); ++it)	{
	//(*it)->Render();
	//}
}


void MapManager::BuildWorld(int start, int counter, std::vector<b2Vec2> *offsets)
{
	int sp = 0;
	bool stayInLoop = true;
	int offset = 0;
	if(counter == 0)
	{
		offset = rand() % m_row0Offsets.size();		
	}
	else
	{
		offset = start;
	}
	int random = rand() %m_type1Rooms.size();
	vec = m_type1Rooms.at(random)->getBlockPositions();
	vecBack = m_type1Rooms.at(random)->getBackBlockPositions();
	heights = m_type1Rooms.at(random)->getBlockHeights();
	if (counter == 0)
	{
		m_startPoint = (m_type1Rooms.at(random)->getSpawnPoint()) + offsets->at(offset);
		m_startPoint.y += 40;
	}
	else if (counter == 3)
	{
		m_endPoint = (m_type1Rooms.at(random)->getSpawnPoint()) + offsets->at(offset);
		m_endPoint.y += 40;
	}

	vecType =  m_type1Rooms.at(random)->getBlockTypes();
	vecBackType = m_type1Rooms.at(random)->getBackBlockTypes();

	for (std::vector<b2Vec2>::iterator iter2 = vec.begin(); iter2 != vec.end(); ++iter2)
	{
		m_levelBlockPositions.push_back(*iter2 + offsets->at(offset));
	}
	for (std::vector<int>::iterator iter1 = heights.begin(); iter1 != heights.end(); ++iter1)
	{
		m_blockHeights.push_back(*iter1);
	}
	for(std::vector<int>::iterator m_iter = vecType.begin(); m_iter != vecType.end(); ++m_iter)
	{
		m_blockTypes.push_back(*m_iter);
	}
	for (std::vector<b2Vec2>::iterator iter3 = vecBack.begin(); iter3 != vecBack.end(); ++iter3)
	{
		m_bgPositions.push_back(*iter3 + offsets->at(offset));
	}
	for (std::vector<int>::iterator iter4 = vecBackType.begin(); iter4 != vecBackType.end(); ++iter4)
	{
		m_backTypes.push_back(*iter4);
	}

	offsets->erase(offsets->begin() + offset);

	while (!offsets->empty() && stayInLoop)
	{
		int nextDirection = rand()%2;
		//if were at very left, go right
		if (0 == offset)
		{
			++offset;
		}
		//at very right, go left
		else if (offset >= offsets->size())
		{
			--offset;
		}
		else if (0 == nextDirection){
			++offset;
		}
		else if (1 == nextDirection){
			--offset;
		}	
		int roomType = rand() % 3;
		if (2 == roomType || 0 == offset || offset == offsets->size())
		{
			if (offset == offsets->size())
			{
				--offset;
			}
			int random = rand() %m_type2Rooms.size();
			vec = m_type2Rooms.at(random)->getBlockPositions();
			vecType =  m_type2Rooms.at(random)->getBlockTypes();
			vecBack = m_type2Rooms.at(random)->getBackBlockPositions();
			vecBackType = m_type2Rooms.at(random)->getBackBlockTypes();
			heights = m_type2Rooms.at(random)->getBlockHeights();
			stayInLoop = false;	
			sp = offsets->at(offset).x;
			for (std::vector<b2Vec2>::iterator iter2 = vec.begin(); iter2 != vec.end(); ++iter2)
			{
				m_levelBlockPositions.push_back(*iter2 + offsets->at(offset));
			}
			for (std::vector<int>::iterator iter1 = heights.begin(); iter1 != heights.end(); ++iter1)
			{
				m_blockHeights.push_back(*iter1);
			}
			for(std::vector<int>::iterator m_iter = vecType.begin(); m_iter != vecType.end(); ++m_iter)
			{
				m_blockTypes.push_back(*m_iter);
			}
			for (std::vector<b2Vec2>::iterator iter3 = vecBack.begin(); iter3 != vecBack.end(); ++iter3)
			{
				m_bgPositions.push_back(*iter3 + offsets->at(offset));
			}
			for (std::vector<int>::iterator iter4 = vecBackType.begin(); iter4 != vecBackType.end(); ++iter4)
			{
				m_backTypes.push_back(*iter4);
			}
		}
		else
		{
			int random = rand() %m_type1Rooms.size();
			vec = m_type1Rooms.at(random)->getBlockPositions();
			vecType = m_type1Rooms.at(random)->getBlockTypes();
			vecBack = m_type1Rooms.at(random)->getBackBlockPositions();
			vecBackType = m_type1Rooms.at(random)->getBackBlockTypes();
			heights = m_type1Rooms.at(random)->getBlockHeights();

			for(std::vector<b2Vec2>::iterator iter2 = vec.begin(); iter2 != vec.end(); ++iter2)
			{
				m_levelBlockPositions.push_back(*iter2 + offsets->at(offset));
			}
			for (std::vector<int>::iterator iter1 = heights.begin(); iter1 != heights.end(); ++iter1)
			{
				m_blockHeights.push_back(*iter1);
			}
			for(std::vector<int>::iterator m_iter = vecType.begin(); m_iter != vecType.end(); ++m_iter)
			{
				m_blockTypes.push_back(*m_iter);
			}
			for (std::vector<b2Vec2>::iterator iter3 = vecBack.begin(); iter3 != vecBack.end(); ++iter3)
			{
				m_bgPositions.push_back(*iter3 + offsets->at(offset));
			}
			for (std::vector<int>::iterator iter4 = vecBackType.begin(); iter4 != vecBackType.end(); ++iter4)
			{
				m_backTypes.push_back(*iter4);
			}
		}
		offsets->erase(offsets->begin() + offset);
	}
	
	while (!offsets->empty())
	{
		int random = rand() %m_type0Rooms.size();
		std::vector<b2Vec2> vec = m_type0Rooms.at(random)->getBlockPositions();
		std::vector<int> vecType = m_type0Rooms.at(random)->getBlockTypes();
		std::vector<b2Vec2> vecBack = m_type0Rooms.at(random)->getBackBlockPositions();
		std::vector<int> vecBackType = m_type0Rooms.at(random)->getBackBlockTypes();
		std::vector<int> vecHeights = m_type0Rooms.at(random)->getBlockHeights();

		if (counter == 2 || counter == 3)
		{
			m_switchPos = (m_type0Rooms.at(random)->getSwitchPos()) + offsets->at(offsets->size() - 1);
			m_switchPos.y += 60;
		} 

		if (!healthPosAssinged)
		{
			m_healthPos = (m_type0Rooms.at(random)->getHealthPos()) + offsets->at(offsets->size() - 1);
			m_healthPos.y += 40;
			healthPosAssinged = true;
		} 

		std::cout << "t:0 x:" << offsets->at(offsets->size() - 1).x << "  y:" << offsets->at(offsets->size() - 1).y << std::endl;
		for (std::vector<b2Vec2>::iterator iter2 = vec.begin(); iter2 != vec.end(); ++iter2)
		{
			m_levelBlockPositions.push_back(*iter2 + offsets->at(offsets->size() - 1));
		}
		for (std::vector<int>::iterator iter1 = vecHeights.begin(); iter1 != vecHeights.end(); ++iter1)
		{
			m_blockHeights.push_back(*iter1);
		}
		for(std::vector<int>::iterator m_iter = vecType.begin(); m_iter != vecType.end(); ++m_iter)
		{
			m_blockTypes.push_back(*m_iter);
		}
		for (std::vector<b2Vec2>::iterator iter3 = vecBack.begin(); iter3 != vecBack.end(); ++iter3)
		{
			m_bgPositions.push_back(*iter3 + offsets->at(offsets->size() - 1));
		}
		for (std::vector<int>::iterator iter4 = vecBackType.begin(); iter4 != vecBackType.end(); ++iter4)
		{
			m_backTypes.push_back(*iter4);
		}
		offsets->pop_back();
	}
	if(counter == 0)
	{
		BuildWorld(sp/600,++counter,&m_row1Offsets);
	}
	else if(counter == 1)
	{
		BuildWorld(sp/600,++counter,&m_row2Offsets);
	}
	else if(counter == 2)
	{
		BuildWorld(sp/600,++counter,&m_row3Offsets);
	}
	
}


void MapManager::BuyBomb()
{
	if (m_goldAmount >= 5)
	{
		SoundManager::getSoundManager()->PlayPurchase();
		AddBomb();
		m_goldAmount -=5;
	}
}
void MapManager::ResetHud()
{
	m_goldAmount = 0;
	m_numBombs = 5;
	m_health = 4;
}

void MapManager::AddLife()
{
	m_health++;
}

void MapManager::AddBomb()
{
	m_numBombs++;
}

b2Vec2 MapManager::GetHealthPickupPos()
{
	return m_healthPos;
}

void MapManager::DecreseHealth(int difference)
{
	SoundManager::getSoundManager()->PlayHit();
	m_health -= difference;
}

void MapManager::DecreaseNumBombs()
{
	m_numBombs--;
}

void MapManager::IncreaseGold()
{
	m_goldAmount++;
}

int MapManager::GetBombs()
{
	return m_numBombs;
}

int MapManager::GetJewels()
{
	return m_goldAmount;
}

int MapManager::GetLives()
{
	return m_health;
}


bool MapManager::CheckPlayerDead()
{
	if (m_alive == false)
	{
		return false;
	}
	return true;
}




b2Vec2 MapManager::GetSwitchPos()
{
	return m_switchPos;
}
std::vector<b2Vec2> MapManager::BuildLevel()
{
	BuildWorld(0,0,&m_row0Offsets);
	return m_levelBlockPositions;
}

std::vector<int> MapManager::getBlockHeights()
{
	return m_blockHeights;
}

std::vector<int> MapManager::getTypes()
{
	return m_blockTypes;
}

std::vector<int> MapManager::getBgTypesOnes()
{
	return m_blockTypesOnes;
}

std::vector<b2Vec2> MapManager::getBgPositions()
{
	return m_bgPositions;
}

std::vector<b2Vec2> MapManager::getBgPos()
{
	return m_backPositions;
}

std::vector<b2Vec2> MapManager::getBgPosOnes()
{
	return m_backPositionsOnes;
}

std::vector<int> MapManager::getBgTypes()
{
	return m_backTypes;
}

b2Vec2 MapManager::GetEndPoint()
{
	return m_endPoint;
}

b2Vec2 MapManager::GetStartPoint()
{
	return m_startPoint;
}

void MapManager::SetDead()
{
	m_alive = false;
}