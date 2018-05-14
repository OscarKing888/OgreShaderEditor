#pragma once
#include "BlockWithView.h"

namespace Ogen
{
	class Material_Technique;

	class Material_Pass : public BlockWithView
	{
	public:

		Material_Pass(Material_Technique* parent, const String& name);
		virtual ~Material_Pass();

		void compile(MaterialPtr mat, Technique* tech, size_t passIdx);

	protected:

		Material_Technique* _parent;

		void compilePSDeclaration(IExpressionParameter* root, String& outCode);
		void compilePSInputStruct(IExpressionParameter* root, StrMap& structMap);
		void compilePSCode(IExpressionParameter* root, String& outCode);
		void compilePSCall(IExpressionParameter* root, String& outCode);
	};
}