#ifndef Vector3D_H
#define Vector3D_H
#include <iostream>
#include <cmath>
template <class T>


class Vector3D
{
public:
	Vector3D()
	{
		t[0] = 0;
		t[1] = 0;
		t[2] = 0;
	};
	Vector3D(T x, T y, T z)
	{
		t[0] = x;
		t[1] = y;
		t[2] = z;
	};
	~Vector3D()
	{
	};

	bool operator==(Vector3D<T>& lhs) { return lhs.t[0] == t[0] && lhs.t[1] == t[1] && lhs.t[2] == t[2]; }

	friend std::ostream& operator<<(std::ostream &output, const Vector3D<T> &v)
	{
		output << v.t[0] << " " << v.t[1] << " " << v.t[2];
		return output;
	}

	friend std::istream& operator>>(std::istream &input,  Vector3D<T> &v)
	{
		input >> v.t[0] >> v.t[1] >> v.t[2];
		return input;
	}

	double InverseMag()
	{
		return (1.0F / sqrtf((t[0] * t[0] + t[1] * t[1] + t[2] * t[2])));
	}

	double SquaredMag()
	{
		return (t[0] * t[0] + t[1] * t[1] + t[2] * t[2]);
	}

	double Magnitude()
	{
		return (sqrtf(t[0] * t[0] + t[1] * t[1] + t[2] * t[2]));
	}

	void operator+=(const Vector3D& v)
	{
		t[0] += v.x();
		t[1] += v.y();
		t[2] += v.z();
	}
	void operator-=(const Vector3D& v)
	{
		t[0] -= v.x();
		t[1] -= v.y();
		t[2] -= v.z();
	}
	void operator*=(const Vector3D& v)
	{
		t[0] *= v.x();
		t[1] *= v.y();
		t[2] *= v.z();
	}
	void operator/=(const Vector3D& v)
	{
		t[0] /= v.x();
		t[1] /= v.y();
		t[2] /= v.z();
	}

	void operator+=(float a)
	{
		t[0] += a;
		t[1] += a;
		t[2] += a;
	}
	void operator-=(float a)
	{
		t[0] -= a;
		t[1] -= a;
		t[2] -= a;
	}
	void operator*=(float a)
	{
		t[0] *= a;
		t[1] *= a;
		t[2] *= a;
	}
	void operator/=(float a)
	{
		t[0] /= a;
		t[1] /= a;
		t[2] /= a;
	}

	Vector3D operator+( Vector3D& v)
	{
		return Vector3D(t[0] + v.x(), t[1] + v.y(), t[2] + v.z());
	}
	Vector3D operator-( Vector3D& v)
	{
		return Vector3D(t[0] - v.x(), t[1] - v.y(), t[2] - v.z());
	}
	Vector3D operator*( Vector3D& v)
	{
		return Vector3D(t[0] * v.x(), t[1] * v.y(), t[2] * v.z());
	}
	Vector3D operator/( Vector3D& v)
	{
		return Vector3D(t[0] / v.x(), t[1] / v.y(), t[2] / v.z());
	}

	Vector3D operator+(float a)
	{
		return Vector3D(t[0] + a, t[1] + a, t[2] + a);
	}
	Vector3D operator-(float a)
	{
		return Vector3D(t[0] - a, t[1] - a, t[2] - a);
	}
	Vector3D operator*(float a)
	{
		return Vector3D(t[0] * a, t[1] * a, t[2] * a);
	}
	Vector3D operator/(float a)
	{
		return Vector3D(t[0] / a, t[1] / a, t[2] / a);
	}

	T& operator[](int i)
	{
		return t[i];
	}

	T& x()
	{
		return t[0];
	};
	T& y()
	{
		return t[1];
	};
	T& z()
	{
		return t[2];
	};

	void set(T x, T y, T z)
	{
		t[0] = x;
		t[1] = y;
		t[2] = z;
	};
	void setX(T n)
	{
		t[0] = n;
	}
	void setY(T n)
	{
		t[1] = n;
	}
	void setZ(T n)
	{
		t[2] = n;
	}

	void zero()
	{
		t[0] = 0;
		t[1] = 0;
		t[2] = 0;
	};
private:
	T t[3];
};
typedef Vector3D<int> Vector3Di;
typedef Vector3D<float> Vector3Df;
typedef Vector3D<double> Vector3Dd;

#endif // !Vector3D_H
