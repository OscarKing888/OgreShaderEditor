#include "stdafx.h"
#include "Material_Vector4Constant.h"
#include "OgreGpuProgram.h"

namespace Ogre
{
	Material_Vector4Constant::Material_Vector4Constant(const String& name)
		: MaterialExpression(name, true)
		, _clr(0, 0.5, 1, 1)
	{

		addOutputSocket(new InputOutputSocket(name + "/Out", false, this, "", "float4"));
	
		addOutputSocket(new InputOutputSocket(name + "/R", false, this, "R", "float", ".r"));
		addOutputSocket(new InputOutputSocket(name + "/G", false, this, "G", "float", ".g"));
		addOutputSocket(new InputOutputSocket(name + "/B", false, this, "B", "float", ".b"));
		addOutputSocket(new InputOutputSocket(name + "/A", false, this, "A", "float", ".a"));

		getOutputSocket(1)->setColour(ColourValue::Red);
		getOutputSocket(2)->setColour(ColourValue::Green);
		getOutputSocket(3)->setColour(ColourValue::Blue);
		getOutputSocket(4)->setColour(ColourValue::White);

		setDimisions(140, 130);
		setCaption("Vector4 Constant");
		this->setViewFillColour(_clr);
	}
	//--------------------------------------------------------------------------------
	Material_Vector4Constant::~Material_Vector4Constant()
	{
	}
	//--------------------------------------------------------------------------------
	String Material_Vector4Constant::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		return formatString("float4(%f, %f, %f, %f)%s", _clr.r, _clr.g, _clr.b, _clr.a, output->getComponents().c_str());
	}
	//--------------------------------------------------------------------------------
	void Material_Vector4Constant::setColour(const ColourValue& clr)
	{
		_clr = clr;
		setViewFillColour(_clr);
	}
}