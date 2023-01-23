//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2022 Ryo Suzuki
//	Copyright (c) 2016-2022 OpenSiv3D Project
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

		int32 priority = 0;

		AddonData() = default;

		AddonData(std::unique_ptr<IAddon>&& _pAddon, StringView _name, int32 _priority)
			: pAddon{ std::move(_pAddon) }
			, name{ _name }
			, priority{ _priority } {}
	};

	class CAddon final : public ISiv3DAddon
	{
	private:

		Array<AddonData> m_addons;

	public:

		bool add(StringView name, std::unique_ptr<IAddon>&& addon, int32 priority) override;

		void remove(StringView name) override;

		void removeAll() override;

		bool isRegistered(StringView name) const noexcept override;

		IAddon* get(StringView name) override;

		bool update() override;

		void draw() const override;

		void postPresent() override;
	};
}
