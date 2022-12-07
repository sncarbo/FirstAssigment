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
	pos = float3(-4.0f, 1.5f, 11.0f);
	front = -float3::unitZ;
	up = float3::unitY;
	movementSpeed = normal_movement_speed;
	rotationSpeed = 30.0f;
	rotationDeltaMatrix = float3x3::identity;
	center = float3(0.0f, 0.0f, 0.0f);
	maxProportionsModel = float3(0.0f, 0.0f, 0.0f);

	frustum.SetKind(frustumProjectiveSpace, frustumHandedness);
	frustum.SetViewPlaneDistances(nearPlane, farPlane);
	frustum.SetHorizontalFovAndAspectRatio(horizontalFov, aspectRatio);
	frustum.SetPos(pos);
	frustum.SetFront(front);
	frustum.SetUp(up);

	AdjustFovForModel();
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

	UpdateParameters();
	
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
	if(App->GetInput()->GetModelChange())
		AdjustFovForModel();

	if (App->GetInput()->CheckScanCode(SDL_SCANCODE_F) || App->GetInput()->GetModelChange())
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

void ModuleCamera::SetHorizontalFov(const float & horizontalFov)
{
	this->horizontalFov += -horizontalFov * rotationSpeed * App->GetSimpleDeltaTime();

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

void ModuleCamera::AdjustFovForModel()
{
	maxProportionsModel = App->GetRenderer()->GetModel()->GetMesh()->GetMaxProportions();
	horizontalFov = 2 * Atan(Sqrt(maxProportionsModel[0] * maxProportionsModel[0] + maxProportionsModel[1] * maxProportionsModel[1] + maxProportionsModel[2] * maxProportionsModel[2]) / 10.0f);
	
	if (horizontalFov < min_horizontal_fov)
		horizontalFov = min_horizontal_fov;
	else if (horizontalFov > max_horizontal_fov)
		horizontalFov = max_horizontal_fov;
	
	frustum.SetHorizontalFovAndAspectRatio(horizontalFov, aspectRatio);
}

void ModuleCamera::NormalMovementSpeed()
{
	movementSpeed = normal_movement_speed;
}

void ModuleCamera::DuplicateMovementSpeed()
{
	movementSpeed = 2 * normal_movement_speed;
}

void ModuleCamera::UpdateParameters()
{
	aspectRatio = App->GetWindow()->GetWidth() / App->GetWindow()->GetHeight();

	frustum.SetHorizontalFovAndAspectRatio(horizontalFov, aspectRatio);
	frustum.SetPos(pos);
	frustum.SetFront(front);
	frustum.SetUp(up);
}

void ModuleCamera::RotateCamera(const float3x3 & rotationDeltaMatrix)
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