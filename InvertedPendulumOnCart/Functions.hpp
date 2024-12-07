
#ifndef PLANE_HPP
#define PLANE_HPP
auto createPlane() {
    std::shared_ptr<threepp::PlaneGeometry> planeGeometry = threepp::PlaneGeometry::create(100, 100);
    std::shared_ptr<threepp::MeshLambertMaterial> planeMaterial = threepp::MeshLambertMaterial::create();
    planeMaterial->color = threepp::Color::gray;
    planeMaterial->side = threepp::Side::Double;
    auto plane = threepp::Mesh::create(planeGeometry, planeMaterial);
    plane->position.y = -10;

    plane->rotateX(threepp::math::degToRad(90));
    return plane;
}




#endif //PLANE_HPP
