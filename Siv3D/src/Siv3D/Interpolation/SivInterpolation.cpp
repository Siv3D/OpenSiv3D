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

# include <Siv3D/Interpolation.hpp>

namespace s3d
{
	namespace Math
	{
		float Damp(const float a, const float b, const float r, const float dt)
		{
			return Lerp(a, b, 1.0f - Exp(-r * dt));
		}

		double Damp(const double a, const double b, const double r, const double dt)
		{
			return Lerp(a, b, 1.0 - Exp(-r * dt));
		}

		Float2 Damp(const Float2& a, const Float2& b, const float r, const float dt)
		{
			return Lerp(a, b, float(1) - Exp(-r * dt));
		}

		Vec2 Damp(const Vec2& a, const Vec2& b, const double r, const double dt)
		{
			return Lerp(a, b, double(1) - Exp(-r * dt));
		}

		Float3 Damp(const Float3& a, const Float3& b, const float r, const float dt)
		{
			return Lerp(a, b, float(1) - Exp(-r * dt));
		}

		Vec3 Damp(const Vec3 & a, const Vec3 & b, const double r, const double dt)
		{
			return Lerp(a, b, double(1) - Exp(-r * dt));
		}

		Float4 Damp(const Float4& a, const Float4& b, const float r, const float dt)
		{
			return Lerp(a, b, float(1) - Exp(-r * dt));
		}

		Vec4 Damp(const Vec4 & a, const Vec4 & b, const double r, const double dt)
		{
			return Lerp(a, b, double(1) - Exp(-r * dt));
		}

		// Implementation based on Game Programming Gems 4 Chapter 1.10
		float SmoothDamp(const float from, float to, float& velocity, const float smoothTime, const float deltaTime, const Optional<float>& maxSpeed)
		{
			const float omega = 2.0f / smoothTime;
			const float x = omega * deltaTime;
			const float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
			float change = from - to;

			// ‘¬“x‚ð maxSpeed ‚É§ŒÀ
			const float originalTo = to;
			if (maxSpeed)
			{
				const float maxChange = maxSpeed.value() * smoothTime;
				change = s3d::Clamp(change, -maxChange, maxChange);
			}
			to = from - change;

			const float temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			float result = to + (change + temp) * exp;

			// s‚«‰ß‚¬‚ð–h‚®
			if (((originalTo - from) > 0.0f) == (result > originalTo))
			{
				result = originalTo;
				velocity = (result - originalTo) / deltaTime;
			}

			return result;
		}

		double SmoothDamp(const double from, double to, double& velocity, const double smoothTime, const double deltaTime, const Optional<double>& maxSpeed)
		{
			const double omega = 2.0 / smoothTime;
			const double x = omega * deltaTime;
			const double exp = 1.0 / (1.0 + x + 0.48 * x * x + 0.235 * x * x * x);
			double change = from - to;

			// ‘¬“x‚ð maxSpeed ‚É§ŒÀ
			const double originalTo = to;
			if (maxSpeed)
			{
				const double maxChange = maxSpeed.value() * smoothTime;
				change = s3d::Clamp(change, -maxChange, maxChange);
			}
			to = from - change;

			const double temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			double result = to + (change + temp) * exp;

			// s‚«‰ß‚¬‚ð–h‚®
			if (((originalTo - from) > 0.0) == (result > originalTo))
			{
				result = originalTo;
				velocity = (result - originalTo) / deltaTime;
			}

			return result;
		}

		Float2 SmoothDamp(const Float2 from, Float2 to, Float2& velocity, const float smoothTime, const float deltaTime, const Optional<float>& maxSpeed)
		{
			const float omega = 2.0f / smoothTime;
			const float x = omega * deltaTime;
			const float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
			Float2 change = from - to;

			// ‘¬“x‚ð maxSpeed ‚É§ŒÀ
			const Float2 originalTo = to;
			if (maxSpeed)
			{
				const float maxChange = maxSpeed.value() * smoothTime;
				change = change.clampLength(maxChange);
			}
			to = from - change;

			const Float2 temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			Float2 result = to + (change + temp) * exp;

			// s‚«‰ß‚¬‚ð–h‚®
			if ((originalTo - from).dot(result - originalTo) > 0.0f)
			{
				result = originalTo;
				velocity = (result - originalTo) / deltaTime;
			}

			return result;
		}

		Vec2 SmoothDamp(const Vec2 from, Vec2 to, Vec2& velocity, const double smoothTime, const double deltaTime, const Optional<double>& maxSpeed)
		{
			const double omega = 2.0 / smoothTime;
			const double x = omega * deltaTime;
			const double exp = 1.0 / (1.0 + x + 0.48 * x * x + 0.235 * x * x * x);
			Vec2 change = from - to;

			// ‘¬“x‚ð maxSpeed ‚É§ŒÀ
			const Vec2 originalTo = to;
			if (maxSpeed)
			{
				const double maxChange = maxSpeed.value() * smoothTime;
				change = change.clampLength(maxChange);
			}
			to = from - change;

			const Vec2 temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			Vec2 result = to + (change + temp) * exp;

			// s‚«‰ß‚¬‚ð–h‚®
			if ((originalTo - from).dot(result - originalTo) > 0.0)
			{
				result = originalTo;
				velocity = (result - originalTo) / deltaTime;
			}

			return result;
		}

		Float3 SmoothDamp(const Float3 from, Float3 to, Float3& velocity, const float smoothTime, const float deltaTime, const Optional<float>& maxSpeed)
		{
			const float omega = 2.0f / smoothTime;
			const float x = omega * deltaTime;
			const float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
			Float3 change = from - to;

			// ‘¬“x‚ð maxSpeed ‚É§ŒÀ
			const Float3 originalTo = to;
			if (maxSpeed)
			{
				const float maxChange = maxSpeed.value() * smoothTime;
				change = change.clampLength(maxChange);
			}
			to = from - change;

			const Float3 temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			Float3 result = to + (change + temp) * exp;

			// s‚«‰ß‚¬‚ð–h‚®
			if ((originalTo - from).dot(result - originalTo) > 0.0f)
			{
				result = originalTo;
				velocity = (result - originalTo) / deltaTime;
			}

			return result;
		}

		Vec3 SmoothDamp(const Vec3 from, Vec3 to, Vec3& velocity, const double smoothTime, const double deltaTime, const Optional<double>& maxSpeed)
		{
			const double omega = 2.0 / smoothTime;
			const double x = omega * deltaTime;
			const double exp = 1.0 / (1.0 + x + 0.48 * x * x + 0.235 * x * x * x);
			Vec3 change = from - to;

			// ‘¬“x‚ð maxSpeed ‚É§ŒÀ
			const Vec3 originalTo = to;
			if (maxSpeed)
			{
				const double maxChange = maxSpeed.value() * smoothTime;
				change = change.clampLength(maxChange);
			}
			to = from - change;

			const Vec3 temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			Vec3 result = to + (change + temp) * exp;

			// s‚«‰ß‚¬‚ð–h‚®
			if ((originalTo - from).dot(result - originalTo) > 0.0)
			{
				result = originalTo;
				velocity = (result - originalTo) / deltaTime;
			}

			return result;
		}

		Float4 SmoothDamp(const Float4 from, Float4 to, Float4& velocity, const float smoothTime, const float deltaTime, const Optional<float>& maxSpeed)
		{
			const float omega = 2.0f / smoothTime;
			const float x = omega * deltaTime;
			const float exp = 1.0f / (1.0f + x + 0.48f * x * x + 0.235f * x * x * x);
			Float4 change = from - to;

			// ‘¬“x‚ð maxSpeed ‚É§ŒÀ
			const Float4 originalTo = to;
			if (maxSpeed)
			{
				const float maxChange = maxSpeed.value() * smoothTime;
				change = change.clampLength(maxChange);
			}
			to = from - change;

			const Float4 temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			Float4 result = to + (change + temp) * exp;

			// s‚«‰ß‚¬‚ð–h‚®
			if ((originalTo - from).dot(result - originalTo) > 0.0f)
			{
				result = originalTo;
				velocity = (result - originalTo) / deltaTime;
			}

			return result;
		}

		Vec4 SmoothDamp(const Vec4 from, Vec4 to, Vec4& velocity, const double smoothTime, const double deltaTime, const Optional<double>& maxSpeed)
		{
			const double omega = 2.0 / smoothTime;
			const double x = omega * deltaTime;
			const double exp = 1.0 / (1.0 + x + 0.48 * x * x + 0.235 * x * x * x);
			Vec4 change = from - to;

			// ‘¬“x‚ð maxSpeed ‚É§ŒÀ
			const Vec4 originalTo = to;
			if (maxSpeed)
			{
				const double maxChange = maxSpeed.value() * smoothTime;
				change = change.clampLength(maxChange);
			}
			to = from - change;

			const Vec4 temp = (velocity + omega * change) * deltaTime;
			velocity = (velocity - omega * temp) * exp;

			Vec4 result = to + (change + temp) * exp;

			// s‚«‰ß‚¬‚ð–h‚®
			if ((originalTo - from).dot(result - originalTo) > 0.0)
			{
				result = originalTo;
				velocity = (result - originalTo) / deltaTime;
			}

			return result;
		}
	}
}
