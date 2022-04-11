#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Cam
{
private:
    glm::mat4 _proj;
    float _height, _width;

    glm::vec3 _position;
    glm::vec3 _front;
    glm::vec3 _up;
    glm::vec3 _right;
    glm::vec3 _worldUp;

    float _yaw;
    float _pitch;
    float _fov;
    float _lastx, _lasty;
    bool _firstMouse;

    float _mouseSensitivity;
    float _movementSpeed;

public:
    enum Camera_Movement {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    Cam(float height, float width) 
        : _height(height), _width(width), _position(glm::vec3(0.0f, 0.0f, 500.0f)), _worldUp(glm::vec3(0.0f, 1.0f, 0.0f)), _right(glm::vec3(0,0,0)),
        _yaw(-90.0f), _pitch(0.0f), _front(glm::vec3(0.0f, 0.0f, -1.0f)), _up(glm::vec3(0,0,0)), _mouseSensitivity(0.1f), _movementSpeed(600.0f), _fov(45.0f),
        _firstMouse(true), _lastx(width/2), _lasty(height/2)
    {
        _proj = glm::perspective(glm::radians(_fov), (float)height / (float)width, 0.1f, 8000.0f);
    }

    inline glm::mat4 GetViewMatrix() { return glm::lookAt(_position, _position + _front, _up); }


    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= _mouseSensitivity;
        yoffset *= _mouseSensitivity;

        _yaw += xoffset;
        _pitch += yoffset;

        if (constrainPitch)
        {
            if (_pitch > 89.0f)
                _pitch = 89.0f;
            if (_pitch < -89.0f)
                _pitch = -89.0f;
        }

        _updateCameraVectors();
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = _movementSpeed * deltaTime;
        if (direction == FORWARD)
            _position += _front * velocity;
        if (direction == BACKWARD)
            _position -= _front * velocity;
        if (direction == LEFT)
            _position -= _right * velocity;
        if (direction == RIGHT)
            _position += _right * velocity;
        if (direction == UP)
            _position += _up    * velocity;
        if (direction == DOWN)
            _position -= _up    * velocity;

    }

    glm::mat4 CamTick(GLFWwindow* window)
    {
        glm::mat4 view = GetViewMatrix();
        return _proj * view;
    }

private:
    void _updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        front.y = sin(glm::radians(_pitch));
        front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
        _front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        _right = glm::normalize(glm::cross(_front, _worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        _up = glm::normalize(glm::cross(_right, _front));
    }
};