#include "aur.hpp"

static const float TRIANGLE_ROT_SPEED{ 0.1f };

[[ noreturn ]]
int main(int argc, char** argv)
{
    using namespace aur;

    auto window = std::make_shared<SDLWindow>("aur", 0, 0);

    auto dataGeometry = geometry_generators::generate_triangle_geometry_data();
    dataGeometry.second[0].color = glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f };
    dataGeometry.second[1].color = glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f };
    dataGeometry.second[2].color = glm::vec4{ 0.0f, 0.0f, 1.0f, 1.0f };

    auto triangleGeometry = std::make_shared<ES2Geometry>(dataGeometry.first, dataGeometry.second);
    triangleGeometry->set_type(Geometry::Type::TriangleFan);

    auto triangleMaterial = std::make_shared<ES2ConstantMaterial>();
  // triangleMaterial->set_emission_color(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

    auto triangle = std::make_shared<Mesh>(triangleGeometry, triangleMaterial, glm::vec3{ 0.0f, 0.0f, 0.0f });
    triangle->set_scale(glm::vec3{ 1.5f, 1.5f, 1.5f });
    triangle->set_name("triangle");

    std::vector<std::shared_ptr<Object>> objects{ triangle };
    auto scene = std::make_shared<Scene>(objects);

    auto& camera = scene->get_camera();
    camera->set_z(5.0f);

    ES2Renderer renderer(scene, window);

    for (;;) {
        window->poll();

        triangle->set_rotation_z(triangle->get_rotation_z() + TRIANGLE_ROT_SPEED);

        renderer.render();
    }
}
