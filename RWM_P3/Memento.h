// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Memento object which stores the last ten seconds of game state.

#pragma once
#include <Box2D\Box2D.h>
#include <vector>

class Memento
{
public:
	/// Constructor
	/// Creates a new memento
	Memento();

	/// Destructor
	/// Destorys the ladder
	~Memento();

	/// Push to positions list
	/// Push a new position to the vector of positions
	/// \position[in] the position to be pushed
	void PushToPositionsList(b2Vec2 position);

	/// Pop from positions list
	/// Pop the last vector from the positions and return it
	/// \return b2vec2 the position at the end of the vector
	b2Vec2 PopFromPositionsList();

protected:
	///the vector of positions
	std::vector<b2Vec2> m_positionsList;
};
