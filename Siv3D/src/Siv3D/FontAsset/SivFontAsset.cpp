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

# include <Siv3D/FontAsset.hpp>
# include <Siv3DEngine.hpp>
# include <Asset/IAsset.hpp>

namespace s3d
{
	namespace detail
	{
		static Font FromAsset(const IAsset* asset)
		{
			if (const FontAssetData* fontAssetData = dynamic_cast<const FontAssetData*>(asset))
			{
				return fontAssetData->font;
			}

			return Font();
		}

		FilePath GetEngineFontPath(const Typeface typeface);
	}

	const String& FontAssetData::Name()
	{
		static const String name = U"Font";

		return name;
	}

	bool FontAssetData::DefaultPreload(FontAssetData& asset)
	{
		if (asset.font)
		{
			return true;
		}

		asset.font = Font(asset.fontSize, asset.path, asset.style);

		return !asset.font.isEmpty();
	}

	bool FontAssetData::DefaultUpdate(FontAssetData&)
	{
		return true;
	}

	bool FontAssetData::DefaultRelease(FontAssetData& asset)
	{
		asset.font.release();

		return true;
	}

	FontAssetData::FontAssetData()
		: IAsset()
		, onPreload(DefaultPreload)
		, onUpdate(DefaultUpdate)
		, onRelease(DefaultRelease)
	{

	}

	FontAssetData::FontAssetData(
		int32 _fontSize,
		Typeface typeface,
		FontStyle _style,
		const AssetParameter& _parameter,
		std::function<bool(FontAssetData&)> _onPreload,
		std::function<bool(FontAssetData&)> _onUpdate,
		std::function<bool(FontAssetData&)> _onRelease)
		: IAsset(_parameter)
		, fontSize(_fontSize)
		, path(detail::GetEngineFontPath(typeface))
		, style(_style)
		, onPreload(_onPreload)
		, onUpdate(_onUpdate)
		, onRelease(_onRelease)
	{

	}

	FontAssetData::FontAssetData(
		int32 _fontSize,
		const FilePath& _path,
		FontStyle _style,
		const AssetParameter& _parameter,
		std::function<bool(FontAssetData&)> _onPreload,
		std::function<bool(FontAssetData&)> _onUpdate,
		std::function<bool(FontAssetData&)> _onRelease)
		: IAsset(_parameter)
		, fontSize(_fontSize)
		, path(_path)
		, style(_style)
		, onPreload(_onPreload)
		, onUpdate(_onUpdate)
		, onRelease(_onRelease)
	{

	}

	bool FontAssetData::preload()
	{
		if (uninitialized())
		{
			setState(onPreload(*this) ? State::LoadSucceeded : State::LoadFailed);
		}

		return loadSucceeded();
	}

	void FontAssetData::preloadAsync()
	{
		if (uninitialized())
		{
			launchLoading([this]() { return onPreload(*this); });

			setState(State::PreloadingAsync);
		}
	}

	bool FontAssetData::update()
	{
		if (!isPreloaded())
		{
			return false;
		}

		return onUpdate(*this);
	}

	bool FontAssetData::release()
	{
		if (uninitialized())
		{
			return true;
		}

		const bool result = onRelease(*this);

		setState(State::Uninitialized);

		return result;
	}

	FontAsset::FontAsset(const AssetName& name)
		: Font(detail::FromAsset(Siv3DEngine::Get<ISiv3DAsset>()->getAsset(AssetType::Font, name)))
	{

	}

	bool FontAsset::Register(const AssetName& name, const int32 fontSize, const AssetParameter& parameter)
	{
		return Register(name, fontSize, Typeface::Default, FontStyle::Default, parameter);
	}

	bool FontAsset::Register(const AssetName& name, const int32 fontSize, const Typeface typeface, const AssetParameter& parameter)
	{
		return Register(name, fontSize, typeface, FontStyle::Default, parameter);
	}

	bool FontAsset::Register(const AssetName& name, const int32 fontSize, const Typeface typeface, FontStyle style, const AssetParameter& parameter)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->registerAsset(AssetType::Font, name, std::make_unique<FontAssetData>(fontSize, typeface, style, parameter));
	}

	bool FontAsset::Register(const AssetName& name, const int32 fontSize, const FilePath& path, const AssetParameter& parameter)
	{
		return Register(name, fontSize, path, FontStyle::Default, parameter);
	}

	bool FontAsset::Register(const AssetName& name, const int32 fontSize, const FilePath& path, FontStyle style, const AssetParameter& parameter)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->registerAsset(AssetType::Font, name, std::make_unique<FontAssetData>(fontSize, path, style, parameter));
	}

	bool FontAsset::Register(const AssetName& name, const FontAssetData& data)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->registerAsset(AssetType::Font, name, std::make_unique<FontAssetData>(data));
	}

	bool FontAsset::IsRegistered(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->isRegistered(AssetType::Font, name);
	}

	bool FontAsset::Preload(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->preload(AssetType::Font, name);
	}

	void FontAsset::Release(const AssetName& name)
	{
		Siv3DEngine::Get<ISiv3DAsset>()->release(AssetType::Font, name);
	}

	void FontAsset::ReleaseAll()
	{
		Siv3DEngine::Get<ISiv3DAsset>()->releaseAll(AssetType::Font);
	}

	void FontAsset::Unregister(const AssetName& name)
	{
		Siv3DEngine::Get<ISiv3DAsset>()->unregister(AssetType::Font, name);
	}

	void FontAsset::UnregisterAll()
	{
		Siv3DEngine::Get<ISiv3DAsset>()->unregisterAll(AssetType::Font);
	}

	bool FontAsset::IsReady(const AssetName& name)
	{
		return Siv3DEngine::Get<ISiv3DAsset>()->isReady(AssetType::Font, name);
	}
}
