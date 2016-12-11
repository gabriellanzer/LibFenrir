#include "Camera.h"


Camera::Camera()
{
	x = 1;
	y = 1;
	z = 1;
	angle = 270;
	
}


Camera::~Camera()
{
}

void Camera::getDirection(float &dx, float &dy, float &dz)
{
	dy = y;
	dx = x + cosf(angle * PI/180.0);
	dz = z + sinf(angle * PI/180.0);
}
float Camera::eyeX()
{
	return x;
}
float Camera::eyeY()
{
	return y;
}
float Camera::eyeZ()
{
	return z;
}

void Camera::setEye(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}
void Camera::setEyeX(float x)
{
	this->x = x;
	
}
void Camera::setEyeY(float y)
{
	this->y = y;
	
}
void Camera::setEyeZ(float z)
{
	this->z = z;
}

void Camera::setAngle(float angle)
{
	this->angle = angle;
}
void Camera::translate(float vel)
{

	x += cosf(angle* PI / 180.0) * vel;
	z += sinf(angle* PI / 180.0) * vel;
}
void Camera::addAngle(float add)
{
	angle += add;
	if (angle > 360)
		angle = angle - 360;
	if (angle < 0)
		angle = 360 + angle;
}
void Camera::addEyeX(float add)
{
	x += add;
}
void Camera::addEyeY(float add)
{
	y += add;
}
void Camera::addEyeZ(float add)
{
	z += add;
}

void Camera::Foward(float vel )
{
	translate(abs(vel));
}

void Camera::Backward(float vel )
{
	translate(-abs(vel));
}


void Camera::SlideRight(float vel)
{
	x += abs(vel) * cosf((90 + angle) * PI / 180.0f);
	z += abs(vel) * sinf((90 + angle) * PI / 180.0f);
}

void Camera::SlideLeft(float vel)
{
	x -= abs(vel) * cosf((90 + angle) * PI / 180.0f);
	z -= abs(vel) * sinf((90 + angle) * PI / 180.0f);
}


void Camera::face(int direction)
{
	
}
