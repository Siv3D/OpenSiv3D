# include <Siv3D.hpp>

void LogPowerStatus()
{
	const String ac[3] = { L"Unknown", L"Offline", L"Online" };
	const String bt[6] = { L"Unknown", L"High", L"Middle", L"Low", L"Critical", L"No battery" };

	PowerStatus status = System::GetPowerStatus();

	Log << L"------";
	Log << L"AC: " << ac[(int32)status.ac];
	Log << L"Battery status: " << bt[(int32)status.battery];

	if (status.batteryLifePercent)
	{
		Log << L"🔋" << status.batteryLifePercent.value() << L"%";
	}
	else
	{
		Log << L"🔋 -- %";
	}

	if (status.batteryLifeTimeSec)
	{
		Log << (status.batteryLifeTimeSec.value() / 60) << L" min to empty";
	}
	else
	{
		Log << L"-- min to empty";
	}

	if (status.batteryTimeToFullChargeSec)
	{
		Log << (status.batteryTimeToFullChargeSec.value() / 60) << L" min to full charge";
	}
	else
	{
		Log << L"-- min to full charge";
	}

	Log << L"charging: " << status.charging;

	Log << L"batterySaver: " << status.batterySaver;
}

void Main()
{
	while (System::Update())
	{
		//
		// macOS may take > 0.1ms for retrieving the power status. 
		// Thus, an application should not call this function every frame.
		//
		if (System::FrameCount() % 100 == 0)
		{
			LogPowerStatus();
		}
	}
}