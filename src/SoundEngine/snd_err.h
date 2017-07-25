#pragma once
#ifndef SNDERR_H
#define SNDERR_H



typedef enum snd_err
{
	OK, // success
	ERR, // failure
	INSUFFICIENT_SPACE, // insufficient_space
	NULLPTR,//null_ptr,
	NOT_FOUND,//not_found,
	NOT_IN_USE,//not_in_use,
	MULTIPLE_ADD,//multiple_add,
	IN_USE,//in_use,
	BAD_HANDLE,//bad_handle,
	NO_TRACK//no_track
} snd_error;

#endif