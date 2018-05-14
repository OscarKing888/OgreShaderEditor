#include "stdafx.h"
#include "Material_If.h"

namespace Ogen
{
	Material_If::Material_If(const String& name)
		: MaterialExpression(name, false)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float3"));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float3"));

		addInputSocket(new InputOutputSocket(name + "/>", true, this, ">", "float3"));
		addInputSocket(new InputOutputSocket(name + "/=", true, this, "=", "float3"));
		addInputSocket(new InputOutputSocket(name + "/<", true, this, "<", "float3"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float3"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("If");
	}
	//--------------------------------------------------------------------------------
	Material_If::~Material_If()
	{
	}

}