#include "stdafx.h"
#include "Material_Sign.h"

namespace Ogre
{
	Material_Sign::Material_Sign(const String& name)
		: Material_Function(name)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("Sign");
	}
	//--------------------------------------------------------------------------------
	Material_Sign::~Material_Sign()
	{
	}
}