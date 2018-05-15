#include "stdafx.h"
#include "Material_Add.h"

namespace Ogre
{
	Material_Add::Material_Add(const String& name)
		: Material_BinaryOperator(name)
	{		
		setCaption("A + B");
	}
	//--------------------------------------------------------------------------------
	Material_Add::~Material_Add()
	{
	}
	//--------------------------------------------------------------------------------
}