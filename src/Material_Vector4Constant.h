#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_Vector4Constant : public MaterialExpression
	{
	public:

		Material_Vector4Constant(const String& name);
		virtual ~Material_Vector4Constant();

		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;

		void setColour(const ColourValue& clr);
		const ColourValue& getColour() const { return _clr; }

	protected:

		ColourValue _clr;
	};
}