#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_Floor : public Material_Function
	{
	public:

		Material_Floor(const String& name);
		virtual ~Material_Floor();

	protected:

		virtual String getFunctionName() const { return "floor"; }
	};
}