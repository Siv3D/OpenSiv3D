//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Common.hpp"
# include "String.hpp"
# include "Array.hpp"

namespace s3d
{
	/// @brief アセット名
	using AssetName = String;

	using AssetNameView = StringView;

	/// @brief アセットタグ名
	using AssetTag = String;

	enum class LoadOption
	{
		Default,
	};

	class IAsset
	{
	public:

		IAsset();

		explicit IAsset(LoadOption loadOption, const Array<String>& tags);

		virtual ~IAsset();

		virtual bool load() = 0;

		[[nodiscard]]
		bool isFinished() const;

	protected:

		enum class State
		{
			Uninitialized,

			//PreloadingAsync,

			Loaded,

			Failed,
		};

		[[nodiscard]]
		bool isUninitialized() const;

		[[nodiscard]]
		bool isLoaded() const;

		void setState(State state);

	private:

		class IAssetDetail;

		std::shared_ptr<IAssetDetail> pImpl;
	};
}
