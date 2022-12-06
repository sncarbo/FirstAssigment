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

	generalWindowFlags |= ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
	propertiesWindowFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
	configurationWindowFlags |= ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
	consoleWindowFlags |= ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;

	p_open_general = true;
	p_open_properties = true;
	p_open_configuration = true;
	p_open_console = true;
	p_open_about = false;

	compiledSDLVersion = SDL_version();
	linkedSDLVersion = SDL_version();
	majorCompiledSDLVersion = new char[5];
	minorCompiledSDLVersion = new char[5];
	patchCompiledSDLVersion = new char[5];
	majorLinkedSDLVersion = new char[5];
	minorLinkedSDLVersion = new char[5];
	patchLinkedSDLVersion = new char[5];
	openGLVersion = new char[10];
	CPUL1CacheLineSize = new char[50];
	CPUL1CacheLineSize[0] = '\0';
	CPUCoresAvalaible = new char[50];
	CPUCoresAvalaible[0] = '\0';
	RAMComsuption = new char[50];
	RAMComsuption[0] = '\0';

	engineStatus = UPDATE_CONTINUE;

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
	GeneralMenu();
	ConfigurationWindow();
	PropertiesWindow();
	AssimpConsole();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return engineStatus;
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

void ModuleEditor::GeneralMenu()
{
	ImGui::Begin("Sakuraba Engine", &p_open_general, generalWindowFlags);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("General Menu"))
		{
			if (ImGui::MenuItem("Visit GitHub Page"))
				ShellExecuteA(NULL, "open", "https://github.com/sncarbo/FirstAssigment", NULL, NULL, SW_SHOWNORMAL);

			if (ImGui::MenuItem("Quit"))
				engineStatus = UPDATE_STOP;

			if (ImGui::MenuItem("Show/Hide About"))
				p_open_about = !p_open_about;

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Turn on/off windows"))
		{
			if (ImGui::MenuItem("Properties Window"))
				p_open_properties = !p_open_properties;

			if (ImGui::MenuItem("Configuration Window"))
				p_open_configuration = !p_open_configuration;

			if (ImGui::MenuItem("Assimp Console Window"))
				p_open_console = !p_open_console;

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	if (p_open_about)
	{
		ImGui::Text("Engine Name: %s", TITLE);
		ImGui::Text("Author: Santiago Carbo Garcia");
		ImGui::Text("Engine developed for the First Assigment");
		ImGui::Text("License: MIT License");
	}

	ImGui::End();
}

void ModuleEditor::ConfigurationWindow()
{
	if (p_open_configuration)
	{
		ImGui::Begin("Configuration", &p_open_configuration, configurationWindowFlags);

		fpsLog.push_back(1.0f / io.DeltaTime);

		sprintf_s(fpsTitleBuffer, 25, "Framerate %.1f", fpsLog[fpsLog.size() - 1]);
		ImGui::PlotHistogram("##framerate", &fpsLog[0], fpsLog.size(), 0, fpsTitleBuffer, 0.0f, 100.0f, ImVec2(210, 100));

		sprintf(CPUL1CacheLineSize, "%d", SDL_GetCPUCacheLineSize());

		ImGui::Text("CPU L1 cache line size (B): ");
		ImGui::SameLine();
		ImGui::Text(CPUL1CacheLineSize);

		sprintf(CPUCoresAvalaible, "%d", SDL_GetCPUCount());

		ImGui::Text("Number of CPU cores avalaible: ");
		ImGui::SameLine();
		ImGui::Text(CPUCoresAvalaible);

		sprintf(RAMComsuption, "%d", SDL_GetSystemRAM());
		
		ImGui::Text("RAM comsumption (MiB): ");
		ImGui::SameLine();
		ImGui::Text(RAMComsuption);

		if(SDL_Has3DNow())
			ImGui::Text("The CPU has 3DNow! features");
		else
			ImGui::Text("The CPU has not 3DNow! features");

		if (SDL_HasAltiVec())
			ImGui::Text("The CPU has AltiVec features");
		else
			ImGui::Text("The CPU has not AltiVec features");

		if (SDL_HasAVX())
			ImGui::Text("The CPU has AVX features");
		else
			ImGui::Text("The CPU has not AVX features");

		if (SDL_HasAVX2())
			ImGui::Text("The CPU has AVX2 features");
		else
			ImGui::Text("The CPU has not AVX2 features");

		if (SDL_HasMMX())
			ImGui::Text("The CPU has MMX features");
		else
			ImGui::Text("The CPU has not MMX features");

		if (SDL_HasRDTSC())
			ImGui::Text("The CPU has RDTSC features");
		else
			ImGui::Text("The CPU has not RDTSC features");

		SDL_VERSION(&compiledSDLVersion);
		SDL_GetVersion(&linkedSDLVersion);

		sprintf(majorCompiledSDLVersion, "%u", compiledSDLVersion.major);
		sprintf(minorCompiledSDLVersion, "%u", compiledSDLVersion.minor);
		sprintf(patchCompiledSDLVersion, "%u", compiledSDLVersion.patch);

		sprintf(majorLinkedSDLVersion, "%u", linkedSDLVersion.major);
		sprintf(minorLinkedSDLVersion, "%u", linkedSDLVersion.minor);
		sprintf(patchLinkedSDLVersion, "%u", linkedSDLVersion.patch);

		ImGui::Text("Compiling SDL Version: ");
		ImGui::SameLine();
		ImGui::Text(majorCompiledSDLVersion);
		ImGui::SameLine();
		ImGui::Text(".");
		ImGui::SameLine();
		ImGui::Text(minorCompiledSDLVersion);
		ImGui::SameLine();
		ImGui::Text(".");
		ImGui::SameLine();
		ImGui::Text(patchCompiledSDLVersion);

		ImGui::Text("Linking SDL Version: ");
		ImGui::SameLine();
		ImGui::Text(majorLinkedSDLVersion);
		ImGui::SameLine();
		ImGui::Text(".");
		ImGui::SameLine();
		ImGui::Text(minorLinkedSDLVersion);
		ImGui::SameLine();
		ImGui::Text(".");
		ImGui::SameLine();
		ImGui::Text(patchLinkedSDLVersion);

		sprintf(openGLVersion, "%d", GL_VERSION);

		ImGui::Text("OpenGL Version: ");
		ImGui::SameLine();
		ImGui::Text(openGLVersion);

		ImGui::End();
	}
}

void ModuleEditor::PropertiesWindow()
{
	if (p_open_properties)
	{
		ImGui::Begin("Properties", &p_open_properties, propertiesWindowFlags);



		ImGui::End();
	}
}

void ModuleEditor::AssimpConsole()
{
	if (p_open_console)
	{
		ImGui::Begin("Assimp Console", &p_open_console, consoleWindowFlags);

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::MenuItem("Clear Console"))
				App->ClearAssimpLOG();

			ImGui::EndMenuBar();
		}

		ImGui::TextUnformatted(App->GetAssimpLOG().c_str());

		ImGui::End();
	}
}