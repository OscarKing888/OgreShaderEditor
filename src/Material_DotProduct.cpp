#include "stdafx.h"
#include "Material_DotProduct.h"

namespace Ogre
{
	Material_DotProduct::Material_DotProduct(const String& name)
		: Material_Function(name)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4"));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float4"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("Dot Product");
	}
	//--------------------------------------------------------------------------------
	Material_DotProduct::~Material_DotProduct()
	{
	}
}