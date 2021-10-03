#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H



class MouseInput
{
public:
	MouseInput() { m_press = 0; m_wheel = 0; };
	~MouseInput() {};

	void SetPosition(float x, float y) { m_position.x = x; m_position.y = y; };
	void SetEvent(KI_MOUSE_EVENT mouseEvent) { m_event = mouseEvent; };
	void SetWheel(int wheel) { m_wheel = wheel; };
	void SetPress(KI_MOUSE_BUTTON value) { m_press |= value; }
	void SetRelease(KI_MOUSE_BUTTON value) { m_press &= ~value; }

	const vec2& Position() const { return m_position; };
	KI_MOUSE_EVENT Event() const { return m_event; };
	int Wheel() const { return m_wheel; };
	bool Press(KI_MOUSE_BUTTON value) const { return m_press & value; }
	KI_MOUSE_BUTTON Press() const { return (KI_MOUSE_BUTTON)m_press; }
private:
	vec2 m_position;
	vec2 m_delta;
	KI_MOUSE_EVENT m_event;
	unsigned int m_press;	//Å@KI_MOUSE_BUTTON
	int m_wheel;
};

#endif MOUSE_INPUT_H
