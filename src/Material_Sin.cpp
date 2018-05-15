#include "stdafx.h"
#include "Material_Sin.h"

namespace Ogre
{
	Material_Sin::Material_Sin(const String& name)
		: Material_Function(name)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("Sin");
	}
	//--------------------------------------------------------------------------------
	Material_Sin::~Material_Sin()
	{
	}
}