#pragma once

namespace Ogre
{
	class IMaterialExpression;
	class IExpressionParameter;

	class IExpressionParameterConnectionLine
	{
	public:

		virtual IExpressionParameter* getInputParameter() const = 0;
		virtual IExpressionParameter* getOutputParameter() const = 0;
	};
	
	//--------------------------------------------------------------------------------

	class IExpressionParameter
	{
	public:
		
		virtual size_t getConnectionLineCount() const = 0;
		virtual IExpressionParameterConnectionLine* getConnectionLine(size_t idx) const = 0;

		virtual IMaterialExpression* getParentExpression() const = 0;
		virtual const String& getParameterType() const = 0;		
		virtual const String& getComponents() const = 0;
	};

	//--------------------------------------------------------------------------------

	// semantic : paraname
	typedef std::map<String, String> StrMap;

	class IMaterialExpression
	{
	public:

		virtual void resetForCompile() = 0;

		virtual size_t getInputParametersCount() const = 0;
		virtual size_t getOutputParametersCount() const = 0;

		virtual IExpressionParameter* getInputParameter(size_t idx) const = 0;
		virtual IExpressionParameter* getOutputParameter(size_t idx) const = 0;

		virtual void startCompileExpressionDeclaration() = 0;
		virtual void compileExpressionDeclaration(String& outCode) = 0;
		virtual void endCompileExpressionDeclaration() = 0;

		virtual void compileInputStruct(StrMap& outMap) = 0;

		virtual void compileExpression(String& outCode, IExpressionParameter* outputParameter) = 0;


		virtual String compileExpressionCallStart(IExpressionParameter* output) const = 0;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const = 0;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const = 0;

		virtual void postCompile() = 0;
	};	
}