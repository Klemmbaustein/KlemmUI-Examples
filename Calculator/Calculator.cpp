#include <KlemmUI/Application.h>
#include <KlemmUI/UI/UIText.h>
#include <KlemmUI/UI/UITextField.h>

#include "ExpressionParser.h"

namespace Calculator
{
	static std::string ExpressionString;
}

int main()
{
	using namespace Calculator;

	// Point the program to the KlemmUI shaders directory.
	Application::SetShaderPath("../KlemmUI/Shaders");

	// Initialize the app window with a window title, window flag and window resolution.
	Application::Initialize("Calculator", 0, Vector2ui(640, 480));


	TextRenderer* Text = new TextRenderer("../Shared/OpenSans.ttf");

	UITextField* CalculatorField = new UITextField(true, 0, 0.1f, Text, []() {});
	CalculatorField
		->SetTextSize(1.0f)
		->SetMinSize(Vector2f(0.5f, 0.1f));

	UIText* ResultText = new UIText(1.0f, Vector3f32(1.0f), "", Text);

	(new UIBox(false, Vector2f(-0.5, -0.5)))
		->AddChild(CalculatorField)
		->AddChild(ResultText);

	while (!Application::Quit)
	{
		if (ExpressionString != CalculatorField->GetText())
		{
			ExpressionString = CalculatorField->GetText();
			ExpressionParser::ExpressionNode Expression = ExpressionParser::Parse(ExpressionString);

			std::string str = std::to_string(Expression.Evaluate());

			str.erase(str.find_last_not_of('0') + 1, std::string::npos);
			str.erase(str.find_last_not_of('.') + 1, std::string::npos);

			ResultText->SetText(str);
		}

		Application::UpdateWindow();
	}
}

#if _WIN32
// On Windows, the entry point for GUI apps is called WinMain() instead of main()
int WinMain()
{
	return main();
}
#endif