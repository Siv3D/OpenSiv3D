# include <Siv3D.hpp>

void Main()
{
	Graphics::SetBackground(ColorF(0.5, 0.9, 0.6));

	const Texture ball(Emoji::SoccerBall);

	const Texture hamburger(Emoji::Hamburger);

	const Texture fire(Emoji::Fire);
		
	while (System::Update())
	{
		ball.draw(100, 100);

		hamburger.draw(400, 200);

		for (auto i : step(10))
		{
			fire.scale(0.5).draw(i * 60, 400);
		}	
	}
}
