#pragma once

#include <d3dx10math.h>

class Light
{
public:
	Light();
	Light(const Light&);
	~Light();

	void setAmbientColour(float r, float g, float b, float a);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);

	D3DXVECTOR4 getAmbientColour() { return m_ambientColour; };
	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();
	D3DXVECTOR4 GetSpecularColor();
	float GetSpecularPower();


private:
	D3DXVECTOR4 m_ambientColour;
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;
};
