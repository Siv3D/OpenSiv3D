
# include <Siv3D.hpp>
# include <ThirdParty/Box2D/Box2D.h>

void Main()
{
	b2Vec2 gravity(0.0f, -9.8f);

	b2World world(gravity);

	world.Step(0.016f, 8, 3);



	Image image(U"example/windmill.png");

	const Texture texture(image.erode(4));

	while (System::Update())
	{
		texture.draw();
	}
}
