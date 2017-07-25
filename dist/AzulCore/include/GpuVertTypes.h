#ifndef GPU_VERTS_H
#define GPU_VERTS_H


struct VertexStride_VUN
{
	float x;    // Vert - V
	float y;
	float z;

	float u;    // UV tex coor - U
	float v;
	float txt;

	float nx;   // Norm verts - N
	float ny;
	float nz;

	float r;
	float g;
	float b;

	void set(float _x, float _y, float _z,
		float _u, float _v,
		float _nx, float _ny, float _nz,
		float _txt = 0,
		float _r = 1, float _g = 1, float _b = 1)
	{
		x = _x; 
		y = _y;
		z = _z;
		u = _u;
		v = _v;
		nx = _nx;
		ny = _ny;
		nz = _nz;

		txt = _txt;
		r = _r;
		g = _g;
		b = _b;
	}
	
};


struct TriangleIndex
{
	unsigned int v0;
	unsigned int v1;
	unsigned int v2;

	void set(int _v0, int _v1, int _v2)
	{
		v0 = _v0;
		v1 = _v1;
		v2 = _v2;
	}
};


#endif