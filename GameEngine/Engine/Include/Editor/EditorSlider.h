#pragma once

#include "EditorWidget.h"

enum class EImGuiSliderType
{
	Int,
	Float,
	Angle
};

class CEditorSlider :
    public CEditorWidget
{
	friend class CEditorWindow;

	template <typename T>
	friend class CEditorTreeItem;

	friend class CEditorTapItem;

	friend class CEditorGroup;

protected:
	CEditorSlider();
	virtual ~CEditorSlider();

private:
	ImGuiSliderFlags		m_Flag;

	EImGuiSliderType		m_SliderType;

	int						m_ValueInt;
	int						m_IntMax;
	int						m_IntMin;


	float					m_ValueFloat;
	float					m_FloatMax;
	float					m_FloatMin;

	float					m_ValueAngle;
	float					m_AngleMax;
	float					m_AngleMin;


	std::function<void()>	m_InputCallback;

public:
	EImGuiSliderType GetSliderType()	const
	{
		return m_SliderType;
	}

	int GetInt()	const
	{
		return m_ValueInt;
	}

	int GetIntMax()	const
	{
		return m_IntMax;
	}

	int GetIntMin()	const
	{
		return m_IntMin;
	}

	float GetFloat()	const
	{
		return m_ValueFloat;
	}

	float GetFloatMax()	const
	{
		return m_FloatMax;
	}

	float GetFloatMin()	const
	{
		return m_FloatMin;
	}

	float GetAngle()	const
	{
		return m_ValueAngle;
	}

	float GetAngleMax()	const
	{
		return m_AngleMax;
	}

	float GetAngleMin()	const
	{
		return m_AngleMin;
	}


public:
	void SetInt(int Value);
	void SetIntMax(int Value);
	void SetIntMin(int Value);
	void SetFloat(float Value);
	void SetFloatMax(float Value);
	void SetFloatMin(float Value);
	void SetAngle(float Value);
	void SetAngleMax(float Value);
	void SetAngleMin(float Value);
	void AddFlag(ImGuiSliderFlags_ Flag);
	void FloatLog(bool Enable);
	void SetSliderType(EImGuiSliderType Type);

public:
	virtual bool Init();
	virtual void Render();

public:
	template <typename T>
	void SetInputCallback(T* Obj, void(T::* Func)())
	{
		m_InputCallback = std::bind(Func, Obj);
	}
};

