#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_ComposeVector4 : public MaterialExpression
	{
	public:

		Material_ComposeVector4(const String& name);
		virtual ~Material_ComposeVector4();

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;

	protected:

	};
}