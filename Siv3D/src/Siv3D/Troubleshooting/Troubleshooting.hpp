//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2025 Ryo Suzuki
//	Copyright (c) 2016-2025 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Common.hpp>
# include <Siv3D/StringView.hpp>

namespace s3d
{
	namespace Troubleshooting
	{
		enum class Warning
		{
			InefficientAssetCreation = 100,
		};

		enum class Error
		{
			AssetInitializationBeforeEngineStartup = 200,
		};

		void Show(Warning id, StringView hint = {});

		void Show(Error id, StringView hint = {});
	}
}
