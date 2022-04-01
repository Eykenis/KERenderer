#pragma once
#include "VirtualShader.h"
class GouraudShader :
    public VirtualShader
{
    Vec3f intensity;
    Model* model;

    virtual Vec4f vertex(int _face_num, int _nth_vert) {
        intensity.v[_nth_vert] = std::max(0.f, model->normal(_face_num, _nth_vert) * light_dir);
        Vec4f vertex = Vec4f(model->vert(_face_num, _nth_vert), 1);
        return get_MVP_matrix(ANGLEX, ANGLEY, ANGLEZ) * vertex;
    }

    virtual bool fragment(Vec3f bary, TGA_Color& color) {
        color = TGA_Color(255, 255, 255, 255) * (intensity * bary);
        return false;
    }
};