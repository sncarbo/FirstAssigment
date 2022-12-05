#include "ModuleCamera.h"

ModuleCamera::ModuleCamera()
{
}

ModuleCamera::~ModuleCamera()
{
}

bool ModuleCamera::Init()
{
	frustumProjectiveSpace = FrustumSpaceGL;
	frustumHandedness = FrustumRightHanded;
	nearPlane = 0.1f;
	farPlane = 200.0f;
	horizontalFov = DegToRad(90.0f);
	aspectRatio = App->GetWindow()->GetWidth() / App->GetWindow()->GetHeight();
	pos = float3(0.0f, 2.0f, -5.0f);
	front = float3::unitZ;
	up = float3::unitY;
	movementSpeed = normal_movement_speed;
	rotationSpeed = 10.0f;
	rotationDeltaMatrix = float3x3::identity;
	center = float3(0.0f, 0.0f, 0.0f);

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
	CalculateMovementSpeed();
	CalculateMouseDownDerivatives();
	CalculateAuxiliaryDerivatives();
	CalculateMouseWheelDerivatives();
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

void ModuleCamera::CalculateMovementSpeed()
{
	if (App->GetInput()->CheckScanCode(SDL_SCANCODE_LSHIFT) || App->GetInput()->CheckScanCode(SDL_SCANCODE_RSHIFT))
		DuplicateMovementSpeed();
	else
		NormalMovementSpeed();
}

void ModuleCamera::CalculateMouseDownDerivatives()
{
	if (App->GetInput()->GetRightMouseDown())
	{
		if (App->GetInput()->CheckScanCode(SDL_SCANCODE_W))
			MoveFront();
		if (App->GetInput()->CheckScanCode(SDL_SCANCODE_S))
			MoveBack();
		if (App->GetInput()->CheckScanCode(SDL_SCANCODE_A))
			MoveLeft();
		if (App->GetInput()->CheckScanCode(SDL_SCANCODE_D))
			MoveRight();

		if (App->GetInput()->GetMouseMotionX() || App->GetInput()->GetMouseMotionY())
		{

			if (App->GetInput()->GetMouseMotionX())
			{
				rotationDeltaMatrix = rotationDeltaMatrix * frustum.ViewMatrix().RotatePart().RotateY(DegToRad(App->GetInput()->GetMouseX() * rotationSpeed * App->GetSimpleDeltaTime()));
			}

			if (App->GetInput()->GetMouseMotionY())
			{
				rotationDeltaMatrix = rotationDeltaMatrix * frustum.ViewMatrix().RotatePart().RotateAxisAngle(frustum.WorldRight(), DegToRad(App->GetInput()->GetMouseY() * rotationSpeed * App->GetSimpleDeltaTime()));
			}

			RotateCamera(rotationDeltaMatrix);
		}
	}
}

void ModuleCamera::CalculateAuxiliaryDerivatives()
{
	if (App->GetInput()->CheckScanCode(SDL_SCANCODE_F))
		Focus();
	
	if ((App->GetInput()->CheckScanCode(SDL_SCANCODE_LALT) || App->GetInput()->CheckScanCode(SDL_SCANCODE_RALT))
		&& App->GetInput()->GetLeftMouseDown())
		Orbit();
}

void ModuleCamera::CalculateMouseWheelDerivatives()
{
	if (App->GetInput()->Scroll())
		Zoom();
}

void ModuleCamera::SetHorizontalFov(float horizontalFov)
{
	this->horizontalFov += -horizontalFov * App->GetSimpleDeltaTime();

	if (this->horizontalFov < min_horizontal_fov)
		this->horizontalFov = min_horizontal_fov;
	else if (this->horizontalFov > max_horizontal_fov)
		this->horizontalFov = max_horizontal_fov;
}

void ModuleCamera::MoveFront()
{
	pos = pos + frustum.Front() * movementSpeed * App->GetSimpleDeltaTime();
}

void ModuleCamera::MoveBack()
{
	pos = pos - frustum.Front() * movementSpeed * App->GetSimpleDeltaTime();
}

void ModuleCamera::MoveRight()
{
	pos = pos + frustum.WorldRight() * movementSpeed * App->GetSimpleDeltaTime();
}

void ModuleCamera::MoveLeft()
{
	pos = pos - frustum.WorldRight() * movementSpeed * App->GetSimpleDeltaTime();
}

void ModuleCamera::Zoom()
{
	SetHorizontalFov(App->GetInput()->GetMouseWheel());
}

void ModuleCamera::Orbit()
{
	pos = ((pos - center) * frustum.ViewMatrix().RotatePart().RotateAxisAngle(up.Normalized(), DegToRad(App->GetInput()->GetMouseX() * rotationSpeed * App->GetSimpleDeltaTime()))
		* frustum.ViewMatrix().RotatePart().RotateAxisAngle(frustum.WorldRight().Normalized(), DegToRad(App->GetInput()->GetMouseY()) * rotationSpeed * App->GetSimpleDeltaTime()));

	RotateCamera(float3x3::LookAt(frustum.Front(), (center - pos).Normalized(), frustum.Up(), float3::unitY));
}

void ModuleCamera::Focus()
{
	center = App->GetRenderer()->GetModel()->GetCenter();
	RotateCamera(float3x3::LookAt(frustum.Front(), (center - pos).Normalized(), frustum.Up(), float3::unitY));
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
	front = rotationDeltaMatrix * oldFront;

	vec oldUp = frustum.Up().Normalized();
	up = rotationDeltaMatrix * oldUp;

	this->rotationDeltaMatrix = float3x3::identity;
}

Frustum ModuleCamera::GetFrustum() const
{
	return frustum;
}