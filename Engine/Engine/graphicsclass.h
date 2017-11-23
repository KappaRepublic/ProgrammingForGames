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
#include "TerrainShaderClass.h"
#include "Light.h"
#include "textclass.h"
#include "timerclass.h"
#include "KeyInput.h"
#include "Terrain.h"

#include "RenderTexture.h"
#include "DebugWindow.h"

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

	bool Initialize(int screenWidth, int screenHeight, HWND hwnd, InputSystem* input);
	void Shutdown();
	bool Frame(int fps, int cpu, float frameTime);

private:
	bool renderToTexture(float rotation, int textureId);
	bool renderScene(float rotation, bool drawText);

	void updateCamera();
	void createEnvironmentMap();
	bool Render(float, float);

private:
	D3DClass* m_D3D;
	InputSystem* m_input;
	CameraClass* m_Camera;
	ModelClass* m_Model;
	ModelClass* m_bumpModel;
	ModelClass* m_fire;
	TextureShaderClass* m_textureShader;
	LightShaderClass* m_LightShader;
	BumpMapShaderClass* m_bumpMapShader;
	FireShaderClass* m_fireShader;
	SpecMapShaderClass* m_specMapShader;
	TerrainShader* m_terrainShader;
	Light* m_Light;
	TextClass* m_text;
	TimerClass* m_timer;

	Terrain* terrain;

	// Skybox
	ModelClass* skyBox;

	RenderTexture* renderTexture1;
	RenderTexture* renderTexture2;
	RenderTexture* renderTexture3;
	RenderTexture* renderTexture4;
	RenderTexture* renderTexture5;
	RenderTexture* renderTexture6;

	DebugWindowClass* debugWindow1;
	DebugWindowClass* debugWindow2;
	DebugWindowClass* debugWindow3;
	DebugWindowClass* debugWindow4;
	DebugWindowClass* debugWindow5;
	DebugWindowClass* debugWindow6;
	ModelClass* test;

	ParticleShaderClass* m_ParticleShader;
	ParticleSystemClass* m_ParticleSystem;
};

#endif