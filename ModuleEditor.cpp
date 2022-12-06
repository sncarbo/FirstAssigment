#include "ModuleEditor.h"

using namespace std;


ModuleEditor::ModuleEditor() : showProperties(true), showConfiguration(true), showAssimpConsole(true)
{}

ModuleEditor::~ModuleEditor()
{}

bool ModuleEditor::Init()
{
	ImGui::CreateContext();
	io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	generalDisplayProportions = ImVec2(App->GetWindow()->GetWidth() / 9.0f, App->GetWindow()->GetHeight() / 4.0f);
	propertiesDisplayProportions = ImVec2(App->GetWindow()->GetWidth() / 9.0f, App->GetWindow()->GetHeight() / 4.0f);
	configurationDisplayProportions = ImVec2(App->GetWindow()->GetWidth() / 9.0f, App->GetWindow()->GetHeight() / 4.0f);
	assimpConsoleDisplayProportions = ImVec2(App->GetWindow()->GetWidth() / 9.0f, App->GetWindow()->GetHeight() / 4.0f);
	
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
	io.DisplaySize = generalDisplayProportions;

	ImGui::Begin("General Menu");

	ImGui::Text("GitHub Page: %s", "https://github.com/sncarbo/FirstAssigment");
	ImGui::Text("Engine Name: %s", TITLE);
	ImGui::Text("Author: Santiago Carbo Garcia");

	ImGui::End();

	if (showProperties)
	{
		io.DisplaySize = propertiesDisplayProportions;

		ImGui::Begin("Properties Menu");

		ImGui::End();
	}

	if (showConfiguration)
	{
		io.DisplaySize = configurationDisplayProportions;

		ImGui::Begin("Configuration menu");

		fpsLog.push_back(1.0f/io.DeltaTime);

		sprintf_s(fpsTitleBuffer, sizeof(fpsTitleBuffer), "FPS %.1f", fpsLog[fpsLog.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, "FPS", 0.0f, 100.0f, ImVec2(310, 100));

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
	}

	if (showAssimpConsole)
	{
		io.DisplaySize = assimpConsoleDisplayProportions;

		ImGui::Begin("Assimp Console");

		ImGui::End();
	}

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