#include "stdafx.h"
#include "ConnectionLine.h"
#include "GlyphBlock.h"
#include "OgreLineOverlayElement.h"
#include "OgreArrowOverlayElement.h"

#define LINE_INTERPOLATE_COUNT 80
#define LINE_INTERPOLATE_OFFSET 18

namespace Ogre
{
	ConnectionLine::ConnectionLine(InputOutputSocket* inputSocket, InputOutputSocket* outputSocket)
		: MaterialGlyph("<-#")
		, _input(inputSocket)
		, _output(outputSocket)
	{
		_input->addConnectionLine(this);
		_output->addConnectionLine(this);

		static size_t lineCnt = 0;
		_line = dynamic_cast<LineOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("Line",
			String("ConnectionLine/") + StringConverter::toString(lineCnt)));

		_arrow = dynamic_cast<ArrowOverlayElement*>(OverlayManager::getSingleton().createOverlayElement("Arrow",
			String("ConnectionLine/") + StringConverter::toString(lineCnt) + "/Arrow"));

		updatePosition();

		++lineCnt;
	}
	//--------------------------------------------------------------------------------
	ConnectionLine::~ConnectionLine()
	{
		_input->removeConnectionLine(this);
		_output->removeConnectionLine(this);

		OverlayManager::getSingleton().destroyOverlayElement(_line);
		_line = 0;

		OverlayManager::getSingleton().destroyOverlayElement(_arrow);
		_arrow = 0;
	}
	//--------------------------------------------------------------------------------
	InputOutputSocket* ConnectionLine::getInputSocket() const
	{
		return _input;
	}
	//--------------------------------------------------------------------------------
	InputOutputSocket* ConnectionLine::getOutputSocket() const
	{
		return _output;
	}
	//--------------------------------------------------------------------------------
	void ConnectionLine::addToContainer(OverlayContainer* c)
	{
		MaterialGlyph::addToContainer(c);
		c->addChild(_line);
		c->addChild(_arrow);
	}
	//--------------------------------------------------------------------------------
	void ConnectionLine::removeFromContainer()
	{
		_parentContainer->removeChild(_line->getName());
		_parentContainer->removeChild(_arrow->getName());
	}
	//--------------------------------------------------------------------------------
	bool ConnectionLine::intersects(Real x, Real y) const
	{
		// TODO:
		return false;
	}
	//--------------------------------------------------------------------------------
	void ConnectionLine::setDimisions(Real w, Real h)
	{

	}
	//--------------------------------------------------------------------------------
	Real ConnectionLine::getWidth() const
	{
		return 1;
	}
	//--------------------------------------------------------------------------------
	void ConnectionLine::setWidth(Real w)
	{
		
	}
	//--------------------------------------------------------------------------------
	Real ConnectionLine::getHeight() const
	{
		return 1;
	}
	//--------------------------------------------------------------------------------
	void ConnectionLine::setHeight(Real h)
	{

	}
	//--------------------------------------------------------------------------------
	void ConnectionLine::setPosition(Real x, Real y)
	{

	}
	//--------------------------------------------------------------------------------
	Vector2 ConnectionLine::getPosition() const
	{
		return Vector2::ZERO;
	}
	//--------------------------------------------------------------------------------
	void ConnectionLine::updatePosition()
	{
		Vector2List pts;
		RealRect rcStart = _input->getWorldBoundingRect();
		RealRect rcEnd = _output->getWorldBoundingRect();

		Vector2 ptStart(rcStart.right, rcStart.top + rcStart.height() * 0.5);
		Vector2 ptEnd(rcEnd.left, rcEnd.top + rcEnd.height() * 0.5);

		pts.push_back(ptStart);

#if 0
		pts.push_back(ptStart + Vector2(LINE_INTERPOLATE_OFFSET, 0));
		pts.push_back(ptEnd + Vector2(-LINE_INTERPOLATE_OFFSET, 0));
#elif 0
		SimpleSpline s;
		s.setAutoCalculate(false);
		s.addPoint(Vector3(ptStart.x, ptStart.y, 0));
		s.addPoint(Vector3(ptStart.x, ptStart.y, 0) + Vector3(LINE_INTERPOLATE_OFFSET, 20, 0));
		s.addPoint(Vector3(ptEnd.x, ptEnd.y, 0) + Vector3(-LINE_INTERPOLATE_OFFSET, -20, 0));
		s.addPoint(Vector3(ptEnd.x, ptEnd.y, 0));
		s.recalcTangents();

		for (int i = 0; i < LINE_INTERPOLATE_COUNT; ++i)
		{
			float r = (float)i / (float)LINE_INTERPOLATE_COUNT;
			Vector3 p = s.interpolate(r);
			pts.push_back(Vector2(p.x, p.y));
		}
#endif
		pts.push_back(ptEnd);
		_line->setPoints(pts);

#if 1
		Vector2 dir = ptStart - ptEnd;
		dir.normalise();
		_arrow->setEndPoint(ptStart);
		_arrow->setStartPoint(ptStart - dir * 16);
#else
		Vector2 dir = Vector2::UNIT_X;
		dir.normalise();
		_arrow->setEndPoint(ptStart);
		_arrow->setStartPoint(ptStart + dir * 16);
#endif
	}
	//--------------------------------------------------------------------------------
	const String& ConnectionLine::getParameterType() const
	{
		assert(_output);
		return _output->getParameterType();		
	}
	//--------------------------------------------------------------------------------
	IExpressionParameter* ConnectionLine::getInputParameter() const
	{
		return getInputSocket();
	}
	//--------------------------------------------------------------------------------
	IExpressionParameter* ConnectionLine::getOutputParameter() const
	{
		return getOutputSocket();
	}

}