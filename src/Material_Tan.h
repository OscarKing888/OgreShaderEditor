#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_Tan : public Material_Function
	{
	public:

		Material_Tan(const String& name);
		virtual ~Material_Tan();

	protected:

		virtual String getFunctionName() const { return "cross"; }
	};
}