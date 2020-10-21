#pragma once
#include "Window.h"

class MyWindow : public Window
{
public:
	static constexpr int DEFAULT_WIDTH = 1920;
	static constexpr int DEFAULT_HEIGHT = 1080;

protected:
	double _angle;
	double _eye_level;
	double house_width = 3;
	double house_height = 2;
	double house_length = 4;

public:
	MyWindow(
		int width = DEFAULT_WIDTH,
		int height = DEFAULT_HEIGHT);

	virtual ~MyWindow() = default;

	virtual void setup() override;

	virtual void render() override;

	virtual void handle_logic() override;
	virtual void handle_keys(const Uint8* keys) override;
};
