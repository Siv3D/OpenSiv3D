
# include <Siv3D.hpp>
# include "Test/Siv3DTest.hpp"
using namespace s3d;
using namespace s3d::literals;
using namespace std::literals;

void Main()
{
	
	TimeProfiler tp;
	
	size_t a= 0,b = 0;

	for(auto n : step(5))
	{
		tp.begin(L"MMF");
		
		{
			MemoryMapping mm(L"example/windmill.png");
	
			size_t count = 0;
	
			const uint8* p = mm.data();
			const size_t size = mm.fileSize();
	
			for(size_t i = 0; i < size; ++i)
			{
				count += (p[i] == 255);
			}
		
			a += count;
		}
		
		tp.end();
	}
	
	for(auto n : step(5))
	{
		tp.begin(L"BR");
		
		{
			BinaryReader mm(L"example/windmill.png");

			size_t count = 0;
		
			const size_t size = mm.size();
		
			Array<uint8> data(size);
		
			mm.read(data.data(), size);
			const uint8* p = data.data();

			for(size_t i=0;i<size; ++i)
				count += (p[i] == 255);

			b += count;
		}
		
		tp.end();
	}
	
	Log(a);
	Log(b);

	//RunTest();
}
