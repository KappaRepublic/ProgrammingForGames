////////////////////////////////////////////////////////////////////////////////
// Filename: cameraclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _CAMERACLASS_H_
#define _CAMERACLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3dx10math.h>
#include "inputclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: CameraClass
////////////////////////////////////////////////////////////////////////////////
class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	void setFrameTime(float time) {
		frameTime = time;
	};

	void moveForward();
	void moveBackward();
	void moveUpward();
	void moveDownward();
	void rotateLeft();
	void rotateRight();
	void rotateUpward();
	void rotateDownward();

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render(float time);
	void GetViewMatrix(D3DXMATRIX&);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;

	float velocity, frameTime;
};

#endif