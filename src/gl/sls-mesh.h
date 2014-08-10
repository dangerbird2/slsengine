#ifndef MESH_H
#define MESH_H


#include "shaderutils.h"
#include "../stdhdr.h"
#include "../linalg/linmath.h"

typedef struct {
    GLuint vbo;
    GLuint ibo;
    mat4x4 transform_mat;
} slsMesh;

typedef struct {
    float pos[4];
    float normal[4];
    float color[4];
    float uv[2];
} Vertex;

slsMesh cube_mesh();
slsMesh plane_mesh();

/**
 * frees buffers from GPU
 **/
void free_mesh(slsMesh *M);

/**
 * scene graph info
 */

 typedef struct _sceneNode {
    char *name;
    slsMesh *mesh;
    mat4x4 transform;
    
    /**
     * @brief number of elements allocated
     */
    uint size;

    /**
     * @brief number of nodes included
     */
    uint len;

    /**
     * @brief children node data
     */
    struct _sceneNode **children;

    /**
     * @brief parent node
     */
    struct _sceneNode *parent;
 } srSceneNode;

/**
 * @brief allocates a new pointer to a SceneNode
 * @details [long description]
 * @return [description]
 */
srSceneNode *sr_new_node(const char *name);

/**
 * @brief frees memory associated with node and its children
 * @details [long description]
 * 
 * @param node pointer to scene node
 */
void sr_delete_node(srSceneNode *node);

void sr_draw_node(srSceneNode *node, mat4x4 view);




#endif //MESH_H
