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
# include <Texture/D3D11/CTexture_D3D11.hpp>

namespace s3d
{
	class D3D11ScreenCapture
	{
	private:

		ID3D11Device* m_device = nullptr;

		ID3D11DeviceContext* m_context = nullptr;

		Image m_image;

		ComPtr<ID3D11Texture2D> m_stagingTexture;

		bool m_requested = false;

	public:

		D3D11ScreenCapture(ID3D11Device* device, ID3D11DeviceContext* context);

		void request();

		bool isRequested() const;

		bool capture(ID3D11Texture2D* texture, const Size& size);

		const Image& getImage() const;
	};
}
