#pragma once
#ifndef SOUNDCALLREG_H
#define SOUNDCALLREG_H

////////////////////////////////////////////////////////////////////////////////////////////////////
/// \enum	SoundCallID
///
/// \brief	Values that represent sound call Identifiers.
////////////////////////////////////////////////////////////////////////////////////////////////////

typedef enum SoundCallID
{
	Hit1,
	Hit2,
	Hit3,
	Shoot1,
	Shoot2,
	Shoot3,
	Ambience,
	Music,
	TankMove,
	Level1Music,
	Level2Music,
	Level3Music,
	GarageMusic
} SoundCallID;

#endif