#pragma once
#include "VirtualShader.h"

class PhongShader :
    public VirtualShader
{
private:
    Vec4f nrm[3];
    Vec3f uv[3];
public:
    PhongShader(Model* m) { model = m; intensity = { 0.333333f, 0.333333f, 0.333333f }; }

    PhongShader& operator = (const PhongShader& g) {
        model = g.model;
        return *this;
    }

    virtual Vec4f vertex(int _face_num, int _nth_vert) {
        Vec4f vertex = Vec4f(model->vert(_face_num, _nth_vert), 1.f);
        nrm[_nth_vert] = Vec4f(model->normal(_face_num, _nth_vert), 0.f);
        nrm[_nth_vert] = normalize(nrm[_nth_vert]);
        vertex.y--;
        return get_MVP_matrix(ANGLEX, ANGLEY, ANGLEZ) * vertex;
    }

    virtual bool fragment(Vec3f bary, TGA_Color& color) {
        float ambient = 25.f;
        Vec3f bn = Vec3f(
            nrm[0].x * bary.x + nrm[1].x * bary.y + nrm[2].x * bary.z,
            nrm[0].y * bary.x + nrm[1].y * bary.y + nrm[2].y * bary.z,
            nrm[0].z * bary.x + nrm[1].z * bary.y + nrm[2].z * bary.z
            );
        bn = normalize(bn);
        float diffuse = std::max(0.f, (bn * normalize(LIGHT_DIR)));
        color = color * diffuse;
        return false;
    }
};