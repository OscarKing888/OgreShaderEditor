#include "stdafx.h"

#include "OgreLineOverlayElement.h"
#include "OgreOverlayManager.h"
#include "OgreRoot.h"
#include "OgreLogManager.h"
#include "OgreOverlayManager.h"
#include "OgreHardwareBufferManager.h"
#include "OgreHardwareVertexBuffer.h"

#define POS_BINDING 0
#define COLOUR_BINDING 1

namespace Ogen
{
	String LineOverlayElement::msTypeName = "Line";

	//--------------------------------------------------------------------------------
	LineOverlayElement::LineOverlayElement(const String& name)
		: OverlayElement(name)
	{
		mColour = ColourValue::Black;
		mColoursChanged = false;
		mAllocSize = 0;
		mMetricsMode = GMM_PIXELS;

		if (createParamDictionary("LineOverlayElement"))
		{
			addBaseParameters();
		}
	}
	//--------------------------------------------------------------------------------
	LineOverlayElement::~LineOverlayElement(void)
	{
	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::initialise(void)
	{
		if (!mInitialised)
		{
			setMaterialName("BaseWhiteNoLighting");

			// Set up the render op
			// Combine positions and texture coords since they tend to change together
			// since character sizes are different
			mRenderOp.vertexData = new VertexData();
			VertexDeclaration* decl = mRenderOp.vertexData->vertexDeclaration;

			// Positions
			decl->addElement(POS_BINDING, 0, VET_FLOAT2, VES_POSITION);
			
			// Texcoords
			//decl->addElement(POS_BINDING, offset, VET_FLOAT2, VES_TEXTURE_COORDINATES, 0);
			//offset += VertexElement::getTypeSize(VET_FLOAT2);

			// Colours - store these in a separate buffer because they change less often
			decl->addElement(COLOUR_BINDING, 0, VET_COLOUR, VES_DIFFUSE);

			mRenderOp.operationType = RenderOperation::OT_LINE_STRIP;
			mRenderOp.useIndexes = false;
			mRenderOp.vertexData->vertexStart = 0;
			// Vertex buffer will be created in checkMemoryAllocation

			checkMemoryAllocation(2);

			mInitialised = true;
		}
	}
	//--------------------------------------------------------------------------------
	const String& LineOverlayElement::getTypeName(void) const
	{
		return msTypeName;
	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::getRenderOperation(RenderOperation& op)
	{
		op = mRenderOp;
	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::updatePositionGeometry()
	{
		Real vpWidth, vpHeight;
		vpWidth = (Real) (OverlayManager::getSingleton().getViewportWidth());
		vpHeight = (Real) (OverlayManager::getSingleton().getViewportHeight());

		checkMemoryAllocation(mPoints.size());
		mRenderOp.vertexData->vertexCount = mPoints.size();

		// Get position / texcoord buffer
		HardwareVertexBufferSharedPtr vbuf = 
			mRenderOp.vertexData->vertexBufferBinding->getBuffer(POS_BINDING);
		
		struct  CustomVertex
		{
			Real x, y;
		};

		CustomVertex* prPos = static_cast<CustomVertex*>(vbuf->lock(HardwareBuffer::HBL_DISCARD));
		{
			size_t sz = mPoints.size();
			Real sw = 1.0 / vpWidth;
			Real sh = 1.0 / vpHeight;
			for(size_t i = 0; i < sz; i++)
			{
				prPos->x = mPoints[i].x * sw * 2.0 - 1.0;
				prPos->y = 1.0 - (mPoints[i].y * sh * 2.0);
				++prPos;
			}
		}

		// Unlock vertex buffer
		vbuf->unlock();
	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::updateColours(void)
	{
		// Convert to system-specific
		RGBA clr;
		Root::getSingleton().convertColourValue(mColour, &clr);

		HardwareVertexBufferSharedPtr vbuf = 
			mRenderOp.vertexData->vertexBufferBinding->getBuffer(COLOUR_BINDING);

		RGBA* pDest = static_cast<RGBA*>(
			vbuf->lock(HardwareBuffer::HBL_DISCARD) );

		for (size_t i = 0; i < mAllocSize; ++i)
		{
			*pDest++ = clr;
		}
		vbuf->unlock();

	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::updateTextureGeometry()
	{
		// Nothing to do, we combine positions and textures
	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::setColour(const ColourValue& col)
	{
		mColour = col;
		mColoursChanged = true;
	}
	//--------------------------------------------------------------------------------
	const ColourValue& LineOverlayElement::getColour(void) const
	{
		// Either one
		return mColour;
	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::_update(void)
	{
		// Check size if pixel-based / relative-aspect-adjusted
		switch (mMetricsMode)
		{
		case GMM_PIXELS:
			if(OverlayManager::getSingleton().hasViewportChanged() || mGeomPositionsOutOfDate)
			{
				mGeomPositionsOutOfDate = true;
			}
			break;

		case GMM_RELATIVE_ASPECT_ADJUSTED:
			if(OverlayManager::getSingleton().hasViewportChanged() || mGeomPositionsOutOfDate)
			{
				mGeomPositionsOutOfDate = true;
			}
			break;

		default:
			break;
		}

		OverlayElement::_update();

		if (mColoursChanged && mInitialised)
		{
			updateColours();
			mColoursChanged = false;
		}
	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::checkMemoryAllocation( size_t numChars )
	{
		if( mAllocSize < numChars)
		{
			// Create and bind new buffers
			// Note that old buffers will be deleted automatically through reference counting

			// 6 verts per char since we're doing tri lists without indexes
			// Allocate space for positions & texture coords
			VertexDeclaration* decl = mRenderOp.vertexData->vertexDeclaration;
			VertexBufferBinding* bind = mRenderOp.vertexData->vertexBufferBinding;

			mRenderOp.vertexData->vertexCount = numChars;

			// Create dynamic since text tends to change alot
			// positions & texcoords
			HardwareVertexBufferSharedPtr vbuf = 
				HardwareBufferManager::getSingleton().
				createVertexBuffer(
				decl->getVertexSize(POS_BINDING), 
				mRenderOp.vertexData->vertexCount,
				HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
			bind->setBinding(POS_BINDING, vbuf);

			// colours
			vbuf = HardwareBufferManager::getSingleton().
				createVertexBuffer(
				decl->getVertexSize(COLOUR_BINDING), 
				mRenderOp.vertexData->vertexCount,
				HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY);
			bind->setBinding(COLOUR_BINDING, vbuf);

			mAllocSize = numChars;
			mColoursChanged = true; // force colour buffer regeneration
		}
	}	
	//--------------------------------------------------------------------------------
	void LineOverlayElement::addBaseParameters(void)
	{
		OverlayElement::addBaseParameters();
		ParamDictionary* dict = getParamDictionary();

		/*dict->addParameter(ParameterDef("char_height", 
			"Sets the height of the characters in relation to the screen."
			, PT_REAL),
			&msCmdCharHeight);*/
	}
	//--------------------------------------------------------------------------------
	void LineOverlayElement::setPoints(const Vector2List& lst)
	{
		mPoints = lst;

		mGeomPositionsOutOfDate = true;
		mGeomUVsOutOfDate = true;
	}
}