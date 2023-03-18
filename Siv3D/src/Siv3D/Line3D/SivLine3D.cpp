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

# include <Siv3D/Line3D.hpp>
# include <Siv3D/Mat4x4.hpp>
# include <Siv3D/Graphics2D.hpp>
# include <Siv3D/FormatFloat.hpp>
# include <Siv3D/Renderer3D/IRenderer3D.hpp>
# include <Siv3D/Common/Siv3DEngine.hpp>


namespace s3d
{
	Line3D Line3D::toScreen(const Mat4x4& vp) const noexcept
	{
		constexpr size_t vertexCount = 2;
		Float3 vertices[vertexCount] = { begin, end };
		DirectX::XMVector3TransformCoordStream(
			reinterpret_cast<DirectX::XMFLOAT3*>(vertices),
			sizeof(Float3),
			reinterpret_cast<const DirectX::XMFLOAT3*>(vertices),
			sizeof(Float3), vertexCount, vp);

		const Float2 resolution = Graphics2D::GetRenderTargetSize();

		for (auto& v : vertices)
		{
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * resolution.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= resolution.y;
		}

		return{ vertices[0], vertices[1] };
	}

	Line Line3D::toScreenLine(const Mat4x4& vp) const noexcept
	{
		const Line3D line = toScreen(vp);

		return{ line.begin.xy(), line.end.xy() };
	}

	const Line3D& Line3D::draw(const ColorF& color) const
	{
		const Float4 rgba = color.toFloat4();

		SIV3D_ENGINE(Renderer3D)->addLine3D(begin, end, { rgba, rgba });

		return *this;
	}

	const Line3D& Line3D::draw(const ColorF& colorBegin, const ColorF& colorEnd) const
	{
		SIV3D_ENGINE(Renderer3D)->addLine3D(begin, end, { colorBegin.toFloat4(), colorEnd.toFloat4() });

		return *this;
	}


	void Formatter(FormatData& formatData, const Line3D& value)
	{
		formatData.string.append(U"(("_sv);

		formatData.string.append(ToString(value.begin.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.begin.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.begin.z, formatData.decimalPlaces.value));
		formatData.string.append(U"), ("_sv);

		formatData.string.append(ToString(value.end.x, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.end.y, formatData.decimalPlaces.value));
		formatData.string.append(U", "_sv);
		formatData.string.append(ToString(value.end.z, formatData.decimalPlaces.value));

		formatData.string.append(U"))"_sv);
	}
}
