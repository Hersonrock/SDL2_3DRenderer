#include "vector.h"

/////////////////////VECTOR 2D//////////////////
float vect2_length(vec2_t v) {
    float length = v.x * v.x + v.y * v.y;
    length = sqrt(length);
    return length;
}

vec2_t vect2_add(vec2_t v1, vec2_t v2) {
    vec2_t result = {0,0};
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;

    return result;
}
vec2_t vect2_sub(vec2_t v1, vec2_t v2) {
    vec2_t result = { 0, 0};
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;

    return result;
}
vec2_t vect2_mult(vec2_t v, float factor) {
    vec2_t result = {0, 0};
    result.x = v.x * factor;
    result.y = v.y * factor;

    return result;
}
vec2_t vect2_div(vec2_t v, float factor) {
    vec2_t result = { 0,0 };
    assert(factor != 0);
    float factor_div = 1 / factor;
    result.x = v.x * factor_div;
    result.y = v.y * factor_div;

    return result;
}
float vect2_dot(vec2_t v1, vec2_t v2) {
    float result;
    result = v1.x * v2.x + v1.y * v2.y;
    return result;
}
void vect2_normalize(vec2_t* v) {
    *v = vect2_div(*v, vect2_length(*v));
}
void vect2_swap(vec2_t* v1, vec2_t* v2) {

    vec2_t temp = *v1;
    v1->x = v2->x;
    v1->y = v2->y;
    v2->x = temp.x;
    v2->y = temp.y;
}
/////////////////////VECTOR 3D//////////////////
float vect3_length(vec3_t v) {
    float length = v.x * v.x + v.y * v.y + v.z * v.z;
    length = sqrt(length);
    return length;
}
vec3_t vect3_add(vec3_t v1, vec3_t v2) {
    vec3_t result = { 0, 0, 0 };
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;

    return result;
}
vec3_t vect3_sub(vec3_t v1, vec3_t v2) {
    vec3_t result = { 0, 0, 0 };
    result.x = v1.x - v2.x;
    result.y = v1.y - v2.y;
    result.z = v1.z - v2.z;

    return result;
}
vec3_t vect3_mult(vec3_t v, float factor) {
    vec3_t result = { 0, 0, 0 };
    result.x = v.x * factor;
    result.y = v.y * factor;
    result.z = v.z * factor;

    return result;
}
vec3_t vect3_div(vec3_t v, float factor) {
    vec3_t result = { 0, 0, 0 };
    assert(factor != 0);
    float factor_div = 1 / factor;
    result.x = v.x * factor_div;
    result.y = v.y * factor_div;
    result.z = v.z * factor_div;

    return result;
}
float vect3_dot(vec3_t v1, vec3_t v2) {
    float result;
    result = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
    return result;
}
vec3_t vect3_cross(vec3_t v1, vec3_t v2) {
    vec3_t result = { 0, 0, 0 };
    result.x = v1.y * v2.z - v2.y * v1.z;
    result.y = v2.x * v1.z - v1.x * v2.z;
    result.z = v1.x * v2.y - v2.x * v1.y;

    return result;
}
void vect3_normalize(vec3_t* v) {
    *v = vect3_div(*v, vect3_length(*v));
}
vec4_t vec4_from_vec3(vec3_t v) {
    vec4_t out = { 0, 0, 0, 0 };

    out.x = v.x;
    out.y = v.y;
    out.z = v.z;
    out.w = 1;

    return out;
}
vec3_t vec3_from_vec4(vec4_t v) {
    vec3_t out = { 0, 0, 0 };
    out.x = v.x;
    out.y = v.y;
    out.z = v.z;

    return out;
}
