#pragma once
#include "MaterialExpression.h"

namespace Ogen
{
	class Material_TextureSampler : public MaterialExpression
	{
	public:

		Material_TextureSampler(const String& name);
		virtual ~Material_TextureSampler();

		virtual void compileExpression(String& outCode, IExpressionParameter* outputParameter);
		virtual void compileInputStruct(StrMap& outMap);

		virtual String compileExpressionCallStart() const;
		virtual String compileExpressionCallArguments() const;
		virtual String compileExpressionCallEnd() const;

	protected:

		ushort _texturerStageIndex;
		ushort _texCoordIndex;

		virtual void compileExpressionDeclarationImp(String& outCode);
		String getVarName() const;
		String getUVName() const;
		String getFunctionName() const;
	};
}