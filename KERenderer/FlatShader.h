#pragma once

#include "VirtualShader.h"

class FlatShader :
    public VirtualShader
{
private:
    Vec3f coords[3];
public:
    FlatShader(Model* m) { model = m; intensity = { 0.333333f, 0.333333f, 0.333333f }; }
    virtual Vec4f vertex(int _face_num, int _nth_vert) {
        coords[_nth_vert] = model->vert(_face_num, _nth_vert);
        Vec4f vertex = Vec4f(model->vert(_face_num, _nth_vert), 1.f);
        vertex.y -= 1.f;
        return get_MVP_matrix(ANGLEX, ANGLEY, ANGLEZ) * vertex;
    }
    virtual bool fragment(Vec3f bary, TGA_Color& color) {
        color = TGA_Color(255, 255, 255, 255);
        float it = normalize(LIGHT_DIR) * normalize((coords[2] - coords[1]) ^ (coords[0] - coords[1]));
        color = color * it;
        return false;
    }
};