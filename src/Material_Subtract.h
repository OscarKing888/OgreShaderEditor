#pragma once
#include "Material_BinaryOperator.h"

namespace Ogre
{
	class Material_Subtract : public Material_BinaryOperator
	{
	public:

		Material_Subtract(const String& name);
		virtual ~Material_Subtract();

	protected:

		virtual String getOperator() const { return "-"; }
	};
}