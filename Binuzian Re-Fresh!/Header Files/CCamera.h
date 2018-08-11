/* * * * * * * * * * * * * * * * * * * * * * * *
*	File Name *	CCamera.h				 	   *
*	   Author *	Basilius Bias Astho Christyono *
* Website URL * bifeldy.blogspot.com		   *
*       Email *	bifeldy@gmail.com              *
* Description *	Camera Management			   *
*  Created On *	15/06/2018					   *
* * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#include "../Header Files/stdafx.h"

class CCamera
{
public:
	CCamera();
	void CreateProjectionMatrix(float fov, float aspect, float nearPlane, float farPlane);
	void MoveForward(float units);
	void Strafe(float units);
	void MoveUp(float units);

	void Yaw(float radians);
	void Pitch(float radians);
	void Roll(float radians);
	void Update();
	BOOL SphereInFrustum(D3DXVECTOR3* pPosition, float radius);

	void SetPosition(D3DXVECTOR3* pPosition);
	void SetLookAt(D3DXVECTOR3* pLookAt);
	void SetFOV(float fov) { CreateProjectionMatrix(fov, m_aspect, m_nearPlane, m_farPlane); }
	void SetAspectRatio(float aspect) { CreateProjectionMatrix(m_fov, aspect, m_nearPlane, m_farPlane); }
	void SetNearPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, plane, m_farPlane); }
	void SetFarPlane(float plane) { CreateProjectionMatrix(m_fov, m_aspect, m_nearPlane, plane); }
	void SetMaxVelocity(float maxVelocity) { m_maxVelocity = maxVelocity; }
	void SetInvertY(BOOL invert) { m_invertY = invert; }
	void SetMaxPitch(float maxPitch) { m_maxPitch = maxPitch; }

	D3DXMATRIX* GetViewMatrix() { return &m_view; }
	D3DXMATRIX* GetProjectionMatrix() { return &m_projection; }
	D3DXVECTOR3* GetPosition() { return &m_position; }
	D3DXVECTOR3* GetLookAt() { return &m_lookAt; }
	float GetFOV() { return m_fov; }
	float GetAspectRatio() { return m_aspect; }
	float GetNearPlane() { return m_nearPlane; }
	float GetFarPlane() { return m_farPlane; }
	float GetMaxVelocity() { return m_maxVelocity; }
	BOOL  GetInvertY() { return m_invertY; }
	float GetPitch() { return m_pitch; }
	float GetYaw() { return m_yaw; }
	float GetMaxPitch() { return m_maxPitch; }

private:
	void BuildViewFrustum();

	D3DXMATRIX  m_view;
	D3DXMATRIX  m_projection;
	D3DXVECTOR3 m_right;
	D3DXVECTOR3 m_up;
	D3DXVECTOR3 m_look;
	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_lookAt;
	D3DXVECTOR3 m_velocity;
	D3DXPLANE   m_frustum[6];
	float       m_yaw;
	float       m_pitch;
	float       m_maxPitch;
	float       m_maxVelocity;
	float       m_fov;
	float       m_aspect;
	float       m_nearPlane;
	float       m_farPlane;
	BOOL        m_invertY;
	BOOL        m_enableYMovement;
};