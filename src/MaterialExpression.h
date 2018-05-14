#pragma once
#include "BlockWithView.h"
#include "IMaterialExpression.h"

namespace Ogen
{	
	class MaterialExpression : public BlockWithView, public IMaterialExpression
	{
	public:

		MaterialExpression(const String& name, bool needDeclaration);
		virtual ~MaterialExpression();

		virtual size_t getInputParametersCount() const;
		virtual size_t getOutputParametersCount() const;

		virtual IExpressionParameter* getInputParameter(size_t idx) const;
		virtual IExpressionParameter* getOutputParameter(size_t idx) const;

		virtual void startCompileExpressionDeclaration();
		virtual void compileExpressionDeclaration(String& outCode);
		virtual void endCompileExpressionDeclaration();

		virtual void compileInputStruct(StrMap& outMap);

		virtual void compileExpression(String& outCode, IExpressionParameter* outputParameter);

		virtual String compileExpressionCallStart() const;
		virtual String compileExpressionCallArguments() const;
		virtual String compileExpressionCallEnd() const;

	protected:

		bool _needDeclaration;
		bool _compileDeclarationOnce;

		virtual void compileExpressionDeclarationImp(String& outCode);
	};
}