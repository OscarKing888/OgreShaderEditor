#include "stdafx.h"
#include "Material_If.h"

namespace Ogre
{
	Material_If::Material_If(const String& name)
		: MaterialExpression(name, false)
		, _ifInstanceCount(0)
	{
		addInputSocket(new InputOutputSocket(name + "/A", true, this, "A", "float4"));
		addInputSocket(new InputOutputSocket(name + "/B", true, this, "B", "float4"));

		addInputSocket(new InputOutputSocket(name + "/>", true, this, ">", "float4"));
		addInputSocket(new InputOutputSocket(name + "/=", true, this, "=", "float4"));
		addInputSocket(new InputOutputSocket(name + "/<", true, this, "<", "float4"));

		addOutputSocket(new InputOutputSocket(name + "/Output", false, this, "", "float4"));

		setDimisions(140, 130);
		setViewFillColour(ColourValue::Black);
		setCaption("If");
	}
	//--------------------------------------------------------------------------------
	Material_If::~Material_If()
	{
	}
	//--------------------------------------------------------------------------------
	void Material_If::compileExpression(String& outCode, IExpressionParameter* outputParameter)
	{
		String funName = getFunctionName();
		if(isFunctionCompiled(funName))
		{
			return;
		}

		addCompiledFunction(funName);

		String a = getInputParameter(0)->getConnectionLine(0)->getOutputParameter()->getParameterType();
		String b = getInputParameter(1)->getConnectionLine(0)->getOutputParameter()->getParameterType();
		String g = getInputParameter(2)->getConnectionLine(0)->getOutputParameter()->getParameterType();
		String e = getInputParameter(3)->getConnectionLine(0)->getOutputParameter()->getParameterType();
		String l = getInputParameter(4)->getConnectionLine(0)->getOutputParameter()->getParameterType();

		outCode += formatString("%s %s(%s a, %s b, %s grt, %s equ, %s les)\n{\n",
			outputParameter->getParameterType().c_str(),
			getFunctionName().c_str(),
			a.c_str(), // A
			b.c_str(), // B
			g.c_str(), // >
			e.c_str(), // =
			l.c_str()); // <
#if 0
		if(a > b)
		{
			return grt;
		}

		if(a == b)
		{
			return equ;
		}

		if(a < b)
		{
			return les;
		}
#endif

		outCode += "\tif(a > b) { return grt; }\n";
		outCode += "\tif(a == b) { return equ; }\n";
		outCode += "\treturn les;\n";
		outCode += "}\n";

		/*outCode += formatString("{\n\t return tex2D(%s, input.%s)%s; \n}\n",			
			outputParameter->getComponents().c_str());*/

		
	}	
	//--------------------------------------------------------------------------------
	String Material_If::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return getFunctionName() + "(";
	}
	//--------------------------------------------------------------------------------
	String Material_If::compileExpressionCallArguments(IExpressionParameter* output) const
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
	String Material_If::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return ")";
	}
	//--------------------------------------------------------------------------------
	void Material_If::resetForCompile()
	{
		MaterialExpression::resetForCompile();
	}
	//--------------------------------------------------------------------------------
	String Material_If::getFunctionName() const
	{
		return formatString("if_%d", _ifInstanceCount);
	}
}