#include "stdafx.h"
#include "Material_Function.h"

namespace Ogre
{
	Material_Function::Material_Function(const String& name)
		: MaterialExpression(name, false)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4", ""));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float4", ""));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4", ""));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
	}
	//--------------------------------------------------------------------------------
	Material_Function::~Material_Function()
	{
	}
	//--------------------------------------------------------------------------------
	String Material_Function::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return getFunctionName() + "(";
	}
	//--------------------------------------------------------------------------------
	String Material_Function::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		String str;

		for (size_t i = 0; i < getInputParametersCount(); ++i)
		{
			// A
			IExpressionParameter* outPar = getInputParameter(i)
				->getConnectionLine(0)->getOutputParameter();

			IMaterialExpression* me = outPar->getParentExpression();

			str += "(";
			str += me->compileExpressionCallStart(outPar);
			str += me->compileExpressionCallArguments(outPar);
			str += me->compileExpressionCallEnd(outPar);
			str += ")";

			if(i < (getInputParametersCount() - 1))
			{
				str += ", ";
			}
		}

		return str;
	}
	//--------------------------------------------------------------------------------
	String Material_Function::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return ")";
	}
}