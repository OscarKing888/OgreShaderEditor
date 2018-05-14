#pragma once
#include "MaterialExpression.h"

namespace Ogen
{
	class Material_Multiply : public MaterialExpression
	{
	public:

		Material_Multiply(const String& name);
		virtual ~Material_Multiply();

		virtual String compileCode() const;

		virtual String compileExpressionCallStart() const;
		virtual String compileExpressionCallArguments() const;
		virtual String compileExpressionCallEnd() const;

	protected:

		String getFunctionName() const;
	};
}