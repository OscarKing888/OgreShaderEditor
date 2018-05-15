/*
-----------------------------------------------------------------------------
This source file is part of OGRE
    (Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2006 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
LGPL like the rest of the engine.
-----------------------------------------------------------------------------
*/

/**
    \file 
        Lighting.h
    \brief
        Shows lighting support in OGRE. Also demonstrates the use of billboards
        and controllers for automatic time-relative behaviour.
*/


#include "ExampleApplication.h"
#include <OgreTextAreaOverlayElement.h>
#include <OgreFontManager.h>
#include <OgreBorderPanelOverlayElement.h>

#include "OgreLineOverlayElement.h"
#include "OgreArrowOverlayElement.h"

#include "PanelGlyph.h"
#include "CaptionBar.h"
#include "GlyphBlock.h"
#include "ConnectionLine.h"


#include "Material_TextureSampler.h"
#include "Material_DotProduct.h"
#include "Material_AutoConstant.h"
#include "Material_If.h"
#include "Material_Multiply.h"

#include "Material_Root.h"
#include "Material_Technique.h"
#include "Material_Pass.h"

ArrowOverlayElement* _arrow;
MaterialPtr _material;

/** This class turns lights & billboards linked to them on & off */
class LightFlasher : public ControllerValue<Real>
{
protected:
	Light* mLight;
	Billboard* mBillboard;
	ColourValue mMaxColour;
	Real intensity;
public:
	LightFlasher(Light* light, Billboard* billboard, ColourValue maxColour)
	{
		mLight = light;
		mBillboard = billboard;
		mMaxColour = maxColour;
	}

	virtual Real  getValue (void) const
	{
		return intensity;
	}

	virtual void  setValue (Real value)
	{
		intensity = value;

		ColourValue newColour;

		// Attenuate the brightness of the light
		newColour.r = mMaxColour.r * intensity;
		newColour.g = mMaxColour.g * intensity;
		newColour.b = mMaxColour.b * intensity;

		mLight->setDiffuseColour(newColour);
		mBillboard->setColour(newColour);
	}
};


/** Controller function mapping waveform to light intensity */
class LightFlasherControllerFunction : public WaveformControllerFunction
{
public:
	LightFlasherControllerFunction(WaveformType wavetype, Real frequency, Real phase) : WaveformControllerFunction(wavetype, 0, frequency, phase, 1, true)
	{

	}
};


// Some global node data
SceneNode* mRedYellowLightsNode;
SceneNode* mGreenBlueLightsNode;
std::vector<AnimationState*> mAnimStateList;

GlyphBlock* _blk1 = 0;
Vector2 _blk1pos(700, 100);

// Listener class for frame updates
class LightingListener : public ExampleFrameListener
{
protected:
public:
    LightingListener(RenderWindow* win, Camera* cam)
        : ExampleFrameListener(win, cam)
    {
    }

    bool frameRenderingQueued(const FrameEvent& evt)
    {
	if( ExampleFrameListener::frameRenderingQueued(evt) == false )
		return false;

		std::vector<AnimationState*>::iterator animi;
		for (animi = mAnimStateList.begin(); animi != mAnimStateList.end(); ++animi)
		{
			(*animi)->addTime(evt.timeSinceLastFrame);
		}

#if 0
		Real r = 200;
		static Real ang = 0.0f;
		Vector2 center(640, 480);

		float a = Degree(ang).valueRadians();
		Real x = cos(a) * r + center.x;
		Real y = sin(a) * r + center.y;
		_arrow->setStartPoint(center);
		_arrow->setEndPoint(x, y);
		_arrow->setWidthRatio(fabs(sin(a)) + 0.1);
		
		ang += 1.0f;
#endif

#if 0
		Real r = 100;
		static Real ang = 0.0f;

		float a = Degree(ang).valueRadians();
		Real x = cos(a) * r + _blk1pos.x;
		Real y = sin(a) * r + _blk1pos.y;
		
		_blk1->setPosition(x, y);
		ang += 1.0f;
#endif

		if(!_material.isNull())
		{
			MaterialSerializer ms;
			ms.queueForExport(_material);
			ms.exportQueued("m.material", false, "m.program");
			//ms.exportMaterial(_material, "mat.material");
			_material.setNull();
		}
        return true;
    }
};

/** Application class */
class LightingApplication : public ExampleApplication
{
protected:

	// The set of all the billboards used for the lights
    // 2 sets because we'll rotate them differently
	BillboardSet* mRedYellowLights;
	BillboardSet* mGreenBlueLights;

	// Billboards
	Billboard* mRedLightBoard;
	Billboard* mBlueLightBoard;
	Billboard* mYellowLightBoard;
	Billboard* mGreenLightBoard;

	// Lights
	Light* mRedLight;
	Light* mBlueLight;
	Light* mYellowLight;
	Light* mGreenLight;


	// Light flashers
	ControllerValueRealPtr mRedLightFlasher;
	ControllerValueRealPtr mBlueLightFlasher;
	ControllerValueRealPtr mYellowLightFlasher;
	ControllerValueRealPtr mGreenLightFlasher;

	// Light controller functions
	ControllerFunctionRealPtr mRedLightControllerFunc;
	ControllerFunctionRealPtr mBlueLightControllerFunc;
	ControllerFunctionRealPtr mYellowLightControllerFunc;
	ControllerFunctionRealPtr mGreenLightControllerFunc;

	// Light controllers
	Controller<Real>* mRedLightController;
	Controller<Real>* mBlueLightController;
	Controller<Real>* mYellowLightController;
	Controller<Real>* mGreenLightController;

	void createScene(void)
    {
		// Set a very low level of ambient lighting
		//mSceneMgr->setAmbientLight(ColourValue(0.1, 0.1, 0.1));
		this->mCamera->getViewport()->setBackgroundColour(ColourValue(165.0f/255.0f, 165.0f/255.0f, 165.0f/255.0f));

        // Use the "Space" skybox
        //mSceneMgr->setSkyBox(true, "Examples/SpaceSkyBox");

		// Load ogre head
		//Entity* head = mSceneMgr->createEntity("head", "ogrehead.mesh");

		// Attach the head to the scene
		//mSceneMgr->getRootSceneNode()->attachObject(head);

// 		Rectangle2D* rc = new Rectangle2D();
// 		mSceneMgr->getRootSceneNode()->attachObject(rc);
// 		rc->setCorners(0, 1, 0.6, -0.8);
// 		rc->setMaterial("Examples/SpaceSkyBox");
// 		rc->setVisible(true);
// 		rc->setVisibilityFlags(0xffffffff);
// 		rc->setRenderQueueGroup(RENDER_QUEUE_OVERLAY);
		

		OverlayManager& om = OverlayManager::getSingleton();

		om.addOverlayElementFactory(new LineOverlayElementFactory());
		om.addOverlayElementFactory(new ArrowOverlayElementFactory());

		Overlay* ol = om.create("testOl");
		PanelOverlayElement* olc = dynamic_cast<PanelOverlayElement*>(om.createOverlayElement("Panel", "testC"));
		
		ol->add2D(olc);
		//ol->add3D(mSceneMgr->getRootSceneNode());
		ol->show();

#if 0
		_arrow = dynamic_cast<ArrowOverlayElement*>(om.createOverlayElement("Arrow", "testArrow"));
		olc->addChild(_arrow);
		_arrow->setStartPoint(Vector2(10, 10));
		_arrow->setEndPoint(Vector2(100, 200));
#endif
		
		//ol->setScroll(0.5, -0.5);
		//ol->setScale(2, 1.5);
		//ol->setRotate(Radian(Degree(45)));

// 		TextAreaOverlayElement* ole = dynamic_cast<TextAreaOverlayElement*>(om.createOverlayElement("TextArea", "testt"));
// 		ole->setCaption("adkfa;dfka;dqpeorui13$!$`");
// 		ResourceHandle rh = FontManager::getSingleton().getResourceIterator().peekNextKey();
// 		String fnt = FontManager::getSingleton().getByHandle(rh)->getName();
// 		ole->setFontName(fnt);
// 		ole->setMetricsMode(Ogre::GMM_PIXELS);
// 		ole->setCharHeight(26);
// 		ole->setDimensions(300, 100);
// 		olc->addChild(ole);
// 
// 		ole = dynamic_cast<TextAreaOverlayElement*>(om.createOverlayElement("TextArea", "testt2"));
// 		ole->setCaption("~!@#@#%#$%$^&*^*((*)*(_+|`");		
// 		ole->setFontName(fnt);
// 		ole->setMetricsMode(Ogre::GMM_PIXELS);
// 		ole->setCharHeight(26);
// 		ole->setDimensions(300, 100);
// 		ole->setPosition(400, 400);	
// 		olc->addChild(ole);

// 		PanelGlyph* p = new PanelGlyph("testPanelGlyph");
// 		p->addToContainer(olc);
// 		p->setDimisions(200, 150);
// 		p->setPosition(100, 100);
		//p->setBorderColour(ColourValue::Green);
		//p->setFillColour(ColourValue::Blue);
		//p->setBorderMaterialName(head->getSubEntity(2)->getMaterialName());

// 		CaptionBar* cb = new CaptionBar("testCap", "~@~!#!@aBC123450;zc;vkl;LLL");
// 		cb->setPosition(100, 300);
// 		cb->setDimisions(10, 5);
// 		cb->addToContainer(olc);
// 		cb->setTextColour(ColourValue::White);

#if 0
 		GlyphBlock* gb = new GlyphBlock("testgb");
 		gb->addToContainer(olc);
		//gb->addToOverlay(ol);
		for (int i = 0; i < 20; ++i)
		{
			InputOutputSocket* inp = new InputOutputSocket(String("TestGB") + "/" + StringConverter::toString(i) + "/input", true, gb, "input", "float");
			gb->addInputSocket(inp);

			InputOutputSocket* oup = new InputOutputSocket(String("TestGB") + "/" + StringConverter::toString(i) + "/output", false, gb, "output", "float");
			gb->addOutputSocket(oup);
		}
 		gb->setPosition(400, 10);
 		gb->setDimisions(260, 200);
		gb->setCaption("ak;dfja;dfkad;sf0123456789-=\\|+_)(*&^%$#@!~`");



		GlyphBlock* gb2 = new GlyphBlock("testgb2");
		gb2->addToContainer(olc);
		for (int i = 0; i < 20; ++i)
		{
			InputOutputSocket* inp = new InputOutputSocket(String("TestGB2") + "/" + StringConverter::toString(i) + "/input", true, gb2, "input", "float");
			gb2->addInputSocket(inp);

			InputOutputSocket* oup = new InputOutputSocket(String("TestGB2") + "/" + StringConverter::toString(i) + "/output", false, gb2, "output", "float");
			gb2->addOutputSocket(oup);
		}
		//gb->addToOverlay(ol);
		gb2->setPosition(_blk1pos.x, _blk1pos.y);
		gb2->setDimisions(200, 200);
		gb2->setCaption("===========");
		_blk1 = gb2;

		for(int i = 0; i < 19; ++i)
		{
			ConnectionLine* c = new ConnectionLine(gb->getInputSocket(i), gb2->getOutputSocket(19 - i));
			c->addToContainer(olc);
		}
#endif

#if 0

		Material_DotProduct* dp = new Material_DotProduct("testMaterial_DotProduct");
		Vector2 pos(mt->getPosition() + Vector2(0, 80 + mt->getHeight()));
		dp->setPosition(pos.x, pos.y);
		dp->addToContainer(olc);

		Material_AutoConstant* ac = new Material_AutoConstant("testMaterial_AutoConstant");
		pos = Vector2(dp->getPosition() + Vector2(0, 10 + dp->getHeight()));
		ac->setPosition(pos.x, pos.y);
		ac->addToContainer(olc);

		Material_If* ifc = new Material_If("testMaterial_If");
		pos = Vector2(ac->getPosition() + Vector2(0, 10 + ac->getHeight()));
		ifc->setPosition(pos.x, pos.y);
		ifc->addToContainer(olc);

		Material_Multiply* mtl = new Material_Multiply("Material_Multiply");
		pos = Vector2(ifc->getPosition() + Vector2(ifc->getWidth(), 0));
		mtl->setPosition(pos.x + 80, 10);
		mtl->addToContainer(olc);
#endif

		Material_Root* mroot = new Material_Root("Material_Root");
		Vector2 pos = Vector2(10, 10);
		mroot->setPosition(pos.x, pos.y);
		ol->add2D(mroot->getRootContainer());

		Material_Technique* mtech = mroot->createTechnique("Default");
		mroot->addTechnique(mtech);
		pos = Vector2(300, 100);
		mtech->setPosition(pos.x, pos.y);
		ol->add2D(mtech->getRootContainer());

		Material_Pass* mpass = mtech->createPass();
		mtech->addPass(mpass);
		pos = Vector2(600, 200);
		mpass->setPosition(pos.x, pos.y);
		ol->add2D(mpass->getRootContainer());

		Material_TextureSampler* mt = new Material_TextureSampler("testMT");
		mt->setPosition(800, 300);
		mt->addToContainer(olc);
		mt->setTextureName("ogrelogo-small.jpg");


		ConnectionLine* c = new ConnectionLine(mpass->getInputSocket(0), mt->getOutputSocket(0));
		c->addToContainer(olc);

		_material = mroot->compile();
		//MaterialSerializer ms;
		//ms.queueForExport(mater);
		//ms.exportMaterial(mater, "mat.material");
		
#if 0
		LineOverlayElement* loe = dynamic_cast<LineOverlayElement*>(om.createOverlayElement("Line", "line1"));
		olc->addChild(loe);
		Vector2List pts;
#if 0
		pts.push_back(Vector2(0, 0));
		pts.push_back(Vector2(0.5, 0.5));
		pts.push_back(Vector2(0.5, 0.2));
		pts.push_back(Vector2(0.4, -0.2));
#else
		SimpleSpline ss;
		ss.addPoint(Vector3(0, 0, 0));
		ss.addPoint(Vector3(100, 100, 0));
		ss.addPoint(Vector3(120, 300, 0));
		ss.addPoint(Vector3(300, 20, 0));
		ss.addPoint(Vector3(500, 300, 0));
		ss.recalcTangents();

		for(int i = 0; i < 40; ++i)
		{
			Vector3 p = ss.interpolate((float)i / 40.0f);
			pts.push_back(Vector2(p.x, p.y));
		}
#	if 0
		pts.push_back(Vector2(0, 0));
		pts.push_back(Vector2(100, 100));
		pts.push_back(Vector2(120, 300));
		pts.push_back(Vector2(500, 0));
#	endif
#endif
		//loe->setMetricsMode(Ogre::GMM_PIXELS);
		loe->setPoints(pts);

		loe = dynamic_cast<LineOverlayElement*>(om.createOverlayElement("Line", "line12"));
		olc->addChild(loe);
		pts.clear();
		pts.push_back(Vector2(0, 0));
		pts.push_back(Vector2(500, 0));
		loe->setColour(ColourValue::Red);
		loe->setPoints(pts);

		loe = dynamic_cast<LineOverlayElement*>(om.createOverlayElement("Line", "line13"));
		olc->addChild(loe);
		pts.clear();
		pts.push_back(Vector2(0, 0));
		pts.push_back(Vector2(0, 300));
		loe->setColour(ColourValue::Red);
		loe->setPoints(pts);
		
		olc->setMetricsMode(Ogre::GMM_PIXELS);
		olc->setDimensions(300, 100);
		olc->setBorderSize(3, 3, 3, 3);
		olc->setBorderMaterialName(head->getSubEntity(0)->getMaterialName());
#endif
		/*
		// Create nodes for the lights to be rotated with
        mRedYellowLightsNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
        mGreenBlueLightsNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();


        // First create the BillboardSets. This will define the materials for the billboards
		// in its set to use
		mRedYellowLights = mSceneMgr->createBillboardSet("RedYellowLights");
		mRedYellowLights->setMaterialName("Examples/Flare");
		mRedYellowLightsNode->attachObject(mRedYellowLights);

		mGreenBlueLights = mSceneMgr->createBillboardSet("GreenBlueLights");
		mGreenBlueLights->setMaterialName("Examples/Flare");
		mGreenBlueLightsNode->attachObject(mGreenBlueLights);

		// Red light billboard, in "off" state
		Vector3 redLightPosition(78, -8, -70);
		mRedLightBoard = mRedYellowLights->createBillboard(redLightPosition);
		mRedLightBoard->setColour(ColourValue::Black);


		// Blue light billboard, in "off" state
		Vector3 blueLightPosition(-90, -8, -70);
		mBlueLightBoard = mGreenBlueLights->createBillboard(blueLightPosition);
		mBlueLightBoard->setColour(ColourValue::Black);


		// Yellow light billboard, in "off" state
		Vector3 yellowLightPosition(-4.5, 30, -80);
		mYellowLightBoard = mRedYellowLights->createBillboard(yellowLightPosition);
		mYellowLightBoard->setColour(ColourValue::Black);

		// Green light billboard, in "off" state
		Vector3 greenLightPosition(50, 70, 80);
		mGreenLightBoard = mGreenBlueLights->createBillboard(greenLightPosition);
		mGreenLightBoard->setColour(ColourValue::Black);

		// Red light, in "off" state
		mRedLight = mSceneMgr->createLight("RedFlyingLight");
		mRedLight->setType(Light::LT_POINT);
		mRedLight->setPosition(redLightPosition);
		mRedLight->setDiffuseColour(ColourValue::Black);
		mRedYellowLightsNode->attachObject(mRedLight);

		// Blue light, in "off" state
		mBlueLight = mSceneMgr->createLight("BlueFlyingLight");
		mBlueLight->setType(Light::LT_POINT);
		mBlueLight->setPosition(blueLightPosition);
		mBlueLight->setDiffuseColour(ColourValue::Black);
		mGreenBlueLightsNode->attachObject(mBlueLight);

		// Yellow light in "off" state
		mYellowLight = mSceneMgr->createLight("YellowFlyingLight");
		mYellowLight->setType(Light::LT_POINT);
		mYellowLight->setPosition(yellowLightPosition);
		mYellowLight->setDiffuseColour(ColourValue::Black);
		mRedYellowLightsNode->attachObject(mYellowLight);

		// Yellow light in "off" state
		mGreenLight = mSceneMgr->createLight("GreenFlyingLight");
		mGreenLight->setType(Light::LT_POINT);
		mGreenLight->setPosition(greenLightPosition);
		mGreenLight->setDiffuseColour(ColourValue::Black);
		mGreenBlueLightsNode->attachObject(mGreenLight);

		// Light flashers
		mRedLightFlasher = ControllerValueRealPtr(
            new LightFlasher(mRedLight, mRedLightBoard, ColourValue::Red));
		mBlueLightFlasher = ControllerValueRealPtr(
            new LightFlasher(mBlueLight, mBlueLightBoard, ColourValue::Blue));
		mYellowLightFlasher = ControllerValueRealPtr(
            new LightFlasher(mYellowLight, mYellowLightBoard, ColourValue(1.0, 1.0, 0.0)));
		mGreenLightFlasher = ControllerValueRealPtr(
            new LightFlasher(mGreenLight, mGreenLightBoard, ColourValue::Green));

		// Light controller functions
		mRedLightControllerFunc = ControllerFunctionRealPtr(
            new LightFlasherControllerFunction(Ogre::WFT_SINE, 0.5, 0.0));
		mBlueLightControllerFunc = ControllerFunctionRealPtr(
            new LightFlasherControllerFunction(Ogre::WFT_SINE, 0.75, 0.5));
		mYellowLightControllerFunc = ControllerFunctionRealPtr(
            new LightFlasherControllerFunction(Ogre::WFT_TRIANGLE, 0.25, 0.0));
		mGreenLightControllerFunc = ControllerFunctionRealPtr(
            new LightFlasherControllerFunction(Ogre::WFT_SINE, 0.25, 0.5));

		// Light controllers
		ControllerManager* mControllerManager = &ControllerManager::getSingleton();
		mRedLightController = mControllerManager->createController(mControllerManager->getFrameTimeSource(), mRedLightFlasher, mRedLightControllerFunc);
		mBlueLightController = mControllerManager->createController(mControllerManager->getFrameTimeSource(), mBlueLightFlasher, mBlueLightControllerFunc);
		mYellowLightController = mControllerManager->createController(mControllerManager->getFrameTimeSource(), mYellowLightFlasher, mYellowLightControllerFunc);
		mGreenLightController = mControllerManager->createController(mControllerManager->getFrameTimeSource(), mGreenLightFlasher, mGreenLightControllerFunc);

		*/

		//setupTrailLights();

    }

	void setupTrailLights(void)
	{
		mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
		Vector3 dir(-1, -1, 0.5);
		dir.normalise();
		Light* l = mSceneMgr->createLight("light1");
		l->setType(Light::LT_DIRECTIONAL);
		l->setDirection(dir);

		NameValuePairList pairList;
		pairList["numberOfChains"] = "3";
		pairList["maxElements"] = "80";
		RibbonTrail* trail = static_cast<RibbonTrail*>(
			mSceneMgr->createMovableObject("1", "RibbonTrail", &pairList));
		trail->setMaterialName("Examples/LightRibbonTrail");
		trail->setTrailLength(400);


		mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(trail);

		// Create 3 nodes for trail to follow
		SceneNode* animNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		animNode->setPosition(50,30,0);
		Animation* anim = mSceneMgr->createAnimation("an1", 14);
		anim->setInterpolationMode(Animation::IM_SPLINE);
		NodeAnimationTrack* track = anim->createNodeTrack(1, animNode);
		TransformKeyFrame* kf = track->createNodeKeyFrame(0);
		kf->setTranslate(Vector3(50,30,0));
		kf = track->createNodeKeyFrame(2);
		kf->setTranslate(Vector3(100, -30, 0));
		kf = track->createNodeKeyFrame(4);
		kf->setTranslate(Vector3(120, -100, 150));
		kf = track->createNodeKeyFrame(6);
		kf->setTranslate(Vector3(30, -100, 50));
		kf = track->createNodeKeyFrame(8);
		kf->setTranslate(Vector3(-50, 30, -50));
		kf = track->createNodeKeyFrame(10);
		kf->setTranslate(Vector3(-150, -20, -100));
		kf = track->createNodeKeyFrame(12);
		kf->setTranslate(Vector3(-50, -30, 0));
		kf = track->createNodeKeyFrame(14);
		kf->setTranslate(Vector3(50,30,0));

		AnimationState* animState = mSceneMgr->createAnimationState("an1");
		animState->setEnabled(true);
		mAnimStateList.push_back(animState);

		trail->setInitialColour(0, 1.0, 0.8, 0);
		trail->setColourChange(0, 0.1, 0.1, 0.1, 0.1);
		trail->setInitialWidth(0, 5);
		trail->setWidthChange(0, 0);
		//trail->setInitialWidth(0, 100);
		//trail->setWidthChange(0, 10);
		trail->setTrailLength(100);
		trail->setFaceToCamera(false);
		trail->setUseLocalPosition(false);

		trail->addNode(animNode);

		// Add light
		Light* l2 = mSceneMgr->createLight("l2");
		l2->setDiffuseColour(trail->getInitialColour(0));
		animNode->attachObject(l2);

		// Add billboard
		BillboardSet* bbs = mSceneMgr->createBillboardSet("bb", 1);
		bbs->createBillboard(Vector3::ZERO, trail->getInitialColour(0));
		bbs->setMaterialName("Examples/Flare");
		animNode->attachObject(bbs);

		animNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		animNode->setPosition(-50,100,0);
		anim = mSceneMgr->createAnimation("an2", 10);
		anim->setInterpolationMode(Animation::IM_SPLINE);
		track = anim->createNodeTrack(1, animNode);
		kf = track->createNodeKeyFrame(0);
		kf->setTranslate(Vector3(-50,100,0));
		kf = track->createNodeKeyFrame(2);
		kf->setTranslate(Vector3(-100, 150, -30));
		kf = track->createNodeKeyFrame(4);
		kf->setTranslate(Vector3(-200, 0, 40));
		kf = track->createNodeKeyFrame(6);
		kf->setTranslate(Vector3(0, -150, 70));
		kf = track->createNodeKeyFrame(8);
		kf->setTranslate(Vector3(50, 0, 30));
		kf = track->createNodeKeyFrame(10);
		kf->setTranslate(Vector3(-50,100,0));

		animState = mSceneMgr->createAnimationState("an2");
		animState->setEnabled(true);
		mAnimStateList.push_back(animState);

		trail->setInitialColour(1, 0.0, 1.0, 0.4);
		trail->setColourChange(1, 0.5, 0.5, 0.5, 0.5);
		//trail->setColourChange(1, ColourValue::ZERO);
		trail->addNode(animNode);


		// Add light
		l2 = mSceneMgr->createLight("l3");
		l2->setDiffuseColour(trail->getInitialColour(1));
		animNode->attachObject(l2);

		// Add billboard
		bbs = mSceneMgr->createBillboardSet("bb2", 1);
		bbs->createBillboard(Vector3::ZERO, trail->getInitialColour(1));
		bbs->setMaterialName("Examples/Flare");
		animNode->attachObject(bbs);


	}

	void createFrameListener(void)
    {
		// This is where we instantiate our own frame listener
        mFrameListener= new LightingListener(mWindow, mCamera);
        mRoot->addFrameListener(mFrameListener);

    }

};
