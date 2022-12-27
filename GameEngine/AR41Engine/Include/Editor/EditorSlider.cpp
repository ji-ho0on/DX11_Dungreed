#include "EditorSlider.h"

CEditorSlider::CEditorSlider() :
	m_Flag(0),
	m_SliderType(EImGuiSliderType::Int),
	m_ValueInt(0),
	m_IntMax(10),
	m_IntMin(0),
	m_ValueFloat(0.f),
	m_FloatMax(1.f),
	m_FloatMin(0.f),
	m_ValueAngle(0.f),
	m_AngleMax(360.f),
	m_AngleMin(-360.f)
{
}

CEditorSlider::~CEditorSlider()
{
}

void CEditorSlider::SetInt(int Value)
{
	m_ValueInt = Value;
}

void CEditorSlider::SetIntMax(int Value)
{
	m_IntMax = Value;
}

void CEditorSlider::SetIntMin(int Value)
{
	m_IntMin = Value;
}

void CEditorSlider::SetFloat(float Value)
{
	m_ValueFloat = Value;
}

void CEditorSlider::SetFloatMax(float Value)
{
	m_FloatMax = Value;
}

void CEditorSlider::SetFloatMin(float Value)
{
	m_FloatMin = Value;
}

void CEditorSlider::SetAngle(float Value)
{
	m_ValueAngle = Value;
}

void CEditorSlider::SetAngleMax(float Value)
{
	m_AngleMax = Value;
}

void CEditorSlider::SetAngleMin(float Value)
{
	m_AngleMin = Value;
}

void CEditorSlider::AddFlag(ImGuiSliderFlags_ Flag)
{
	m_Flag |= Flag;
	/*
    ImGuiSliderFlags_None                   = 0,
    ImGuiSliderFlags_AlwaysClamp            = 1 << 4,       // Clamp value to min/max bounds when input manually with CTRL+Click. By default CTRL+Click allows going out of bounds.
    ImGuiSliderFlags_Logarithmic            = 1 << 5,       // Make the widget logarithmic (linear otherwise). Consider using ImGuiSliderFlags_NoRoundToFormat with this if using a format-string with small amount of digits.
    ImGuiSliderFlags_NoRoundToFormat        = 1 << 6,       // Disable rounding underlying value to match precision of the display format string (e.g. %.3f values are rounded to those 3 digits)
    ImGuiSliderFlags_NoInput                = 1 << 7,       // Disable CTRL+Click or Enter key allowing to input text directly into the widget
    ImGuiSliderFlags_InvalidMask_           = 0x7000000F,   // [Internal] We treat using those bits as being potentially a 'float power' argument from the previous API that has got miscast to this enum, and will trigger an assert if needed
	*/
}

void CEditorSlider::FloatLog(bool Enable)
{
	if (Enable)
		m_Flag |= ImGuiSliderFlags_Logarithmic;

	else if (m_Flag & ImGuiSliderFlags_Logarithmic)
		m_Flag ^= ImGuiSliderFlags_Logarithmic;
}

void CEditorSlider::SetSliderType(EImGuiSliderType Type)
{
	m_SliderType = Type;
}

bool CEditorSlider::Init()
{
	return true;
}

void CEditorSlider::Render()
{
	switch (m_SliderType)
	{
	case EImGuiSliderType::Int:
		ImGui::SliderInt(m_NameUTF8.c_str(), &m_ValueInt, m_IntMin, m_IntMax, "%d", m_Flag);
		break;
	case EImGuiSliderType::Float:
		ImGui::SliderFloat(m_NameUTF8.c_str(), &m_ValueFloat, m_FloatMin, m_FloatMax, "%.3f", m_Flag);
		break;
	case EImGuiSliderType::Angle:
		ImGui::SliderAngle(m_NameUTF8.c_str(), &m_ValueAngle, m_AngleMin, m_AngleMax, "%0.f deg", m_Flag);
		break;
	}

}
