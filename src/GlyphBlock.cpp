#include "stdafx.h"
#include "GlyphBlock.h"
#include "CaptionBar.h"
#include "PanelGlyph.h"
#include "ConnectionLine.h"

namespace Ogen
{
	static const Real C_SocketWidth = 11.0;
	static const Real C_SocketHeight = 8.0;
	static const Real C_SocketSpacing = 16.0;
	static const Real C_SocketInitSpacing = 12.0;

	//--------------------------------------------------------------------------------
	// InputOutputSocket
	//--------------------------------------------------------------------------------
	InputOutputSocket::InputOutputSocket(const String& name, bool isInputSocket,
		GlyphBlock* parent, const DisplayString& displayString,
		const String& parameterType, const String& components)
		: PanelGlyph(name)
		, _isInputSocket(isInputSocket)
		, _parent(parent)
		, _parameterType(parameterType)
		, _components(components)
	{
		_label = dynamic_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton()
			.createOverlayElement("TextArea", name + "/Label"));
		_label->setCaption(displayString);
		_label->setMetricsMode(GMM_PIXELS);
		_label->setCharHeight(C_CHAR_HEIGHT);
		_label->setFontName(C_DEFAULT_FONT_NAME);
		_label->setColour(ColourValue::White);

		_labelShadow = dynamic_cast<TextAreaOverlayElement*>(OverlayManager::getSingleton()
			.createOverlayElement("TextArea", name + "/LabelShadow"));
		_labelShadow->setCaption(displayString);
		_labelShadow->setMetricsMode(GMM_PIXELS);
		_labelShadow->setCharHeight(C_CHAR_HEIGHT);
		_labelShadow->setFontName(C_DEFAULT_FONT_NAME);
		_labelShadow->setColour(ColourValue::Black);

		if(_isInputSocket)
		{
			_label->setAlignment(TextAreaOverlayElement::Right);
			_labelShadow->setAlignment(TextAreaOverlayElement::Right);
		}

	}
	//--------------------------------------------------------------------------------
	InputOutputSocket::~InputOutputSocket()
	{

	}
	//--------------------------------------------------------------------------------
	const ConnectionLineList& InputOutputSocket::getConnectionLineList() const
	{
		return _connectionLineList;
	}
	//--------------------------------------------------------------------------------
	bool InputOutputSocket::isConnected() const
	{
		return !_connectionLineList.empty();
	}
	//--------------------------------------------------------------------------------
	void InputOutputSocket::addConnectionLine(ConnectionLine* connectionLine)
	{
		_connectionLineList.push_back(connectionLine);
	}
	//--------------------------------------------------------------------------------
	void InputOutputSocket::removeConnectionLine(ConnectionLine* connectionLine)
	{
		ConnectionLineList::iterator i =
			std::find(_connectionLineList.begin(), _connectionLineList.end(), connectionLine);
		
		if(i != _connectionLineList.end())
		{
			_connectionLineList.erase(i);
		}
	}
	//--------------------------------------------------------------------------------
	RealRect InputOutputSocket::getWorldBoundingRect() const
	{
		RealRect rc = getBoundingRect();
		rc.left += _parent->getPosition().x;
		rc.right += _parent->getPosition().x;

		rc.top += _parent->getPosition().y;
		rc.bottom += _parent->getPosition().y;
		return rc;
	}
	//--------------------------------------------------------------------------------
	void InputOutputSocket::addToContainer(OverlayContainer* c)
	{
		PanelGlyph::addToContainer(c);
		c->addChild(_labelShadow);
		c->addChild(_label);
	}
	//--------------------------------------------------------------------------------
	void InputOutputSocket::removeFromContainer()
	{
		PanelGlyph::removeFromContainer();
		_parentContainer->removeChild(_label->getName());
		_parentContainer->removeChild(_labelShadow->getName());
	}
	//--------------------------------------------------------------------------------
	void InputOutputSocket::setPosition(Real x, Real y)
	{
		PanelGlyph::setPosition(x, y);
		if(_isInputSocket)
		{
			_label->setPosition(x - _label->getWidth() - C_TEXT_MARGIN_LEFT, y);
			_labelShadow->setPosition(x - _label->getWidth() - C_TEXT_MARGIN_LEFT
				+ C_TEXT_SHADOW_OFFSET, y + C_TEXT_SHADOW_OFFSET);
		}
		else
		{
			_label->setPosition(x + C_SocketWidth + C_TEXT_MARGIN_LEFT, y);
			_labelShadow->setPosition(x + C_SocketWidth + C_TEXT_SHADOW_OFFSET
				+ C_TEXT_MARGIN_LEFT, y + C_TEXT_SHADOW_OFFSET);
		}

		updatePosition();
	}
	//--------------------------------------------------------------------------------
	void InputOutputSocket::updatePosition()
	{
		ConnectionLineList::iterator i = _connectionLineList.begin();
		for (; i != _connectionLineList.end(); ++i)
		{
			(*i)->updatePosition();
		}
	}
	//--------------------------------------------------------------------------------
	const String& InputOutputSocket::getParameterType() const
	{
		return _parameterType;
	}
	//--------------------------------------------------------------------------------
	const String& InputOutputSocket::getComponents() const
	{
		return _components;
	}
	//--------------------------------------------------------------------------------
	IMaterialExpression* InputOutputSocket::getParentExpression() const
	{
		return dynamic_cast<IMaterialExpression*>(_parent);
	}
	//--------------------------------------------------------------------------------
	size_t InputOutputSocket::getConnectionLineCount() const
	{
		return _connectionLineList.size();
	}
	//--------------------------------------------------------------------------------
	IExpressionParameterConnectionLine* InputOutputSocket::getConnectionLine(size_t idx) const
	{
		assert(idx < _connectionLineList.size());
		return _connectionLineList[idx];
	}
	//--------------------------------------------------------------------------------
	// GlyphBlock
	//--------------------------------------------------------------------------------
	GlyphBlock::GlyphBlock(const String& name)
		: MaterialGlyph(name)
		, _container(0)
		, _caption(0)
		, _panel(0)
	{
		_container = dynamic_cast<PanelOverlayElement*>(
			OverlayManager::getSingleton().createOverlayElement("Panel", name + "/RootContainer"));
		_container->setTransparent(true);
		_container->setMetricsMode(GMM_PIXELS);

		_caption = new CaptionBar(name + "/Caption", "N/A");
		_panel = new PanelGlyph(name + "/Panel");
		_caption->setAutoUpdateSize(false);
		_caption->setTextColour(ColourValue(1.0, 1.0, 0));

		_panel->addToContainer(_container);
		_caption->addToContainer(_container);

		layout();
	}
	//--------------------------------------------------------------------------------
	GlyphBlock::~GlyphBlock()
	{
		delete _caption; 
		_caption = 0;

		delete _panel;
		_panel = 0;
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::setDimisions(Real w, Real h)
	{
		_container->setDimensions(w, h);
		layout();
	}
	//--------------------------------------------------------------------------------
	Real GlyphBlock::getWidth() const
	{
		return _container->getWidth();
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::setWidth(Real w)
	{
		_container->setWidth(w);
		layout();
	}
	//--------------------------------------------------------------------------------
	Real GlyphBlock::getHeight() const
	{
		return _container->getHeight();
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::setHeight(Real h)
	{
		_container->setHeight(h);
		layout();
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::setPosition(Real x, Real y)
	{
		_container->setPosition(x, y);
		
		size_t sz = _inputSocketList.size();
		for (size_t i = 0; i < sz; ++i)
		{
			InputOutputSocket* p = _inputSocketList[i];
			p->updatePosition();
		}

		sz = _outputSocketList.size();
		for (size_t i = 0; i < sz; ++i)
		{
			InputOutputSocket* p = _outputSocketList[i];
			p->updatePosition();
		}
	}
	//--------------------------------------------------------------------------------
	Vector2 GlyphBlock::getPosition() const
	{
		return Vector2(_container->getLeft(), _container->getTop());
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::layout()
	{
		_caption->setPosition(0, 0);
		_caption->forceAutoUpdateSize();
		_caption->setWidth(_container->getWidth());

		RealRect rc = _caption->getBoundingRect();
		_panel->setPosition(0, rc.bottom + C_ELEMENT_SPACING);
		_panel->setWidth(rc.width());

		size_t maxSz = std::max(_inputSocketList.size(), _outputSocketList.size());
		Real panelHeight = maxSz * (C_SocketSpacing + C_SocketHeight) + C_SocketInitSpacing;		
		panelHeight = std::max(panelHeight, _container->getHeight() - rc.bottom - C_ELEMENT_SPACING);
		_panel->setHeight(panelHeight);

		rc = _panel->getBoundingRect();

		size_t sz = _inputSocketList.size();
		for (size_t i = 0; i < sz; ++i)
		{
			InputOutputSocket* p = _inputSocketList[i];
			p->setDimisions(C_SocketWidth, C_SocketHeight);
			p->setPosition(rc.right, rc.top + i * C_SocketSpacing
				+ C_SocketInitSpacing + i * C_SocketHeight);
		}

		sz = _outputSocketList.size();
		for (size_t i = 0; i < sz; ++i)
		{
			InputOutputSocket* p = _outputSocketList[i];
			p->setDimisions(C_SocketWidth, C_SocketHeight);
			p->setPosition(rc.left - C_SocketWidth, rc.top + i * C_SocketSpacing 
				+ C_SocketInitSpacing + i * C_SocketHeight);
		}
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::addToContainer(OverlayContainer* c)
	{
		c->addChild(_container);
		MaterialGlyph::addToContainer(c);
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::removeFromContainer()
	{
		_caption->removeFromContainer();
		_panel->removeFromContainer();

		for (size_t i = 0; i < _inputSocketList.size(); ++i)
		{
			_inputSocketList[i]->removeFromContainer();
		}

		for (size_t j = 0; j < _outputSocketList.size(); ++j)
		{
			_outputSocketList[j]->removeFromContainer();
		}

		_inputSocketList.clear();
		_outputSocketList.clear();
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::setCaption(const DisplayString& cap)
	{
		_caption->setCaption(cap);
	}
	//--------------------------------------------------------------------------------
	const DisplayString& GlyphBlock::getCaption() const
	{
		return _caption->getCaption();
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::addInputSocket(InputOutputSocket* inputSocket)
	{
		assert(inputSocket->isInputSocket());

		inputSocket->setFillColour(ColourValue::Black);
		inputSocket->setBorderColour(ColourValue::Black);
		inputSocket->addToContainer(_container);
		_inputSocketList.push_back(inputSocket);
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::removeInputSocket(const String& name)
	{
		InputOutputSocketList::iterator it = _inputSocketList.begin();
		for (; it != _inputSocketList.end(); ++it)
		{
			if((*it)->getName() == name)
			{
				(*it)->removeFromContainer();
				_inputSocketList.erase(it);
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::addOutputSocket(InputOutputSocket* outputSocket)
	{
		assert(!outputSocket->isInputSocket());

		outputSocket->setFillColour(ColourValue::Black);
		outputSocket->setBorderColour(ColourValue::Black);
		outputSocket->addToContainer(_container);
		_outputSocketList.push_back(outputSocket);
	}
	//--------------------------------------------------------------------------------
	void GlyphBlock::removeOutputSocket(const String& name)
	{
		InputOutputSocketList::iterator it = _outputSocketList.begin();
		for (; it != _outputSocketList.end(); ++it)
		{
			if((*it)->getName() == name)
			{
				(*it)->removeFromContainer();
				_outputSocketList.erase(it);
				return;
			}
		}
	}
	//--------------------------------------------------------------------------------
	InputOutputSocket* GlyphBlock::getInputSocket(size_t idx) const
	{
		assert(idx < _inputSocketList.size());
		return _inputSocketList[idx];
	}
	//--------------------------------------------------------------------------------
	InputOutputSocket* GlyphBlock::getOutputSocket(size_t idx) const
	{
		assert(idx < _outputSocketList.size());
		return _outputSocketList[idx];
	}
	//--------------------------------------------------------------------------------
	size_t GlyphBlock::getInputSocketCount() const
	{
		return _inputSocketList.size();
	}
	//--------------------------------------------------------------------------------
	size_t GlyphBlock::getOutputSocketCount() const
	{
		return _outputSocketList.size();
	}
	//--------------------------------------------------------------------------------
	RealRect GlyphBlock::getClientRect() const
	{
		RealRect rc = _panel->getBoundingRect();
		return rc;
	}
	//--------------------------------------------------------------------------------
	String GlyphBlock::compileCode() const
	{
		return "";
	}
}