#ifndef MODEL_H
#define MODEL_H

class Vect;
struct TriangleIndex;
struct VertexStride_VUN;

class Model
{
private:
	Vect *pVect;
	TriangleIndex *pTriList;

	char *textNames;

	unsigned int vao;
	unsigned int vbo[2];

	// Model information
	int numTextures;
	int numVerts;
	int numTris;

	// Bounding Sphere: bounding volume
	Vect *center;
	float radius;

	// AABB: axis aligned bounding box
	// Specifies the minimum extent of this AABB in the world space x, y and z axes.
	Vect *minPointAABB;
	// Specifies the maximum extent of this AABB in the world space x, y and z axes
	Vect *maxPointAABB;

	void privCreateVAO(VertexStride_VUN *pVerts, int nverts, TriangleIndex *pTriList, int ntri);
	void privCreateVAOFromFile(const char * const _modelName);
	void privBindAndLoadGPU(VertexStride_VUN *pVerts, int nverts, TriangleIndex *pTriList, int ntri);

public:

	enum PreMadedeModels {
		UnitSquareXY,
		UnitBox_WF,
		UnitSphere
	};

	Model(const char * const _modelName);
	Model(VertexStride_VUN *pVerts, int nverts, TriangleIndex *pTriList, int ntri);
	Model(PreMadedeModels pm);
	Model(int vertical_slices, int hor_slices);

	virtual ~Model();

	// Get the texture name
	char *getTextureName(int index);

	// Get access
	Vect* getVectList(void);
	int getVectNum()
	{ 
		return numVerts; 
	}
	TriangleIndex *getTriangleList(void);
	int getTriNum()
	{ 
		return numTris; 
	};
	int getTextureNum()
	{ 
		return numTextures; 
	};
	unsigned int getvao(){ return vao; }

	Vect& getCenter(){ return *center; }
	float getRadius(){ return radius; }
	Vect& getMinAABB(){ return *minPointAABB; }
	Vect& getMaxAABB(){ return *maxPointAABB; }

};


#endif