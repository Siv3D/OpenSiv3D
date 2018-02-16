//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2018 Ryo Suzuki
//	Copyright (c) 2016-2018 OpenSiv3D Project
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
}
