#pragma once

#include <d3d11.h>
#include <d3dx10math.h>

#include "textureclass.h"

class Bitmap {
private:
	struct VertexType {
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	Bitmap();
	Bitmap(const Bitmap& other);
	~Bitmap();

	bool initialize(ID3D11Device* device, int screenWidth, int screenHeight, WCHAR* textureFilename, int bitmapWidth, int bitmapHeight);
	void shutDown();
	bool render(ID3D11DeviceContext* deviceContext, int positionX, int positionY);

	int getIndexCount();
	ID3D11ShaderResourceView* getTexture();

private:
	bool initializeBuffers(ID3D11Device* device);
	void shutDownBuffers();
	bool updateBuffers(ID3D11DeviceContext*, int, int);
	void renderBuffers(ID3D11DeviceContext*);

	bool loadTexture(ID3D11Device*, WCHAR*);
	void releaseTexture();

private:
	ID3D11Buffer *vertexBuffer, *indexBuffer;
	int vertexCount, indexCount;
	TextureClass* texture;

	int screenWidth, screenHeight;
	int bitmapWidth, bitmapHeight;
	int previousPosX, previousPosY;
};