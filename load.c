#include "load.h"
#include "array.h"

FILE* open_file(char* filename) {
	FILE* fd = NULL;

	errno_t err = fopen_s(&fd, filename, "r");

	if (err != 0) {
		fprintf_s(stderr, "Failed to open file\n");
	}

	return fd;
}

bool read_file(FILE* obj_file_descriptor, vec3_t **out_vertices, face_t **out_faces) {

	char  input_buffer[MAX_LINE_SIZE];
	while (fgets(input_buffer, sizeof(input_buffer), obj_file_descriptor)) {
		// remove trailing newline and carriage return
		uint32_t new_line_index = strcspn(input_buffer, "\r\n");
		input_buffer[new_line_index] = '\0';
		if (input_buffer[0] == '\0') {
			continue;
		}
		if (strncmp(input_buffer, "v ", 2) == 0){
			vec3_t vertex = {0};
			sscanf_s(input_buffer, "v %f %f %f", &vertex.x, &vertex.y, &vertex.z);

			array_push(*out_vertices, vertex);
			continue;
		}

		else if (strncmp(input_buffer, "f ", 2) == 0) {
			face_t faces = {0};
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
			continue;
		}
	}
	return true;
}


void load_obj_file_data(char* filename, mesh_t* in_mesh) {
	FILE* fd = open_file(filename);
	in_mesh->vertices = NULL;
	in_mesh->faces = NULL;
	read_file(fd, &in_mesh->vertices, &in_mesh->faces);
}