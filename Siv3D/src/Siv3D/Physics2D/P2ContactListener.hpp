//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/HashTable.hpp>
# include <Siv3D/Physics2D/P2ContactPair.hpp>
# include <Siv3D/Physics2D/P2Collision.hpp>
# include "P2Common.hpp"

namespace s3d
{
	namespace detail
	{
		class P2ContactListener : public b2ContactListener
		{
		public:

			const HashTable<P2ContactPair, P2Collision>& getCollisions() const noexcept;

			void clearContacts();

		private:

			HashTable<P2ContactPair, P2Collision> m_collisions;

			void BeginContact(b2Contact* contact) override;

			void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

			void EndContact(b2Contact* contact) override;
		};
	}
}
