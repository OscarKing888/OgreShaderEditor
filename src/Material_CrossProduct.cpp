#include "stdafx.h"
#include "Material_CrossProduct.h"

namespace Ogre
{
	Material_CrossProduct::Material_CrossProduct(const String& name)
		: Material_Function(name)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4"));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float4"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("Cross Product");
	}
	//--------------------------------------------------------------------------------
	Material_CrossProduct::~Material_CrossProduct()
	{
	}
}