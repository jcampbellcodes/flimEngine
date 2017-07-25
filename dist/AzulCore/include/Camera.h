#ifndef CAMERA_H
#define CAMERA_H

#include "MathEngine.h"


class Camera final : public Align16
{

public:

	enum class Type
	{
		PERSPECTIVE_3D, 
		ORTHOGRAPHIC_2D
	};

   // Default constructor
	Camera( Camera::Type type);
	~Camera();

   // Setup on single camera
	void setPerspective(const float FieldOfView_Degs, const float AspectRatio, const float NearDist, const float FarDist);
	void setOrthographic(const float xMin, const float xMax, const float yMin, const float yMax, const float zMin, const float zMax);
	void setViewport(const int inX, const int inY, const int width, const int height);
	void setOrientAndPosition(const Vect &Up_vect, const Vect &inLookAt_pt, const Vect &pos_pt);

   // update camera system
	void updateCamera(void);

   // Get the matrices for rendering
	Matrix &getViewMatrix();
	Matrix &getProjMatrix();
	
	// accessors
	Camera::Type getType() const;

	void getPos( Vect &outPos) const;
	void getDir( Vect &outDir) const;
	void getUp( Vect &outUp) const;
	void getLookAt( Vect &outLookAt ) const;
	void getRight( Vect &outRight ) const;

	int getScreenWidth() const;
	int getScreenHeight() const;
			
	// Why no SETS?  Pos,Dir,Up,LookAt, Right
	//   They have to be adjust together in setOrientAndPosition()
			
	void getFieldOfView( float &Value) const;
	void setFieldOfView( const float Value);

	void getNearDist( float &Value) const;
	void setNearDist( const float Value);

	// helper functions

	void getNearTopLeft(Vect &vOut) const;
	void getNearTopRight(Vect &vOut) const;
	void getNearBottomLeft(Vect &vOut) const;
	void getNearBottomRight(Vect &vOut) const;	
	void getFarTopLeft(Vect &vOut) const;
	void getFarTopRight(Vect &vOut) const;
	void getFarBottomLeft(Vect &vOut) const;
	void getFarBottomRight(Vect &vOut) const;

	// Get the world 
	void TargetWorldScreen( Vect &outCamPos, Vect &outCamLookAt, float worldScreenX, float worldScreenY );
	void CorrectForOrigin(float &xpos,float &ypos );

private:  // methods should never be public
    void privSetViewState( void );
	void privCalcPlaneHeightWidth( void );
	void privCalcFrustumVerts( void );
	void privCalcFrustumCollisionNormals( void );
	void privUpdateProjectionMatrix( void );
	void privUpdateViewMatrix( void );


private:  // data  (Keep it private)

	// -------------------------------------------------------
	// 16-bit aligned data below this point:
	// -------------------------------------------------------

	// Projection Matrix
	Matrix	projMatrix;
	Matrix	viewMatrix;

	// camera unit vectors (up, dir, right)
	Vect	vUp;
	Vect	vDir;
	Vect	vRight;  // derived by up and dir
	Vect	vPos;    
	Vect	vLookAt;

	// world space coords for viewing frustum
	Vect	nearTopLeft;
	Vect	nearTopRight;
	Vect	nearBottomLeft;
	Vect	nearBottomRight;
	Vect	farTopLeft;
	Vect	farTopRight;
	Vect	farBottomLeft;
	Vect	farBottomRight;

	// Normals of the frustum
	Vect	frontNorm;
	Vect	backNorm;
	Vect	rightNorm;
	Vect	leftNorm;
	Vect	topNorm;
	Vect	bottomNorm;

	// -------------------------------------------------------
	// unaligned data below this point:
	// -------------------------------------------------------

	Camera::Type camType;

	// Define the frustum inputs
	float	nearDist;
	float	farDist;
	float	fovy;
	float	aspectRatio;

	// Screen size in world space
	float	near_height;
	float	near_width;
	float	far_height;
	float	far_width;
	
	// Ortho hacks
	float	xMin;
	float	yMin;
	float	zMin;
	float	xMax;

	float	yMax;
	float	zMax;

	// viewports
	int		viewport_x;
	int		viewport_y;
	int		viewport_width;
	int		viewport_height;

	int		pad0;  // can be replaced, only here to demonstrate the additional padding



};

#endif