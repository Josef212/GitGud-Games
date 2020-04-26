#pragma once

class GameElement
{
public:
	virtual ~GameElement() = default;

	inline bool IsActive()const { return _active; }
	inline void SetACtive(bool active) { _active = active; }

	virtual void Update(float dt) {}
	virtual void Render() {}

protected:
	GameElement() : _active(true) {}

protected:
	bool _active;
};