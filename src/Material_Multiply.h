#pragma once
#include "Material_BinaryOperator.h"

namespace Ogre
{
	class Material_Multiply : public Material_BinaryOperator
	{
	public:

		Material_Multiply(const String& name);
		virtual ~Material_Multiply();

	protected:

		virtual String getOperator() const { return "*"; }
	};
}