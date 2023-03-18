//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2023 Ryo Suzuki
//	Copyright (c) 2016-2023 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Image.hpp>
# include <Siv3D/Common/D3D11.hpp>
# include "../Device/D3D11Device.hpp"

namespace s3d
{
	class D3D11ScreenCapture
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		Image m_image;

		ComPtr<ID3D11Texture2D> m_stagingTexture;

	public:

		D3D11ScreenCapture(const D3D11Device& device);

		bool capture(ID3D11Texture2D* texture, const Size& size);

		[[nodiscard]]
		const Image& getImage() const noexcept;
	};
}
