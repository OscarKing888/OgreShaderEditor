#include "stdafx.h"
#include "Material_Negative.h"

namespace Ogre
{
	Material_Negative::Material_Negative(const String& name)
		: MaterialExpression(name, false)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4", ""));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4", ""));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption(" -A");
	}
	//--------------------------------------------------------------------------------
	Material_Negative::~Material_Negative()
	{
	}
	//--------------------------------------------------------------------------------
	String Material_Negative::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return "(";
	}
	//--------------------------------------------------------------------------------
	String Material_Negative::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		// A
		IExpressionParameter* outPar = getInputParameter(0)
			->getConnectionLine(0)->getOutputParameter();

		IMaterialExpression* me = outPar->getParentExpression();

		String str = "- ";

		// B
		outPar = getInputParameter(0)->getConnectionLine(0)->getOutputParameter();
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
	String Material_Negative::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return ")";
	}
	//--------------------------------------------------------------------------------
}