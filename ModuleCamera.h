#pragma once
#include "Globals.h"
#include "Module.h"
#include "Application.h"

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

	void CalculateMovementSpeed();
	void CalculateMouseDownDerivatives();
	void CalculateAuxiliaryDerivatives();
	void CalculateMouseWheelDerivatives();

	void SetHorizontalFov(float horizontalFov);

	void MoveFront();
	void MoveBack();
	void MoveRight();
	void MoveLeft();
	void Zoom();
	void Orbit();
	void Focus();
	void NormalMovementSpeed();
	void DuplicateMovementSpeed();

	void UpdateFrustumParameters();
	void RotateCamera(float3x3 rotationDeltaMatrix);

	Frustum GetFrustum() const;

private:
	const float min_horizontal_fov = 1.0;
	const float max_horizontal_fov = 2.0;
	const float normal_movement_speed = 3;

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
	float rotationSpeed;

	float3x3 rotationDeltaMatrix;

	float3 center;
};