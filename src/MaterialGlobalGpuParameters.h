#pragma once

namespace Ogre
{
	class MaterialGlobalGpuParameters
	{
	public:
		
		static ColourValue SceneAmbientColor;
		static String SceneAmbientColorName;

		static void setSceneAmbientColor(GpuProgramParametersSharedPtr gpp);
		static void setSceneAmbientColor(const String& parameterName, GpuProgramParametersSharedPtr gpp);

	};

	//--------------------------------------------------------------------------------

	class ShaderCompileContex
	{
	public:

		static String PSInputParameterName;

		static ushort TextureSamplerStageIndex;

		static Material* CurrentMaterial;
		static Technique* CurrentTechnique;
		static Pass* CurrentPass;
		static HighLevelGpuProgram* CurrentPS;

		static void reset();
	};

	//--------------------------------------------------------------------------------
	class ShaderUtil
	{
	public:

		static HighLevelGpuProgramPtr createOrGetPS(const String& name);
	
	};
}