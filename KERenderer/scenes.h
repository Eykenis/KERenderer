#pragma once
#ifndef SCENES_H
#define SCENES_H
#include "VirtualShader.h"
#include "model.h"
#include "pipeline.h"
#include "TGA_Image.h"
struct Scenes {

	void african(Model* model, VirtualShader& shader, TGA_Image& image) {
		model = new Model("african.obj");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 1);
		delete model;
	}

	void dark_magician(Model* model, VirtualShader& shader, TGA_Image& image) {
		model = new Model("./obj/dark_magician/SubTool-0-12649208.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-1-3545828.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-2-3995078.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-3-14259780.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-4-7489388.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-5-4670765.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-6-9130786.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-7-3995078.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-8-15602477.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		//model = new Model("./obj/dark_magician/SubTool-9-4631043.OBJ");
		//shader.model = model;
		//rasterizeTri(image, model, WHITE, shader);
		//delete model;

		model = new Model("./obj/dark_magician/SubTool-10-4631043.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-11-4631043.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-12-958719.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-13-958719.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-14-3923915.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;

		model = new Model("./obj/dark_magician/SubTool-15-3923915.OBJ");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
		delete model;
	}

	void a2(Model* model, VirtualShader& shader, TGA_Image& image) {
		model = new Model("0.obj");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 1);
		delete model;
	}

	void lm(Model* model, VirtualShader& shader, TGA_Image& image) {
		model = new Model("luomo.obj");
		shader.model = model;
		rasterizeTri(image, model, WHITE, shader, 2);
	}
};
#endif // SCENES_H