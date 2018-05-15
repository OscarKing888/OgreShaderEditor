#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_If : public MaterialExpression
	{
	public:

		Material_If(const String& name);
		virtual ~Material_If();

		virtual void compileExpression(String& outCode, IExpressionParameter* outputParameter);

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;

		virtual void resetForCompile();

	protected:

		ushort _ifInstanceCount;
		String getFunctionName() const;
	};
}