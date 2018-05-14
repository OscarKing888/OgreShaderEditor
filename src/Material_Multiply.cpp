#include "stdafx.h"
#include "Material_Multiply.h"

namespace Ogen
{
	Material_Multiply::Material_Multiply(const String& name)
		: MaterialExpression(name, false)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4", ""));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float4", ""));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4", ""));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("Multiply");
	}
	//--------------------------------------------------------------------------------
	Material_Multiply::~Material_Multiply()
	{
	}
	//--------------------------------------------------------------------------------
	String Material_Multiply::compileCode() const
	{
		String str;

		return str;
	}
	//--------------------------------------------------------------------------------
	String Material_Multiply::getFunctionName() const
	{
		return formatString("Multiply");
	}
	//--------------------------------------------------------------------------------
	String Material_Multiply::compileExpressionCallStart() const
	{
		return getFunctionName() + "(";
	}
	//--------------------------------------------------------------------------------
	String Material_Multiply::compileExpressionCallArguments() const
	{
		// A
		IMaterialExpression* me = getInputParameter(0)->getParentExpression();
		String str = "(";
		str += me->compileExpressionCallStart();
		str += me->compileExpressionCallArguments();
		str += me->compileExpressionCallEnd();
		str += ")";
		str += " * ";

		// B
		me = getInputParameter(1)->getParentExpression();
		str += "(";
		str += me->compileExpressionCallStart();
		str += me->compileExpressionCallArguments();
		str += me->compileExpressionCallEnd();
		str += ")";

		return str;
	}
	//--------------------------------------------------------------------------------
	String Material_Multiply::compileExpressionCallEnd() const
	{
		return ")";
	}
	//--------------------------------------------------------------------------------
}