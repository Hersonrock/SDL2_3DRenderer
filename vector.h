#ifndef VECTOR
#define VECTOR

typedef  struct {
    float x;
    float y;
}vec2_t;

typedef  struct {
    float x;
    float y;
    float z;
}vec3_t;

typedef  struct {
    float x;
    float y;
    float z;
    float w;
}vec4_t;

/////////////////////VECTOR 2D//////////////////
float vect2_length(vec2_t v);
vec2_t vect2_add(vec2_t v1, vec2_t v2);
vec2_t vect2_sub(vec2_t v1, vec2_t v2);
vec2_t vect2_mult(vec2_t v, float factor);
vec2_t vect2_div(vec2_t v, float factor);
float vect2_dot(vec2_t v1, vec2_t v2);
void vect2_normalize(vec2_t* v);
void vect2_swap(vec2_t* v1, vec2_t* v2);
/////////////////////VECTOR 3D//////////////////
float vect3_length(vec3_t v);
vec3_t vect3_add(vec3_t v1, vec3_t v2);
vec3_t vect3_sub(vec3_t v1, vec3_t v2);
vec3_t vect3_mult(vec3_t v, float factor);
vec3_t vect3_div(vec3_t v, float factor);
float vect3_dot(vec3_t v1, vec3_t v2);
vec3_t vect3_cross(vec3_t v1, vec3_t v2);
void vect3_normalize(vec3_t* v);
/////////////////////VECTOR 4D//////////////////
/// Conversion
vec4_t vec4_from_vec3(vec3_t v);
vec3_t vec3_from_vec4(vec4_t v);


#endif // VECTOR