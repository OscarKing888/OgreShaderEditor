#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_Sin : public Material_Function
	{
	public:

		Material_Sin(const String& name);
		virtual ~Material_Sin();

	protected:

		virtual String getFunctionName() const { return "sin"; }
	};
}