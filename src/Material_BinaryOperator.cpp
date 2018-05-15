#include "stdafx.h"
#include "Material_BinaryOperator.h"

namespace Ogre
{
	Material_BinaryOperator::Material_BinaryOperator(const String& name)
		: MaterialExpression(name, false)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4", ""));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float4", ""));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4", ""));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
	}
	//--------------------------------------------------------------------------------
	Material_BinaryOperator::~Material_BinaryOperator()
	{
	}
	//--------------------------------------------------------------------------------
	String Material_BinaryOperator::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return "(";
	}
	//--------------------------------------------------------------------------------
	String Material_BinaryOperator::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		// A
		IExpressionParameter* outPar = getInputParameter(0)
			->getConnectionLine(0)->getOutputParameter();

		IMaterialExpression* me = outPar->getParentExpression();

		String str = "(";
		str += me->compileExpressionCallStart(outPar);
		str += me->compileExpressionCallArguments(outPar);
		str += me->compileExpressionCallEnd(outPar);
		str += ")";
		//str += outPar->getComponents();
		str += " " + getOperator() + " ";

		// B
		outPar = getInputParameter(1)->getConnectionLine(0)->getOutputParameter();
		me = outPar->getParentExpression();

		str += "(";
		str += me->compileExpressionCallStart(outPar);
		str += me->compileExpressionCallArguments(outPar);
		str += me->compileExpressionCallEnd(outPar);
		str += ")";
		//str += outPar->getComponents();

		return str;
	}
	//--------------------------------------------------------------------------------
	String Material_BinaryOperator::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return ")";
	}
	//--------------------------------------------------------------------------------
}