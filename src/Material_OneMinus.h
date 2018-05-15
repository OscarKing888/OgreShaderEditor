#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_OneMinus : public MaterialExpression
	{
	public:

		Material_OneMinus(const String& name);
		virtual ~Material_OneMinus();

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;
	};
}