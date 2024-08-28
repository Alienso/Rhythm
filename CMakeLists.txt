cmake_minimum_required(VERSION 3.23)
project(Rhythm)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -g -O0")
endif(WIN32)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -g -O0 -fsanitize=address")
endif(UNIX)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

include_directories(${PROJECT_SOURCE_DIR}/source)
include_directories(${PROJECT_SOURCE_DIR}/include)

link_directories(${PROJECT_SOURCE_DIR}/lib)
link_directories(${PROJECT_SOURCE_DIR}/lib/portaudio)
if (WIN32)
    link_directories(${PROJECT_SOURCE_DIR}/lib/GLFW/lib-mingw-w64)
endif(WIN32)

add_executable(Rhythm main.cpp

        include/imgui/imgui.cpp include/imgui/imgui.h
        include/imgui/imgui_draw.cpp
        include/imgui/imgui_tables.cpp include/imgui/imgui_widgets.cpp
        include/imgui/imgui_impl_glfw.h include/imgui/imgui_impl_glfw.cpp
        include/imgui/imgui_impl_opengl3.h include/imgui/imgui_impl_opengl3.cpp

        include/stb_image.cpp include/stb_image.h
        include/glad.c include/glad.h

        source/render/buffer/VertexBuffer.cpp source/render/buffer/VertexBuffer.h
        source/render/buffer/IndexBuffer.cpp source/render/buffer/IndexBuffer.h
        source/render/buffer/VertexArray.cpp source/render/buffer/VertexArray.h
        source/render/buffer/VertexBufferLayout.cpp source/render/buffer/VertexBufferLayout.h
        source/render/buffer/UniformBuffer.cpp source/render/buffer/UniformBuffer.h
        source/render/buffer/FrameBuffer.cpp source/render/buffer/FrameBuffer.h
        source/render/buffer/ShaderStorageBuffer.cpp source/render/buffer/ShaderStorageBuffer.h
        source/render/buffer/GlBufferWrapper.cpp source/render/buffer/GlBufferWrapper.h

        source/render/Texture.cpp source/render/Texture.h
        source/render/Shader.cpp source/render/Shader.h

        source/Rhythm.cpp source/Rhythm.h
        source/reference/Global.h source/manager/AssetManager.h
        source/Level.cpp source/Level.h
        source/reference/Configuration.cpp source/reference/Configuration.h
        source/InputHandler.cpp source/InputHandler.h
        source/entity/Sprite.cpp source/entity/Sprite.h
        source/reference/Reference.cpp source/reference/Reference.h
        source/entity/SpriteStateMachine.cpp source/entity/SpriteStateMachine.h
        source/physics/PhysicsEngine.cpp source/physics/PhysicsEngine.h
        source/entity/SpriteStates.h
        source/entity/Entity.cpp source/entity/Entity.h
        source/render/UiRenderer.cpp source/render/UiRenderer.h
        source/entity/Player.cpp source/entity/Player.h
        source/sound/SoundEngine.cpp source/sound/SoundEngine.h
        source/sound/Sound.cpp source/sound/Sound.h
        source/sound/filter/LpFilter.cpp source/sound/filter/LpFilter.h
        source/entity/Particle.cpp source/entity/Particle.h
        source/manager/ParticleManager.cpp source/manager/ParticleManager.h source/manager/EntityManager.cpp source/manager/EntityManager.h source/entity/enemy/Nightmare.cpp source/entity/enemy/Nightmare.h source/entity/ai/AiTaskBase.h source/entity/ai/AiTaskWalkToPlayer.cpp source/entity/ai/AiTaskWalkToPlayer.h source/entity/EntityLiving.cpp source/entity/EntityLiving.h source/physics/AxisAlignedBB.cpp source/physics/AxisAlignedBB.h)

if (WIN32)
    target_link_libraries(Rhythm glfw3 gdi32 opengl32 pthread portaudio)
endif(WIN32)
if (UNIX)
    target_link_libraries(Rhythm glfw3 GL X11 pthread portaudio)
endif(UNIX)

add_custom_command(TARGET Rhythm PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/shader $<TARGET_FILE_DIR:Rhythm>/shader)

add_custom_command(TARGET Rhythm PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resource $<TARGET_FILE_DIR:Rhythm>/resource)

add_custom_command(TARGET Rhythm PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/lib/portaudio $<TARGET_FILE_DIR:Rhythm>)