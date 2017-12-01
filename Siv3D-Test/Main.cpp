
# include <Siv3D.hpp>

void Main()
{
	using s3d::Lambda::_;

	const Array<double> v = { 0.0, 0.1, 0.2, 0.3, 1.0, 1.1, 1.2, 1.3 };

	Logger << v.map(-_);

	Logger << v.map(Fmod(_, 0.5));

	Logger << v.map(Fraction);

	Logger << v.map(Fraction(_));

	Logger << Math::Lerp(0, 100, 0.3);

	Logger << Math::Lerp(Vec2(0, 0), Vec2(100, 100), 0.3);
}
