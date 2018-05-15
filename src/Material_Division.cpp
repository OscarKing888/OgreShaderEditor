#include "stdafx.h"
#include "Material_Division.h"

namespace Ogre
{
	Material_Division::Material_Division(const String& name)
		: Material_BinaryOperator(name)
	{		
		setCaption("A / B");
	}
	//--------------------------------------------------------------------------------
	Material_Division::~Material_Division()
	{
	}
	//--------------------------------------------------------------------------------
}