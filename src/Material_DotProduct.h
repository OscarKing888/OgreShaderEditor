#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_DotProduct : public Material_Function
	{
	public:

		Material_DotProduct(const String& name);
		virtual ~Material_DotProduct();

	protected:

		virtual String getFunctionName() const { return "dot"; }
	};
}