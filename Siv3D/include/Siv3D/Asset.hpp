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
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"

namespace s3d
{
	/// <summary>
	/// アセット名
	/// </summary>
	using AssetName = String;

	/// <summary>
	/// アセットタグ名
	/// </summary>
	using AssetTag = String;

	struct AssetParameter
	{
		Array<AssetTag> tags;

		bool loadImmediately = false;

		bool loadAsync = false;

		[[nodiscard]] static AssetParameter Default();

		[[nodiscard]] static AssetParameter LoadImmediately();

		[[nodiscard]] static AssetParameter LoadAsync();

		[[nodiscard]] AssetParameter withTag(const AssetTag& tag) const;

		[[nodiscard]] AssetParameter withTag(const Array<AssetTag>& _tags) const;
	};

	/// <summary>
	/// アセットインタフェースクラス
	/// </summary>
	class IAsset
	{
	private:

		class IAssetDetail;

		std::shared_ptr<IAssetDetail> pImpl;

	protected:

		enum class State
		{
			Uninitialized,

			PreloadingAsync,

			LoadSucceeded,

			LoadFailed,
		};

		void setState(State state);

		[[nodiscard]] bool uninitialized() const;

		void launchLoading(std::function<bool()>&& loader);

	public:

		IAsset();

		explicit IAsset(const AssetParameter& parameter);

		virtual ~IAsset();

		virtual bool preload() = 0;

		virtual void preloadAsync() = 0;

		virtual bool update() = 0;

		virtual bool release() = 0;

		[[nodiscard]] virtual const AssetParameter& getParameter() const;

		[[nodiscard]] virtual bool isReady() const;

		void wait();

		[[nodiscard]] bool isLoadingAsync();
		
		[[nodiscard]] bool isPreloaded() const;

		[[nodiscard]] bool loadSucceeded() const;
	};
}
