#pragma once
#include "VirtualShader.h"
Vec3f light_dir(0.f, 0.f, 1.f);

class GouraudShader :
    public VirtualShader
{
public:
    GouraudShader(Model* m) { model = m; intensity = { 0.333333f, 0.333333f, 0.333333f }; }

    virtual Vec4f vertex(int _face_num, int _nth_vert) {
        intensity.v[_nth_vert] = std::max(0.f, model->normal(_face_num, _nth_vert) * light_dir);
        Vec4f vertex = Vec4f(model->vert(_face_num, _nth_vert), 1.f);
        vertex.y += 0.7f;
        return get_MVP_matrix(ANGLEX, ANGLEY, ANGLEZ) * vertex;
    }
    
    virtual bool fragment(Vec3f bary, TGA_Color& color) {
        color = TGA_Color(255, 255, 255, 255);
        float it = std::min(intensity * bary, 1.f);
        color = color * it;
        return false;
    }

    GouraudShader& operator = (const GouraudShader& g) {
        model = g.model;
        return *this;
    }
};