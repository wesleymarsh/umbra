#pragma once

#include <raylib/raylib.h>

#include <string>

using std::string;

class Screen
{
	friend class Application;

public:
	float Width() const;
	float Height() const;

	const string& Title() const;
	const Color& ClearColor() const;

	void SetWidth(int newWidth);
	void SetHeight(int newHeight);

	void SetTitle(const char* newTitle);
	void SetClearColor(Color newClearColor);

private:
	int m_width;
	int m_height;

	string m_title;
	Color m_clearColor;

	bool m_isUsingAudio;

private:
	Screen();
	~Screen();

private:
	bool Open(bool initialiseAudio = false);
	void Close();

	void NewFrame();
	void EndFrame();
};