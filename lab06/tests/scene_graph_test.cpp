#include "aur.hpp"
#include <time.h>
#include <chrono>
#include <ctime>

const int NUM_SECONDS = 1;
static float CENTER_ROTATION_ANGLE{ 0.0f };
static float CENTER_ROTATION_ANGLE_HOURS{ 0.0f };
static const float CAMERA_SPEED{ 0.1f };
static const float CAMERA_ROT_SPEED{ 0.03f };

static const float SPHERE_RADIUS{ 0.1f };
static const float SPHERE_ROT_SPEED{ 0.01f };

static const int SPHERE_SEGMENT_COUNT{ 60 };
static const int SPHERE_RING_COUNT{ 32 };

static const float CIRCLE_RADIUS{ 0.02f };
static const float CIRCLE_SEGMENTS_COUNT{ 60 };

static const float PLANE_WIDTH{ 0.2f };
static const float PLANE_HEIGHT{ 0.2f };
static const float WIDTH_SEGMENTS_COUNT{ 10 };
static const float HEIGHT_SEGMENTS_COUNT{ 10 };

static const float ROOT_ROTATION_ANGLE{0.0f};
static const glm::vec4 FORWARD{ 0.0f, 0.0f, 1.0f, 0.0f };

[[ noreturn ]]
int main(int argc, char** argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);


    auto sphereGeometryData = geometry_generators::generate_sphere_geometry_data(SPHERE_RADIUS, SPHERE_SEGMENT_COUNT, SPHERE_RING_COUNT);

    auto sphereGeometry = std::make_shared<ES2Geometry>(sphereGeometryData.first, sphereGeometryData.second);
    sphereGeometry->set_type(Geometry::Type::LineLoop);

    auto sphereMaterial = std::make_shared<ES2ConstantMaterial>();
    sphereMaterial->set_emission_color(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

    auto sphere = std::make_shared<Mesh>(sphereGeometry, sphereMaterial, glm::vec3{ 0.0f, 0.0f, 0.0f });
    sphere->set_name("sphere");

    auto circleGeometryData = geometry_generators::generate_circle_geometry_data(CIRCLE_RADIUS, CIRCLE_SEGMENTS_COUNT);

    auto circleGeometry = std::make_shared<ES2Geometry>(circleGeometryData.first, circleGeometryData.second);
    circleGeometry->set_type(Geometry::Type::TriangleFan);

    auto circleMaterial = std::make_shared<ES2ConstantMaterial>();
    circleMaterial->set_emission_color(glm::vec4{ 1.0f, 1.0f, 1.0f, 1.0f });


    auto planeGeometryData = geometry_generators::generate_plane_geometry_data(PLANE_WIDTH, PLANE_HEIGHT, WIDTH_SEGMENTS_COUNT, HEIGHT_SEGMENTS_COUNT);

    auto planeGeometry = std::make_shared<ES2Geometry>(planeGeometryData.first, planeGeometryData.second);
    planeGeometry->set_type(Geometry::Type::TriangleFan);

    auto planeMaterial1 = std::make_shared<ES2ConstantMaterial>();
    planeMaterial1->set_emission_color(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

    auto planeMaterial2 = std::make_shared<ES2ConstantMaterial>();
    planeMaterial2->set_emission_color(glm::vec4{ 2.0f, 0.0f, 0.0f, 1.0f });


    std::vector<std::shared_ptr<Object>> objects{ sphere };

    for (int i = 0; i < 60; i++) {

        float angle = i / 60.0f * (float)2 * (float)M_PI;
        float x = cosf(angle) * 2.0f;
        float y = sinf(angle) * 2.0f;

        auto circle = std::make_shared<Mesh>(circleGeometry, circleMaterial, glm::vec3{ x, y, 0.0f });
        //objects.push_back(circle);

        sphere->add_child(circle);
        if (i % 15 == 0) {
            auto plane = std::make_shared<Mesh>(planeGeometry, planeMaterial1, glm::vec3{ x, y, -0.3f });
            plane->set_rotation_z((float)M_PI / 180.0 * 45.0);
            sphere->add_child(plane);
        }

        if (i % 5 == 0) {
            auto plane = std::make_shared<Mesh>(planeGeometry, planeMaterial2, glm::vec3{ x, y, -0.4f });
            plane->set_rotation_z((float)M_PI / 180.0 * 45.0);
            plane->set_scale(glm::vec3{ 0.3f, 0.3f, 0.3f });
            sphere->add_child(plane);
        }
    }

    auto secsGeometryData = geometry_generators::generate_plane_geometry_data(0.05f, 2.0f, WIDTH_SEGMENTS_COUNT, HEIGHT_SEGMENTS_COUNT);
    auto secsGeometry = std::make_shared<ES2Geometry>(secsGeometryData.first, secsGeometryData.second);
    secsGeometry->set_type(Geometry::Type::TriangleFan);
    auto secsMaterial = std::make_shared<ES2ConstantMaterial>();
    secsMaterial->set_emission_color(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
    auto sec = std::make_shared<Mesh>(secsGeometry, secsMaterial, glm::vec3{ 0.0f, 1.0f, 0.0f });
    auto root1 = std::make_shared<Object>();
    root1->add_child(sec);
    objects.push_back(root1);

    auto minsGeometryData = geometry_generators::generate_plane_geometry_data(0.08f, 1.5f, WIDTH_SEGMENTS_COUNT, HEIGHT_SEGMENTS_COUNT);
    auto minsGeometry = std::make_shared<ES2Geometry>(minsGeometryData.first, minsGeometryData.second);
    minsGeometry->set_type(Geometry::Type::TriangleFan);
    auto minsMaterial = std::make_shared<ES2ConstantMaterial>();
    minsMaterial->set_emission_color(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
    auto root2 = std::make_shared<Object>();
    objects.push_back(root2);
    auto min = std::make_shared<Mesh>(minsGeometry, minsMaterial, glm::vec3{ 0.0f, 0.75f, 0.0f });
    root2->add_child(min);

    auto hoursGeometryData = geometry_generators::generate_plane_geometry_data(0.1f, 1.0f, WIDTH_SEGMENTS_COUNT, HEIGHT_SEGMENTS_COUNT);
    auto hoursGeometry = std::make_shared<ES2Geometry>(hoursGeometryData.first, hoursGeometryData.second);
    hoursGeometry->set_type(Geometry::Type::TriangleFan);
    auto hoursMaterial = std::make_shared<ES2ConstantMaterial>();
    hoursMaterial->set_emission_color(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });
    auto root3 = std::make_shared<Object>();
    objects.push_back(root3);
    auto hour = std::make_shared<Mesh>(hoursGeometry, hoursMaterial, glm::vec3{ 0.0f, 0.6f, 0.0f });
    root3->add_child(hour);

    auto scene = std::make_shared<Scene>(objects);

    auto& camera = scene->get_camera();
    camera->set_z(5.0f);

    ES2Renderer renderer(scene, window);
    
    int countSecs = 1;
    int countMins = 1;
    int countHours = 1;
    double time_counter = 0;

    clock_t this_time = clock();
    clock_t last_time = this_time;

    CENTER_ROTATION_ANGLE = 2 * M_PI / 60.0f;
    CENTER_ROTATION_ANGLE_HOURS = 2 * M_PI / 12.0f;

    std::time_t t = std::time(0);   // get time now
    std::tm* now = std::localtime(&t);

    int hours = now->tm_hour;
    int mins = now->tm_min;
    int secs = now->tm_sec;

    root1->set_rotation_z(root1->get_rotation_z() + secs * 2 * M_PI / 60.0f);
    root2->set_rotation_z(root2->get_rotation_z() + mins * 2 * M_PI / 60.0f);
    root3->set_rotation_z(root3->get_rotation_z() + hours * 2 * M_PI / 12.0f);

    for (;;) {
        window->poll();

        sphere->set_rotation_y(sphere->get_rotation_y() + SPHERE_ROT_SPEED);
        root1->set_rotation_y(root1->get_rotation_y() + SPHERE_ROT_SPEED);
        root2->set_rotation_y(root2->get_rotation_y() + SPHERE_ROT_SPEED);
        root3->set_rotation_y(root3->get_rotation_y() + SPHERE_ROT_SPEED);

        
        this_time = clock();

        time_counter += (double)(this_time - last_time);

        last_time = this_time;

        if (time_counter > (double)(CLOCKS_PER_SEC))
        {
            time_counter -= (double)(CLOCKS_PER_SEC);
            root1->set_rotation_z(root1->get_rotation_z() + CENTER_ROTATION_ANGLE);
            countSecs++;

            if (countSecs % 60 == 0) {
                root2->set_rotation_z(root2->get_rotation_z() + CENTER_ROTATION_ANGLE);
                countSecs = 0;
                countMins++;
            }

            if (countMins % 60 == 0) {
                root2->set_rotation_z(root2->get_rotation_z() + CENTER_ROTATION_ANGLE_HOURS);
                countMins = 0;
                countHours++;
            }
        }
        

        renderer.render();
    }
}
