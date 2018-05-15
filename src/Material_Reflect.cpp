#include "stdafx.h"
#include "Material_Reflect.h"

namespace Ogre
{
	Material_Reflect::Material_Reflect(const String& name)
		: Material_Function(name)
	{
		addInputSocket(new InputOutputSocket(name + "/I", true, this, "I", "float4"));
		addInputSocket(new InputOutputSocket(name + "/N", true, this, "N", "float4"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("Reflect");
	}
	//--------------------------------------------------------------------------------
	Material_Reflect::~Material_Reflect()
	{
	}
}