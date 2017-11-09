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
	m_fire = 0;
	m_LightShader = 0;
	m_bumpMapShader = 0;
	m_specMapShader = 0;
	m_fireShader = 0;
	m_Light = 0;
	m_text = 0;
	m_ParticleShader = 0;
	m_ParticleSystem = 0;
	m_timer = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, InputClass* input)
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
	result = m_Model->Initialize(m_D3D->GetDevice(), "../Engine/data/cube.txt", L"../Engine/data/Volcanic_glass_001_COLOR.png", L"../Engine/data/Volcanic_glass_001_NRM.png", 
		L"../Engine/data/Volcanic_glass_001_SPEC.png");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_bumpModel = new ModelClass;
	if (!m_bumpModel) {
		return false;
	}

	result = m_bumpModel->Initialize(m_D3D->GetDevice(), "../Engine/data/sphere.txt", L"../Engine/data/Bronze_002_COLOR.png", L"../Engine/data/Bronze_002_NRM.png",
		L"../Engine/data/Bronze_002_SPEC.png");

	m_fire = new ModelClass;
	if (!m_fire) {
		return false;
	}

	result = m_fire->Initialize(m_D3D->GetDevice(), "../Engine/data/square.txt", L"../Engine/data/water.jpg", L"../Engine/data/noise01.dds", L"../Engine/data/alpha01.dds");
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
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->setAmbientColour(0.2f, 0.2f, 0.2f, 0.3f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(1.0f, 0.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);

	// Create the particle shader object.
	m_ParticleShader = new ParticleShaderClass;
	if (!m_ParticleShader)
	{
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
	result = m_ParticleSystem->Initialize(m_D3D->GetDevice(), L"../Engine/data/smoke.png");
	if (!result)
	{
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
		m_fire->Shutdown();
		delete m_fire;
		m_fire = 0;
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
	static float delta =0.0f;

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
}

bool GraphicsClass::Render(float rotation, float deltavalue)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix;
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
	scrollSpeeds = D3DXVECTOR3(1.3f, 2.1f, 2.3f);

	// Set the three scales which will be used to create the three different noise octave textures.
	scales = D3DXVECTOR3(1.0f, 2.0f, 3.0f);

	// Set the three different x and y distortion factors for the three different noise textures.
	distortion1 = D3DXVECTOR2(0.1f, 0.2f);
	distortion2 = D3DXVECTOR2(0.1f, 0.3f);
	distortion3 = D3DXVECTOR2(0.1f, 0.1f);

	// The the scale and bias of the texture coordinate sampling perturbation.
	distortionScale = 0.8f;
	distortionBias = 0.5f;

	// m_Camera->SetRotation(0.0f, rotation, 0.0f);

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.3f, 0.8f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render(m_timer->GetTime());

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

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

	D3DXMatrixTranslation(&worldMatrix, -3.0f, 2.0f, 0.0f);

	// Turn on alpha blending.
	m_D3D->TurnOnAlphaBlending();

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

	// Turn on alpha blending for the fire transparency.
	m_D3D->TurnOnAlphaBlending();

	D3DXMatrixTranslation(&worldMatrix, 3.0f, 0.0f, 0.0f);

	// Put the square model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_fire->Render(m_D3D->GetDeviceContext());

	// Render the square model using the fire shader.
	result = m_fireShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_fire->getTexture1(), m_fire->getTexture2(), m_fire->getTexture3(), frameTime, scrollSpeeds,
		scales, distortion1, distortion2, distortion3, distortionScale, distortionBias);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending.
	m_D3D->TurnOffAlphaBlending();

	// Rotate the world matrix by the rotation value so that the triangle will spin.
	D3DXMatrixRotationY(&worldMatrix, rotation);

	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_Model->Render(m_D3D->GetDeviceContext());

	// Render the model using the light shader.
	result = m_specMapShader->Render(m_D3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
								   m_Model->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Camera->GetPosition(),
									m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	D3DXMatrixTranslation(&worldMatrix, 0.0f, 2.5f, 0.0f);

	m_bumpModel->Render(m_D3D->GetDeviceContext());

	result = m_bumpMapShader->Render(m_D3D->GetDeviceContext(), m_bumpModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_bumpModel->GetTextureArray(), m_Light->GetDirection(), m_Light->GetDiffuseColor(), m_Light->getAmbientColour());
	

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}