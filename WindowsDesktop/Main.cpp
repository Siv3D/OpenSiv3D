
# include <Siv3D.hpp> // OpenSiv3D v0.4.2

void Main()
{
	constexpr double fov = 45_deg;
	constexpr Vec3 focusPosition(0, 0, 0);
	Vec3 eyePosition(0, 10, 0);
	experimental::BasicCamera3D camera(Scene::Size(), fov, eyePosition, focusPosition);

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

			//experimental::AABB(Vec3(0, 1, 0), Vec3(2, 2, 2)).draw(mat, Palette::White);
			experimental::AABB(Vec3(-8, 1, 8), Vec3(2, 2, 2)).draw(mat, HSV(0));
			experimental::AABB(Vec3(8, 1, 8), Vec3(2, 2, 2)).draw(mat, HSV(90));
			experimental::AABB(Vec3(8, 1, -8), Vec3(2, 2, 2)).draw(mat, HSV(270));
			experimental::AABB(Vec3(-8, 1, -8), Vec3(2, 2, 2)).draw(mat, HSV(180));

		
			experimental::OBB(Vec3(0, 1, 0), Vec3(2, 2, 2), Quaternion::RollPitchYaw(0, Scene::Time() * 180_deg, 0)).draw(mat, Palette::White);
			experimental::OBB(Vec3(0, 6, 0), Vec3(2, 2, 10), Quaternion::RollPitchYaw(0, -Scene::Time() * 180_deg, 0)).draw(mat, Palette::Orange);

		}
	}
}
