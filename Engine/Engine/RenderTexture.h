#pragma once

#include <D3D11.h>

class RenderTexture {
public:
	RenderTexture();
	RenderTexture(const RenderTexture& renderTex);
	~RenderTexture();

	bool initialize(ID3D11Device* device, int textureWidth, int textureHeight);
	void shutDown();

	void setRenderTarget(ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthStencilView);
	void clearRenderTarget(ID3D11DeviceContext* deviceContext, ID3D11DepthStencilView* depthStencilView, float red, float green, float blue, float alpha);
	ID3D11ShaderResourceView* getShaderResourceView();

private:
	ID3D11Texture2D* renderTargetTexture;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11ShaderResourceView* shaderResourceView;
};
