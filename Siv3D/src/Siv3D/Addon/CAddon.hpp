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
# include <Siv3D/Array.hpp>
# include <Siv3D/IAddon.hpp>
# include "IAddon.hpp"

namespace s3d
{
	struct AddonData
	{
		std::unique_ptr<IAddon> pAddon;

		String name;

		int32 updatePriority = 0;

		int32 drawPriority = 0;

		AddonData() = default;

		AddonData(std::unique_ptr<IAddon>&& _pAddon, StringView _name, int32 _updatePriority, int32 _drawPriority);
	};

	class CAddon final : public ISiv3DAddon
	{
	private:

		Array<AddonData> m_addons;

		Array<std::pair<size_t, int32>> m_updateIndices;

		Array<std::pair<size_t, int32>> m_drawIndices;

	public:

		bool add(StringView name, std::unique_ptr<IAddon>&& addon, int32 updatePriority, int32 drawPriority) override;

		void remove(StringView name) override;

		void removeAll() override;

		bool isRegistered(StringView name) const noexcept override;

		IAddon* get(StringView name) override;

		bool update() override;

		void draw() const override;

		void postPresent() override;
	};
}
