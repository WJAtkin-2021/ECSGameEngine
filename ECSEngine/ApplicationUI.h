#pragma once

class ApplicationUI
{
protected:

	ApplicationUI() { }
	~ApplicationUI() { };

public:

	virtual void DrawUI() = 0;
};