#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "camera.hpp"
#include "renderer.hpp"
#include "vertex_array.hpp"
#include "index_buffer.hpp"
#include "vertex_buffer.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "ui.hpp"
#include "shader_program.hpp"
#include "model.hpp"
#include <memory>
#include <string>
#include <unordered_map>

#define UINEXT ImGui::SameLine();
#define UIDIVIDER ImGui::Separator();

#define axisVertexPath "D:/home/Prism/resources/shader/axis_vertex.glsl"
#define axisFragPath "D:/home/Prism/resources/shader/axis_frag.glsl"

#define texPath "D:/home/Prism/resources/img/image.png"
#define fontPath1 "D:/home/Prism/resources/font/JetBrainsMonoNerdFontMono-Regular.ttf"
#define fontPath2 "D:/home/Prism/resources/font/JetBrainsMonoNerdFontMono-SemiBold.ttf"

struct CreateModelInfo {
    const char* name;
    const char* modelPath;
    bool flip;
    glm::mat4 mMat = glm::mat4(1.0f);
};

struct CreateShaderInfo {
    const char* name;
    const char* vsPath;
    const char* fsPath;
};

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
    std::unordered_map<std::string, VertexArray*>   _vaos;
    std::unordered_map<std::string, VertexBuffer*>  _vbos;
    std::unordered_map<std::string, IndexBuffer*>   _ibos;
    std::unordered_map<std::string, Texture*>       _texs;

    std::vector<CreateModelInfo> createModelInfos_; 
    std::vector<CreateShaderInfo> createShaderInfos_; 

    glm::mat4 globalTransform_ = glm::mat4(1.0f);

    std::unordered_map<std::string, ShaderProgram>  shaders_;
    struct ModelRenderInfo {
        std::shared_ptr<pmodel::Model> ptr;
        glm::mat4 mMat;
    };
    std::unordered_map<std::string, ModelRenderInfo>  models_;

    float _lightColor[3];
    float _lightPos[3];

    bool _axis_mode;
    bool _should_cull;

    friend class UI;
    UI* _ui;
    bool _show_demo;
    bool show_debug_;

    enum Theme {
        Light =  0,
        Dark,
        Classic,
    };

    int _theme = Theme::Dark;

    std::unordered_map<std::string, ImFont*> _fonts;
public:
    Renderer(int w, int h, const char* name);
    ~Renderer();

    bool init();

    void run();

    inline int width() const { return _width; }
    inline int height() const { return _height; }
    inline void setCamera(Camera* camera) { _camera = camera; }

    void createModel(CreateModelInfo info);
    void createShader(CreateShaderInfo info);

    inline void setGlobalTransform(glm::mat4 mat) { globalTransform_ = mat; }
private:
    void initModels();
    void initShaders();

    void processInput(GLFWwindow *window);
    void toggleFrameMode();
    void toggle(bool* value);
    void axisShader();
    void drawAxis(glm::mat4& view);
    void mouse_callback(double xposIn, double yposIn);
    void scroll_callback( double xoffset, double yoffset);
};