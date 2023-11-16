#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "camera.hpp"
#include "geo.hpp"
#include "renderer.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "anim.hpp"
#include "ui.hpp"
#include "scene.hpp"
#include "shader_program.hpp"

#define UINEXT ImGui::SameLine();
#define UIDIVIDER ImGui::Separator();

#define DISPLAY_BUFFER_SIZE 1024
#define EDITOR_BUFFER_SIZE 2048

#define vertexPath "../resources/shader/vertex.glsl"
#define fragPath "../resources/shader/frag.glsl"
#define axisVertexPath "../resources/shader/axis_vertex.glsl"
#define axisFragPath "../resources/shader/axis_frag.glsl"
#define pureVertexPath "../resources/shader/pure_vertex.glsl"
#define pureFragPath "../resources/shader/pure_frag.glsl"
#define colorVertexPath "../resources/shader/color_vertex.glsl"
#define colorFragPath "../resources/shader/color_frag.glsl"
#define meshVertexPath "../resources/shader/mesh_vertex.glsl"
#define meshFragPath "../resources/shader/mesh_frag.glsl"
#define texPath "../resources/img/image.png"
#define fontPath1 "../resources/font/JetBrainsMonoNerdFontMono-Regular.ttf"
#define fontPath2 "../resources/font/JetBrainsMonoNerdFontMono-SemiBold.ttf"

class UI;

class Renderer {
private:
    // 窗口信息
    int _width;
    int _height;
    const char* _name;
    GLFWwindow* _window;

    // 摄像机属性
    Camera* _camera;
    float _aspect;
    bool _first_mouse;
    glm::mat4 _vMat;

    bool _frame_mode;
    float _delta_time;
    float _last_time;
    float _last_x, _last_y;
    std::unordered_map<std::string, Geo*>           _geos;
    std::unordered_map<std::string, VertexArray*>   _vaos;
    std::unordered_map<std::string, VertexBuffer*>  _vbos;
    std::unordered_map<std::string, IndexBuffer*>   _ibos;
    std::unordered_map<std::string, Texture*>       _texs;
    std::unordered_map<std::string, ShaderProgram>  _shaders;
    float _lightColor[3];
    float _lightPos[3];

    char _editor_buffer[EDITOR_BUFFER_SIZE];
    bool _is_editing;
    ShaderType _current_shader_src;

    float _clear_color;
    std::string _shader_program;

    bool _axis_mode;
    bool _show_demo;
    bool _show_editor;
    bool _should_cull;
    unsigned int _front_face;
    bool _modify_presicion;

    friend class UI;
    UI* _ui;

    enum Theme {
        Light =  0,
        Dark,
        Classic,
    };

    int _theme = Theme::Dark;
    float _color[3];
    bool _use_color;

    std::unordered_map<std::string, ImFont*> _fonts;
    std::vector<const char*> _shader_sources = {
        "none",
        vertexPath, 
        fragPath, 
        axisVertexPath,
        axisFragPath,
        pureVertexPath,
        pureFragPath,
        colorVertexPath,
        colorFragPath,
        meshVertexPath,
        meshFragPath,
    };
public:
    Renderer(int w, int h, const char* name);
    ~Renderer();

    bool init();

    void run();

    inline int width() const { return _width; }
    inline int height() const { return _height; }

private:
    void processInput(GLFWwindow *window);
    void toggleFrameMode();
    void toggle(bool* value);
    void axisShader();
    void drawAxis(glm::mat4& view);
    void mouse_callback(double xposIn, double yposIn);
    void scroll_callback( double xoffset, double yoffset);
};