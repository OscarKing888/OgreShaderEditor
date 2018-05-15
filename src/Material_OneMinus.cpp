#include "stdafx.h"
#include "Material_OneMinus.h"

namespace Ogre
{
	Material_OneMinus::Material_OneMinus(const String& name)
		: MaterialExpression(name, false)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4", ""));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4", ""));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("1 - A");
	}
	//--------------------------------------------------------------------------------
	Material_OneMinus::~Material_OneMinus()
	{
	}
	//--------------------------------------------------------------------------------
	String Material_OneMinus::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return "(";
	}
	//--------------------------------------------------------------------------------
	String Material_OneMinus::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		// A
		IExpressionParameter* outPar = getInputParameter(0)
			->getConnectionLine(0)->getOutputParameter();

		IMaterialExpression* me = outPar->getParentExpression();

		String str = "1 - ";

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
	String Material_OneMinus::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return ")";
	}
	//--------------------------------------------------------------------------------
}