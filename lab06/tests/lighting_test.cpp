#include "aur.hpp"

static const float CAMERA_SPEED{ 0.05f };
static const float CAMERA_ROT_SPEED{ 0.05f };

static const float SPHERE_RADIUS{ 0.5f };
static const float SPHERE_SEGMENT_COUNT{ 50 };
static const float SPHERE_RING_COUNT{ 50 };

static const float PLANE_WIDTH{ 1000 };
static const float PLANE_HEIGHT{ 1000 };
static const float WIDTH_SEGMENT_COUNT{ 100 };
static const float HEIGHT_SEGMENT_COUNT{ 100 };

static const float ÑENTER_SPEED = 0.02f;

static const glm::vec4 FORWARD{ 0.0f, 0.0f, 1.0f, 0.0f };

[[ noreturn ]]
int main(int argc, char** argv)
{
	using namespace aur;
	using namespace aur::geometry_generators;

	auto window = std::make_shared<SDLWindow>("aur", 0, 0);

	auto sphereData = generate_sphere_geometry_data(SPHERE_RADIUS, SPHERE_SEGMENT_COUNT, SPHERE_RING_COUNT);
	auto sphereGeometry = std::make_shared<ES2Geometry>(sphereData.first, sphereData.second);

	auto sphereMaterial = std::make_shared<ES2PhongMaterial>();
	sphereMaterial->set_specular_exponent(30.0f);
	sphereMaterial->set_emission_color(glm::vec4{ 0.1f, 0.1f, 0.1f, 1.0f}); //set grey color
	auto sphere = std::make_shared<Mesh>(sphereGeometry, sphereMaterial, glm::vec3(0.0f, 0.0f, 0.0f));

	auto planeMaterial = std::make_shared<ES2PhongMaterial>();
	planeMaterial->set_specular_exponent(30.0f);
	planeMaterial->set_emission_color(glm::vec4{ 0.0f, 0.0f, 0.0f, 1.0f }); //set black color 

	auto planeData = generate_plane_geometry_data(PLANE_WIDTH, PLANE_HEIGHT, WIDTH_SEGMENT_COUNT, HEIGHT_SEGMENT_COUNT);
	auto planeGeometry = std::make_shared<ES2Geometry>(planeData.first, planeData.second);
	auto plane = std::make_shared<Mesh>(planeGeometry, planeMaterial, glm::vec3{ 0.0f, -2.5f, 0.0f });
	plane->set_rotation_x(plane->get_rotation_x() -(float)M_PI / 2.0f);

	auto plane_2 = std::make_shared<Mesh>(planeGeometry, planeMaterial, glm::vec3{ 0.0f, +2.5f, 0.0f });
	plane_2->set_rotation_x(plane_2->get_rotation_x() + (float)M_PI / 2.0f);

	auto plane_3 = std::make_shared<Mesh>(planeGeometry, planeMaterial, glm::vec3{ -2.5f, 0.0f, 0.0f });
	plane_3->set_rotation_y(plane_3->get_rotation_y() + (float)M_PI / 2.0f);

	auto plane_4 = std::make_shared<Mesh>(planeGeometry, planeMaterial, glm::vec3{ 2.5f, 0.0f, 0.0f });
	plane_4->set_rotation_y(plane_4->get_rotation_y() - (float)M_PI / 2.0f);

	auto plane_5 = std::make_shared<Mesh>(planeGeometry, planeMaterial, glm::vec3{ 0.0f, 0.0f, -2.5f });
	//plane_5->set_rotation_y(plane_5->get_rotation_y() - (float)M_PI / 2.0f);


	auto centerGeometry = std::make_shared<ES2Geometry>(sphereData.first, sphereData.second);
	auto centerMaterial = std::make_shared<ES2ConstantMaterial>();

	auto material2 = std::make_shared<ES2PhongMaterial>();
	material2->set_emission_color(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	
	auto lampGeometry = std::make_shared<ES2Geometry>(sphereData.first, sphereData.second);

	auto lamp = std::make_shared<Mesh>(lampGeometry, material2, glm::vec3(2.0f, 1.0f, 0.0f));
	lamp->set_scale(glm::vec3(0.2f));
	
	auto lamp2 = std::make_shared<Mesh>(lampGeometry, material2, glm::vec3(-1.7f, 1.0f, 0.0f));
	lamp2->set_scale(glm::vec3(0.2f));

	auto light = std::make_shared<PointLight>();
	light->set_diffuse_color(glm::vec3(0.1f, 0.1f, 0.1f));
	light->set_specular_color(glm::vec3(0.6f, 0.6f, 0.6f));

	auto light2 = std::make_shared<PointLight>();
	light2->set_diffuse_color(glm::vec3(0.2f, 0.2f, 0.2f));
	light2->set_specular_color(glm::vec3(0.6f, 0.6f, 0.6f));

	auto center2 = std::make_shared<Object>();

	sphere->add_child(lamp);
	center2->add_child(lamp2);

	lamp->add_child(light);
	lamp2->add_child(light2);


	std::vector<std::shared_ptr<Object>> objects{ sphere, plane, center2, plane_2, plane_3, plane_4, plane_5 };

	auto scene = std::make_shared<Scene>(objects);


	auto camera = scene->get_camera();
	camera->set_z(6.0f);
	//camera->set_y(-1.0f);
	//camera->set_x(-1.0f);
	//camera->set_rotation_x(0.2f);
	//camera->set_rotation_y(-0.2f);

	scene->get_point_lights().clear();
	scene->get_directional_lights().clear();

	scene->get_point_lights().push_back(light);
	scene->get_point_lights().push_back(light2);

	window->set_on_key([&](int key) {
		switch (key) {
		case SDLK_w: camera->set_rotation_x(camera->get_rotation_x() - CAMERA_ROT_SPEED); break;
		case SDLK_a: camera->set_rotation_y(camera->get_rotation_y() + CAMERA_ROT_SPEED); break;
		case SDLK_s: camera->set_rotation_x(camera->get_rotation_x() + CAMERA_ROT_SPEED); break;
		case SDLK_d: camera->set_rotation_y(camera->get_rotation_y() - CAMERA_ROT_SPEED); break;
		case SDLK_e: camera->set_y(camera->get_y() + CAMERA_ROT_SPEED); break;
		case SDLK_q: camera->set_y(camera->get_y() - CAMERA_ROT_SPEED); break;
		case SDLK_UP: camera->set_position(camera->get_position() - glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED));   break;
		case SDLK_DOWN: camera->set_position(camera->get_position() + glm::vec3(camera->get_model_matrix() * FORWARD * CAMERA_SPEED)); break;
		case SDLK_ESCAPE: exit(0); break;
		default: break;
		}
	});

	ES2Renderer renderer(scene, window);
	for (;;) {
		window->poll();

		sphere->set_rotation_y(sphere->get_rotation_y() + ÑENTER_SPEED);
		sphere->set_rotation_x(sphere->get_rotation_x() + ÑENTER_SPEED);
		center2->set_rotation_y(center2->get_rotation_y() - ÑENTER_SPEED - 0.01f);
		center2->set_rotation_x(center2->get_rotation_x() - ÑENTER_SPEED - 0.01f);
		
		renderer.render();

		
	}
}