#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_Reflect : public Material_Function
	{
	public:

		Material_Reflect(const String& name);
		virtual ~Material_Reflect();

	protected:

		virtual String getFunctionName() const { return "cross"; }
	};
}