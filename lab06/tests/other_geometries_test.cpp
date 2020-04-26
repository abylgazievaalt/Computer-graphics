#include "aur.hpp"

static const float PLANE_ROT_SPEED{ 0.01f };
static const float PLANE_WIDTH{ 1.0f };
static const float PLANE_HEIGHT{ 1.0f };
static const float WIDTH_SEGMENTS_COUNT{ 20 };
static const float HEIGHT_SEGMENTS_COUNT{ 20 };

static const float CIRCLE_RADIUS{ 0.5f };
static const float CIRCLE_SEGMENTS_COUNT{ 10 };
static const float CIRCLE_SEGMENTS_COUNT2{ 80 };

static const float SPHERE_RADIUS{ 0.5f };
static const float SPHERE_SEGMENT_COUNT{ 20 };
static const float SPHERE_RING_COUNT{ 20 };

[[ noreturn ]]
int main(int argc, char** argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);
    

    auto dataGeometry = geometry_generators::generate_plane_geometry_data(PLANE_WIDTH, PLANE_HEIGHT, WIDTH_SEGMENTS_COUNT, HEIGHT_SEGMENTS_COUNT);

    auto planeGeometry1 = std::make_shared<ES2Geometry>(dataGeometry.first, dataGeometry.second);
    planeGeometry1->set_type(Geometry::Type::TriangleFan);

    auto planeMaterial1 = std::make_shared<ES2ConstantMaterial>();
    planeMaterial1->set_emission_color(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

    auto plane1 = std::make_shared<Mesh>(planeGeometry1, planeMaterial1, glm::vec3{ -2.0f, 2.0f, 0.0f });
    plane1->set_name("plane1");

    
    auto planeGeometry2 = std::make_shared<ES2Geometry>(dataGeometry.first, dataGeometry.second);
    planeGeometry2->set_type(Geometry::Type::LineLoop);

    auto planeMaterial2 = std::make_shared<ES2ConstantMaterial>();
    planeMaterial2->set_emission_color(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

    auto plane2 = std::make_shared<Mesh>(planeGeometry2, planeMaterial2, glm::vec3{ 0.0f, 2.0f, 0.0f });
    plane2->set_scale(glm::vec3{ 1.0f, 1.0f, 1.0f });
    plane2->set_name("plane2");
   

    auto planeGeometry3 = std::make_shared<ES2Geometry>(dataGeometry.first, dataGeometry.second);
    planeGeometry3->set_type(Geometry::Type::Points);

    auto planeMaterial3 = std::make_shared<ES2ConstantMaterial>();
    planeMaterial3->set_emission_color(glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f });

    auto plane3 = std::make_shared<Mesh>(planeGeometry3, planeMaterial3, glm::vec3{ 2.0f, 2.0f, 0.0f });
    plane3->set_scale(glm::vec3{ 1.0f, 1.0f, 1.0f });
    plane3->set_name("plane3");

    
    auto circleGeometry = geometry_generators::generate_circle_geometry_data(CIRCLE_RADIUS, CIRCLE_SEGMENTS_COUNT);

    auto circleGeometry1= std::make_shared<ES2Geometry>(circleGeometry.first, circleGeometry.second);
    circleGeometry1->set_type(Geometry::Type::TriangleFan);

    auto circleMaterial1 = std::make_shared<ES2ConstantMaterial>();
    circleMaterial1->set_emission_color(glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f });

    auto circle1 = std::make_shared<Mesh>(circleGeometry1, circleMaterial1, glm::vec3{ -2.0f, 0.0f, 0.0f });
    circle1->set_scale(glm::vec3{ 1.0f, 1.0f, 1.0f });
    circle1 ->set_name("circle1");
    

    circleGeometry = geometry_generators::generate_circle_geometry_data(CIRCLE_RADIUS, CIRCLE_SEGMENTS_COUNT2);

    auto circleGeometry2 = std::make_shared<ES2Geometry>(circleGeometry.first, circleGeometry.second);
    circleGeometry2->set_type(Geometry::Type::LineLoop);

    auto circleMaterial2 = std::make_shared<ES2ConstantMaterial>();
    circleMaterial2->set_emission_color(glm::vec4{ 0.2f, 1.5f, 0.0f, 1.0f });

    auto circle2 = std::make_shared<Mesh>(circleGeometry2, circleMaterial2, glm::vec3{ 0.0f, 0.0f, 0.0f });
    circle2->set_scale(glm::vec3{ 1.0f, 1.0f, 1.0f });
    circle2->set_name("circle2");


    circleGeometry = geometry_generators::generate_circle_geometry_data(CIRCLE_RADIUS, CIRCLE_SEGMENTS_COUNT2);
    auto circleGeometry3 = std::make_shared<ES2Geometry>(circleGeometry.first, circleGeometry.second);
    circleGeometry3->set_type(Geometry::Type::Points);

    auto circleMaterial3 = std::make_shared<ES2ConstantMaterial>();
    circleMaterial3->set_emission_color(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

    auto circle3 = std::make_shared<Mesh>(circleGeometry3, circleMaterial3, glm::vec3{ 2.0f, 0.0f, 0.0f });
    circle3->set_scale(glm::vec3{ 1.0f, 1.0f, 1.0f });
    circle3->set_name("circle3");


    auto sphereGeometry = geometry_generators::generate_sphere_geometry_data(SPHERE_RADIUS, SPHERE_SEGMENT_COUNT, SPHERE_RING_COUNT);
    auto sphereGeometry1 = std::make_shared<ES2Geometry>(sphereGeometry.first, sphereGeometry.second);
    sphereGeometry1->set_type(Geometry::Type::TriangleFan);

    auto sphereMaterial1 = std::make_shared<ES2ConstantMaterial>();
    sphereMaterial1->set_emission_color(glm::vec4{ 4.0f, 0.5f, 0.0f, 1.0f });

    auto sphere1 = std::make_shared<Mesh>(sphereGeometry1, sphereMaterial1, glm::vec3{ -2.0f, -2.0f, 0.0f });
    sphere1->set_scale(glm::vec3{ 1.0f, 1.0f, 1.0f });
    sphere1->set_name("sphere1");

   
    //auto sphereGeometry = geometry_generators::generate_sphere_geometry_data(SPHERE_RADIUS, SPHERE_SEGMENT_COUNT, SPHERE_RING_COUNT);
    auto sphereGeometry2 = std::make_shared<ES2Geometry>(sphereGeometry.first, sphereGeometry.second);
    sphereGeometry2->set_type(Geometry::Type::LineLoop);

    auto sphereMaterial2 = std::make_shared<ES2ConstantMaterial>();
    sphereMaterial2->set_emission_color(glm::vec4{ 1.0f, 0.0f, 1.0f, 1.0f });

    auto sphere2 = std::make_shared<Mesh>(sphereGeometry2, sphereMaterial2, glm::vec3{ 0.0f, -2.0f, 0.0f });
    sphere2->set_scale(glm::vec3{ 1.0f, 1.0f, 1.0f });
    sphere2->set_name("sphere2");


    //auto sphereGeometry = geometry_generators::generate_sphere_geometry_data(SPHERE_RADIUS, SPHERE_SEGMENT_COUNT, SPHERE_RING_COUNT);
    auto sphereGeometry3 = std::make_shared<ES2Geometry>(sphereGeometry.first, sphereGeometry.second);
    sphereGeometry3->set_type(Geometry::Type::Points);

    auto sphereMaterial3 = std::make_shared<ES2ConstantMaterial>();
    sphereMaterial3->set_emission_color(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });

    auto sphere3 = std::make_shared<Mesh>(sphereGeometry3, sphereMaterial3, glm::vec3{ 2.0f, -2.0f, 0.0f });
    sphere3->set_scale(glm::vec3{ 1.0f, 1.0f, 1.0f });
    sphere3->set_name("sphere3");


    std::vector<std::shared_ptr<Object>> objects{ plane1, plane2, plane3, circle1, circle2, circle3, sphere1, sphere2, sphere3 };
    auto scene = std::make_shared<Scene>(objects);

    auto& camera = scene->get_camera();
    camera->set_z(5.0f);

    ES2Renderer renderer(scene, window);

    for (;;) {
        window->poll();

        plane1->set_rotation_y(plane1->get_rotation_y() + PLANE_ROT_SPEED);
        plane1->set_rotation_x(plane1->get_rotation_x() + PLANE_ROT_SPEED);

        plane2->set_rotation_x(plane2->get_rotation_z() + PLANE_ROT_SPEED);
        plane2->set_rotation_z(plane2->get_rotation_z() + PLANE_ROT_SPEED);
        
        plane3->set_rotation_y(plane3->get_rotation_y() + PLANE_ROT_SPEED);
        plane3->set_rotation_x(plane2->get_rotation_x() + PLANE_ROT_SPEED);

        circle1->set_rotation_x(circle1->get_rotation_x() + PLANE_ROT_SPEED);
        circle1->set_rotation_y(circle1->get_rotation_y() + PLANE_ROT_SPEED);

        circle2->set_rotation_x(circle2->get_rotation_x() + PLANE_ROT_SPEED);

        circle3->set_rotation_x(circle3->get_rotation_x() + PLANE_ROT_SPEED);
        circle3->set_rotation_y(circle3->get_rotation_y() + PLANE_ROT_SPEED);
        
        sphere1->set_rotation_x(sphere1->get_rotation_x() + PLANE_ROT_SPEED);
        sphere1->set_rotation_y(sphere1->get_rotation_y() + PLANE_ROT_SPEED);

        sphere2->set_rotation_x(sphere2->get_rotation_x() + PLANE_ROT_SPEED);
        sphere2->set_rotation_y(sphere2->get_rotation_y() + PLANE_ROT_SPEED);
       
        sphere3->set_rotation_x(sphere3->get_rotation_x() + PLANE_ROT_SPEED);
        sphere3->set_rotation_y(sphere3->get_rotation_y() + PLANE_ROT_SPEED);

        renderer.render();
    }
}
