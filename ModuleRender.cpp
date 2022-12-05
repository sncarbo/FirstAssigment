#include "ModuleRender.h"

ModuleRender::ModuleRender()
{
}

ModuleRender::~ModuleRender()
{
}

void ModuleRender::InitSDL()
{
	LOG2("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	context = SDL_GL_CreateContext(App->GetWindow()->window);
}

void ModuleRender::InitGlew()
{
	glewInit();

	LOG2("Using Glew %s", glewGetString(GLEW_VERSION));
	LOG2("Vendor: %s", glGetString(GL_VENDOR));
	LOG2("Renderer: %s", glGetString(GL_RENDERER));
	LOG2("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG2("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
}

bool ModuleRender::Init()
{
	InitSDL();
	InitGlew();

	model = new Model();
	model->Load();

	program = new ShadersProgram();

	return true;
}

update_status ModuleRender::PreUpdate()
{
	int width, height;
	SDL_GetWindowSize(App->GetWindow()->window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0.4f, 0.4f, 0.5f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

update_status ModuleRender::Update()
{
	SDL_GetWindowSize(App->GetWindow()->window, &width, &height);

	Draw();

	App->GetDebugDraw()->DrawSquareGrid(square_grid_mins, square_grid_maxs, square_grid_y, square_grid_step, dd::colors::Black);

	App->GetDebugDraw()->Draw(App->GetCamera()->GetFrustum().ViewMatrix(), App->GetCamera()->GetFrustum().ProjectionMatrix(), App->GetWindow()->GetWidth(), App->GetWindow()->GetHeight());
	
	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->GetWindow()->window);

	return UPDATE_CONTINUE;
}

bool ModuleRender::CleanUp()
{
	LOG2("Destroying renderer");

	glDeleteBuffers(1, &VBO);

	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRender::SetModel(const char* path)
{
	model->Load(path);
}

void ModuleRender::SetTexture(const char* path)
{
	model->LoadMaterials(nullptr, path);
}

Model* ModuleRender::GetModel() const
{
	return model;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	this->width = width;
	this->height = height;
}

void* ModuleRender::GetContext()
{
	return context;
}

ShadersProgram* ModuleRender::GetProgram() const
{
	return program;
}

void ModuleRender::Draw()
{
	model->GetMesh()->Draw(model->GetMaterial(), float4x4::identity);
}


