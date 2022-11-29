#include "ModuleEditor.h"


using namespace std;


ModuleEditor::ModuleEditor()
{

}

ModuleEditor::~ModuleEditor()
{

}

bool ModuleEditor::Init()
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
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
	ImGui::Begin("About...");

	string title = "Engine name: ";
	string aux(TITLE);
	title += aux;
	string author = "Author: Santiago Carbo Garcia";

	ImGui::Text(aux.c_str());
	ImGui::Text(author.c_str());
	//ImGui::PlotHistogram("##framerate")

	ImGui::End();

	return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
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