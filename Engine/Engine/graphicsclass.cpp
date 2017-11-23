////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_input = 0;
	m_Model = 0;
	m_bumpModel = 0;
	skyBox = 0;
	m_fire = 0;
	m_textureShader = 0;
	m_LightShader = 0;
	m_bumpMapShader = 0;
	m_specMapShader = 0;
	m_fireShader = 0;
	m_terrainShader = 0;
	m_Light = 0;
	m_text = 0;
	m_ParticleShader = 0;
	m_ParticleSystem = 0;
	m_timer = 0;

	renderTexture1 = 0;
	renderTexture2 = 0;
	renderTexture3 = 0;
	renderTexture4 = 0;
	renderTexture5 = 0;
	renderTexture6 = 0;

	debugWindow1 = 0;
	debugWindow2 = 0;
	debugWindow3 = 0;
	debugWindow4 = 0;
	debugWindow5 = 0;
	debugWindow6 = 0;
	test = 0;
	terrain = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, InputSystem* input)
{
	bool result;
	D3DXMATRIX baseViewMatrix;

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the timer class
	m_timer = new TimerClass;
	if (!m_timer) {
		return false;
	}

	// Initialize the timer
	m_timer->Initialize();

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering.
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render(m_timer->GetTime());
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the input object
	m_input = input;

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -10.0f);
	
	

	// Create the model object.
	m_Model = new ModelClass;
	if(!m_Model)
	{
		return false;
	}

	// Initialize the model object.
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/Volcanic_glass_001_COLOR.png", L"../Engine/data/Volcanic_glass_001_NRM.png", 
		L"../Engine/data/Volcanic_glass_001_SPEC.png");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	test = new ModelClass;
	if (!test) {
		return false;
	}

	result = test->Initialize(m_D3D->GetDevice(), "../Engine/data/square.txt", L"../Engine/data/SkyBoxTex.jpg", NULL, NULL);
	if (!result) {
		return false;
	}

	skyBox = new ModelClass;
	if (!skyBox) {
		return false;
	}

	result = skyBox->Initialize(m_D3D->GetDevice(), "../Engine/data/skybox.txt", L"../Engine/data/SkyBoxTex.jpg", NULL, NULL);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_bumpModel = new ModelClass;
	if (!m_bumpModel) {
		return false;
	}

	result = m_bumpModel->Initialize(m_D3D->GetDevice(), "../Engine/data/laytonGold.txt", L"../Engine/data/gold.png", L"../Engine/data/Normal.png",
		L"../Engine/data/Bronze_002_SPEC.png");

	m_fire = new Terrain;
	if (!m_fire) {
		return false;
	}

	result = m_fire->initialize(m_D3D->GetDevice(), "../Engine/data/heightmap02.bmp", L"../Engine/data/water.png", L"../Engine/data/noise01.dds", L"../Engine/data/alpha01.dds", 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the fire object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_text = new TextClass;
	if (!m_text)
	{
		return false;
	}

	// Initialize the text object.
	result = m_text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object
	m_textureShader = new TextureShaderClass;
	if (!m_textureShader) {
		return false;
	}

	// Initialize the texture shader object
	result = m_textureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bump map shader object
	m_bumpMapShader = new BumpMapShaderClass;
	if (!m_bumpMapShader) {
		return false;
	}

	// Initialise the bump map shader object
	result = m_bumpMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the Bump Map Shader Object", L"Error", MB_OK);
		return false;
	}

	m_fireShader = new FireShaderClass;
	if (!m_fireShader) {
		return false;
	}

	result = m_fireShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the Fire Shader Object", L"Error", MB_OK);
	}

	// Create the specular map shader object.
	m_specMapShader = new SpecMapShaderClass;
	if (!m_specMapShader)
	{
		return false;
	}

	// Initialize the specular map shader object.
	result = m_specMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new Light;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->setAmbientColour(0.2f, 0.2f, 0.2f, 0.3f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.5f, -1.0f, 0.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);

	// Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader) {
		return false;
	}

	// Initialize the particle shader object.
	result = m_ParticleShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the particle shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the particle system object.
	m_ParticleSystem = new ParticleSystemClass;
	if (!m_ParticleSystem)
	{
		return false;
	}

	// Initialize the particle system object.
	// 0.5, 0.1, 2.0f
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/flare.png", 320.0f, 320.0f, 320.0f, 1.0f, 2.0f, 10.0f, 100000);
	if (!result)
	{
		return false;
	}

	// Create the render to texture object.
	renderTexture1 = new RenderTexture;
	if (!renderTexture1)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = renderTexture1->initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}
	// Create the render to texture object.
	renderTexture2 = new RenderTexture;
	if (!renderTexture2)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = renderTexture2->initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	// Create the render to texture object.
	renderTexture3 = new RenderTexture;
	if (!renderTexture3)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = renderTexture3->initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	// Create the render to texture object.
	renderTexture4 = new RenderTexture;
	if (!renderTexture4)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = renderTexture4->initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	// Create the render to texture object.
	renderTexture5 = new RenderTexture;
	if (!renderTexture5)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = renderTexture5->initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}

	// Create the render to texture object.
	renderTexture6 = new RenderTexture;
	if (!renderTexture6)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = renderTexture6->initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		return false;
	}


	// Create the debug window object.
	debugWindow1 = new DebugWindowClass;
	if (!debugWindow1)
	{
		return false;
	}

	// Initialize the debug window object.
	result = debugWindow1->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

	debugWindow2 = new DebugWindowClass;
	if (!debugWindow2)
	{
		return false;
	}

	// Initialize the debug window object.
	result = debugWindow2->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

	debugWindow3 = new DebugWindowClass;
	if (!debugWindow3)
	{
		return false;
	}

	// Initialize the debug window object.
	result = debugWindow3->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

	debugWindow4 = new DebugWindowClass;
	if (!debugWindow4)
	{
		return false;
	}

	// Initialize the debug window object.
	result = debugWindow4->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

	debugWindow5 = new DebugWindowClass;
	if (!debugWindow5)
	{
		return false;
	}

	// Initialize the debug window object.
	result = debugWindow5->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}

	debugWindow6 = new DebugWindowClass;
	if (!debugWindow6)
	{
		return false;
	}

	// Initialize the debug window object.
	result = debugWindow6->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, 100, 100);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the debug window object.", L"Error", MB_OK);
		return false;
	}


	// Initialize the terrain class 
	terrain = new Terrain;
	if (!terrain) {
		return false;
	}

	result = terrain->initialize(m_D3D->GetDevice(), "../Engine/data/heightmap01.bmp", L"../Engine/data/Rough_rock_012_COLOR.jpg", L"../Engine/data/slope.dds", L"../Engine/data/rock.dds", 100, 100);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the terrain object.", L"Error", MB_OK);
		return false;
	}

	// Create the terrain shader object

	m_terrainShader = new TerrainShader;
	if (!m_terrainShader) {
		return false;
	}
	 
	// Initialize the terrain shader object
	result = m_terrainShader->initialize(m_D3D->GetDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the terrain shader object", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the terrain shader object
	if (m_terrainShader) {
		m_terrainShader->shutDown();
		delete m_terrainShader;
		m_terrainShader = 0;
	}

	// Release the debug window object.
	if (debugWindow1)
	{
		debugWindow1->Shutdown();
		delete debugWindow1;
		debugWindow1 = 0;
	}

	if (debugWindow2)
	{
		debugWindow2->Shutdown();
		delete debugWindow2;
		debugWindow2 = 0;
	}

	if (debugWindow3)
	{
		debugWindow3->Shutdown();
		delete debugWindow3;
		debugWindow3 = 0;
	}

	if (debugWindow4)
	{
		debugWindow4->Shutdown();
		delete debugWindow4;
		debugWindow4 = 0;
	}

	if (debugWindow5)
	{
		debugWindow5->Shutdown();
		delete debugWindow5;
		debugWindow5 = 0;
	}

	if (debugWindow6)
	{
		debugWindow6->Shutdown();
		delete debugWindow6;
		debugWindow6 = 0;
	}
	// Release the render to texture object.
	if (renderTexture1)
	{
		renderTexture1->shutDown();
		delete renderTexture1;
		renderTexture1 = 0;
	}

	// Release the render to texture object.
	if (renderTexture2)
	{
		renderTexture2->shutDown();
		delete renderTexture2;
		renderTexture2 = 0;
	}

	// Release the render to texture object.
	if (renderTexture3)
	{
		renderTexture3->shutDown();
		delete renderTexture3;
		renderTexture3 = 0;
	}

	// Release the render to texture object.
	if (renderTexture4)
	{
		renderTexture4->shutDown();
		delete renderTexture4;
		renderTexture4 = 0;
	}

	// Release the render to texture object.
	if (renderTexture5)
	{
		renderTexture5->shutDown();
		delete renderTexture5;
		renderTexture5 = 0;
	}

	// Release the render to texture object.
	if (renderTexture6)
	{
		renderTexture6->shutDown();
		delete renderTexture6;
		renderTexture6 = 0;
	}

	// Release the input object
	if (m_input) {
		delete m_input;
		m_input = 0;
	}

	// Release the specular map shader object.
	if (m_specMapShader)
	{
		m_specMapShader->Shutdown();
		delete m_specMapShader;
		m_specMapShader = 0;
	}


	// Release the particle system object.
	if (m_ParticleSystem)
	{
		m_ParticleSystem->Shutdown();
		delete m_ParticleSystem;
		m_ParticleSystem = 0;
	}

	// Release the particle shader object.
	if (m_ParticleShader)
	{
		m_ParticleShader->Shutdown();
		delete m_ParticleShader;
		m_ParticleShader = 0;
	}

	// Release the text object.
	if (m_text)
	{
		m_text->Shutdown();
		delete m_text;
		m_text = 0;
	}

	// Release the texture shader object
	if (m_textureShader) {
		m_textureShader->Shutdown();
		delete m_textureShader;
		m_textureShader = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Release the bump map shader object
	if (m_bumpMapShader) {
		m_bumpMapShader->Shutdown();
		delete m_bumpMapShader;
		m_bumpMapShader = 0;
	}

	// Release the fire shader object
	if (m_fireShader) {
		m_fireShader->Shutdown();
		delete m_fireShader;
		m_fireShader = 0;
	}

	// Release the model object.
	if(m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	if (m_bumpModel) {
		m_bumpModel->Shutdown();
		delete m_bumpModel;
		m_bumpModel = 0;
	}

	// Release the fire object

	if (m_fire) {
		m_fire->shutDown();
		delete m_fire;
		m_fire = 0;
	}

	// Release the skyboc
	if (skyBox) {
		skyBox->Shutdown();
		delete skyBox;
		skyBox = 0;
	}

	if (test) {
		test->Shutdown();
		delete test;
		test = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	static float rotation = 0.0f;
	static float delta = 0.0f;

	// Update the timer
	m_timer->Frame();

	// Run the frame processing for the particle system.
	m_ParticleSystem->Frame(frameTime, m_D3D->GetDeviceContext());

	// Set the frames per second.
	result = m_text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}

	// Update the delta variable each frame. (keep this between 0 and 1)
	delta += 0.001;
	if(delta >1.0f)
	{
		delta -=1.0f;
	}

	// Update the camera
	updateCamera();
	
	// Render the graphics scene.
	result = Render(rotation, delta);
	if(!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::updateCamera() {
	if (m_input->getKeys().keyW) {
		m_Camera->moveForward();
	}
	else if (m_input->getKeys().keyS) {
		m_Camera->moveBackward();
	}
	if (m_input->getKeys().keyA) {
		m_Camera->rotateLeft();
	}
	else if (m_input->getKeys().keyD) {
		m_Camera->rotateRight();
	}

	if (m_input->getKeys().keyQ) {
		m_Camera->moveUpward();
	}
	else if (m_input->getKeys().keyE) {
		m_Camera->moveDownward();
	}

	if (m_input->getKeys().keyI) {
		m_Camera->rotateUpward();
	}
	else if (m_input->getKeys().keyK) {
		m_Camera->rotateDownward();
	}
}

bool GraphicsClass::Render(float rotation, float deltavalue)
{
	D3DXMATRIX worldMatrix, viewMatrix, orthoMatrix;
	bool result;

	float tempPosX, tempPosY, tempPosZ, tempRotX, tempRotY, tempRotZ;

	tempPosX = m_Camera->GetPosition().x;
	tempPosY = m_Camera->GetPosition().y;
	tempPosZ = m_Camera->GetPosition().z;

	tempRotX = m_Camera->GetRotation().x;
	tempRotY = m_Camera->GetRotation().y;
	tempRotZ = m_Camera->GetRotation().z;

	// Render the entire scene to the texture first.

	m_Camera->SetPosition(0.0f, 15.0f, 0.0f);
	m_Camera->SetRotation(0.0f, 0.0f, 0.0f);

	// Set the render target to be the render to texture.
	renderTexture1->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

	// Clear the render to texture.
	renderTexture1->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	result = renderToTexture(rotation, 1);
	if (!result)
	{
		return false;
	}

	m_Camera->SetRotation(0.0f, 90.0f, 0.0f);

	// Set the render target to be the render to texture.
	renderTexture2->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

	// Clear the render to texture.
	renderTexture2->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	result = renderToTexture(rotation, 2);
	if (!result)
	{
		return false;
	}

	m_Camera->SetRotation(0.0f, 180.0f, 0.0f);

	// Set the render target to be the render to texture.
	renderTexture3->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

	// Clear the render to texture.
	renderTexture3->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	result = renderToTexture(rotation, 3);
	if (!result)
	{
		return false;
	}

	m_Camera->SetRotation(0.0f, 270.0f, 0.0f);

	// Set the render target to be the render to texture.
	renderTexture4->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

	// Clear the render to texture.
	renderTexture4->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	result = renderToTexture(rotation, 4);
	if (!result)
	{
		return false;
	}

	m_Camera->SetRotation(90.0f, 0.0f, 0.0f);

	

	result = renderToTexture(rotation, 5);
	if (!result)
	{
		return false;
	}

	m_Camera->SetRotation(270.0f, 0.0f, 0.0f);

	// Set the render target to be the render to texture.
	renderTexture6->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

	// Clear the render to texture.
	renderTexture6->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);

	result = renderToTexture(rotation, 6);
	if (!result)
	{
		return false;
	}

	
	

	// m_D3D->GetDevice()->Render
	
	m_Camera->SetPosition(tempPosX, tempPosY, tempPosZ);
	m_Camera->SetRotation(tempRotX, tempRotY, tempRotZ);

	// m_Camera->SetRotation(0.0f, rotation, 0.0f);

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.3f, 0.8f, 1.0f);

	// Render the scene as normal to the back buffer.
	result = renderScene(rotation, true, true);
	if (!result)
	{
		return false;
	}

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	// Get the world, view, and ortho matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	
	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = debugWindow1->Render(m_D3D->GetDeviceContext(), 150, 150);
	if (!result)
	{
		return false;
	}

	// Render the debug window using the texture shader.
	result = m_textureShader->Render(m_D3D->GetDeviceContext(), debugWindow1->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, renderTexture1->getShaderResourceView());
	if (!result)
	{
		return false;
	}

	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = debugWindow2->Render(m_D3D->GetDeviceContext(), 250, 150);
	if (!result)
	{
		return false;
	}

	// Render the debug window using the texture shader.
	result = m_textureShader->Render(m_D3D->GetDeviceContext(), debugWindow2->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, renderTexture2->getShaderResourceView());
	if (!result)
	{
		return false;
	}

	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = debugWindow3->Render(m_D3D->GetDeviceContext(), 50, 150);
	if (!result)
	{
		return false;
	}

	// Render the debug window using the texture shader.
	result = m_textureShader->Render(m_D3D->GetDeviceContext(), debugWindow3->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, renderTexture3->getShaderResourceView());
	if (!result)
	{
		return false;
	}

	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = debugWindow4->Render(m_D3D->GetDeviceContext(), 350, 150);
	if (!result)
	{
		return false;
	}

	// Render the debug window using the texture shader.
	result = m_textureShader->Render(m_D3D->GetDeviceContext(), debugWindow4->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, renderTexture4->getShaderResourceView());
	if (!result)
	{
		return false;
	}

	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = debugWindow5->Render(m_D3D->GetDeviceContext(), 150, 250);
	if (!result)
	{
		return false;
	}

	// Render the debug window using the texture shader.
	result = m_textureShader->Render(m_D3D->GetDeviceContext(), debugWindow5->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, renderTexture5->getShaderResourceView());
	if (!result)
	{
		return false;
	}

	// Put the debug window vertex and index buffers on the graphics pipeline to prepare them for drawing.
	result = debugWindow6->Render(m_D3D->GetDeviceContext(), 150, 50);
	if (!result)
	{
		return false;
	}

	// Render the debug window using the texture shader.
	result = m_textureShader->Render(m_D3D->GetDeviceContext(), debugWindow6->GetIndexCount(), worldMatrix, viewMatrix,
		orthoMatrix, renderTexture6->getShaderResourceView());
	if (!result)
	{
		return false;
	}
	
	
	
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::renderToTexture(float rotation, int textureId) {
	bool result;

	switch (textureId) {
	case 1:
		// Set the render target to be the render to texture.
		renderTexture1->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

		// Clear the render to texture.
		renderTexture1->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 2:
		// Set the render target to be the render to texture.
		renderTexture2->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

		// Clear the render to texture.
		renderTexture2->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 3:
		// Set the render target to be the render to texture.
		renderTexture3->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

		// Clear the render to texture.
		renderTexture3->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 4:
		// Set the render target to be the render to texture.
		renderTexture4->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

		// Clear the render to texture.
		renderTexture4->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 5:
		// Set the render target to be the render to texture.
		renderTexture5->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

		// Clear the render to texture.
		renderTexture5->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	case 6:
		// Set the render target to be the render to texture.
		renderTexture6->setRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView());

		// Clear the render to texture.
		renderTexture6->clearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->getDepthStencilView(), 0.0f, 0.0f, 1.0f, 1.0f);
		break;
	default:
		break;
	}

	// Render the scene now and it will draw to the render to texture instead of the back buffer.
	result = renderScene(rotation, false, false);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->setBackBufferRenderTarget();

	return true;
}

bool GraphicsClass::renderScene(float rotation, bool drawText, bool drawModel) {
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
	D3DXMATRIX yRotation, translation;

	bool result;
	D3DXVECTOR3 scrollSpeeds, scales;
	D3DXVECTOR2 distortion1, distortion2, distortion3;
	float distortionScale, distortionBias;
	static float frameTime = 0.0f;

	// Increment the frame time counter.
	frameTime += 0.01f;
	if (frameTime > 1000.0f)
	{
		frameTime = 0.0f;
	}

	// Set the three scrolling speeds for the three different noise textures.
	scrollSpeeds = D3DXVECTOR3(0.3f, 0.6f, 0.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	// Generate the view matrix based on the camera's position.
	m_Camera->Render(m_timer->GetTime());

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);


	// SKYBOX /////////////////////////////////////////////////////////////////////////////////////////////////////////////

	m_D3D->TurnZBufferOff();

	D3DXMatrixTranslation(&worldMatrix, m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z);

	skyBox->Render(m_D3D->GetDeviceContext());

	result = m_textureShader->Render(m_D3D->GetDeviceContext(), skyBox->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		skyBox->GetTextureArray()[0]);

	m_D3D->TurnZBufferOn();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (drawText) {
		// Turn off the Z buffer to begin all 2D rendering.
		m_D3D->TurnZBufferOff();

		D3DXMatrixTranslation(&worldMatrix, 0.0f, 0.0f, 0.0f);


		// Turn on the alpha blending before rendering the text.
		m_D3D->TurnOnAlphaBlending();

		// Render the text strings.
		result = m_text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
		if (!result)
		{
			return false;
		}

		// Turn off alpha blending after rendering the text.
		m_D3D->TurnOffAlphaBlending();

		// Turn the Z buffer back on now that all 2D rendering has completed.
		m_D3D->TurnZBufferOn();
	}

	D3DXMatrixTranslation(&worldMatrix, -3.0f, 2.0f, 0.0f);



	

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixRotationY(&worldMatrix, rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_specMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_Model->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
		m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// D3DXMatrixTranslation(&worldMatrix, 0.0f, 2.5f, 0.0f);

	if (drawModel) {
		// Rotate the world matrix by the rotation value so that the triangle will spin.
		D3DXMatrixRotationY(&yRotation, rotation);
		D3DXMatrixTranslation(&translation, 0.0f, 3.0f, 50.0f);

		D3DXMatrixMultiply(&worldMatrix, &yRotation, &translation);

		m_bumpModel->Render(m_D3D->GetDeviceContext());

		result = m_bumpMapShader->Render(m_D3D->GetDeviceContext(), m_bumpModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
			m_bumpModel->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->getAmbientColour());
	}

	// Render the terrain
	D3DXMatrixTranslation(&worldMatrix, -100.0f, -6.0f, -100.0f);

	terrain->render(m_D3D->GetDeviceContext());

	result = m_terrainShader->render(m_D3D->GetDeviceContext(), terrain->getIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
		m_Light->getAmbientColour(), m_Light->GetDiffuseColor(), m_Light->GetDirection(), terrain->getGrassTexture(), terrain->getSlopeTexture(), terrain->getRockTexture());
	if (!result) {
		return false;
	}

	

	// Turn on alpha blending for the fire transparency.
	m_D3D->TurnOnAlphaBlending();

	D3DXMatrixTranslation(&worldMatrix, -100.0f, -3.0f, -100.0f);

	// Put the square model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_fire->render(m_D3D->GetDeviceContext());

	// Render the square model using the fire shader.
	result = m_fireShader->Render(m_D3D->GetDeviceContext(), m_fire->getIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_fire->getGrassTexture(), m_fire->getSlopeTexture(), m_fire->getRockTexture(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();

	// Turn on alpha blending.
	m_D3D->TurnOnAlphaBlending();

	D3DXMatrixTranslation(&worldMatrix, -3.0f, 1.0f, 0.0f);

	// Put the particle system vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_ParticleSystem->Render(m_D3D->GetDeviceContext());

	// Render the model using the texture shader.
	result = m_ParticleShader->Render(m_D3D->GetDeviceContext(), m_ParticleSystem->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_ParticleSystem->GetTexture());
	if (!result)
	{
		return false;
	}

	m_D3D->TurnOffAlphaBlending();

	


	return true;
}