#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_Sign : public Material_Function
	{
	public:

		Material_Sign(const String& name);
		virtual ~Material_Sign();

	protected:

		virtual String getFunctionName() const { return "sign"; }
	};
}