#include "stdafx.h"
#include "Material_SceneAmbient.h"
#include "OgreGpuProgram.h"
#include "MaterialGlobalGpuParameters.h"

namespace Ogre
{
	Material_SceneAmbient::Material_SceneAmbient(const String& name)
		: MaterialExpression(name, true)
	{

		addOutputSocket(new InputOutputSocket(name + "/Out", false, this, "", "float4"));
	
		setDimisions(140, 130);
		
		_gpuProg = ShaderUtil::createOrGetPS(_name);

		setCaption("Scene Ambient");
		setupViewPS();
	}
	//--------------------------------------------------------------------------------
	Material_SceneAmbient::~Material_SceneAmbient()
	{
	}
	//--------------------------------------------------------------------------------
	void Material_SceneAmbient::setupViewPS()
	{
		String hlslCode = "uniform float4 " +
			MaterialGlobalGpuParameters::SceneAmbientColorName + ";\n";
		hlslCode += "float4 ps_2_0() : COLOR \n {\n return (";
		hlslCode += MaterialGlobalGpuParameters::SceneAmbientColorName;
		hlslCode += "); \n}\n";

		_gpuProg->unload();
		_gpuProg->setSource(hlslCode);
		_gpuProg->load();

		GpuProgramParametersSharedPtr gps = _gpuProg->getDefaultParameters();
		//GpuProgramParametersSharedPtr gps = getViewMaterialPass()->getFragmentProgramParameters();

		MaterialGlobalGpuParameters::setSceneAmbientColor(gps);

		getViewMaterialPass()->setFragmentProgram(_gpuProg->getName());

	}
	//--------------------------------------------------------------------------------
	void Material_SceneAmbient::compileExpressionDeclarationImp(String& outCode)
	{
		outCode += formatString("uniform float4 %s;\n",
			MaterialGlobalGpuParameters::SceneAmbientColorName.c_str());
	}
	//--------------------------------------------------------------------------------
	String Material_SceneAmbient::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return "(";
	}
	//--------------------------------------------------------------------------------
	String Material_SceneAmbient::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		return MaterialGlobalGpuParameters::SceneAmbientColorName;
	}
	//--------------------------------------------------------------------------------
	String Material_SceneAmbient::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return ")";
	}
	//--------------------------------------------------------------------------------
	void Material_SceneAmbient::postCompile()
	{
		MaterialExpression::postCompile();
		MaterialGlobalGpuParameters::setSceneAmbientColor(ShaderCompileContex::CurrentPS->getDefaultParameters());
	}
}
