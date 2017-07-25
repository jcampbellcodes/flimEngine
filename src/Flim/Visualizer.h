#pragma once
#ifndef VISUALIZER_H
#define VISUALIZER_H

#include "AzulCore.h"

#include "CollisionVolumeBSphere.h"
#include "RenderBoxCommand.h"
#include "FlimColor.h"
#include <stack>

//#define USE_FLIM_VISUALIZER

class RenderBSphereCommand;
class Collidable;

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	Visualizer
///
/// \brief	A visualizer.
/// \ingroup TOOLS
/// 		 
/// \par Can be used to render visual aids that represent colliders for models.
///
/// \author	Jack Campbell
/// \date	3/5/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class Visualizer : public Align16
{
public:

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static errcode Visualizer::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR)
	///
	/// \brief	Shows the b sphere.
	/// \ingroup TOOLS
	/// \author	Jack Campbell
	/// \date	3/5/2017
	///
	/// \param	S  	The CollisionVolumeBSphere to process.
	/// \param	col	(Optional) The col.
	///
	/// \par Give this function a BSphere and a color to render.
	/// 
	/// \return	An errcode.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static errcode ShowBSphere(const CollisionVolumeBSphere& S,
		const Vect& col = Vect(1.0f, 1.0f,1.0f))
	{
#ifdef USE_FLIM_VISUALIZER
		return Instance().privShowBSphere(S, col);
#else
		S;
		col;
		return errcode::no_terrain;
#endif

	}

	static errcode ShowAABB(const CollisionVolumeAABB& S,
		const Vect& col = Vect(1.0f, 1.0f, 1.0f))
	{
#ifdef USE_FLIM_VISUALIZER
		return Instance().privShowAABB(S, col);
#else
		S;
		col;
		return errcode::no_terrain;
#endif
	}

	static errcode ShowAABB(const Vect& min, const Vect& max,
		const Vect& col = Vect(1.0f, 1.0f, 1.0f))
	{
#ifdef USE_FLIM_VISUALIZER
		return Instance().privShowAABB(min, max, col);
#else
		min, max, col;
		return errcode::no_terrain;
#endif
	}

	static errcode ShowOBB(const Matrix& world, const CollisionVolumeOBB& S,
		const Vect& col = Vect(1.0f, 1.0f, 1.0f))
	{
#ifdef USE_FLIM_VISUALIZER
		return Instance().privShowOBB(world, S, col);
#else
		world, S, col;
		return errcode::no_terrain;
#endif
	}

	static errcode Terminate()
	{
#ifdef USE_FLIM_VISUALIZER
		return Instance().privTerminate();
#else
		return errcode::no_terrain;
#endif
	}

	static errcode VisualizeAll()
	{
#ifdef USE_FLIM_VISUALIZER
		return Instance().privVisualizeAll();
#else
		return errcode::no_terrain;
#endif
	}

	static errcode ShowCollisionVolume(const Collidable & S, const Vect & col)
	{
#ifdef USE_FLIM_VISUALIZER
		return Instance().privShowCollisionVolume(S, col);
#else
		S, col;
		return errcode::no_terrain;
#endif
	}

	static errcode ShowMarker(const Vect& pos, const Vect& col = flimColor::pink, float radius = 1);

	static errcode ShowLine(const Vect& start, const Vect& end, const Vect& col = flimColor::pink);

private:

	friend class RenderBSphereCommand;
	static errcode RenderBSphere(Matrix& mat, const Vect& col)
	{
		return Instance().privRenderBSphere(mat, col);
	}

	friend class RenderAABBCommand;
	friend class RenderBoxCommand;
	static errcode RenderAABB(Matrix& mat, const Vect& col)
	{
		return Instance().privRenderAABB(mat, col);
	}

	//big four
	Visualizer();
	~Visualizer() = default;
	Visualizer& operator=(const Visualizer&) = delete;
	Visualizer(const Visualizer&) = delete;

	// singleton
	static Visualizer* instance;
	static Visualizer& Instance()
	{
		if (!instance)
		{
			instance = new Visualizer();
		}
		return *instance;
	}

	static Vect DEFAULT_COLOR;

	GraphicsObject_WireframeConstantColor* WFUnitSphere;
	GraphicsObject_WireframeConstantColor* WFUnitBox;

	// instance methods
	errcode privRenderBSphere(Matrix& S, const Vect& col);
	errcode privRenderAABB(Matrix& mat, const Vect& col);
	errcode privTerminate();
	errcode privVisualizeAll();
	errcode privShowBSphere(const CollisionVolumeBSphere& S, const Vect& col = DEFAULT_COLOR);
	errcode privShowAABB(const CollisionVolumeAABB& S, const Vect& col = DEFAULT_COLOR);

	errcode privShowAABB(const Vect & _min, const Vect & _max, const Vect & col);
	errcode privShowOBB(const Matrix& world, const CollisionVolumeOBB& S, const Vect& col = DEFAULT_COLOR);

	errcode privShowCollisionVolume(const Collidable& S, const Vect& col = DEFAULT_COLOR);

	// command pattern
	std::stack<RenderBSphereCommand*> executeBSphereCmds; // pop these all off 
	std::stack<RenderAABBCommand*> executeAABBCmds;
	std::stack<RenderBoxCommand*> executeBoxCmds;

	// object pool
	// b spheres
	// show bsphere grabs and initializes one of these baddies if it can, execute returns them here
	std::stack<RenderBSphereCommand*> inactiveBSphereCmds;
	std::stack<RenderAABBCommand*> inactiveAABBCmds;
	std::stack<RenderBoxCommand*> inactiveBoxCmds;

};

#endif