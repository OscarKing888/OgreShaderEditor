#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_Exp : public Material_Function
	{
	public:

		Material_Exp(const String& name);
		virtual ~Material_Exp();

	protected:

		virtual String getFunctionName() const { return "exp"; }
	};
}