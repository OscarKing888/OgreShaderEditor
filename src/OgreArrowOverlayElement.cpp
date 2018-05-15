#include "stdafx.h"

#include "OgreArrowOverlayElement.h"
#include "OgreOverlayManager.h"
#include "OgreRoot.h"
#include "OgreLogManager.h"
#include "OgreOverlayManager.h"
#include "OgreHardwareBufferManager.h"
#include "OgreHardwareVertexBuffer.h"

#define POS_BINDING 0
#define COLOUR_BINDING 1

namespace Ogre
{
	String ArrowOverlayElement::msTypeName = "Arrow";

	//--------------------------------------------------------------------------------
	ArrowOverlayElement::ArrowOverlayElement(const String& name)
		: OverlayElement(name)
		, mStartPoint(Vector2::ZERO)
		, mEndPoint(Vector2::UNIT_SCALE)
		, mArrowWidthRatio(0.6f)
	{
		mColour = ColourValue::Black;
		mColoursChanged = false;
		mAllocSize = 0;
		mMetricsMode = GMM_PIXELS;

		if (createParamDictionary("ArrowOverlayElement"))
		{
			addBaseParameters();
		}
	}
	//--------------------------------------------------------------------------------
	ArrowOverlayElement::~ArrowOverlayElement(void)
	{
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::initialise(void)
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

			mRenderOp.operationType = RenderOperation::OT_TRIANGLE_LIST;
			mRenderOp.useIndexes = false;
			mRenderOp.vertexData->vertexStart = 0;
			// Vertex buffer will be created in checkMemoryAllocation

			checkMemoryAllocation(3);

			mInitialised = true;
		}
	}
	//--------------------------------------------------------------------------------
	const String& ArrowOverlayElement::getTypeName(void) const
	{
		return msTypeName;
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::getRenderOperation(RenderOperation& op)
	{
		op = mRenderOp;
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::updatePositionGeometry()
	{
		Real vpWidth, vpHeight;
		vpWidth = (Real) (OverlayManager::getSingleton().getViewportWidth());
		vpHeight = (Real) (OverlayManager::getSingleton().getViewportHeight());

		
		mRenderOp.vertexData->vertexCount = 3;

		// Get position / texcoord buffer
		HardwareVertexBufferSharedPtr vbuf = 
			mRenderOp.vertexData->vertexBufferBinding->getBuffer(POS_BINDING);

		struct  CustomVertex
		{
			Real x, y;
		};

		Vector2 dir = mEndPoint - mStartPoint;
		Vector3 dir3(dir.x, dir.y, 0);
		Vector3 dirp3 = dir3.crossProduct(-Vector3::UNIT_Z);

		Vector2 dirp2(dirp3.x, dirp3.y);
		dirp2.normalise();


		Real sw = 1.0 / vpWidth;
		Real sh = 1.0 / vpHeight;
		Real w = dir.length() * mArrowWidthRatio;

		CustomVertex* prPos = static_cast<CustomVertex*>(vbuf->lock(HardwareBuffer::HBL_DISCARD));
		{
			// end
			prPos->x = mEndPoint.x * sw * 2.0 - 1.0;
			prPos->y = 1.0 - (mEndPoint.y * sh * 2.0);
			++prPos;

			// start 2
			Vector2 start2 = mStartPoint - dirp2 * w * 0.5;
			prPos->x = start2.x * sw * 2.0 - 1.0;
			prPos->y = 1.0 - (start2.y * sh * 2.0);
			++prPos;

			// start 1
			Vector2 start1 = mStartPoint + dirp2 * w * 0.5;
			prPos->x = start1.x * sw * 2.0 - 1.0;
			prPos->y = 1.0 - (start1.y * sh * 2.0);
			++prPos;
		}

		// Unlock vertex buffer
		vbuf->unlock();
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::updateColours(void)
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
	void ArrowOverlayElement::updateTextureGeometry()
	{
		// Nothing to do, we combine positions and textures
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::setColour(const ColourValue& col)
	{
		mColour = col;
		mColoursChanged = true;
	}
	//--------------------------------------------------------------------------------
	const ColourValue& ArrowOverlayElement::getColour(void) const
	{
		// Either one
		return mColour;
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::_update(void)
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
	void ArrowOverlayElement::checkMemoryAllocation( size_t numChars )
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
	void ArrowOverlayElement::addBaseParameters(void)
	{
		OverlayElement::addBaseParameters();
		ParamDictionary* dict = getParamDictionary();

		/*dict->addParameter(ParameterDef("char_height", 
		"Sets the height of the characters in relation to the screen."
		, PT_REAL),
		&msCmdCharHeight);*/
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::setStartPoint(const Vector2& pt)
	{
		setStartPoint(pt.x, pt.y);
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::setEndPoint(const Vector2& pt)
	{
		setEndPoint(pt.x, pt.y);
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::setWidthRatio(Real r) 
	{ 
		mArrowWidthRatio = r;
		mGeomPositionsOutOfDate = true;
		mGeomUVsOutOfDate = true;
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::setStartPoint(Real x, Real y)
	{
		mStartPoint.x = x;
		mStartPoint.y = y;

		mGeomPositionsOutOfDate = true;
		mGeomUVsOutOfDate = true;		
	}
	//--------------------------------------------------------------------------------
	void ArrowOverlayElement::setEndPoint(Real x, Real y)
	{
		mEndPoint.x = x;
		mEndPoint.y = y;

		mGeomPositionsOutOfDate = true;
		mGeomUVsOutOfDate = true;
	}
}