#pragma once
#include <memory>
#include "ApplicationUI.h"

class UI
{
public:

	UI();
	virtual ~UI();

	// Getters
	static void SetApplicationUI(std::shared_ptr<ApplicationUI> _applicationUI);

	// Setters
	static UI* GetIU() { return m_instance; }
	std::shared_ptr<ApplicationUI> GetApplicationUI() { return m_applicationUI; }

	virtual void DrawUI();

protected:

	void SetupImGuiPlatformIndependant();
	void DrawDockSpace();

private:

	static UI* m_instance;
	std::shared_ptr<ApplicationUI> m_applicationUI = nullptr;
};