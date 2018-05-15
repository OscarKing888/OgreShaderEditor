#include "stdafx.h"
#include "Material_Lerp.h"

namespace Ogre
{
	Material_Lerp::Material_Lerp(const String& name)
		: Material_Function(name)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4"));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float4"));
		addInputSocket(new InputOutputSocket(name + "/S", true, this, "S", "float"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("Lerp");
	}
	//--------------------------------------------------------------------------------
	Material_Lerp::~Material_Lerp()
	{
	}
}