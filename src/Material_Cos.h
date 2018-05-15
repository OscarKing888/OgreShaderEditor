#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_Cos : public Material_Function
	{
	public:

		Material_Cos(const String& name);
		virtual ~Material_Cos();

	protected:

		virtual String getFunctionName() const { return "cos"; }
	};
}