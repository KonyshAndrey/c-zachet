#include <cmath>
#include "MyWindow.h"

MyWindow::MyWindow(int width, int height)
	: Window(width, height)
{
	_angle = 0.;
	_eye_level = 1.;
}

static const float s_material_red[4]{ 1.f, 0.f, 0.f, 1.f };
static const float s_material_yellow[4]{ 1.f, 1.f, 0.f, 1.f };

void MyWindow::setup()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClearColor(1.f, 1.f, 1.f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45., double(width()) / double(height()), 0.01, 20.0);
	glMatrixMode(GL_MODELVIEW);
}

void MyWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(
		10., 10., 10. * _eye_level + 1,
		0, 0, house_height/2,
		0., 0., 1.);

	glRotated(_angle, 0, 0, 1);

	glBegin(GL_QUADS);

	glNormal3d(1., 0., 0.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_red);
	glVertex3d(house_length / 2, -house_width / 2, house_height);
	glVertex3d(house_length / 2, house_width / 2, house_height);
	glVertex3d(house_length / 2, house_width / 2, 0);
	glVertex3d(house_length / 2, -house_width / 2, 0);

	glNormal3d(-1., 0., 0.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_red);
	glVertex3d(-house_length / 2, house_width / 2, house_height);
	glVertex3d(-house_length / 2, -house_width / 2, house_height);
	glVertex3d(-house_length / 2, -house_width / 2, 0.);
	glVertex3d(-house_length / 2, house_width / 2, 0.);

	glNormal3d(0., 1., 0.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_red);
	glVertex3d(-house_length / 2, house_width / 2, house_height);
	glVertex3d(house_length / 2, house_width / 2, house_height);
	glVertex3d(house_length / 2, house_width / 2, 0.);
	glVertex3d(-house_length / 2, house_width / 2, 0.);

	glNormal3d(0., -1., 0.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_red);
	glVertex3d(house_length / 2, -house_width / 2, house_height);
	glVertex3d(-house_length / 2, -house_width / 2, house_height);
	glVertex3d(-house_length / 2, -house_width / 2, 0.);
	glVertex3d(house_length / 2, -house_width / 2, 0.);

	glNormal3d(0., 0., -1.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_yellow);
	glVertex3d(house_length / 2, house_width / 2, 0.);
	glVertex3d(-house_length / 2, house_width / 2, 0.);
	glVertex3d(-house_length / 2, -house_width / 2, 0.);
	glVertex3d(house_length / 2, -house_width / 2, 0.);

	glNormal3d(0., -2, 3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_yellow);
	glVertex3d(-house_length / 2, 0., house_height * 1.5);
	glVertex3d(house_length / 2, 0., house_height * 1.5);
	glVertex3d(house_length / 2, -house_width / 2, house_height);
	glVertex3d(-house_length / 2, -house_width / 2, house_height);

	glNormal3d(0., 2, 3);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_yellow);
	glVertex3d(-house_length / 2, house_width / 2, house_height);
	glVertex3d(house_length / 2, house_width / 2, house_height);
	glVertex3d(house_length / 2, 0, house_height * 1.5);
	glVertex3d(-house_length / 2, 0, house_height * 1.5);

	glEnd();

	glBegin(GL_TRIANGLES);
		glNormal3d(-1., 0., 0.);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_yellow);
		glVertex3d(-house_length / 2, house_width / 2, house_height);
		glVertex3d(-house_length / 2, -house_width / 2, house_height);
		glVertex3d(-house_length / 2, 0, house_height * 1.5);

		glNormal3d(1., 0., 0.);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_yellow);
		glVertex3d(house_length / 2, house_width / 2, house_height);
		glVertex3d(house_length / 2, -house_width / 2, house_height);
		glVertex3d(house_length / 2, 0, house_height * 1.5);
	glEnd();
}

void MyWindow::handle_logic()
{
	if (_angle >= 360.)
		_angle -= 360.;
	else if (_angle <= 0.)
		_angle += 360.;
}

void MyWindow::handle_keys(const Uint8* keys)
{
	if(keys[SDL_SCANCODE_LEFT])
		_angle -= 0.1;
	if (keys[SDL_SCANCODE_RIGHT])
		_angle += 0.1;
	if (keys[SDL_SCANCODE_KP_PLUS])
	{
		if (keys[SDL_SCANCODE_KP_4])
			house_width += 0.01;
		if (keys[SDL_SCANCODE_KP_5])
			house_length += 0.01;
		if (keys[SDL_SCANCODE_KP_6])
			house_height += 0.01;
	}
	if (keys[SDL_SCANCODE_KP_MINUS])
	{
		if (keys[SDL_SCANCODE_KP_4])
			if (house_width > 0.05)
				house_width -= 0.01;
		if (keys[SDL_SCANCODE_KP_5])
			if (house_length > 0.05)
				house_length -= 0.01;
		if (keys[SDL_SCANCODE_KP_6])
			if (house_height > 0.05)
				house_height -= 0.01;
	}
}