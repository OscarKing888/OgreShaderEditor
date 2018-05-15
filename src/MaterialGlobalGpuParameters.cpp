#include "stdafx.h"
#include "MaterialGlobalGPUParameters.h"

namespace Ogre
{
	//--------------------------------------------------------------------------------
	//	MaterialGlobalGpuParameters
	//--------------------------------------------------------------------------------
	ColourValue MaterialGlobalGpuParameters::SceneAmbientColor(0.49f, 0.49f, 0.49f);
	String MaterialGlobalGpuParameters::SceneAmbientColorName("Global_SceneAmbientColor");

	//--------------------------------------------------------------------------------
	//	ShaderCompileContex
	//--------------------------------------------------------------------------------
	String ShaderCompileContex::PSInputParameterName("input");
	ushort ShaderCompileContex::TextureSamplerStageIndex = 0;
	Material* ShaderCompileContex::CurrentMaterial = 0;
	Technique* ShaderCompileContex::CurrentTechnique = 0;
	Pass* ShaderCompileContex::CurrentPass = 0;
	HighLevelGpuProgram* ShaderCompileContex::CurrentPS = 0;
	//--------------------------------------------------------------------------------
	//	MaterialGlobalGpuParameters
	//--------------------------------------------------------------------------------
	void MaterialGlobalGpuParameters::setSceneAmbientColor(const String& parameterName, GpuProgramParametersSharedPtr gpp)
	{
		gpp->setNamedConstant(parameterName, SceneAmbientColor);
	}
	//--------------------------------------------------------------------------------
	void MaterialGlobalGpuParameters::setSceneAmbientColor(GpuProgramParametersSharedPtr gpp)
	{
		gpp->setNamedConstant(SceneAmbientColorName, SceneAmbientColor);
	}
	//--------------------------------------------------------------------------------
	// ShaderCompileContex
	//--------------------------------------------------------------------------------
	void ShaderCompileContex::reset()
	{
		TextureSamplerStageIndex = 0;
		CurrentMaterial = 0;
		CurrentTechnique = 0;
		CurrentPass = 0;
		CurrentPS = 0;
	}

	//--------------------------------------------------------------------------------
	// ShaderUtil
	//--------------------------------------------------------------------------------
	HighLevelGpuProgramPtr ShaderUtil::createOrGetPS(const String& name)
	{
		HighLevelGpuProgramPtr gpuProg;
		if(!HighLevelGpuProgramManager::getSingleton().resourceExists(name))
		{
			gpuProg = HighLevelGpuProgramManager::getSingleton().createProgram(name,
				ResourceGroupManager::INTERNAL_RESOURCE_GROUP_NAME, "hlsl", GPT_FRAGMENT_PROGRAM);

			gpuProg->setParameter("entry_point", "ps_2_0");
			gpuProg->setParameter("target", "ps_2_0");
		}
		else
		{
			gpuProg = HighLevelGpuProgramPtr(HighLevelGpuProgramManager::getSingleton()
				.getByName(name));
		}

		return gpuProg;
	}

}
