#pragma once 

#include <glm/glm.hpp>


class Camera{
    public:
        Camera(glm::vec3 position ,float fov);
    public:
        inline void setPositionX(float x) { position_.x = x;};
        inline void setPositionY(float y) { position_.y = y;};
        inline void setPositionZ(float z) { position_.z = z;};
        glm::mat4 getProjection();
        glm::mat4 getView();
        glm::vec3 position_;

        glm::vec3 front_;
        glm::vec3 right_;
        glm::vec3 up_;

        glm::mat4 rotation_;
        void rotate(float x, float y, float z);
    private:
        void updateVectors();

    private:
        float fov_;


};