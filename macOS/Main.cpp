
# include <Siv3D.hpp> // OpenSiv3D v0.4.1

namespace s3d::experimental
{
	namespace Graphics3D
	{
		[[nodiscard]] Float3 SIV3D_VECTOR_CALL WorldToScreenPoint(SIMD_Float4 worldPos, Mat4x4 viewProjMat,
																  const Float2& sceneSize = Graphics2D::GetRenderTargetSize())
		{
			Float3 v = SIMD::Vector3TransformCoord(worldPos, viewProjMat).xyz();
			v.x += 1.0f;
			v.y += 1.0f;
			v.x *= 0.5f * sceneSize.x;
			v.y *= 0.5f;
			v.y = 1.0f - v.y;
			v.y *= sceneSize.y;
			return v;
		}
		
		[[nodiscard]] Float3 SIV3D_VECTOR_CALL WorldToScreenPoint(const Vec3& worldPos, Mat4x4 viewProjMat,
																  const Float2& sceneSize = Graphics2D::GetRenderTargetSize())
		{
			return WorldToScreenPoint(SIMD_Float4(worldPos, 0.0f), viewProjMat, sceneSize);
		}
	}
}

void Main()
{
	Window::Resize(1280, 720);
	Scene::SetBackground(ColorF(0.05, 0.3, 0.7));
	
	RenderTexture rt(100, 100, ColorF(0.0), TextureFormat::R32_Float);
	Grid<float> heightMap;
	Grid<Float3> positions;
	
	constexpr double fov = 45_deg;
	constexpr Vec3 focusPosition(50, 0, -50);
	Vec3 eyePositon(0, 100, 0);
	experimental::BasicCamera3D camera(Scene::Size(), fov, eyePositon, focusPosition);
	
	while (System::Update())
	{
		eyePositon = Cylindrical(Arg::r = 80, Arg::phi = Scene::Time() * 30_deg, Arg::y = 50) + Vec3(50, 0, -50);
		camera.setView(eyePositon, focusPosition);
		const Mat4x4 mat = camera.getMat4x4();
		
		rt.read(heightMap);
		{
			positions.resize(heightMap.size());
			
			for (auto p : step(heightMap.size()))
			{
				positions[p] = Float3(p.x, heightMap[p], -p.y);
			}
		}
		
		{
			ScopedRenderTarget2D target(rt);
			ScopedRenderStates2D blend(BlendState::Additive);
			
			if (MouseL.pressed())
			{
				Circle(Cursor::Pos(), 8).draw(ColorF(Scene::DeltaTime() * 24.0));
			}
		}
		
		if (positions)
		{
			ScopedRenderStates2D blend(RasterizerState::SolidCullBack);
			
			for (auto x : step(positions.width() - 1))
			{
				for (auto y : step(positions.height()))
				{
					const Float3 begin = positions[{x, y}];
					const Float3 end = positions[{x + 1, y}];
					const ColorF color = HSV(120 - (begin.y + end.y) * 3, 0.75, 0.7);
					experimental::Line3D(begin, end).draw(mat, color);
				}
			}
			
			for (auto x : step(positions.width()))
			{
				for (auto y : step(positions.height() - 1))
				{
					const Float3 begin = positions[{x, y}];
					const Float3 end = positions[{x, y + 1}];
					const ColorF color = HSV(120 - (begin.y + end.y) * 3, 0.75, 0.7);
					experimental::Line3D(begin, end).draw(mat, color);
				}
			}
		}
		
		rt.draw(ColorF(0.1));
	}
}
