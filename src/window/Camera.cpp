#include "Camera.hpp"

#include <glm/ext.hpp>


Camera::Camera(glm::vec3 position , float fov) : position_(position) , fov_(fov) , rotation_(1.0f){
    updateVectors();
}

void Camera::updateVectors(){
    front_ = glm::vec3(rotation_ * glm::vec4(0,0,-1,1));
    right_ = glm::vec3(rotation_ * glm::vec4(1,0,0,1));
    up_ = glm::vec3(rotation_ * glm::vec4(0,1,0,1));
}

void Camera::rotate(float x, float y , float z){
    rotation_ = glm::rotate(rotation_ , z , glm::vec3(0,0,1));
    rotation_ = glm::rotate(rotation_ , y , glm::vec3(0,1,0));
    rotation_ = glm::rotate(rotation_ , x , glm::vec3(1,0,0));

    updateVectors();
}

glm::mat4 Camera::getProjection(){
    float aspect = static_cast<float>(1280) / static_cast<float>(720);
    return glm::perspective(fov_, aspect , 0.1f,100.0f);
}

glm::mat4 Camera::getView(){
    return glm::lookAt(position_ , position_+front_ , up_);
}