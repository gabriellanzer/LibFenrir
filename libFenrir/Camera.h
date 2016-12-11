#pragma once
#include <cmath>
#include<iostream>
#include <iomanip> 
using namespace std;

#ifndef PI
#define PI 3.14159265
#endif

class Camera
{
public:
	Camera();
	~Camera();

	friend ostream& operator<<(ostream &out, Camera &camera)
	{
		out << "Camera at " << camera.x << ", " << camera.y << ", " << camera.z << ".";
		float dx, dy, dz;
		camera.getDirection(dx, dy, dz);
		out << " Looking at " << dx << ", " << dy << ", " << dz << ".\n";
		return out;
	}

	void getDirection(float &dx, float &dy, float &dz);
	float eyeX();
	float eyeY();
	float eyeZ();

	void setEye(float x, float y, float z);
	void setEyeX(float x);
	void addEyeX(float add);

	void setEyeY(float y);
	void addEyeY(float add);

	void setEyeZ(float z);
	void addEyeZ(float add);

	void setAngle(float angle);
	void addAngle(float add);

	void Foward(float vel = 0.1f);
	void Backward(float vel = 0.1f);
	
	void SlideRight(float vel = 0.1f);
	void SlideLeft(float vel = 0.1f);

	void face(int direction);
	

	void translate(float vel);

private:
	float x, y, z;
	int angle;



};

