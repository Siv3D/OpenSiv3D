
# include <Siv3D.hpp>

void Main()
{
	while (System::Update())
	{
		PowerStatus status = System::GetPowerStatus();
		Log << L"------";
		Log << (int32)status.ac;
		Log << (int32)status.battery;
		Log << status.batteryLifePercent;
		Log << status.batteryLifeTimeSec;
		Log << status.batteryFullLifeTimeSec;
		Log << status.charging;
		Log << status.batterySaver;
	}
}
