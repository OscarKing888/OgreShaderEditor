#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_AutoConstant : public MaterialExpression
	{
	public:

		Material_AutoConstant(const String& name);
		virtual ~Material_AutoConstant();

		void setAutoConstantName(const String& name);
		const String& getAutoConstantName() const { return _constantName; }

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;

		virtual void postCompile();

	protected:

		String _constantName;
		HighLevelGpuProgramPtr _gpuProg;
		void setupViewPS(const GpuProgramParameters::AutoConstantDefinition* acd);
		void setupViewPSCode(const GpuProgramParameters::AutoConstantDefinition* acd, const String& hlsl);

		virtual void compileExpressionDeclarationImp(String& outCode);
	};
}