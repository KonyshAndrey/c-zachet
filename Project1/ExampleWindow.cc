/*
 * ExampleWindow.cc
 *
 *  Created on: 19 окт. 2020 г.
 *      Author: unyuu
 */

#include <cmath>

static constexpr double Pi = 3.14;

#include "ExampleWindow.h"

ExampleWindow::ExampleWindow(int width, int height)
: Window(width, height)
{
	_angle = 0.;
	_eye_level = 0.;
}

static const float s_material_red[4]     { 1.f, 0.f, 0.f, 1.f };//задаём цвета
static const float s_material_green[4]   { 0.f, 1.f, 0.f, 1.f };
static const float s_material_blue[4]    { 0.f, 0.f, 1.f, 1.f };
static const float s_material_cyan[4]    { 0.f, 1.f, 1.f, 1.f };
static const float s_material_magenta[4] { 1.f, 0.f, 1.f, 1.f };
static const float s_material_yellow[4]  { 1.f, 1.f, 0.f, 1.f };

void ExampleWindow::setup()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glClearColor(0.15f, 0.15f, 0.4f, 1.0f);//цвет фона
	glMatrixMode(GL_PROJECTION);
	gluPerspective(45., double(width()) / double(height()), 0.01, 20.0);//настройки перспективы
	glMatrixMode(GL_MODELVIEW);
}

void ExampleWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	gluLookAt(
			5., 5., 5. * _eye_level, //координаты зрителя
			0., 0., 0., //координаты центра (точка, куда смотрим)
			0., 0., 1.);//вектор, определяющий направление "вверх"

	glRotated(_angle, 0., 0., 1.); //поворот на угол относительно вектора (0;0;1)

	glBegin(GL_QUADS);//Начинаем рисовать, в данном случае -- квадраты. Разделяет все следующие glVertex3d на группы по 4, оставшиеся точки будут проигнорированы

	glNormal3d(  1.,  0.,  0.);//нормаль к нашей плоскости, используется при вычислении освещённости
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_red);//задаём свойства материала
	glVertex3d(  1., -1.,  1.);//задаём 
	glVertex3d(  1.,  1.,  1.);//четырёхугольник
	glVertex3d(  1.,  1., -1.);//4
	glVertex3d(  1., -1., -1.);//точками

	glNormal3d( -1.,  0.,  0.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_cyan);
	glVertex3d( -1.,  1.,  1.);
	glVertex3d( -1., -1.,  1.);
	glVertex3d( -1., -1., -1.);
	glVertex3d( -1.,  1., -1.);

	glNormal3d(  0.,  1.,  0.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_green);
	glVertex3d( -1.,  1.,  1.);
	glVertex3d(  1.,  1.,  1.);
	glVertex3d(  1.,  1., -1.);
	glVertex3d( -1.,  1., -1.);

	glNormal3d(  0., -1.,  0.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_magenta);
	glVertex3d(  1., -1.,  1.);
	glVertex3d( -1., -1.,  1.);
	glVertex3d( -1., -1., -1.);
	glVertex3d(  1., -1., -1.);

	glNormal3d(  0.,  0.,  1.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_blue);
	glVertex3d( -1.,  1.,  1.);
	glVertex3d(  1.,  1.,  1.);
	glVertex3d(  1., -1.,  1.);
	glVertex3d( -1., -1.,  1.);

	glNormal3d(  0.,  0., -1.);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_material_yellow);
	glVertex3d(  1.,  1., -1.);
	glVertex3d( -1.,  1., -1.);
	glVertex3d( -1., -1., -1.);
	glVertex3d(  1., -1., -1.);

	glEnd();
}

void ExampleWindow::handle_logic()
{
	_angle += 0.25;//увечили угол
	if (_angle >= 360.)//если больше 360
		_angle -= 360.;// устанавливаем в ~0

	_eye_level = sin(_angle / 180. * Pi); //изменяем высоту зрителя в зависимости от угла
}
