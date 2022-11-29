#pragma once
#include "Globals.h"
#include "Module.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "glew.h"
#include "Geometry/Frustum.h"
#include "Math/float3x3.h"

class ModuleCamera: public Module
{
public:
	ModuleCamera();
	~ModuleCamera();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	void MoveFront();
	void MoveBack();
	void MoveRight();
	void MoveLeft();
	void ZoomIn();
	void ZoomOut();
	void Orbit();
	void Focus();
	void NormalMovementSpeed();
	void DuplicateMovementSpeed();

	void RotateCamera(float3x3 rotationDeltaMatrix);

	Frustum GetFrustum() const;

private:
	const float normal_movement_speed = 0.015625;

	Frustum frustum;

	FrustumProjectiveSpace frustumProjectiveSpace;
	FrustumHandedness frustumHandedness;
	float nearPlane;
	float farPlane;
	float horizontalFov;
	float aspectRatio;
	float3 pos;
	float3 front;
	float3 up;

	float movementSpeed;
};