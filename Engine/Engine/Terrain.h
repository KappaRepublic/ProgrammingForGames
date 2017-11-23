#pragma once

#include <d3d11.h>
#include <d3dx10math.h>
#include <stdio.h>

#include "textureclass.h"

const int TEXTURE_REPEAT = 8;

class Terrain {
private:
	struct VertexType {
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct HeightMapType {
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VectorType {
		float x, y, z;
	};

public:
	Terrain();
	Terrain(const Terrain& terrain);
	~Terrain();

	bool initialize(ID3D11Device* device, char* fileName, WCHAR* grassTex, WCHAR* slopeTex, WCHAR* rockTex, int width, int height);
	void shutDown();
	void render(ID3D11DeviceContext* deviceContext);

	int getIndexCount();

	ID3D11ShaderResourceView* getGrassTexture();
	ID3D11ShaderResourceView* getSlopeTexture();
	ID3D11ShaderResourceView* getRockTexture();

private:
	bool loadHeightMap(char* fileName);
	void normalizeHeightMap();
	bool calculateNormals();
	void shutDownHeightMap();

	void calculateTextureCoordinates();
	bool loadTextures(ID3D11Device* device, WCHAR* grassTex, WCHAR* slopeTex, WCHAR* rockTex);
	void releaseTextures();

	bool initializeBuffers(ID3D11Device* device);
	void shutDownBuffers();
	void renderBuffers(ID3D11DeviceContext* deviceContext);

	int terrainWidth, terrainHeight;
	int vertexCount, indexCount;
	ID3D11Buffer *vertexBuffer, *indexBuffer;
	HeightMapType* heightMap;
	TextureClass *grassTexture, *slopeTexture, *rockTexture;
};