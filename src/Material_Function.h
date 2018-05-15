#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_Function : public MaterialExpression
	{
	public:

		Material_Function(const String& name);
		virtual ~Material_Function();

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;

	protected:

		virtual String getFunctionName() const = 0;
	};
}