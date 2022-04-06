#pragma once
#include "VirtualShader.h"

class GouraudShader :
    public VirtualShader
{
private:
    Vec2f uv[3];
public:
    GouraudShader(Model* m) { model = m; intensity = { 0.333333f, 0.333333f, 0.333333f }; }

    virtual Vec4f vertex(int _face_num, int _nth_vert) {
        intensity.v[_nth_vert] = MAX(0.f, model->normal(_face_num, _nth_vert) * normalize(LIGHT_DIR));
        Vec4f vertex = Vec4f(model->vert(_face_num, _nth_vert), 1.f);
        uv[_nth_vert] = Vec2f(model->uv(_face_num, _nth_vert));
        vertex.y -= 1.f;
        return get_MVP_matrix() * vertex;
    }
    
    virtual bool fragment(Vec3f bary, TGA_Color& color) {
        color = TGA_Color(255, 255, 255, 255);
        Vec2f this_uv = Vec2f(
            uv[0].x * bary.x + uv[1].x * bary.y + uv[2].x * bary.z,
            uv[0].y * bary.x + uv[1].y * bary.y + uv[2].y * bary.z
        );

        float diffuse = MIN(intensity * bary, 1.f);
        color = model->diff(this_uv.x, this_uv.y) * diffuse;
        return false;
    }

    GouraudShader& operator = (const GouraudShader& g) {
        model = g.model;
        return *this;
    }
};