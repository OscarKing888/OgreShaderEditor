#include "stdafx.h"
#include "Material_DotProduct.h"
#include "OgreMaterialManager.h"
#include "OgreTechnique.h"
#include "OgrePass.h"
#include "OgreTextureUnitState.h"

namespace Ogen
{
	Material_DotProduct::Material_DotProduct(const String& name)
		: MaterialExpression(name, false)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float3"));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float3"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float3"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("Dot Product");
	}
	//--------------------------------------------------------------------------------
	Material_DotProduct::~Material_DotProduct()
	{
	}

}