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
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_MACOS) || defined(SIV3D_TARGET_LINUX)

# include "../IGraphics.hpp"

namespace s3d
{
	class CGraphics_GL : public ISiv3DGraphics
	{
	private:

	public:

		CGraphics_GL();

		~CGraphics_GL() override;

		bool init() override;

		Array<DisplayOutput> enumOutputs() override
		{
			return{};
		}

		void setClearColor(const ColorF& color) override
		{

		}

		bool setFullScreen(bool fullScreen, const Size& size, size_t displayIndex, double refreshRateHz) override
		{
			return false;
		}

		bool present() override
		{
			return true;
		}

		void clear() override
		{

		}

		void beginResize() override
		{

		}

		bool endResize(const Size& size) override
		{
			return true;
		}
	};
}

# endif
