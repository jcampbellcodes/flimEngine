#include "Visualizer.h"
#include "SceneManager.h"
#include "ShaderManager.h"
#include "Scene.h"
#include "Camera.h"
#include "RenderBSphereCommand.h"
#include "RenderAABBCommand.h"
#include "Collidable.h"
#include "CollisionVolumeOBB.h"

Visualizer* Visualizer::instance = nullptr;

errcode Visualizer::ShowMarker(const Vect & pos, const Vect & col, float radius)
{
	Matrix M = Matrix(SCALE, radius, radius, radius) * Matrix(TRANS, pos);

	RenderBoxCommand* cmd = new RenderBoxCommand(M, col);

	Instance().executeBoxCmds.push(cmd);

	return errcode::success;
}

errcode Visualizer::ShowLine(const Vect & start, const Vect & end, const Vect & col)
{
	Matrix M;
	M.set(ROT_ORIENT, end - start, Vect(0, 1, 0));
	M = M*Matrix(TRANS, end);

	Vect Min = Vect(0, 0, 0, 1);
	Vect Max = -(start - end).mag() * Vect(0, 0, 1);

	M = Matrix(SCALE, (Max - Min)) * Matrix(TRANS, .5*(Max + Min)) * M;


	RenderBoxCommand* cmd = new RenderBoxCommand(M, col);

	Instance().executeBoxCmds.push(cmd);

	return errcode::success;
}

Visualizer::Visualizer()
{
	Vect v(0, 0, 0);
	WFUnitSphere = new GraphicsObject_WireframeConstantColor(new Model(Model::PreMadedeModels::UnitSphere), &ShaderManager::GetShader("__FLIM__colorConstantRender"), v);
	WFUnitBox = new GraphicsObject_WireframeConstantColor(new Model(Model::PreMadedeModels::UnitBox_WF), &ShaderManager::GetShader("__FLIM__colorConstantRender"), v);
}

errcode Visualizer::privRenderBSphere(Matrix & S, const Vect& col)
{

	this->WFUnitSphere->pWireColor->set(col);

	this->WFUnitSphere->SetWorld(S);

	Camera* cam = &SceneManager::GetCurrentScene().GetCamera()->MainCamera();
	assert(cam);
	this->WFUnitSphere->Render(cam);
	return errcode::success;
}

errcode Visualizer::privRenderAABB(Matrix & mat, const Vect & col)
{

	this->WFUnitBox->pWireColor->set(col);

	this->WFUnitBox->SetWorld(mat);

	Camera* cam = &SceneManager::GetCurrentScene().GetCamera()->MainCamera();
	assert(cam);
	this->WFUnitBox->Render(cam);
	return errcode::success;
}

errcode Visualizer::privTerminate()
{

	if (this->WFUnitSphere)
	{
		delete this->WFUnitSphere;
		this->WFUnitSphere = nullptr;
	}
	if (this->WFUnitBox)
	{
		delete this->WFUnitBox;
		this->WFUnitBox = nullptr;
	}
	// empty the stack
	while (this->executeBSphereCmds.size())
	{
		this->executeBSphereCmds.pop();
	}

	while (this->inactiveBSphereCmds.size())
	{
		this->inactiveBSphereCmds.pop();
	}

	while (this->executeAABBCmds.size())
	{
		this->executeAABBCmds.pop();
	}

	while (this->inactiveAABBCmds.size())
	{
		this->inactiveAABBCmds.pop();
	}

	while (this->executeBoxCmds.size())
	{
		this->executeBoxCmds.pop();
	}

	while (this->inactiveBoxCmds.size())
	{
		this->inactiveBoxCmds.pop();
	}

	return errcode::success;
}

errcode Visualizer::privVisualizeAll()
{
#ifdef USE_FLIM_VISUALIZER

	// execute the command on top
	// add top to the inactive stack
	// pop it

	while (!executeBSphereCmds.empty())
	{
		executeBSphereCmds.top()->execute();
		inactiveBSphereCmds.push(executeBSphereCmds.top());
		executeBSphereCmds.pop();
	}

	while (!executeAABBCmds.empty())
	{
		executeAABBCmds.top()->execute();
		inactiveAABBCmds.push(executeAABBCmds.top());
		executeAABBCmds.pop();
	}

	while (!executeBoxCmds.empty())
	{
		executeBoxCmds.top()->execute();
		inactiveBoxCmds.push(executeBoxCmds.top());
		executeBoxCmds.pop();
	}
#endif

	return errcode::success;
}

errcode Visualizer::privShowBSphere(const CollisionVolumeBSphere & S, const Vect & col)
{
	Matrix worldBS = Matrix(SCALE, S.getRadius() * Vect(1, 1, 1)) * Matrix(TRANS, S.getCenter());
	// look for an inactive command, or make one
	if (inactiveBSphereCmds.size())
	{
		// set context and add the top to the active stack
		inactiveBSphereCmds.top()->setContext(worldBS, col);
		executeBSphereCmds.push(inactiveBSphereCmds.top());
		inactiveBSphereCmds.pop();
	}
	else
	{
		RenderBSphereCommand* cmdBS = new RenderBSphereCommand(worldBS, col);
		executeBSphereCmds.push(cmdBS);
	}
	return errcode::success;
}

errcode Visualizer::privShowAABB(const CollisionVolumeAABB & S, const Vect & col)
{
	Matrix worldAABB = Matrix(SCALE, S.getMin() - S.getMax()) * Matrix(TRANS, 0.5 * (S.getMin() + S.getMax()));

	// look for an inactive command, or make one
	if (inactiveAABBCmds.size())
	{
		// set context and add the top to the active stack
		inactiveAABBCmds.top()->setContext(worldAABB, col);
		executeAABBCmds.push(inactiveAABBCmds.top());
		inactiveAABBCmds.pop();
	}
	else
	{
		RenderAABBCommand* cmdBS = new RenderAABBCommand(worldAABB, col);
		executeAABBCmds.push(cmdBS);
	}
	return errcode::success;
}


errcode Visualizer::privShowAABB(const Vect& _min, const Vect& _max, const Vect & col)
{
	Matrix worldAABB = Matrix(SCALE, _min - _max) * Matrix(TRANS, 0.5 * (_min + _max));

	// look for an inactive command, or make one
	if (inactiveAABBCmds.size())
	{
		// set context and add the top to the active stack
		inactiveAABBCmds.top()->setContext(worldAABB, col);
		executeAABBCmds.push(inactiveAABBCmds.top());
		inactiveAABBCmds.pop();
	}
	else
	{
		RenderAABBCommand* cmdBS = new RenderAABBCommand(worldAABB, col);
		executeAABBCmds.push(cmdBS);
	}
	return errcode::success;
}

errcode Visualizer::privShowOBB(const Matrix& world, const CollisionVolumeOBB & S, const Vect & col)
{
	Matrix worldOBB = Matrix(SCALE, S.getMin() - S.getMax()) * Matrix(TRANS, 0.5 * (S.getMin() + S.getMax())) * world;

	// look for an inactive command, or make one
	if (inactiveAABBCmds.size())
	{
		// set context and add the top to the active stack
		inactiveAABBCmds.top()->setContext(worldOBB, col);
		executeAABBCmds.push(inactiveAABBCmds.top());
		inactiveAABBCmds.pop();
	}
	else
	{
		RenderAABBCommand* cmdBS = new RenderAABBCommand(worldOBB, col);
		executeAABBCmds.push(cmdBS);
	}
	return errcode::success;
}

errcode Visualizer::privShowCollisionVolume(const Collidable & S, const Vect & col)
{
	S.GetCollisionVolume().DebugView(col);
	return errcode::success;
}
