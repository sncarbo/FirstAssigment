#include "ModuleCamera.h"

ModuleCamera::ModuleCamera()
{
	frustumProjectiveSpace = FrustumSpaceGL;
	frustumHandedness = FrustumRightHanded;
	nearPlane = 0.1f;
	farPlane = 200.0f;
	horizontalFov = DegToRad(90.0f);
	aspectRatio = SCREEN_WIDTH / SCREEN_HEIGHT;
	pos = float3(0.0f, 2.0f, -5.0f);
	front = float3::unitZ;
	up = float3::unitY;
	movementSpeed = normal_movement_speed;
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	frustum.SetKind(frustumProjectiveSpace, frustumHandedness);
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetHorizontalFovAndAspectRatio(horizontalFov, aspectRatio);
	frustum.SetPos(pos);
	frustum.SetFront(front);
	frustum.SetUp(up);

	Focus();

	return true;
}

update_status ModuleCamera::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::Update()
{
	if (App->GetInput()->CheckScanCode(SDL_SCANCODE_LSHIFT) || App->GetInput()->CheckScanCode(SDL_SCANCODE_RSHIFT))
		DuplicateMovementSpeed();
	else
		NormalMovementSpeed();

	if (App->GetInput()->CheckScanCode(SDL_SCANCODE_W))
		MoveFront();
	else if (App->GetInput()->CheckScanCode(SDL_SCANCODE_S))
		MoveBack();
	else if (App->GetInput()->CheckScanCode(SDL_SCANCODE_A))
		MoveLeft();
	else if (App->GetInput()->CheckScanCode(SDL_SCANCODE_D))
		MoveRight();

	if (App->GetInput()->Scroll())
		Zoom();

	UpdateFrustumParameters();
	
	return UPDATE_CONTINUE;
}

update_status ModuleCamera::PostUpdate()
{
	return UPDATE_CONTINUE;
}

bool ModuleCamera::CleanUp()
{
	return true;
}

void ModuleCamera::SetHorizontalFov(float horizontalFov)
{
	this->horizontalFov -= horizontalFov;

	if (this->horizontalFov < min_horizontal_fov)
		this->horizontalFov = min_horizontal_fov;
	else if (this->horizontalFov > max_horizontal_fov)
		this->horizontalFov = max_horizontal_fov;
}

void ModuleCamera::MoveFront()
{
	pos = pos + frustum.Front() * movementSpeed;
}

void ModuleCamera::MoveBack()
{
	pos = pos - frustum.Front() * movementSpeed;
}

void ModuleCamera::MoveRight()
{
	pos = pos + frustum.WorldRight() * movementSpeed;
}

void ModuleCamera::MoveLeft()
{
	pos = pos - frustum.WorldRight() * movementSpeed;
}

void ModuleCamera::Zoom()
{
	SetHorizontalFov(App->GetInput()->GetMouseWheel());
}

void ModuleCamera::Orbit()
{

}

void ModuleCamera::Focus()
{

}

void ModuleCamera::NormalMovementSpeed()
{
	movementSpeed = normal_movement_speed;
}

void ModuleCamera::DuplicateMovementSpeed()
{
	movementSpeed = 2 * normal_movement_speed;
}

void ModuleCamera::UpdateFrustumParameters()
{
	frustum.SetHorizontalFovAndAspectRatio(horizontalFov, aspectRatio);
	frustum.SetPos(pos);
	frustum.SetFront(front);
	frustum.SetUp(up);
}

void ModuleCamera::RotateCamera(float3x3 rotationDeltaMatrix)
{
	vec oldFront = frustum.Front().Normalized();
	frustum.SetFront(rotationDeltaMatrix * oldFront);

	vec oldUp = frustum.Up().Normalized();
	frustum.SetUp(rotationDeltaMatrix * oldUp);
}

Frustum ModuleCamera::GetFrustum() const
{
	return frustum;
}