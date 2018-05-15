#include "stdafx.h"
#include "MaterialExpression.h"

namespace Ogre
{
	MaterialExpression::MaterialExpression(const String& name, bool needDeclaration)
		: BlockWithView(name)
		, _needDeclaration(needDeclaration)
		, _compileDeclarationOnce(false)
	{

	}
	//--------------------------------------------------------------------------------
	MaterialExpression::~MaterialExpression()
	{

	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::startCompileExpressionDeclaration()
	{
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::compileExpressionDeclaration(String& outCode)
	{
		if(_needDeclaration)
		{
			if(!_compileDeclarationOnce)
			{
				_compileDeclarationOnce = true;
				compileExpressionDeclarationImp(outCode);
			}
		}
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::endCompileExpressionDeclaration()
	{
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::compileExpression(String& outCode, IExpressionParameter* outputParameter)
	{

	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::compileExpressionDeclarationImp(String& outCode)
	{

	}
	//--------------------------------------------------------------------------------
	size_t MaterialExpression::getInputParametersCount() const
	{
		return _inputSocketList.size();
	}
	//--------------------------------------------------------------------------------
	size_t MaterialExpression::getOutputParametersCount() const
	{
		return _outputSocketList.size();
	}
	//--------------------------------------------------------------------------------
	IExpressionParameter* MaterialExpression::getInputParameter(size_t idx) const
	{
		return getInputSocket(idx);
	}
	//--------------------------------------------------------------------------------
	IExpressionParameter* MaterialExpression::getOutputParameter(size_t idx) const
	{
		return getOutputSocket(idx);
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::compileInputStruct(StrMap& outMap)
	{

	}
	//--------------------------------------------------------------------------------
	String MaterialExpression::compileExpressionCallStart(IExpressionParameter* output) const
	{
		return "";
	}
	//--------------------------------------------------------------------------------
	String MaterialExpression::compileExpressionCallArguments(IExpressionParameter* output) const
	{
		return "";
	}
	//--------------------------------------------------------------------------------
	String MaterialExpression::compileExpressionCallEnd(IExpressionParameter* output) const
	{
		return "";
	}
	//--------------------------------------------------------------------------------	
	void MaterialExpression::resetForCompile()
	{
		_compiledFunctionMap.clear();
		_compileDeclarationOnce = false;
	}
	//--------------------------------------------------------------------------------	
	void MaterialExpression::addCompiledFunction(const String& funName)
	{
		_compiledFunctionMap.insert(std::make_pair(funName, true));
	}
	//--------------------------------------------------------------------------------	
	bool MaterialExpression::isFunctionCompiled(const String& funName) const
	{
		CompiledFunctionMap::const_iterator it = _compiledFunctionMap.find(funName);
		if(it != _compiledFunctionMap.end())
		{
			return it->second;
		}

		return false;
	}
	//--------------------------------------------------------------------------------
	void MaterialExpression::postCompile()
	{
		for (size_t i = 0; i < getInputParametersCount(); ++i)
		{
			IExpressionParameter* p = getInputParameter(i);
			if(p->getConnectionLineCount() > 0)
			{
				IMaterialExpression* me =
					p->getConnectionLine(0)->getOutputParameter()->getParentExpression();
				me->postCompile();
			}
		}
	}

}