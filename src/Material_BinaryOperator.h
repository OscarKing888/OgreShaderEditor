#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_BinaryOperator : public MaterialExpression
	{
	public:

		Material_BinaryOperator(const String& name);
		virtual ~Material_BinaryOperator();

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;

	protected:

		virtual String getOperator() const = 0;
	};
}