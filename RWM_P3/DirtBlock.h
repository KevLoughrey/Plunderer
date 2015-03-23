// ------------------------------------------------------------------
//
// PLATFORM : ALL
// PRODUCT : Plunderer
// VISIBILITY : PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE : This is used for the standard blocks built using the tiled map


#pragma once

#include <vector>
#include <Box2D\Box2D.h>
#include <BaseObject.h>
#include <Block.h>
#include <BlockParticles.h>
#include <TileBase.h>

class DirtBlock : public Block {
public:
	DirtBlock();
	/// Used to create a Block Object
	/// \param[world] The Box2d world used to add bodies
	/// \param[dimensions] the width and height of the object
	/// \param[position] the position to place the block
	/// \param[renderer] the renderer used to draw the block
	/// \param[type] if the block is destructable or not
	DirtBlock(b2World *world, 
			  b2Vec2 dimensions, 
			  b2Vec2 position, 
			  SDL_Renderer *renderer, 
			  int type);
	/// Destroye the Object
	virtual ~DirtBlock();
	/// Draws the object
	/// \param[offset] make sure the object draws in the correct position
	void Render(b2Vec2 offset);
	/// Destorys the body and fills the blocvk bits vector
	void Destroy();
	/// destorys the body after the block bits vector is empty
	void DestroyBody();
	/// Updates the blockbits if the vector is not empty
	/// \param[deltatime] used for smooth update of the block bit particles
	void Update(double deltaTime);
	/// returns if the block is not alive and blockbits is empty
	bool ShouldRemove();
	/// returns the body of the block
	b2Body* GetBody();

protected:
	/// if the block is alive or not
	bool m_alive;
	/// a vector to store the block particles
	std::vector<BlockParticles*> m_blockBits;
	/// the number of particles to generate
	int m_numParticles;
	/// the curve shape on the box so the player dosent stick
	b2EdgeShape m_edgeShape;
	/// if the block is destructable or not
	int m_blockType;
	/// check if the body is destroyed
	bool m_isBodyDestroyed;
};