#pragma once
#include "VirtualShader.h"
class BlinnShader :
    public VirtualShader
{
private:
    Vec4f nrm[3];
    Vec2f uv[3];
public:
    Vec3f lookat;
    float gloss;

    BlinnShader(Model* m) { model = m; intensity = { 0.333333f, 0.333333f, 0.333333f }; gloss = 20; }

    BlinnShader& operator = (const BlinnShader& g) {
        model = g.model;
        lookat = g.lookat;
        return *this;
    }

    virtual Vec4f vertex(int _face_num, int _nth_vert) {
        Vec4f vertex = Vec4f(model->vert(_face_num, _nth_vert), 1.f);
        nrm[_nth_vert] = Vec4f(model->normal(_face_num, _nth_vert), 0.f);
        nrm[_nth_vert] = normalize(nrm[_nth_vert]);
        uv[_nth_vert] = Vec2f(model->uv(_face_num, _nth_vert));
        vertex.y -= .8f;
        return get_MVP_matrix() * vertex;
    }

    virtual bool fragment(Vec3f bary, TGA_Color& color) {
        Vec3f bn = Vec3f(
            nrm[0].x * bary.x + nrm[1].x * bary.y + nrm[2].x * bary.z,
            nrm[0].y * bary.x + nrm[1].y * bary.y + nrm[2].y * bary.z,
            nrm[0].z * bary.x + nrm[1].z * bary.y + nrm[2].z * bary.z
        );

        Vec2f this_uv = Vec2f(
            uv[0].x * bary.x + uv[1].x * bary.y + uv[2].x * bary.z,
            uv[0].y * bary.x + uv[1].y * bary.y + uv[2].y * bary.z
        );
        bn = normalize(bn);
        // specular:
        Vec3f halfDir = normalize(LIGHT_DIR + lookat);
        
        float ambient = 0.08f;

        float specular = std::pow(MAX(0.f, bn * halfDir), gloss);

        float diffuse = MAX(0.f, (bn * normalize(LIGHT_DIR)));

        // Half Lambert
        color = model->diff(this_uv.x, this_uv.y) * (0.5 * (diffuse + specular + ambient) + 0.5);

        return false;
    }
};