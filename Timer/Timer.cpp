#include <KlemmUI/Application.h>
#include <KlemmUI/UI/UIText.h>
#include <KlemmUI/UI/UIButton.h>
#include <string>
#include <sstream>
#include <iomanip>

static std::string ToString(int Value, int Precision)
{
	std::stringstream ss;
	ss << std::setfill('0') << std::setw(Precision) << Value;
	return ss.str();
}

static std::string FormatTime(float TimeInSeconds)
{
	return ToString((int)TimeInSeconds / 60, 2)
		+ ":"
		+ ToString((int)std::floorf(TimeInSeconds) % 60, 2)
		+ ":"
		+ ToString((int)(TimeInSeconds * 100) % 100, 2);
}

static float AppTimer = 0;
static bool TimerActive = false;

// Functions for the timer buttons

static void StartTimer()
{
	TimerActive = true;
}

static void StopTimer()
{
	TimerActive = false;
}

static void ResetTimer()
{
	StopTimer();
	AppTimer = 0;
}

static UIButton* MakeTimerButton(void(*OnPressed)(), const std::string& Name, TextRenderer* Font)
{
	return static_cast<UIButton*>((new UIButton(true, 0, Vector3f32(1), OnPressed))
		->SetPaddingSizeMode(UIBox::SizeMode::PixelRelative)
		->SetMinSize(Vector2f32(0.3f, 0))
		->SetSizeMode(UIBox::SizeMode::PixelRelative)
		->SetHorizontalAlign(UIBox::Align::Centered)
		->AddChild((new UIText(0.75f, Vector3f32(0), Name, Font))
			->SetTextSizeMode(UIBox::SizeMode::PixelRelative)
			->SetPaddingSizeMode(UIBox::SizeMode::PixelRelative)));
}

int main()
{
	// Point the program to the KlemmUI shaders directory.
	Application::SetShaderPath("../KlemmUI/Shaders");

	// Initialize the app window with a window title, window flag and window resolution.
	Application::Initialize("Timer", 0, Vector2ui(640, 480));

#if _WIN32
	TextRenderer* Font = new TextRenderer("C:/Windows/Fonts/segoeui.ttf");
#else
#endif

	UIText* TimerText = new UIText(1.5f, Vector3f32(1), "00:00:00", Font);
	TimerText
		->SetTextSizeMode(UIBox::SizeMode::PixelRelative);

	UIBox* MainBox = new UIBox(true, -1);
	MainBox
		->SetMinSize(2)
		->SetMaxSize(2)
		->SetVerticalAlign(UIBox::Align::Centered)
		->SetHorizontalAlign(UIBox::Align::Centered)
		->AddChild(TimerText)
		->AddChild((new UIBox(false, 0))
			->SetPadding(0, 0, 0.25f, 0)
			->SetPaddingSizeMode(UIBox::SizeMode::PixelRelative)
			->AddChild(MakeTimerButton(StartTimer, "Start", Font))
			->AddChild(MakeTimerButton(StopTimer, "Stop", Font))
			->AddChild(MakeTimerButton(ResetTimer, "Reset", Font)));

	// Application will be true if the program should be closed.
	while (!Application::Quit)
	{
		TimerText->SetText(FormatTime(AppTimer));

		Application::UpdateWindow();

		if (TimerActive)
		{
			AppTimer += Application::DeltaTime;
		}
	}
}

#if _WIN32
int WinMain()
{
	return main();
}
#endif