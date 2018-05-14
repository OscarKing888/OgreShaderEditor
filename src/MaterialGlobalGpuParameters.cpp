#include "stdafx.h"
#include "MaterialGlobalGPUParameters.h"

namespace Ogen
{
	//--------------------------------------------------------------------------------
	//	MaterialGlobalGpuParameters
	//--------------------------------------------------------------------------------
	ColourValue MaterialGlobalGpuParameters::MaterialAmbientColor(0.49f, 0.49f, 0.49f);
	String MaterialGlobalGpuParameters::MaterialAmbientColorName("GlobalMaterial_AmbientColor");

	//--------------------------------------------------------------------------------
	//	ShaderCompileContex
	//--------------------------------------------------------------------------------
	String ShaderCompileContex::PSInputParameterName("input");
	ushort ShaderCompileContex::TextureSamplerStageIndex = 0;
	Material* ShaderCompileContex::CurrentMaterial = 0;
	Technique* ShaderCompileContex::CurrentTechnique = 0;
	Pass* ShaderCompileContex::CurrentPass = 0;

	//--------------------------------------------------------------------------------
	//	MaterialGlobalGpuParameters
	//--------------------------------------------------------------------------------
	void MaterialGlobalGpuParameters::setMaterialAmbientColor(const String& parameterName, GpuProgramParametersSharedPtr gpp)
	{
		gpp->setNamedConstant(parameterName, MaterialAmbientColor);
	}
	//--------------------------------------------------------------------------------
	void MaterialGlobalGpuParameters::setMaterialAmbientColor(GpuProgramParametersSharedPtr gpp)
	{
		gpp->setNamedConstant(MaterialAmbientColorName, MaterialAmbientColor);
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
	}

}
