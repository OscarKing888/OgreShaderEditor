#include "stdafx.h"
#include "Material_Subtract.h"

namespace Ogre
{
	Material_Subtract::Material_Subtract(const String& name)
		: Material_BinaryOperator(name)
	{		
		setCaption("A - B");
	}
	//--------------------------------------------------------------------------------
	Material_Subtract::~Material_Subtract()
	{
	}
	//--------------------------------------------------------------------------------
}