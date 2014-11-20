#include "sls-content.h"
#include "sls-sprite.h"

#include "sls-mesh.h"
#include "sls-shader.h"


#include "../stdhdr.h"

static const int MAX_KEY_SIZE = 200;

static const slsContentManager sls_contentManager_proto = {
    .assets_dir = NULL,

    .content = NULL,
    .textures = NULL,
    .sprites = NULL,
    .shaders = NULL,
    .meshes = NULL,
    .get_asset_path = slsContentManager_get_full_path,
    .init = slsContentManager_init,
    .dtor = slsContentManager_destroy
};

slsContentManager *slsContentManager_new(char const *path)
{
    slsContentManager *self = NULL;
    self = sls_objalloc(&sls_contentManager_proto, sizeof(slsContentManager));
    check_mem(self);
    if (!path) {
        self = slsMsg(self, init, "projects/slsengine/content");
    } else {
        self = slsMsg(self, init, path);
    }
    

    return self;

error:
    if (self) {
        free(self);
    }
    return NULL;
}

char const *sls_get_home_dir() 
{
    // get path of home directory
    // todo: give valid home variable for Wingdows
    char const *home_env = "HOME";
    return g_getenv(home_env);
    
}

GString *sls_get_assets_dir(char const *assets_shortpath)
{
    char *full_dir = NULL;
    GString *dir_str = NULL;

    char const *home_dir = sls_get_home_dir();

    if (assets_shortpath) {
        full_dir = g_build_path("/", home_dir, assets_shortpath, NULL);
    } else {
        log_warn("no asset dir given!");
        full_dir = g_build_path("/", home_dir, "assets", NULL);
    }
    check_mem(full_dir);

    dir_str = g_string_new(full_dir);
    check_mem(dir_str);

    free(full_dir);
    
    return dir_str;

error:
    if (full_dir) {free(full_dir);}
    if (dir_str) {g_string_free(dir_str, true);}

    return NULL;
}

slsContentManager *slsContentManager_init(slsContentManager *self, char const *assets_shortpath)
{
    if (!self) {return NULL;}

    *self = sls_contentManager_proto;

    self->assets_dir = sls_get_assets_dir(assets_shortpath);

    // create hash tables with two arrays, corresponding to pointers to hash table attributes
    // and cooresponding free functions for specified value type
    GHashTable **tables[] = {
        &(self->content),
        &(self->textures),
        &(self->sprites),
        &(self->shaders),
        &(self->meshes),
        NULL
    };
    GDestroyNotify free_fns[] = {
        NULL,
        sls_hash_texture_free,
        sls_hash_sprite_free,
        sls_hash_shader_free,
        sls_hash_mesh_free
    };

    GDestroyNotify string_key_free = free;

    for (int i=0; tables[i] != NULL; i++) {
        GHashTable *table = g_hash_table_new_full(
            g_str_hash,
            g_str_equal,
            string_key_free,
            free_fns[i]);
        
        check_mem(table);

        *(tables[i]) = table;
    }

    return self;

error:
    log_err("slsContentManager_init failure");
    slsMsg(self, dtor);
    return NULL;
}

void sls_clear_hash(GHashTable *hash, slsFreeFn free_fn)
{

    

    
}

void slsContentManager_destroy(slsContentManager *self)
{
    if (!self) {return;}

    if (self->assets_dir) {
        g_string_free(self->assets_dir, true);
    }

    GHashTable **tables[] = {
        &(self->content),
        &(self->shaders),
        &(self->sprites),
        &(self->meshes),
        &(self->textures),
        NULL
    };
    for (int i=0; tables[i] != NULL; i++) {
        if (*tables[i]) {
            g_hash_table_unref(*tables[i]);
        }
    }
    
    free(self);
}

void sls_hash_texture_free(void * texture)
{
    if (!texture) {return;}
    SDL_DestroyTexture((SDL_Texture *) texture);
}

void sls_hash_shader_free(void * shader)
{
    if (!shader) {return;}
    slsShader *self = shader;
    if (self->dtor != NULL){
        self->dtor(self);
    }
}

void sls_hash_mesh_free(void * mesh)
{
    if (!mesh) {return;}
    slsMesh *self = mesh;
    if (self->dtor){
        slsMsg(self, dtor);
    }
}

void sls_hash_sprite_free(void *sprite)
{
    if (!sprite) {return;}
    slsSprite_destroy((slsSprite*)sprite);
}


char *slsContentManager_get_full_path(
    slsContentManager *self,
    char const *path)
{
    char *str = NULL;
    str = g_build_path("/", self->assets_dir->str, path, NULL);
    
    return str;
}


SDL_Texture *slsContentManager_load_texture(
    slsContentManager *self,
    SDL_Renderer *renderer,
    char const *texture_key,
    char const *image_path)
{
    SDL_Surface *tmp_surface = NULL;
    SDL_Texture *texture = NULL;
    char *path = slsMsg(self, get_asset_path, image_path);

    tmp_surface = IMG_Load(path);
    if (!tmp_surface) {
        g_critical("IMG_Load(): %s\n", IMG_GetError());
        g_return_val_if_reached(NULL);
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp_surface);
    
    g_hash_table_insert(
        self->textures,
        g_strndup(texture_key, MAX_KEY_SIZE),
        texture);


    free(path);
    return texture;
}


slsShader *slsContentManager_load_shader(
    slsContentManager *self,
    char const *shader_name,
    char const *vspath,
    char const *fspath)
{
    slsShader *shader = NULL;
    char *rvspath = slsMsg(self, get_asset_path, vspath);
    char *rfspath = slsMsg(self, get_asset_path, fspath);
    shader = slsShader_create(shader_name, rvspath, rfspath);
    g_return_val_if_fail(shader != NULL, NULL);

    free(rvspath);
    free(rfspath);

    g_hash_table_insert(
        self->shaders,
        g_strndup(shader_name, MAX_KEY_SIZE),
        shader);

    return shader;
}

slsMesh *slsContentManager_loadExistingMesh(
    slsContentManager *self,
    char const *mesh_name,
    slsMesh *mesh)
{
    g_hash_table_insert(
        self->meshes,
        g_strndup(mesh_name, MAX_KEY_SIZE),
        mesh
    );

    return mesh;
}