# include <Siv3D.hpp> // OpenSiv3D v0.4.1

void Main()
{
	const SIMD_Float4 ev(0.1f, 0.2f, 0.3f, 0.4f);
	
	SIMD_Float4 ev2(0.1f, 0.2f, 0.3f, 0.4f);
	Print << ev2;
	ev2.setX(1.1f);
	Print << ev2;
	ev2.setY(2.2f);
	Print << ev2;
	ev2.setZ(3.3f);
	Print << ev2;
	ev2.setW(4.4f);
	Print << ev2;
	
	Print << U"---";
	
	Print << Float4(ev.getX(), ev.getY(), ev.getZ(), ev.getW());
	
	Print << Float4(ev.elem(0), ev.elem(1), ev.elem(2), ev.elem(3));
	
	Print << Parse<SIMD_Float4>(U"(0.1, 0.2, 0.3, 0.4)");
	
	Print << SIMD_Float4(0.1f, 0.2f, 0.3f, 0.4f);
	
	Print << SIMD_Float4(0.1234f);
	
	SIMD_Float4 f0(0.1f, Random(0.2f), Random(0.2f), Random(0.2f));
	
	Print << f0;
	
	Print << (f0 + f0 + f0);
	
	Print << U"---";
	
	Print << ev.fastReciprocal();
	
	Print << ev.reciprocal();
	
	Print << ev.xy();
	
	Print << ev.xyz();
	
	while (System::Update())
	{
		
	}
}
