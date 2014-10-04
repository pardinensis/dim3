#include "file_utils.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "light.hpp"
#include "phong_material.hpp"
#include "normals_material.hpp"
#include "common.hpp"
#include "gl_utils.hpp"


SDL_Window* window = nullptr;
Renderer* renderer = nullptr;

bool should_quit = false;



void init() {
	parse_config_file("config.txt");

	// initializing SDL
	int success = SDL_Init(SDL_INIT_VIDEO);
	check_sdl_error(success, "SDL_Init");
	push_cleanup_function(SDL_Quit);

	// creating a window
	uint window_flags = SDL_WINDOW_HIDDEN | SDL_WINDOW_OPENGL;
	if (get<int>("WINDOW_FULLSCREEN", 0)) window_flags |= SDL_WINDOW_FULLSCREEN;
	if (get<int>("WINDOW_RESIZABLE", 0)) window_flags |= SDL_WINDOW_RESIZABLE;
	int size_x = get<int>("WINDOW_SIZE_X");
	int size_y = get<int>("WINDOW_SIZE_Y");
	window = SDL_CreateWindow(
		get<std::string>("WINDOW_NAME").c_str(),
		get<int>("WINDOW_POS_X", SDL_WINDOWPOS_CENTERED),
		get<int>("WINDOW_POS_Y", SDL_WINDOWPOS_CENTERED),
		size_x, size_y, window_flags);
	check_sdl_error(window, "SDL_CreateWindow");
	push_cleanup_function(std::bind(SDL_DestroyWindow, window));

	// initializing GL context
	SDL_GLContext gl_context = SDL_GL_CreateContext(window);
	push_cleanup_function(std::bind(SDL_GL_DeleteContext, gl_context));

	// initializing GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	// creating the render context
	renderer = new Renderer(window);

	// create camera
	Camera* cam = Camera::create("cam");
	glm::vec3 cam_pos = glm::vec3(3.0, 2.0, 3.0);
	glm::vec3 cam_center = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 cam_up = glm::vec3(0.0, 1.0, 0.0);
	cam->set_lookat(cam_pos, cam_center, cam_up);
	cam->set_perspective_projection(45, ((float)size_x)/size_y, 0.1, 100);
	renderer->set_camera("cam");

	// create material
	Material* blue = new PhongMaterial(glm::vec3(1, 1, 1), 0.1, 5);
	add_material("blue", blue);
	Material* normals = new NormalsMaterial();
	add_material("normals", normals);

	// create light
	//add_light(create_pointlight(glm::vec3(5, 0, 3), 2, glm::vec3(0.2, 0.9, 0.2)));
	add_light(create_pointlight(glm::vec3(-3, 2, 1), 3, glm::vec3(0.2, 0.2, 0.9)));

	// test cube
	RenderObject* test = create_render_object("test");
	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> norm;
	std::vector<glm::uvec3> idx;
	create_cube_vertex_buffer(pos);
	create_cube_index_buffer(idx);
	convert_to_triangle_soup(pos, idx);
	calculate_vertex_normals_by_angle(pos, idx, norm);
	test->add_vertex_buffer(RenderObject::BufferType::POS, pos, 0);
	test->add_vertex_buffer(RenderObject::BufferType::NORM, norm, 1);
	test->add_index_buffer(idx);
	test->set_material("blue");
	renderer->register_render_object(test);

	// test plane
	RenderObject* plane = create_render_object("plane");
	create_plane_vertex_buffer(pos, 4, -2);
	create_plane_index_buffer(idx);
	calculate_vertex_normals_by_angle(pos, idx, norm);
	plane->add_vertex_buffer(RenderObject::BufferType::POS, pos, 0);
	plane->add_vertex_buffer(RenderObject::BufferType::NORM, norm, 1);
	plane->add_index_buffer(idx);
	plane->set_material("blue");
	renderer->register_render_object(plane);


	// make the window visible
	SDL_ShowWindow(window);
}

void process_events() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch(e.type) {
			case SDL_QUIT:
			case SDL_KEYDOWN:
				should_quit = true;
				break;
		}
	}
}

void loop() {
	process_events();
	renderer->render();
}


int main() {
	try {
		// init program
		init();

		// start the main loop
		while (!should_quit) {
			loop();
		}
	
	// print out errors and quit
	} catch (std::string str) {
		std::cerr << "[ERROR] " << str << std::endl;
		clean_up();
		return -1;
	}

	clean_up();
}