#include "file_utils.hpp"
#include "renderer.hpp"
#include "texture.hpp"
#include "phong_material.hpp"
#include "common.hpp"


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

	// create shader
	//shader::create("test", "shader/vs.glsl", GL_VERTEX_SHADER);
	//shader::create("test", "shader/fs.glsl", GL_FRAGMENT_SHADER);

	// create texture
	//texture::create("orange", "media/dev.jpg");

	Material* blue = new PhongMaterial(glm::vec3(0, 0, 0.2), glm::vec3(0.2, 0.2, 1),
			glm::vec3(1, 1, 1), 5);
	add_material("blue", blue);

	// test cube
	RenderObject* test = create_render_object("test");
	std::vector<glm::vec3> pos = {
		glm::vec3(-1,  1, -1),
		glm::vec3( 1,  1, -1),
		glm::vec3(-1, -1, -1),
		glm::vec3( 1, -1, -1),
		glm::vec3(-1,  1,  1),
		glm::vec3( 1,  1,  1),
		glm::vec3(-1, -1,  1),
		glm::vec3( 1, -1,  1)
	};
	std::vector<glm::vec2> tc = {
		glm::vec2(0, 1),
		glm::vec2(0, 1),
		glm::vec2(1, 0),
		glm::vec2(1, 1),
		glm::vec2(1, 1),
		glm::vec2(1, 0),
		glm::vec2(0, 1),
		glm::vec2(0, 0)
	};
	std::vector<glm::vec3> col = {
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0, 1),
		glm::vec3(0, 1, 0),
		glm::vec3(0, 1, 1),
		glm::vec3(1, 0, 0),
		glm::vec3(1, 0, 1),
		glm::vec3(1, 1, 0),
		glm::vec3(1, 1, 1)
	};
	std::vector<glm::uvec3> idx = {
		glm::uvec3(0, 1, 2), //front
		glm::uvec3(2, 1, 3),
		glm::uvec3(5, 4, 7), //back
		glm::uvec3(7, 4, 6),
		glm::uvec3(1, 5, 3), //right
		glm::uvec3(3, 5, 7),
		glm::uvec3(4, 0, 6), //left
		glm::uvec3(6, 0, 2),
		glm::uvec3(4, 5, 0), //top
		glm::uvec3(0, 5, 1),
		glm::uvec3(2, 3, 6), //bottom
		glm::uvec3(6, 3, 7)
	};
	test->add_vertex_buffer(RenderObject::BufferType::POS, pos, 0);
	//test->add_vertex_buffer(RenderObject::BufferType::TC, tc, 1);
	//test->add_vertex_buffer(RenderObject::BufferType::COLOR, col, 2);
	test->add_index_buffer(idx);
	test->set_material("blue");
	renderer->register_render_object(test);


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