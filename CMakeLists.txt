cmake_minimum_required(VERSION 3.23)

#set(CMAKE_TOOLCHAIN_FILE ${ENV}/scripts/buildsystems/vcpkg.cmake)
if (WIN32)
    set(VCPKG_TARGET_TRIPLET x64-mingw-dynamic)
    set(VCPKG_HOST_TRIPLET x64-mingw-dynamic)
endif(WIN32)

project(Rhythm)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -g -O0")
endif(WIN32)
if (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wno-unused-parameter -g -O0 -fsanitize=address -fsanitize=undefined")
endif(UNIX)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(portaudio REQUIRED)
find_package(glad REQUIRED)
find_package(imgui REQUIRED)
find_package(glm REQUIRED)
find_package(Stb REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/source)

remove_definitions(-D_PA_ENABLE_DEBUG_OUTPUT)

add_executable(Rhythm main.cpp

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
        source/level/Level.cpp source/level/Level.h
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
        source/manager/ParticleManager.cpp source/manager/ParticleManager.h
        source/manager/EntityManager.cpp source/manager/EntityManager.h
        source/entity/enemy/Nightmare.cpp source/entity/enemy/Nightmare.h
        source/entity/ai/AiTaskBase.h
        source/entity/ai/AiTaskWalkToPlayer.cpp source/entity/ai/AiTaskWalkToPlayer.h
        source/entity/EntityLiving.cpp source/entity/EntityLiving.h
        source/physics/AxisAlignedBB.cpp source/physics/AxisAlignedBB.h
        source/render/ParallaxTexture.cpp source/render/ParallaxTexture.h
        source/entity/SpriteInstanced.cpp source/entity/SpriteInstanced.h
        source/render/buffer/GlBufferWrapperInstanced.cpp source/render/buffer/GlBufferWrapperInstanced.h
        source/physics/RayTrace.cpp source/physics/RayTrace.h source/weapon/RangedWeaponBase.cpp source/weapon/RangedWeaponBase.h source/weapon/PistolWeapon.cpp source/weapon/PistolWeapon.h source/sound/BeatOffset.cpp source/sound/BeatOffset.h source/level/Tile.cpp source/level/Tile.h)

if (WIN32)
    target_link_libraries(Rhythm glad::glad imgui::imgui glfw gdi32 opengl32 pthread portaudio)
endif(WIN32)
if (UNIX)
    target_link_libraries(Rhythm glad::glad imgui::imgui glfw GL X11 pthread portaudio)
endif(UNIX)

add_custom_command(TARGET Rhythm PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/shader $<TARGET_FILE_DIR:Rhythm>/shader)

add_custom_command(TARGET Rhythm PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/resource $<TARGET_FILE_DIR:Rhythm>/resource)