#pragma once
#include "MaterialExpression.h"

namespace Ogen
{
	class Material_AutoConstant : public MaterialExpression
	{
	public:

		Material_AutoConstant(const String& name);
		virtual ~Material_AutoConstant();

		void setAutoConstantName(const String& name);
		const String& getAutoConstantName() const { return _constantName; }

	protected:

		String _constantName;
	};
}