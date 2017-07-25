#include "CameraManager.h"
#include "Flim.h"


CameraManager::CameraManager()
{
	this->InitCamera();
}

errcode CameraManager::InitCamera()
{
	this->currentCam = new Camera(Camera::Type::PERSPECTIVE_3D);
	this->p2DCam = new Camera(Camera::Type::ORTHOGRAPHIC_2D);


	p2DCam->setViewport(0, 0, Flim::GetWidth(), Flim::GetHeight());
	p2DCam->setOrthographic(-0.5f*Flim::GetWidth(), 0.5f*Flim::GetWidth(), -0.5f*Flim::GetHeight(), 0.5f*Flim::GetHeight(), 1.0f, 1000.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	p2DCam->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);
	p2DCam->updateCamera();


	return errcode::success;
}

errcode CameraManager::InitCamera(Camera * out)
{
	out = this->currentCam;
	return errcode::success;
}

Camera & CameraManager::MainCamera()
{
	return *this->currentCam;
}


errcode CameraManager::MainCamera(Camera * out)
{
	out = this->currentCam;
	return errcode::success;
}

Camera & CameraManager::Get2DCamera()
{
	return *this->p2DCam;
}

errcode CameraManager::Get2DCamera(Camera * out)
{
	out = this->p2DCam;
	return errcode::success;
}

errcode CameraManager::ShutDown()
{
	if (this->currentCam)
	{
		delete this->currentCam;
	}
	if (this->p2DCam)
	{
		delete this->p2DCam;
	}

	return errcode::success;
}
