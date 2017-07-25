#ifndef RECT_H
#define RECT_H

struct Rect
{
public:
	// Constructors
	Rect( float x, float y, float width, float height);
	Rect();

	// Clear method
	void clear();

	// Structure data, public
	float x;
	float y;
	float width;
	float height;
};


#endif