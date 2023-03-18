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
# include <Siv3D/Common.hpp>
# include <Siv3D/IAddon.hpp>

namespace s3d
{
	class SIV3D_NOVTABLE ISiv3DAddon
	{
	public:

		static ISiv3DAddon* Create();

		virtual ~ISiv3DAddon() = default;

		virtual bool add(StringView name, std::unique_ptr<IAddon>&& addon, int32 updatePriority, int32 drawPriority) = 0;

		virtual void remove(StringView name) = 0;

		virtual void removeAll() = 0;

		virtual bool isRegistered(StringView name) const noexcept = 0;

		virtual IAddon* get(StringView name) = 0;

		virtual bool update() = 0;

		virtual void draw() const = 0;

		virtual void postPresent() = 0;
	};
}
