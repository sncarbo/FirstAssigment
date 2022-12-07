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

	generalWindowFlags |= ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize;
	propertiesWindowFlags |= ImGuiWindowFlags_NoResize;
	configurationWindowFlags |= ImGuiWindowFlags_NoResize;
	consoleWindowFlags |= ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize;

	transformationSectionFlags |= ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen;
	geometrySectionFlags |= ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen;
	textureSectionFlags |= ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen;

	moduleRendererVariablesFlags |= ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen;
	moduleWindowVariablesFlags |= ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen;
	moduleInputVariablesFlags |= ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen;
	moduleTexturesVariablesFlags |= ImGuiTreeNodeFlags_CollapsingHeader | ImGuiTreeNodeFlags_DefaultOpen;

	p_open_general = true;
	p_open_properties = true;
	p_open_configuration = true;
	p_open_console = true;
	p_open_about = true;

	p_open_module_renderer_variables = true;
	p_open_module_window_variables = true;
	p_open_module_input_variables = true;
	p_open_module_texture_variables = true;

	p_open_transformation_section = true;
	p_open_geometry_section = true;
	p_open_texture_section = true;

	fullscreen = false;
	fullscreenDesktop = false;
	resizable = true;

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

	widthTexture = new char[10];
	widthTexture[0] = '\0';
	heightTexture = new char[10];
	heightTexture[0] = '\0';
	verticesCount = new char[20];
	verticesCount[0] = '\0';
	indicesCount = new char[20];
	indicesCount[0] = '\0';
	triangleCount = new char[20];
	triangleCount[0] = '\0';
	meshCount = new char[20];
	meshCount[0] = '\0';

	mouseMotionSensitivity = 1.0f;
	inverseMouse = false;

	squareGridMins = -50.0f;
	squareGridMaxs = 50.0f;
	squareGridY = 0.0f;
	squareGridStep = 1.0f;

	flippedTexture = true;

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

		if (fpsLog.size() == fpsLog.max_size())
			fpsLog.clear();

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

		if (SDL_HasSSE())
			ImGui::Text("The CPU has SSE features");
		else
			ImGui::Text("The CPU has not SEE features");

		if (SDL_HasSSE2())
			ImGui::Text("The CPU has SSE2 features");
		else
			ImGui::Text("The CPU has not SEE2 features");

		if (SDL_HasSSE3())
			ImGui::Text("The CPU has SSE3 features");
		else
			ImGui::Text("The CPU has not SEE3 features");

		if (SDL_HasSSE41())
			ImGui::Text("The CPU has SSE41 features");
		else
			ImGui::Text("The CPU has not SEE41 features");

		if (SDL_HasSSE42())
			ImGui::Text("The CPU has SSE42 features");
		else
			ImGui::Text("The CPU has not SEE42 features");

		SDL_VERSION(&compiledSDLVersion);
		SDL_GetVersion(&linkedSDLVersion);

		sprintf(majorCompiledSDLVersion, "%u", compiledSDLVersion.major);
		sprintf(minorCompiledSDLVersion, "%u", compiledSDLVersion.minor);
		sprintf(patchCompiledSDLVersion, "%u", compiledSDLVersion.patch);

		sprintf(majorLinkedSDLVersion, "%u", linkedSDLVersion.major);
		sprintf(minorLinkedSDLVersion, "%u", linkedSDLVersion.minor);
		sprintf(patchLinkedSDLVersion, "%u", linkedSDLVersion.patch);

		ImGui::Text("Compiling SDL Version: ");
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(majorCompiledSDLVersion);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(".");
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(minorCompiledSDLVersion);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(".");
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(patchCompiledSDLVersion);

		ImGui::Text("Linking SDL Version: ");
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(majorLinkedSDLVersion);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(".");
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(minorLinkedSDLVersion);
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(".");
		ImGui::SameLine(0.0f, 0.0f);
		ImGui::Text(patchLinkedSDLVersion);

		sprintf(openGLVersion, "%d", GL_VERSION);

		ImGui::Text("OpenGL Version: ");
		ImGui::SameLine();
		ImGui::Text(openGLVersion);

		if (ImGui::CollapsingHeader("Module Renderer Variables", &p_open_module_renderer_variables, moduleRendererVariablesFlags))
		{
			ImGui::Text("Square Grid");

			if (ImGui::SliderFloat("Mins", &squareGridMins, -60.0f, -40.0f))
				App->GetRenderer()->SetSquareGridMins(squareGridMins);

			if (ImGui::SliderFloat("Maxs", &squareGridMaxs, 40.0f, 60.0f))
				App->GetRenderer()->SetSquareGridMaxs(squareGridMaxs);

			if (ImGui::SliderFloat("Y", &squareGridY, -1.0f, 1.0f))
				App->GetRenderer()->SetSquareGridY(squareGridY);

			if (ImGui::SliderFloat("Step", &squareGridStep, 0.5f, 2.0f))
				App->GetRenderer()->SetSquareGridStep(squareGridStep);
		}

		if (ImGui::CollapsingHeader("Module Window Variables", &p_open_module_window_variables, moduleWindowVariablesFlags))
		{
			if (ImGui::Checkbox("Fullscreen", &fullscreen))
				App->GetWindow()->SetFullscreen(fullscreen);
			
			if (!fullscreen)
			{
				if (ImGui::Checkbox("Fullscreen Desktop", &fullscreenDesktop))
					App->GetWindow()->SetFullscreenDesktop(fullscreenDesktop);

				if (!fullscreen && !fullscreenDesktop)
				{
					if (ImGui::Checkbox("Resizable", &resizable))
						App->GetWindow()->SetResizable(resizable);
				}
			}
		}

		if (ImGui::CollapsingHeader("Module Input Variables", &p_open_module_input_variables, moduleInputVariablesFlags))
		{
			if (ImGui::Checkbox("Inverse Mouse", &inverseMouse))
				App->GetInput()->SetInverseMouse(inverseMouse);

			ImGui::Text("Mouse Sensitivity");

			if (ImGui::SliderFloat(" ", &mouseMotionSensitivity, 0.5f, 2.0f))
				App->GetInput()->SetMouseMotionSensitivity(mouseMotionSensitivity);
		}

		if (ImGui::CollapsingHeader("Module Texture Variables", &p_open_module_texture_variables, moduleTexturesVariablesFlags))
		{
			if (ImGui::Checkbox("Flipped Texture", &flippedTexture))
				App->GetTextures()->SetFlippedTexture(flippedTexture);
		}

		ImGui::End();
	}
}

void ModuleEditor::PropertiesWindow()
{
	if (p_open_properties)
	{
		ImGui::Begin("Properties", &p_open_properties, propertiesWindowFlags);

		if (ImGui::CollapsingHeader("Transformation", &p_open_transformation_section, transformationSectionFlags))
		{
			sprintf(meshCount, "%u", App->GetRenderer()->GetModel()->GetMeshCount());

			ImGui::Text("Meshes Count: ");
			ImGui::SameLine(0.0f, 0.0f);
			ImGui::Text(meshCount);

			ImGui::Text("Textures Count: 1");
		}

		if (ImGui::CollapsingHeader("Geometry", &p_open_geometry_section, geometrySectionFlags))
		{
			sprintf(verticesCount, "%u", App->GetRenderer()->GetModel()->GetMesh()->GetNumIndices());
			sprintf(indicesCount, "%u", App->GetRenderer()->GetModel()->GetMesh()->GetNumIndices());
			sprintf(triangleCount, "%u", App->GetRenderer()->GetModel()->GetMesh()->GetNumFaces());

			ImGui::Text("Vertices Count: ");
			ImGui::SameLine(0.0f, 0.0f);
			ImGui::Text(verticesCount);

			ImGui::Text("Indices Count: ");
			ImGui::SameLine(0.0f, 0.0f);
			ImGui::Text(indicesCount);

			ImGui::Text("Triangle Count: ");
			ImGui::SameLine(0.0f, 0.0f);
			ImGui::Text(triangleCount);
		}

		if (ImGui::CollapsingHeader("Texture", &p_open_texture_section, textureSectionFlags))
		{
			sprintf(widthTexture, "%u", App->GetTextures()->GetInfo().width);
			sprintf(heightTexture, "%u", App->GetTextures()->GetInfo().height);

			ImGui::Text("Texture Size (px): ");
			ImGui::SameLine(0.0f, 0.0f);
			ImGui::Text(widthTexture);
			ImGui::SameLine(0.0f, 0.0f);
			ImGui::Text("x");
			ImGui::SameLine(0.0f, 0.0f);
			ImGui::Text(heightTexture);

			if (App->GetTextures()->GetInfo().IsVolumemap())
				ImGui::Text("The texture is a Volume Map");
			else
				ImGui::Text("The texture is not a Volume Map");

			if (App->GetTextures()->GetInfo().IsCubemap())
				ImGui::Text("The texture is a Cube Map");
			else
				ImGui::Text("The texture is not a Cube Map");

			if (App->GetTextures()->GetInfo().IsPMAlpha())
				ImGui::Text("The texture has PM Alpha");
			else
				ImGui::Text("The texture has not PM Alpha");
		}

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