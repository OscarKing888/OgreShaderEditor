#pragma once
#include "Material_BinaryOperator.h"

namespace Ogre
{
	class Material_Add : public Material_BinaryOperator
	{
	public:

		Material_Add(const String& name);
		virtual ~Material_Add();

	protected:

		virtual String getOperator() const { return "+"; }
	};
}