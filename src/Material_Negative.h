#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_Negative : public MaterialExpression
	{
	public:

		Material_Negative(const String& name);
		virtual ~Material_Negative();

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;
	};
}