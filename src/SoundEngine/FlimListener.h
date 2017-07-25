#pragma once
#ifndef FLIMLISTENER_H
#define FLIMLISTENER_H

#include "AzulCore.h"
#include "snd_err.h"

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \class	FlimListener
///
/// \brief	A flim listener.
/// \ingroup FLIMLISTENER
/// \author	Jack Campbell
/// \date	6/1/2017
////////////////////////////////////////////////////////////////////////////////////////////////////

class FlimListener : public Align16
{
public:

	// get pos

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static const Vect& FlimListener::GetPosition()
	///
	/// \brief	Gets the position.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup FLIMLISTENER
	/// \return	The position.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static const Vect& GetPosition()
	{
		return Instance().privGetPosition();
	}
	
	// set pos

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err FlimListener::SetPosition(float x, float y, float z)
	///
	/// \brief	Sets a position.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup FLIMLISTENER
	/// \param	x	The x coordinate.
	/// \param	y	The y coordinate.
	/// \param	z	The z coordinate.
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err SetPosition(float x, float y, float z)
	{
		return Instance().privSetPosiion(x, y, z);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err FlimListener::SetPosition(const Vect& vect)
	///
	/// \brief	Sets a position.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup FLIMLISTENER
	/// \param	vect	The vect.
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err SetPosition(const Vect& vect)
	{
		return Instance().privSetPosiion(vect.X(), vect.Y(), vect.Z());
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err FlimListener::UpdateOrientation(float xF, float yF, float zF, float xU, float yU, float zU)
	///
	/// \brief	Updates the orientation.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup FLIMLISTENER
	/// \param	xF	The x coordinate f.
	/// \param	yF	The y coordinate f.
	/// \param	zF	The z coordinate f.
	/// \param	xU	The x coordinate u.
	/// \param	yU	The y coordinate u.
	/// \param	zU	The z coordinate u.
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err UpdateOrientation(float xF, float yF, float zF, float xU, float yU, float zU)
	{
		return Instance().privUpdateOrientation(xF, yF, zF, xU, yU, zU);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err FlimListener::SetOrientation(const Vect& vectF, float x = 0.0f, float y = 1.0f, float z = 0.0f)
	///
	/// \brief	Sets an orientation.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup FLIMLISTENER
	/// \param	vectF	The vect f.
	/// \param	x	 	(Optional) The x coordinate.
	/// \param	y	 	(Optional) The y coordinate.
	/// \param	z	 	(Optional) The z coordinate.
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err SetOrientation(const Vect& vectF, float x = 0.0f, float y = 1.0f, float z = 0.0f)
	{
		return Instance().privUpdateOrientation(vectF.X(), vectF.Y(), vectF.Z(), x,y,z);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// \fn	static snd_err FlimListener::SetOrientation(const Vect& vectF, const Vect& vectU)
	///
	/// \brief	Sets an orientation.
	///
	/// \author	Jack Campbell
	/// \date	6/1/2017
	///\ingroup FLIMLISTENER
	/// \param	vectF	The vect f.
	/// \param	vectU	The vect u.
	///
	/// \return	A snd_err.
	////////////////////////////////////////////////////////////////////////////////////////////////////

	static snd_err SetOrientation(const Vect& vectF, const Vect& vectU)
	{
		return Instance().privUpdateOrientation(vectF.X(), vectF.Y(), vectF.Z(), vectU.X(), vectU.Y(), vectU.Z());
	}

private:
	// singleton
	FlimListener();

	static FlimListener* instance;
	static FlimListener& Instance()
	{
		if (!instance)
		{
			instance = new FlimListener();
		}
		return *instance;
	}

	const Vect& privGetPosition();
	snd_err privSetPosiion(float x, float y, float z);
	snd_err privUpdateOrientation(float xF, float yF, float zF, float xU, float yU, float zU);

	Vect position;

};

#endif