//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "Array.hpp"
# include "String.hpp"
# include "Texture.hpp"

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

		static AssetParameter Default()
		{
			return AssetParameter{};
		}

		static AssetParameter LoadImmediately()
		{
			AssetParameter parameter;

			parameter.loadImmediately = true;

			return parameter;
		}

		static AssetParameter LoadAsync()
		{
			AssetParameter parameter;

			parameter.loadImmediately = true;

			parameter.loadAsync = true;

			return parameter;
		}

		AssetParameter withTag(const AssetTag& tag) const
		{
			AssetParameter parameter(*this);

			parameter.tags << tag;

			return parameter;
		}

		AssetParameter withTag(const Array<AssetTag>& _tags) const
		{
			AssetParameter parameter(*this);

			parameter.tags.append(_tags);

			return parameter;
		}
	};

	/// <summary>
	/// アセットインタフェースクラス
	/// </summary>
	class IAsset
	{
	protected:

		AssetParameter parameter;

		std::shared_ptr<std::future<bool>> m_loadingThread;

		enum class State
		{
			Uninitialized,

			PreloadingAsync,

			LoadScceeded,

			LoadFailed,

		} m_state = State::Uninitialized;

		template <class Fty>
		void launchLoading(Fty&& fty)
		{
			m_loadingThread = std::make_unique<std::future<bool>>(std::async(std::launch::async, std::forward<Fty>(fty)));
		}

	public:

		IAsset() = default;

		IAsset(const AssetParameter& _parameter)
			: parameter(_parameter) {}

		virtual ~IAsset()
		{
			if (m_loadingThread)
			{
				m_loadingThread->wait();

				m_loadingThread.reset();
			}
		}

		virtual bool preload() = 0;

		virtual void preloadAsync() = 0;

		virtual bool update() = 0;

		virtual bool release() = 0;

		virtual const AssetParameter& getParameter() const
		{
			return parameter;
		}

		virtual bool isReady() const
		{
			if (!m_loadingThread)
			{
				return true;
			}

		# if defined(SIV3D_TARGET_WINDOWS)

			return m_loadingThread->_Is_ready();

		# else

			return m_loadingThread->wait_for(std::chrono::seconds(0)) == std::future_status::ready;

		# endif	
		}

		void wait()
		{
			if (m_state != State::PreloadingAsync)
			{
				return;
			}

			m_state = m_loadingThread->get() ? State::LoadScceeded : State::LoadFailed;

			m_loadingThread.reset();
		}

		bool isLoadingAsync()
		{
			if (m_state != State::PreloadingAsync)
			{
				return false;
			}
			
			if (isReady())
			{
				m_state = m_loadingThread->get() ? State::LoadScceeded : State::LoadFailed;
				
				m_loadingThread.reset();
				
				return false;
			}
			
			return false;
		}
		
		bool isPreloaded() const
		{
			return (m_state == State::LoadScceeded || m_state == State::LoadFailed);
		}

		bool loadScceeded() const
		{
			return (m_state == State::LoadScceeded);
		}
	};

	/// <summary>
	/// Texture アセットデータ
	/// </summary>
	struct TextureAssetData : IAsset
	{
		FilePath path;

		TextureDesc desc = TextureDesc::Unmipped;

		Texture texture;

		std::function<bool(TextureAssetData&)> onPreload = DefaultPreload;

		std::function<bool(TextureAssetData&)> onUpdate = DefaultUpdate;

		std::function<bool(TextureAssetData&)> onRelease = DefaultRelease;

		static const String& Name()
		{
			static const String name = U"Texture";

			return name;
		}

		static bool DefaultPreload(TextureAssetData& asset)
		{
			if (asset.texture)
			{
				return true;
			}

			asset.texture = Texture(asset.path, asset.desc);

			return !asset.texture.isEmpty();
		}

		static bool DefaultUpdate(TextureAssetData&)
		{
			return true;
		}

		static bool DefaultRelease(TextureAssetData& asset)
		{
			asset.texture.release();

			return true;
		}

		TextureAssetData() = default;

		explicit TextureAssetData(
			const FilePath& _path,
			TextureDesc _desc = TextureDesc::Unmipped,
			const AssetParameter& _parameter = AssetParameter(),
			std::function<bool(TextureAssetData&)> _onPreload = DefaultPreload,
			std::function<bool(TextureAssetData&)> _onUpdate = DefaultUpdate,
			std::function<bool(TextureAssetData&)> _onRelease = DefaultRelease);

		bool preload() override
		{
			if (m_state == State::Uninitialized)
			{
				m_state = onPreload(*this) ? State::LoadScceeded : State::LoadFailed;
			}

			return (m_state == State::LoadScceeded);
		}

		void preloadAsync() override
		{
			if (m_state == State::Uninitialized)
			{
				launchLoading([this]() { return onPreload(*this); });

				m_state = State::PreloadingAsync;
			}
		}

		bool update() override
		{
			if (!isPreloaded())
			{
				return false;
			}

			return onUpdate(*this);
		}

		bool release() override
		{
			if (m_state == State::Uninitialized)
			{
				return true;
			}

			const bool result = onRelease(*this);

			m_state = State::Uninitialized;

			return result;
		}
	};

	/// <summary>
	/// Texture アセット
	/// </summary>
	class TextureAsset : public Texture
	{
	public:

		TextureAsset(const AssetName& name);

		static bool Register(const AssetName& name, const FilePath& path, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const FilePath& path, TextureDesc desc, const AssetParameter& parameter = AssetParameter{});

		static bool Register(const AssetName& name, const TextureAssetData& data);

		static bool IsRegistered(const AssetName& name);

		static bool Preload(const AssetName& name);

		//static bool PreloadByTag(const AssetTag& tag);

		//static bool PreloadAll();

		static void Release(const AssetName& name);

		//static void ReleaseByTag(const AssetTag& tag);

		static void ReleaseAll();

		static void Unregister(const AssetName& name);

		//static void UnregisterByTag(const AssetTag& tag);

		static void UnregisterAll();

		static bool IsReady(const AssetName& name);
	};
}
