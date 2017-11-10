////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "bumpmapshaderclass.h"
#include "FireShaderClass.h"
#include "SpecShaderClass.h"
#include "textureshaderclass.h"
#include "lightclass.h"
#include "textclass.h"
#include "timerclass.h"
#include "KeyInput.h"

#include "ParticleShaderClass.h"
#include "ParticleSystemClass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd, InputClass* input);
	void Shutdown();
	bool Frame(int fps, int cpu, float frameTime);

private:
	void updateCamera();
	bool Render(float, float);

private:
	D3DClass* m_D3D;
	InputClass* m_input;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ModelClass* m_bumpModel;
	ModelClass* m_fire;
	TextureShaderClass* m_textureShader;
	LightShaderClass* m_LightShader;
	BumpMapShaderClass* m_bumpMapShader;
	FireShaderClass* m_fireShader;
	SpecMapShaderClass* m_specMapShader;
	LightClass* m_Light;
	TextClass* m_text;
	TimerClass* m_timer;

	// Skybox
	ModelClass* skyBox;

	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;
};

#endif