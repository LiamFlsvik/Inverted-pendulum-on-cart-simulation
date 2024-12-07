#ifndef CART_HPP
#define CART_HPP

#include "threepp/threepp.hpp"
#include <memory>
#include <cmath>

class InvertedPendulumOnCart {
public:
    InvertedPendulumOnCart(const threepp::Vector3 &initialPosition){

//Cart
        geometry = threepp::BoxGeometry::create(1.0, 0.5, 0.5);
        material = threepp::MeshPhongMaterial::create();
        material->color = threepp::Color::darkred;
        cartMesh = threepp::Mesh::create(geometry, material);
        cartMesh->position.copy(initialPosition);
//Pendulum
        sphereGeometry = threepp::SphereGeometry::create(0.25, 16, 16);
        sphereMaterial = threepp::MeshPhongMaterial::create();
        sphereMaterial->color = threepp::Color::orangered;; ;
        sphereMesh = threepp::Mesh::create(sphereGeometry, sphereMaterial);
//Line, TODO: implement cylinder instead.
        lineMaterial = threepp::LineBasicMaterial::create();
        lineMaterial->color = threepp::Color::blue;;
        lineGeometry = threepp::BufferGeometry::create();
        lineGeometry->setFromPoints({
            cartMesh->position,
            sphereMesh->position,
        });
        rod = threepp::Line::create(lineGeometry, lineMaterial);


        cart.position = initialPosition;
        pendulum.position = threepp::Vector3(initialPosition.x, pendulum.rodLength, 0);
    }



    void update() {
        dt = clock.getDelta();

        solveDifferentialEquation();

        cartMesh->position.x = cart.position.x;
        pendulum.position.x = cart.position.x + pendulum.rodLength * std::sin(pendulum.angle);
        pendulum.position.y = pendulum.rodLength * std::cos(pendulum.angle);

        sphereMesh->position.set(pendulum.position.x, pendulum.position.y, 0);




    }

    void solveDifferentialEquation() {
        cart.acceleration.x = (+pendulum.mass * pendulum.rodLength * pendulum.angularVelocity * pendulum.angularVelocity * std::sin(pendulum.angle) - pendulum.mass * pendulum.rodLength * pendulum.angularAcceleration * std::cos(pendulum.angle)+cart.force) / (pendulum.mass + cart.mass);

        pendulum.angularAcceleration = (g*std::sin(pendulum.angle)+cart.acceleration.x*std::cos(pendulum.angle))/pendulum.rodLength;

        cart.velocity.x +=cart.acceleration.x*dt;
        cart.position.x +=cart.velocity.x*dt;

        pendulum.angularVelocity += pendulum.angularAcceleration*dt;
        pendulum.angle += pendulum.angularVelocity*dt;

    }

    std::shared_ptr<threepp::Mesh> getCartMesh() const {
        return cartMesh;
    }
    std::shared_ptr<threepp::Mesh> getPendulumMesh() const {
        return sphereMesh;
    }
    std::shared_ptr<threepp::Line> getRod() const {
        return rod;
    }



private:

    struct CartPhysics {
        float mass = 1.0;
        threepp::Vector3 acceleration;
        threepp::Vector3 position;
        threepp::Vector3 velocity;
        float force = 0.0;
    };

    struct PendulumPhysics {
        threepp::Vector3 position;
        float mass = 3.0;
        float angle = threepp::math::PI*2+0.01;
        float angularVelocity = 0.0;
        float angularAcceleration = 0.0;
        float rodLength = 5.0;
    };


    CartPhysics cart;
    PendulumPhysics pendulum;

    threepp::Clock clock;
    float dt = 0.1;
    float elapsedTime = 1;
    float g = 9.81;

    std::shared_ptr<threepp::BoxGeometry> geometry;
    std::shared_ptr<threepp::MeshPhongMaterial> material;
    std::shared_ptr<threepp::Mesh> cartMesh;


    std::shared_ptr<threepp::SphereGeometry> sphereGeometry;
    std::shared_ptr<threepp::MeshPhongMaterial> sphereMaterial;
    std::shared_ptr<threepp::Mesh> sphereMesh;

    std::shared_ptr<threepp::LineBasicMaterial> lineMaterial;
    std::shared_ptr<threepp::BufferGeometry> lineGeometry;
    std::shared_ptr<threepp::Line> rod;

};

#endif // CART_HPP
