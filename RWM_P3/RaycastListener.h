// ------------------------------------------------------------------
//
// PLATFORM: ALL
// PRODUCT: PLUNDERER
// VISIBILITY: PUBLIC
//
// ------------------------------------------------------------------
// PURPOSE: Box2D raycast class, for player when the player uses the whip.

#pragma once

#include <Box2D\Box2D.h>
#include <Mummy.h>
#include <Snake.h>
#include <Bat.h>

class RayCastListener: public b2RayCastCallback
{
public:
	/// Constructor
	/// Creates a Raycast listener
	RayCastListener();

	/// Destructor
	/// Destroys the object
	~RayCastListener();

	/// Object intersected
	/// Has the raycast intersected a fixture?
	/// \return bool intersection or not
	bool ObjectIntersected();

	/// ReportFixture
	/// Box2D method for raycast response 
	/// \fixture[in] fixture that has been hit
	/// \point[in] point where the raycast hit
	/// \normal[in] normal to the ray hit
	/// \fraction[in] fraction along the ray where the hit occured
	/// \return float should the raycase continue or not?
	float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point,const b2Vec2& normal, float32 fraction);

protected:
	///has the raycast intersected a fixture?
	bool intersectedObject;
};