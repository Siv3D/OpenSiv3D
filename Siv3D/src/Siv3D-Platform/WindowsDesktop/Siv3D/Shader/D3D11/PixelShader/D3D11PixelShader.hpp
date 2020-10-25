﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Blob.hpp>
# include <Siv3D/Common/D3D11.hpp>

namespace s3d
{
	class D3D11PixelShader
	{
	private:

		Blob m_binary;

		ComPtr<ID3D11PixelShader> m_shader;

		bool m_initialized = false;

	public:

		struct Null {};

		D3D11PixelShader() = default;

		D3D11PixelShader(Null);

		D3D11PixelShader(Blob&& binary, ID3D11Device* device);

		bool isInitialized() const noexcept;

		ID3D11PixelShader* getShader() const;

		const Blob& getBinary() const noexcept;
	};
}
