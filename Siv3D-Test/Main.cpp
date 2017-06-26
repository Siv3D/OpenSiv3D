# include <Siv3D.hpp> // OpenSiv3D v0.1.6

struct Ripple : IEffect
{
	Point pos;

	Ripple(const Point& _pos)
		: pos(_pos) {}

	bool update(double t) override
	{
		Circle(pos, t * 100).draw(ColorF(Palette::Skyblue, 1.0 - t));
		return t < 1.0;
	}
};

void Main()
{
	Effect effect;

	while (System::Update())
	{	
		if (MouseL.down()) // (従来) IEffect
		{
			effect.add<Ripple>(Cursor::Pos());
		}
		
		if (MouseR.down()) // (新機能) ラムダ式
		{
			effect.add([pos = Cursor::Pos()](double t){
				Circle(pos, t * 100).draw(ColorF(Palette::Orange, 1.0 - t));
				return t < 1.0; });
		}

		effect.update();
	}
}
