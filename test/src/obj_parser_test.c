#define CLOVE_SUITE_NAME ObjParserTest
#include "clove-unit.h"
#include "test-utils.h"
#define OBJ_PARSER_IMPLEMENTATION
#include "obj_parser.h"


CLOVE_TEST(TestCountMeshData) {
   const char *base_test_path = CLOVE_EXEC_BASE_PATH();
   const char *source_path = tut_concat_path(base_test_path, "\\resources\\quad.obj");

   obj_t *mesh;
   int result = obj_parser_parse(&mesh, source_path);

   CLOVE_INT_EQ(0, result);
   CLOVE_ULLONG_EQ(4, mesh->vertex_count);
   CLOVE_ULLONG_EQ(4, mesh->vertex_texture_count);
   CLOVE_ULLONG_EQ(1, mesh->vertex_normal_count);
   CLOVE_ULLONG_EQ(2, mesh->face_count);
}

CLOVE_TEST(TestQuadParse) {
   const char *base_test_path = CLOVE_EXEC_BASE_PATH();
   const char *source_path = tut_concat_path(base_test_path, "\\resources\\quad.obj");

   obj_t *mesh;
   int result = obj_parser_parse(&mesh, source_path);

   //T1
   //V1
   //Position
   CLOVE_FLOAT_EQ(1, mesh->triangles[0].v1.position.x);
   CLOVE_FLOAT_EQ(-1, mesh->triangles[0].v1.position.y);
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v1.position.z);
   //UV
   CLOVE_FLOAT_EQ(1, mesh->triangles[0].v1.uv.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v1.uv.y);
   //Normal
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v1.normal.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v1.normal.y);
   CLOVE_FLOAT_EQ(1, mesh->triangles[0].v1.normal.z);
   //V2
   //Position
   CLOVE_FLOAT_EQ(-1, mesh->triangles[0].v2.position.x);
   CLOVE_FLOAT_EQ(-1, mesh->triangles[0].v2.position.y);
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v2.position.z);
   //UV
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v2.uv.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v2.uv.y);
   //Normal
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v2.normal.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v2.normal.y);
   CLOVE_FLOAT_EQ(1, mesh->triangles[0].v2.normal.z);
   //V3
   //Position
   CLOVE_FLOAT_EQ(-1, mesh->triangles[0].v3.position.x);
   CLOVE_FLOAT_EQ(1, mesh->triangles[0].v3.position.y);
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v3.position.z);
   //UV
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v3.uv.x);
   CLOVE_FLOAT_EQ(1, mesh->triangles[0].v3.uv.y);
   //Normal
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v3.normal.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[0].v3.normal.y);
   CLOVE_FLOAT_EQ(1, mesh->triangles[0].v3.normal.z);

   //T2
   //V1
   //Position
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v1.position.x);
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v1.position.y);
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v1.position.z);
   //UV
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v1.uv.x);
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v1.uv.y);
   //Normal
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v1.normal.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v1.normal.y);
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v1.normal.z);
   //V2
   //Position
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v2.position.x);
   CLOVE_FLOAT_EQ(-1, mesh->triangles[1].v2.position.y);
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v2.position.z);
   //UV
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v2.uv.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v2.uv.y);
   //Normal
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v2.normal.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v2.normal.y);
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v2.normal.z);
   //V3
   //Position
   CLOVE_FLOAT_EQ(-1, mesh->triangles[1].v3.position.x);
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v3.position.y);
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v3.position.z);
   //UV
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v3.uv.x);
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v3.uv.y);
   //Normal
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v3.normal.x);
   CLOVE_FLOAT_EQ(0, mesh->triangles[1].v3.normal.y);
   CLOVE_FLOAT_EQ(1, mesh->triangles[1].v3.normal.z);
}

CLOVE_TEST(TestSuzanneVertexesCount) {
   const char *base_test_path = CLOVE_EXEC_BASE_PATH();
   const char *source_path = tut_concat_path(base_test_path, "\\resources\\suzanne.obj");

   obj_t *mesh;
   CLOVE_INT_EQ(0, obj_parser_parse(&mesh, source_path));
   CLOVE_NOT_NULL(mesh);
   CLOVE_INT_EQ(511, mesh->vertex_count);
   CLOVE_INT_EQ(590, mesh->vertex_texture_count);
   CLOVE_INT_EQ(507, mesh->vertex_normal_count);
   CLOVE_INT_EQ(968, mesh->face_count);
}