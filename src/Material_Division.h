#pragma once
#include "Material_BinaryOperator.h"

namespace Ogre
{
	class Material_Division : public Material_BinaryOperator
	{
	public:

		Material_Division(const String& name);
		virtual ~Material_Division();

	protected:

		virtual String getOperator() const { return "/"; }
	};
}