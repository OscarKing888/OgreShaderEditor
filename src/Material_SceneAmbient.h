#pragma once
#include "MaterialExpression.h"

namespace Ogre
{
	class Material_SceneAmbient : public MaterialExpression
	{
	public:

		Material_SceneAmbient(const String& name);
		virtual ~Material_SceneAmbient();

		virtual String compileExpressionCallStart(IExpressionParameter* output) const;
		virtual String compileExpressionCallArguments(IExpressionParameter* output) const;
		virtual String compileExpressionCallEnd(IExpressionParameter* output) const;

		virtual void postCompile();

	protected:

		HighLevelGpuProgramPtr _gpuProg;
		void setupViewPS();

		virtual void compileExpressionDeclarationImp(String& outCode);
	};
}