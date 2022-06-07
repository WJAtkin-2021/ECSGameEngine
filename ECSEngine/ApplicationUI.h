#pragma once

class ApplicationUI
{
protected:

	ApplicationUI() { }
	~ApplicationUI() { };

public:

	virtual void DrawUI() = 0;
	virtual void OnSceneChanged() = 0;
};