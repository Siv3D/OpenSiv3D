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

# include "../Siv3DEngine.hpp"
# include "../Asset/IAsset.hpp"
# include <Siv3D/FontAsset.hpp>

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

	FontAsset::FontAsset(const AssetName& name)
		: Font(detail::FromAsset(Siv3DEngine::GetAsset()->getAsset(AssetType::Font, name)))
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
		return Siv3DEngine::GetAsset()->registerAsset(AssetType::Font, name, std::make_unique<FontAssetData>(fontSize, typeface, style, parameter));
	}

	bool FontAsset::Register(const AssetName& name, const int32 fontSize, const FilePath& path, const AssetParameter& parameter)
	{
		return Register(name, fontSize, path, FontStyle::Default, parameter);
	}

	bool FontAsset::Register(const AssetName& name, const int32 fontSize, const FilePath& path, FontStyle style, const AssetParameter& parameter)
	{
		return Siv3DEngine::GetAsset()->registerAsset(AssetType::Font, name, std::make_unique<FontAssetData>(fontSize, path, style, parameter));
	}

	bool FontAsset::Register(const AssetName& name, const FontAssetData& data)
	{
		return Siv3DEngine::GetAsset()->registerAsset(AssetType::Font, name, std::make_unique<FontAssetData>(data));
	}

	bool FontAsset::IsRegistered(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->isRegistered(AssetType::Font, name);
	}

	bool FontAsset::Preload(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->preload(AssetType::Font, name);
	}

	void FontAsset::Release(const AssetName& name)
	{
		Siv3DEngine::GetAsset()->release(AssetType::Font, name);
	}

	void FontAsset::ReleaseAll()
	{
		Siv3DEngine::GetAsset()->releaseAll(AssetType::Font);
	}

	void FontAsset::Unregister(const AssetName& name)
	{
		Siv3DEngine::GetAsset()->unregister(AssetType::Font, name);
	}

	void FontAsset::UnregisterAll()
	{
		Siv3DEngine::GetAsset()->unregisterAll(AssetType::Font);
	}

	bool FontAsset::IsReady(const AssetName& name)
	{
		return Siv3DEngine::GetAsset()->isReady(AssetType::Font, name);
	}
}
