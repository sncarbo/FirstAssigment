#include "ModuleEditor.h"

using namespace std;


ModuleEditor::ModuleEditor()
{}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init()
{
	ImGui::CreateContext();
	io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	
	return true;
}

update_status ModuleEditor::Start()
{
	ImGui_ImplSDL2_InitForOpenGL(App->GetWindow()->window, App->GetRenderer()->GetContext());
	ImGui_ImplOpenGL3_Init("#version 440");

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->GetWindow()->window);
	ImGui::NewFrame();

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
	ImGui::Begin("General Menu");
	ImGui::Text("Engine Name: Sakuraba Engine");
	ImGui::Text("Author: Santiago Carbo Garcia");
	ImGui::End();

	ImGui::Begin("Configuration menu");

	ImGui::PlotHistogram("##framerate", nullptr, 0, 0, 0, "Frames Per Second", 0.0f, 100.0f, ImVec2(310, 100));

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Renderer variables"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O"))
			{

			}
			
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{	
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	SDL_GL_MakeCurrent(App->GetWindow()->window, App->GetRenderer()->GetContext());

	return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp() 
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}