////////////////////////////////////////////////////////////////////////////////
// Filename: Light.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Light.h"


Light::Light()
{
}


Light::Light(const Light& other)
{
}


Light::~Light()
{
}

void Light::SetSpecularColor(float red, float green, float blue, float alpha)
{
	m_specularColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}


void Light::SetSpecularPower(float power)
{
	m_specularPower = power;
	return;
}

void Light::setAmbientColour(float r, float g, float b, float a)
{
	m_ambientColour = D3DXVECTOR4(r, g, b, a);
	return;
}

void Light::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
	return;
}


void Light::SetDirection(float x, float y, float z)
{
	m_direction = D3DXVECTOR3(x, y, z);
	return;
}


D3DXVECTOR4 Light::GetDiffuseColor()
{
	return m_diffuseColor;
}


D3DXVECTOR3 Light::GetDirection()
{
	return m_direction;
}

D3DXVECTOR4 Light::GetSpecularColor()
{
	return m_specularColor;
}


float Light::GetSpecularPower()
{
	return m_specularPower;
}