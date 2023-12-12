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

# include <Siv3D/Mat3x3.hpp>
# include <Siv3D/OpenCV_Bridge.hpp>

namespace s3d
{
	Mat3x3 Mat3x3::Homography(const Quad& to)
	{
		const float x00 = static_cast<float>(to.p0.x);
		const float y00 = static_cast<float>(to.p0.y);
		const float x10 = static_cast<float>(to.p1.x);
		const float y10 = static_cast<float>(to.p1.y);
		const float x11 = static_cast<float>(to.p2.x);
		const float y11 = static_cast<float>(to.p2.y);
		const float x01 = static_cast<float>(to.p3.x);
		const float y01 = static_cast<float>(to.p3.y);

		const float a = (x10 - x11);
		const float b = (x01 - x11);
		const float c = (x00 - x01 - x10 + x11);
		const float d = (y10 - y11);
		const float e = (y01 - y11);
		const float f = (y00 - y01 - y10 + y11);

		const float m31 = x00;
		const float m32 = y00;
		const float m23 = (c * d - a * f) / (b * d - a * e);
		const float m13 = (c * e - b * f) / (a * e - b * d);
		const float m11 = (x10 - x00 + m13 * x10);
		const float m21 = (x01 - x00 + m23 * x01);
		const float m12 = (y10 - y00 + m13 * y10);
		const float m22 = (y01 - y00 + m23 * y01);

		return{ m11, m12, m13, m21, m22, m23, m31, m32, 1.0f };
	}

	Mat3x3 Mat3x3::Homography(const RectF& from, const RectF& to)
	{
		return Homography(from.asQuad(), to.asQuad());
	}

	Mat3x3 Mat3x3::Homography(const RectF& from, const Quad& to)
	{
		return Homography(from.asQuad(), to);
	}

	Mat3x3 Mat3x3::Homography(const Quad& from, const RectF& to)
	{
		return Homography(from, to.asQuad());
	}

	Mat3x3 Mat3x3::Homography(const Quad& from, const Quad& to)
	{
		const std::array<cv::Point2f, 4> fromQ = {
			cv::Point2f(static_cast<float>(from.p0.x), static_cast<float>(from.p0.y)),
			cv::Point2f(static_cast<float>(from.p1.x), static_cast<float>(from.p1.y)),
			cv::Point2f(static_cast<float>(from.p2.x), static_cast<float>(from.p2.y)),
			cv::Point2f(static_cast<float>(from.p3.x), static_cast<float>(from.p3.y)),
		};

		const std::array<cv::Point2f, 4> toQ = {
			cv::Point2f(static_cast<float>(to.p0.x), static_cast<float>(to.p0.y)),
			cv::Point2f(static_cast<float>(to.p1.x), static_cast<float>(to.p1.y)),
			cv::Point2f(static_cast<float>(to.p2.x), static_cast<float>(to.p2.y)),
			cv::Point2f(static_cast<float>(to.p3.x), static_cast<float>(to.p3.y)),
		};

		const cv::Mat t = cv::getPerspectiveTransform(fromQ, toQ);
		const double* p0 = t.ptr<double>(0);
		const double* p1 = t.ptr<double>(1);
		const double* p2 = t.ptr<double>(2);

		return{
			static_cast<float>(p0[0]), static_cast<float>(p1[0]), static_cast<float>(p2[0]),
			static_cast<float>(p0[1]), static_cast<float>(p1[1]), static_cast<float>(p2[1]),
			static_cast<float>(p0[2]), static_cast<float>(p1[2]), static_cast<float>(p2[2]),
		};
	}

	void Formatter(FormatData& formatData, const Mat3x3& value)
	{
		formatData.string.push_back(U'(');
		Formatter(formatData, Float3{ value._11, value._12, value._13 });
		formatData.string.push_back(U',');
		Formatter(formatData, Float3{ value._21, value._22, value._23 });
		formatData.string.push_back(U',');
		Formatter(formatData, Float3{ value._31, value._32, value._33 });
		formatData.string.push_back(U')');
	}
}
