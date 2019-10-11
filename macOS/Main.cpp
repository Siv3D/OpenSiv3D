# include <Siv3D.hpp>

void Main()
{
	Print << U"{:#x}"_fmt(uint16(0x1122));
	Print << U"{:#x}"_fmt(uint32(0x11223344));
	Print << U"{:#x}"_fmt(uint64(0x1122334455667788));

	Print << U"{:#x}"_fmt(SwapEndian(uint16(0x1122)));
	Print << U"{:#x}"_fmt(SwapEndian(uint32(0x11223344)));
	Print << U"{:#x}"_fmt(SwapEndian(uint64(0x1122334455667788)));

	Print << U"{:#x}"_fmt(uint16(0xFFEE));
	Print << U"{:#x}"_fmt(uint32(0xFFEEDDCC));
	Print << U"{:#x}"_fmt(uint64(0xFFEEDDCCBBAA9988));

	Print << U"{:#x}"_fmt(SwapEndian(uint16(0xFFEE)));
	Print << U"{:#x}"_fmt(SwapEndian(uint32(0xFFEEDDCC)));
	Print << U"{:#x}"_fmt(SwapEndian(uint64(0xFFEEDDCCBBAA9988)));

    while (System::Update())
    {
		
    }
}
