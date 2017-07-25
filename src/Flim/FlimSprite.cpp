#include "FlimSprite.h"
#include "ImageManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "SceneManager.h"

FlimSprite::FlimSprite() : _sprite(nullptr)
{
}

FlimSprite::~FlimSprite()
{
	if (_sprite)
	{
		delete _sprite;
	} 
}

FlimSprite::FlimSprite(const char * imageName) : angle(0.0f), scale(1.0f, 1.0f,1.0f), pos(0.0f,0.0f,0.0f)
{

	Image& img = ImageManager::Get(imageName);
	this->_sprite = new GraphicsObject_Sprite(ImageManager::getSpriteModel(), ImageManager::getSpriteShader(), &img, new Rect(150.0f, 500.0f, 100.0f, 100.0f));
}

errcode FlimSprite::SetAngle(float ang)
{
	errcode err = errcode::success;
	if (!_sprite)
	{
		err = errcode::failure;
		return err;
	}
	this->angle = ang;
	Matrix ROTZ = Matrix(ROT_Z, ang) * _sprite->getWorld();
	_sprite->SetWorld(ROTZ);

	return err;
}

float FlimSprite::GetAngle()
{
	return angle;
}

errcode FlimSprite::SetScale(float x, float y)
{
	errcode err = errcode::success;
	if (!_sprite)
	{
		err = errcode::failure;
		return err;
	}

	this->scale.set(x, y, 1.0f);

	Matrix Scale = Matrix(SCALE, x, y, 1.0f) * _sprite->getWorld();
	_sprite->SetWorld(Scale);

	return err;
}


errcode FlimSprite::SetScale(float factor)
{
	errcode err = errcode::success;
	if (!_sprite)
	{
		err = errcode::failure;
		return err;
	}

	this->scale.set(this->scale.X() * factor, this->scale.Y() * factor, 1.0f);

	Matrix Scale = Matrix(SCALE, factor, factor, 1.0f) * _sprite->getWorld();
	_sprite->SetWorld(Scale);

	return err;
}

errcode FlimSprite::SetScale(float factor, SpriteParam sp)
{
	errcode err = errcode::success;
	if (!_sprite)
	{
		err = errcode::failure;
		return err;
	}
	if (sp == SpriteParam::sprite_x)
	{
		this->scale.set(this->scale.X() * factor, this->scale.Y(), 1.0f);
		Matrix Scale = Matrix(SCALE, factor, 1.0f, 1.0f) * _sprite->getWorld();
		_sprite->SetWorld(Scale);
	}
	else
	{
		this->scale.set(this->scale.X(), this->scale.Y() * factor, 1.0f);
		Matrix Scale = Matrix(SCALE, 1.0f, factor, 1.0f) * _sprite->getWorld();
		_sprite->SetWorld(Scale);
	}



	return err;
}

Vect & FlimSprite::GetScale()
{
	return scale;
}

errcode FlimSprite::SetPos(float x, float y)
{
	errcode err = errcode::success;
	if (!_sprite)
	{
		err = errcode::failure;
		return err;
	}
	this->pos.set(x, y, 1.0f);
	Matrix Pos = Matrix(TRANS, x, y, 1.0f); //*  _sprite->getWorld();
	_sprite->SetWorld(Pos);

	return err;
}

Vect & FlimSprite::GetPos()
{
	return pos;
}

errcode FlimSprite::SetCenter(float x, float y)
{
	errcode err = errcode::success;
	if (!_sprite)
	{
		err = errcode::failure;
		return err;
	}

	this->_sprite->pImage->pImageRect->x = x;
	this->_sprite->pImage->pImageRect->y = y;

	return err;
}

Vect & FlimSprite::GetCenter()
{
	return center;
}

errcode FlimSprite::Render()
{
	errcode err = errcode::success;
	if (!_sprite)
	{
		err = errcode::failure;
		return err;
	}

	_sprite->Render(&SceneManager::Get2DCamera());

	return err;  
}

Vect FlimSprite::GetSize() const
{
	return Vect(_sprite->origWidth * this->scale.X(), _sprite->origHeight * this->scale.Y(), 0);
}
