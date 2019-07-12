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

# include "P2ContactListner.hpp"
# include "Physics2DUtility.hpp"
# include "P2BodyDetail.hpp"

namespace s3d
{
	void P2ContactListener::BeginContact(b2Contact* contact)
	{
		const P2Body::P2BodyDetail* pBodyA = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureA()->GetBody()->GetUserData());
		const P2Body::P2BodyDetail* pBodyB = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureB()->GetBody()->GetUserData());
		const P2ContactPair pair{ pBodyA->id(), pBodyB->id() };

		if (auto it = m_collisions.find(pair); it != m_collisions.end())
		{
			++(it.value()._internal_count);
		}
		else
		{
			m_collisions.emplace(pair, P2Collision());
		}
	}

	void P2ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		const P2Body::P2BodyDetail* pBodyA = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureA()->GetBody()->GetUserData());
		const P2Body::P2BodyDetail* pBodyB = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureB()->GetBody()->GetUserData());
		const P2ContactPair pair{ pBodyA->id(), pBodyB->id() };

		auto& collision = m_collisions.find(pair).value();
		const uint32 current_num_contacts = static_cast<uint32>(contact->GetManifold()->pointCount);
		collision.num_contacts = std::max(collision.num_contacts, current_num_contacts);

		if (current_num_contacts)
		{
			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);
			collision.normal = detail::ToVec2(worldManifold.normal);

			for (uint32 i = 0; i < current_num_contacts; ++i)
			{
				auto& c = collision.contacts[i];
				c.point = detail::ToVec2(worldManifold.points[i]);
			}

			for (int32 i = 0; i < impulse->count; ++i)
			{
				auto& c = collision.contacts[i];
				c.normalImpulse += impulse->normalImpulses[i];
				c.tangentImpulse += impulse->tangentImpulses[i];
			}
		}
	}

	void P2ContactListener::EndContact(b2Contact* contact)
	{
		const P2Body::P2BodyDetail* pBodyA = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureA()->GetBody()->GetUserData());
		const P2Body::P2BodyDetail* pBodyB = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureB()->GetBody()->GetUserData());
		const P2ContactPair pair{ pBodyA->id(), pBodyB->id() };

		if (auto it = m_collisions.find(pair); it != m_collisions.end())
		{
			if (--(it.value()._internal_count) == 0)
			{
				m_collisions.erase(it);
			}
		}
	}

	const HashTable<P2ContactPair, P2Collision>& P2ContactListener::getCollisions() const
	{
		return m_collisions;
	}

	void P2ContactListener::clearContacts()
	{
		const auto itEnd = m_collisions.end();

		for (auto it = m_collisions.begin(); it != itEnd; ++it)
		{
			it.value().num_contacts = 0;
			it.value().contacts[0].clearImpulse();
			it.value().contacts[1].clearImpulse();
		}
	}
}
