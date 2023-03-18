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

# include "P2BodyDetail.hpp"
# include "P2ContactListener.hpp"

namespace s3d
{
	void detail::P2ContactListener::BeginContact(b2Contact* contact)
	{
		const P2Body::P2BodyDetail* pBodyA = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureA()->GetBody()->GetUserData().pBody);
		const P2Body::P2BodyDetail* pBodyB = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureB()->GetBody()->GetUserData().pBody);
		const P2ContactPair pair{ pBodyA->id(), pBodyB->id() };

		if (auto it = m_collisions.find(pair); it != m_collisions.end())
		{
			++(it->second.m_internalCount);
		}
		else
		{
			m_collisions.emplace(pair, P2Collision{});
		}
	}

	void detail::P2ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
	{
		const P2Body::P2BodyDetail* pBodyA = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureA()->GetBody()->GetUserData().pBody);
		const P2Body::P2BodyDetail* pBodyB = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureB()->GetBody()->GetUserData().pBody);
		const P2ContactPair pair{ pBodyA->id(), pBodyB->id() };

		auto& collision = m_collisions.find(pair)->second;
		const uint32 current_num_contacts = static_cast<uint32>(contact->GetManifold()->pointCount);
		collision.m_num_contacts = Max(collision.m_num_contacts, current_num_contacts);

		if (current_num_contacts)
		{
			b2WorldManifold worldManifold;
			contact->GetWorldManifold(&worldManifold);
			collision.m_normal = detail::ToVec2(worldManifold.normal);

			for (uint32 i = 0; i < current_num_contacts; ++i)
			{
				auto& c = collision.m_contacts[i];
				c.point = detail::ToVec2(worldManifold.points[i]);
			}

			for (int32 i = 0; i < impulse->count; ++i)
			{
				auto& c = collision.m_contacts[i];
				c.normalImpulse += impulse->normalImpulses[i];
				c.tangentImpulse += impulse->tangentImpulses[i];
			}
		}
	}

	void detail::P2ContactListener::EndContact(b2Contact* contact)
	{
		const P2Body::P2BodyDetail* pBodyA = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureA()->GetBody()->GetUserData().pBody);
		const P2Body::P2BodyDetail* pBodyB = static_cast<const P2Body::P2BodyDetail*>(contact->GetFixtureB()->GetBody()->GetUserData().pBody);		const P2ContactPair pair{ pBodyA->id(), pBodyB->id() };

		if (auto it = m_collisions.find(pair); it != m_collisions.end())
		{
			if (--(it->second.m_internalCount) == 0)
			{
				m_collisions.erase(it);
			}
		}
	}

	const HashTable<P2ContactPair, P2Collision>& detail::P2ContactListener::getCollisions() const noexcept
	{
		return m_collisions;
	}

	void detail::P2ContactListener::clearContacts()
	{
		const auto itEnd = m_collisions.end();

		for (auto it = m_collisions.begin(); it != itEnd; ++it)
		{
			auto& collision = it->second;
			collision.m_num_contacts = 0;
			collision.m_contacts[0].normalImpulse = 0.0;
			collision.m_contacts[0].tangentImpulse = 0.0;
			collision.m_contacts[1].normalImpulse = 0.0;
			collision.m_contacts[1].tangentImpulse = 0.0;
		}
	}
}
