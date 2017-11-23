#pragma once

#include <d3d11.h>
#include <D3DX10math.h>
#include <D3DX11async.h>
#include <fstream>
using namespace std;

class TerrainShader
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct LightBufferType
	{
		D3DXVECTOR4 ambientColour;
		D3DXVECTOR4 diffuseColour;
		D3DXVECTOR3 lightDirection;
		float padding;
	};

public:
	TerrainShader();
	TerrainShader(const TerrainShader& other);
	~TerrainShader();

	bool initialize(ID3D11Device*, HWND);
	void shutDown();
	bool render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3, ID3D11ShaderResourceView* grassTexture, ID3D11ShaderResourceView* slopeTexture, ID3D11ShaderResourceView* rockTexture);

private:
	bool initializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void shutDownShader();
	void outputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool setShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXVECTOR4, D3DXVECTOR4, D3DXVECTOR3, ID3D11ShaderResourceView* grassTexture, ID3D11ShaderResourceView* slopeTexture, ID3D11ShaderResourceView* rockTexture);
	void renderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11InputLayout* layout;
	ID3D11SamplerState* sampleState;
	ID3D11Buffer* matrixBuffer;
	ID3D11Buffer* lightBuffer;
};