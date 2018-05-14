#include "stdafx.h"
#include "Material_AutoConstant.h"
#include "OgreGpuProgram.h"

namespace Ogen
{
	Material_AutoConstant::Material_AutoConstant(const String& name)
		: MaterialExpression(name, true)
	{

		addOutputSocket(new InputOutputSocket(name + "/Out", false, this, "C", "float"));
	
		setDimisions(140, 130);
		setCaption("Auto Constant");
	}
	//--------------------------------------------------------------------------------
	Material_AutoConstant::~Material_AutoConstant()
	{
	}
	//--------------------------------------------------------------------------------
	void Material_AutoConstant::setAutoConstantName(const String& name)
	{
		_constantName = name;

		const GpuProgramParameters::AutoConstantDefinition* ad = GpuProgramParameters::getAutoConstantDefinition(name);
		String tp = "float";

		if((ad->elementCount > 1) && (ad->elementCount <= 4))
		{
			tp = tp + StringConverter::toString(ad->elementCount);
		}
		else
		{
			tp = tp + "4x" + StringConverter::toString(ad->elementCount / 4);
		}
		
		getOutputSocket(0)->setParameterType(tp);
	}
	
}