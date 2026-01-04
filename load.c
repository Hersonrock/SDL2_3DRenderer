#include "load.h"
#include "array.h"
#include "io.h"

FILE* open_file(char* filename, char* mode) {
	FILE* fd = NULL;

	errno_t err = fopen_s(&fd, filename, mode);

	if (err != 0) {
		fprintf_s(stderr, "Failed to open file\n");
	}

	return fd;
}

bool read_file(FILE* file_stream, vec3_t** out_vertices, face_t** out_faces) {

	char  input_buffer[MAX_LINE_SIZE];
	int n_faces = 0;
	while (fgets(input_buffer, sizeof(input_buffer), file_stream)) {
		// remove trailing newline and carriage return
		uint32_t new_line_index = strcspn(input_buffer, "\r\n");
		input_buffer[new_line_index] = '\0';
		if (input_buffer[0] == '\0') {
			continue;
		}
		if (strncmp(input_buffer, "v ", 2) == 0) {
			vec3_t vertex = { 0 };
			sscanf_s(input_buffer, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);

			array_push(*out_vertices, vertex);
			continue;
		}

		else if (strncmp(input_buffer, "f ", 2) == 0) {
			face_t faces = { 0 };
			int vertex_indices[3];
			int texture_indices[3];
			int normal_indices[3];
			sscanf_s(input_buffer, "f %d/%d/%d %d/%d/%d %d/%d/%d",
				&vertex_indices[0], &texture_indices[0], &normal_indices[0],
				&vertex_indices[1], &texture_indices[1], &normal_indices[1],
				&vertex_indices[2], &texture_indices[2], &normal_indices[2]);
			faces.a = vertex_indices[0];
			faces.b = vertex_indices[1];
			faces.c = vertex_indices[2];
			array_push(*out_faces, faces);
			n_faces++;
			continue;
		}
		
	}
	meshes->n_faces = n_faces;
	return true;
}


bool read_file_stl(FILE* file_stream, vec3_t** out_vertices) {

	fseek(file_stream, 80, SEEK_SET);

	uint8_t number_of_triangles_raw[4];
	for (size_t i = 0; i < 4; i++) {
		number_of_triangles_raw[i] = fgetc(file_stream);
	}
	uint32_t number_of_triangles = (number_of_triangles_raw[0]) |
								   (number_of_triangles_raw[1] << 8) |
								   (number_of_triangles_raw[2] << 16) |
								   (number_of_triangles_raw[3] << 24);

	meshes->n_faces = number_of_triangles;
	for (uint32_t n = 0; n < number_of_triangles; n++) {
		vec3_t vertex[3] = { 0 };
		uint8_t float_raw[4] = { 0 };
		float vertex_data[3] = { 0.0f,0.0f,0.0f };

		fseek(file_stream, 12, SEEK_CUR);  //Skipping Normal vector
		for (size_t i = 0; i < 3; i++) {
			for (size_t j = 0; j < 3; j++) {
				for (size_t w = 0; w < 4; w++) {
					float_raw[w] = fgetc(file_stream);
					
				}
				memcpy_s(&vertex_data[j], sizeof(float), float_raw, sizeof(float));
			}
			vertex[i].x = vertex_data[0] / FACTOR;
			vertex[i].y = vertex_data[1] / FACTOR;
			vertex[i].z = vertex_data[2] / FACTOR;
			array_push(*out_vertices, vertex[i]);
		}
		fseek(file_stream, 2, SEEK_CUR);  //Skipping Attribute byte count
	}
	return true;
}


void load_obj_file_data(char* filename, mesh_t* in_mesh) {

	FILE* fd = NULL;
	in_mesh->vertices = NULL;
	in_mesh->faces = NULL;

	switch (in_mesh->filet) {
		case OBJ:
			fd = open_file(filename, "r" );
			read_file(fd, &in_mesh->vertices, &in_mesh->faces);
			break;
		case STL:
			fd = open_file(filename, "rb");
			read_file_stl(fd, &in_mesh->vertices);
			break;
	}
}
