//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Physics2D.hpp>
# include <Box2D/Box2D.h>
# include <Siv3D/HashTable.hpp>

namespace s3d
{
	class P2ContactListener : public b2ContactListener
	{
	private:

		HashTable<P2ContactPair, P2Collision> m_collisions;

		void BeginContact(b2Contact* contact) override;

		void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

		void EndContact(b2Contact* contact) override;

	public:

		const HashTable<P2ContactPair, P2Collision>& getCollisions() const;

		void clearContacts();
	};
}
