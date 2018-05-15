#include "stdafx.h"
#include "MaterialGlyph.h"

namespace Ogre
{
	MaterialGlyph::MaterialGlyph(const String& name)
		: _name(name)
		, _parentContainer(0)
	{

	}
	//--------------------------------------------------------------------------------
	MaterialGlyph::~MaterialGlyph()
	{
	}
	//--------------------------------------------------------------------------------
	void MaterialGlyph::setName(const String& name)
	{
		_name = name;
	}
	//--------------------------------------------------------------------------------
	bool MaterialGlyph::intersects(Real x, Real y) const
	{
		RealRect rc = getBoundingRect();
		if((x >= rc.left) && (x <= rc.right)
			&& (y >= rc.top) && (y <= rc.bottom))
		{
			return true;
		}
		return false;
	}
	//--------------------------------------------------------------------------------	
	Vector2 MaterialGlyph::getDimisions() const
	{
		return Vector2(getWidth(), getHeight());
	}
	//--------------------------------------------------------------------------------
	RealRect MaterialGlyph::getBoundingRect() const
	{
		Vector2 pos = getPosition();
		Vector2 dim = getDimisions();
		RealRect r;
		r.left = pos.x;
		r.top = pos.y;
		r.right = pos.x + dim.x;
		r.bottom = pos.y + dim.y;
		return r;
	}
	//--------------------------------------------------------------------------------
	void MaterialGlyph::setPosition(const Vector2& pos)
	{
		setPosition(pos.x, pos.y);
	}
	//--------------------------------------------------------------------------------
	void MaterialGlyph::addToContainer(OverlayContainer* c)
	{
		_parentContainer = c;
	}
	//--------------------------------------------------------------------------------
	void MaterialGlyph::layout()
	{

	}

}