#ifndef Face_H
#define Face_H


#include <vector>

#ifndef UINT_H
#define UINT_H
typedef unsigned int uint;
#endif // !UINT_H


class Face
{
public:
	Face();
	Face(std::vector<uint> &vertex);
	~Face();


	inline bool operator==(const Face& lhs) {
		if (lhs.v.size() == v.size())
		{
			bool b;
			for (int i = 0; i < v.size(); i++)
			{
				if (v[i] != lhs.v[i])
					return false;
			}
			return true;
		}
		else
			return false;
	}

	inline bool operator!=(const Face& lhs) {
		return !(&lhs == &*this);
	}

	/*friend ostream &operator<<(ostream &output,
		const Face &v)
	{
		output <<
			return output;
	}

	friend std::istream &operator>>(std::istream &input,
		const Face &v)
	{
		uint a;
		
	}*/

	std::vector<uint>& vertex();
	uint& vertex(int& n);

	std::vector<uint>& normal();
	uint& normal(int& n);

	std::vector<uint>& mapping();
	uint& mapping(int& n);

	void set(std::vector<uint> &v, std::vector<uint> &vn, std::vector<uint> &t);

	void addVertex(uint& n);
	void addVertexAt(uint & n, int& w);

	void removeVertex(uint &n);
	void removeVertexAt(int &n);

	void addNormal(uint& n);
	void addNormalAt(uint & n, int& w);

	void removeNormal(uint &n);
	void removeNormalAt(int &n);

	void addMapping(uint& n);
	void addMappingAt(uint & n, int& w);

	void removeMapping(uint &n);
	void removeMappingAt(int &n);

	int sizeVertex();
	int sizeMapping();
	int sizeNormal();

private:
	std::vector<uint> v;
	std::vector<uint> vn;
	std::vector<uint> t;
};


#endif // !Face_H