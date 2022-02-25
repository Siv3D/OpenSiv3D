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
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"
# include "AssetState.hpp"
# include "AssetInfo.hpp"

namespace s3d
{
	class IAsset
	{
	public:

		IAsset();

		explicit IAsset(const Array<String>& tags);

		virtual ~IAsset();

		virtual bool load(const String& hint = {}) = 0;

		virtual void loadAsync(const String& hint = {}) = 0;

		virtual void wait() = 0;

		virtual void release() = 0;

		[[nodiscard]]
		AssetState getState() const;

		[[nodiscard]]
		const Array<AssetTag>& getTags() const;

		[[nodiscard]]
		bool isAsyncLoading() const;

		[[nodiscard]]
		bool isFinished() const;

	protected:

		[[nodiscard]]
		bool isUninitialized() const;

		[[nodiscard]]
		bool isLoaded() const;

		void setState(AssetState state);

	private:

		class IAssetDetail;

		std::shared_ptr<IAssetDetail> pImpl;
	};
}
