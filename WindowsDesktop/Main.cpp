
# include <Siv3D.hpp>

void Main()
{
	Scene::SetBackground(ColorF(0.9, 0.6, 0.3));
	NotificationID latest = -1;

	while (System::Update())
	{
		ClearPrint();
		Print << (int32)Platform::Windows::ToastNotification::GetState(latest);
		Print << U"Action: " << Platform::Windows::ToastNotification::GetAction(latest);

		if (SimpleGUI::Button(U"Send a notification", Vec2(10, 70)))
		{
			ToastNotificationProperty toast{
				.title = U"Title",
				.message = U"Message",
				.actions = { U"Yes", U"No" }
			};
			latest = Platform::Windows::ToastNotification::Show(toast);
		}
	}
}



