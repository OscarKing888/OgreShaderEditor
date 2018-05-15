#pragma once
#include "Material_Function.h"

namespace Ogre
{
	class Material_CrossProduct : public Material_Function
	{
	public:

		Material_CrossProduct(const String& name);
		virtual ~Material_CrossProduct();

	protected:

		virtual String getFunctionName() const { return "cross"; }
	};
}