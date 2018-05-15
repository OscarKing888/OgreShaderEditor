#pragma once
#include "BlockWithView.h"
#include "IMaterialExpression.h"

namespace Ogre
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

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;

		virtual void resetForCompile();

		virtual void postCompile();

	protected:

		bool _needDeclaration;
		bool _compileDeclarationOnce;

		virtual void compileExpressionDeclarationImp(String& outCode);

		typedef std::map<String, bool> CompiledFunctionMap;
		CompiledFunctionMap _compiledFunctionMap;

		void addCompiledFunction(const String& funName);
		bool isFunctionCompiled(const String& funName) const;
	};
}