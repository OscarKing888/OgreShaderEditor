#include "stdafx.h"
#include "Material_ComposeVector4.h"

namespace Ogre
{
	Material_ComposeVector4::Material_ComposeVector4(const String& name)
		: MaterialExpression(name, false)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float", ""));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float", ""));
		addInputSocket(new InputOutputSocket(name + "/C", true, this, "C", "float", ""));
		addInputSocket(new InputOutputSocket(name + "/D", true, this, "D", "float", ""));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4", ""));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);

		setCaption("ComposeVector4");
	}
	//--------------------------------------------------------------------------------
	Material_ComposeVector4::~Material_ComposeVector4()
	{
	}
	//--------------------------------------------------------------------------------
	String Material_ComposeVector4::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return "(";
	}
	//--------------------------------------------------------------------------------
	String Material_ComposeVector4::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		// A
		String str = "float4(";
		for (size_t i = 0; i < 4; ++i)
		{
			IExpressionParameter* inPar = getInputParameter(i);

			if(inPar->getConnectionLineCount() > 0)
			{
				IExpressionParameter* outPar = inPar->getConnectionLine(0)->getOutputParameter();

				IMaterialExpression* me = outPar->getParentExpression();

				str += "(";
				str += me->compileExpressionCallStart(outPar);
				str += me->compileExpressionCallArguments(outPar);
				str += me->compileExpressionCallEnd(outPar);
				str += ")";
			}
			else
			{
				str += "0";
			}

			if(i < 3)
			{
				str += ", ";
			}
		}

		str += ")";

		return str;
	}
	//--------------------------------------------------------------------------------
	String Material_ComposeVector4::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return ")";
	}
	//--------------------------------------------------------------------------------
}