#include <iostream>

#include "threepp/threepp.hpp"
#include "InvertedPendulumOnCart.hpp"
#include "PID.hpp"
#include "Functions.hpp"

using namespace threepp;




InvertedPendulumOnCart pendulumCart(Vector3(0.0, 0.0, 0.0));
PID pid( 2.5, 3, 10,Vector3(0,0,0));



int main() {

    Canvas canvas("Dynamic system simulation");
    GLRenderer renderer{canvas.size()};
    std::shared_ptr<Scene> scene = Scene::create();
    std::shared_ptr<PerspectiveCamera>  camera = PerspectiveCamera::create(70, canvas.aspect(), 0.1f, 100);
    camera->position.z = 5;
    OrbitControls controls{*camera, canvas};

    std::shared_ptr<HemisphereLight>  light = HemisphereLight::create();
    std::shared_ptr<Mesh> plane = createPlane();

    scene->add(plane);
    scene->add(light);
    scene->add(pendulumCart.getCartMesh());
    scene->add(pendulumCart.getPendulumMesh());
    scene->add(pendulumCart.getRod());

    canvas.onWindowResize([&](WindowSize size) {
        camera->aspect = size.aspect();
        camera->updateProjectionMatrix();
        renderer.setSize(size);
    });

    Clock clock;
    canvas.animate([&]() {
        pendulumCart.update();
        renderer.render(*scene, *camera);
    });




}
