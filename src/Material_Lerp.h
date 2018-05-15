#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_Lerp : public Material_Function
	{
	public:

		Material_Lerp(const String& name);
		virtual ~Material_Lerp();

	protected:

		virtual String getFunctionName() const { return "lerp"; }
	};
}