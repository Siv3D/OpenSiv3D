
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	constexpr double fov = 45_deg;
	constexpr Vec3 focusPosition(0, 0, 0);
	Vec3 eyePosition(0, 10, 0);
	experimental::BasicCamera3D camera(Scene::Size(), fov, eyePosition, focusPosition);

	Array<experimental::AABB> aabbs;

	for (auto x : Range(-2, 2))
	{
		for (auto z : Range(2, -2, -1))
		{
			aabbs << experimental::AABB(Vec3(x * 4, 1, z * 4), Vec3(2, 2, 2));
			aabbs << experimental::AABB(Vec3(x * 4, 5, z * 4), Vec3(2, 2, 2));
		}
	}

	while (System::Update())
	{
		eyePosition = Cylindrical(20, Scene::Time() * 30_deg, 8 + Periodic::Sine0_1(4s) * 8);
		camera.setView(eyePosition, focusPosition);
		const Mat4x4 mat = camera.getMat4x4();

		{
			ScopedRenderStates2D culling(RasterizerState::SolidCullBack);

			for (auto i : Range(-10, 10))
			{
				experimental::Line3D(Vec3(-10, 0, i), Vec3(10, 0, i)).draw(mat, ColorF(0.5));
				experimental::Line3D(Vec3(i, 0, -10), Vec3(i, 0, 10)).draw(mat, ColorF(0.5));
			}

			const Vec3 eyePos = camera.getEyePosition();
			const Vec3 rayEnd = camera.screenToWorldPoint(Cursor::Pos(), 0.5f);
			const Ray cursorRay(eyePos, (rayEnd - eyePos).normalized());

			aabbs.sort_by([&](const experimental::AABB& a, const experimental::AABB& b)
			{
				return (eyePos.distanceFromSq(a.center)) > (eyePos.distanceFromSq(b.center));
			});

			Optional<size_t> intersectionIndex;

			for (auto [i, aabb] : IndexedReversed(aabbs))
			{
				if (cursorRay.intersects(aabb))
				{
					intersectionIndex = i;
					Cursor::RequestStyle(CursorStyle::Hand);
					break;
				}
			}

			for (auto [i, aabb] : Indexed(aabbs))
			{
				const HSV color((aabb.center.x * 50 + aabb.center.z * 10), 1.0, (i == intersectionIndex) ? 1.0 : 0.3);
				aabb.draw(mat, color);
			}
		}
	}
}
