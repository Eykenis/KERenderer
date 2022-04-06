#pragma once
struct mesh
{
	const char* _obj_file_name;
	const char* _dif_file_name;
	const char* _nrm_file_name;
	const char* _spe_file_name;
	const char* _mtl_file_name;
	mesh(const char* f1, const char* f2 = nullptr, const char* f3 = nullptr, const char* f4 = nullptr, const char* f5 = nullptr) :
		_obj_file_name(f1), _dif_file_name(f2), _nrm_file_name(f3), _spe_file_name(f4), _mtl_file_name(f5) {}

};

extern mesh mesh_Aiz;

extern mesh mesh_African;