#ifndef Vector2D_H
#define Vector2D_H

#include <iostream>

template <class T>
class Vector2D
{
public:
	Vector2D()
	{
		t[0] = 0;
		t[1] = 0;

	};
	Vector2D(T x, T y)
	{
		t[0] = x;
		t[1] = y;
	};
	~Vector2D() 
	{

	};

	bool operator==(Vector2D<T>& lhs) { return lhs.t[0] == t[0] && lhs.t[1] == t[1]; }


	friend std::ostream &operator<<(std::ostream &output,
		const Vector2D<T> &v)
	{
		output << v.t[0] << " " << v.t[1];
		return output;
	}

	friend std::istream &operator>>(std::istream &input,
		 Vector2D<T> &v)
	{
		input >> v.t[0] >> v.t[1];
		return input;
	}

	T& operator[](int i)
	{
		return t[i];
	}

	T& x()
	{
		return t[0];
	}
	T& y()
	{
		return t[1];
	}

	void set(T x, T y)
	{
		t[0] = x;
		t[1] = y;
	}
	void setX(T n)
	{
		t[0] = n;
	}
	void setY(T n)
	{
		t[1] = n;
	}

	void zero()
	{
		t[0] = 0;
		t[1] = 0;
	}
private:
	T t[2];
};

typedef Vector2D<int> Vector2Di;
typedef Vector2D<float> Vector2Df;
typedef Vector2D<double> Vector2Dd;



#endif // !Vector2D_H