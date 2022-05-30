#pragma once

class Entity
{
public:
	Entity() = default;
	Entity(int _id);
	~Entity();

private:

	int m_id = -1;
};