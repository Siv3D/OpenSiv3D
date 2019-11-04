
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	constexpr double fov = 45_deg;
	constexpr Vec3 focusPosition(0, 0, 0);
	Vec3 eyePosition(0, 10, 0);
	experimental::BasicCamera3D camera(Scene::Size(), fov, eyePosition, focusPosition);

	Array<OBB> objects;

	for (auto x : Range(-2, 2))
	{
		for (auto z : Range(2, -2, -1))
		{
			objects << OBB(Vec3(x * 4, 1, z * 4), Vec3(3, 2, 0.5), Quaternion::RollPitchYaw(0, x * 30_deg, 0));

			objects << OBB(Vec3(x * 4, 5, z * 4), Vec3(2, 1, 2), Quaternion::RollPitchYaw(x * 30_deg, 0, 0));
			//objects << AABB(Vec3(x * 4, 1, z * 4), Vec3(2, 2, 2));
			//objects << AABB(Vec3(x * 4, 5, z * 4), Vec3(2, 2, 2));
		}
	}

	const Quaternion value = Quaternion::RollPitchYaw(10_deg, 20_deg, 30_deg);
	Print << value;
	Print << U"{}"_fmt(value);
	Print << U"{:.1f}"_fmt(value);

	while (System::Update())
	{
		eyePosition = Cylindrical(20, Scene::Time() * 30_deg, 8 + Periodic::Sine0_1(4s) * 8);
		camera.setView(eyePosition, focusPosition);
		const Mat4x4 mat = camera.getMat4x4();

		{
			ScopedRenderStates2D culling(RasterizerState::SolidCullBack);

			for (auto i : Range(-10, 10))
			{
				Line3D(Vec3(-10, 0, i), Vec3(10, 0, i)).draw(mat, ColorF(0.5));
				Line3D(Vec3(i, 0, -10), Vec3(i, 0, 10)).draw(mat, ColorF(0.5));
			}

			const Vec3 eyePos = camera.getEyePosition();
			const Vec3 rayEnd = camera.screenToWorldPoint(Cursor::Pos(), 0.5f);
			const Ray cursorRay(eyePos, (rayEnd - eyePos).normalized());

			//for (auto i : Range(1, 10))
			//{
			//	const Vec3 eyePos = camera.getEyePosition();
			//	const Vec3 rayEnd = camera.screenToWorldPoint(Cursor::Pos(), i / 10.0);
			//	const Ray cursorRay(eyePos, (rayEnd - eyePos).normalized());
			//	Print << 10_dp << cursorRay;
			//}

			objects.sort_by([&](const OBB& a, const OBB& b)
			{
				return (eyePos.distanceFromSq(a.center)) > (eyePos.distanceFromSq(b.center));
			});

			Optional<size_t> intersectionIndex;

			for (auto [i, object] : IndexedReversed(objects))
			{
				if (cursorRay.intersects(object))
				{
					intersectionIndex = i;
					Cursor::RequestStyle(CursorStyle::Hand);
					break;
				}
			}

			for (auto [i, object] : Indexed(objects))
			{
				const HSV color((object.center.x * 50 + object.center.z * 10), 1.0, (i == intersectionIndex) ? 1.0 : 0.3);
				object.draw(mat, color);
			}
		}
	}
}
