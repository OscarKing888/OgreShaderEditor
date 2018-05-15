#include "stdafx.h"
#include "Material_Multiply.h"

namespace Ogre
{
	Material_Multiply::Material_Multiply(const String& name)
		: Material_BinaryOperator(name)
	{		
		setCaption("A * B");
	}
	//--------------------------------------------------------------------------------
	Material_Multiply::~Material_Multiply()
	{
	}
}