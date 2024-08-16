#pragma once

// For used by Tesla applications
#include "Tesla/Core/Base.h"

#include "Tesla/Core/Application.h"

// ----- Layer -------

#include "Tesla/Core/Layer.h"

// ----- Logger -------

#include "Tesla/Core/Log.h"

#include "Tesla/Core/Timestep.h"

// ----- Input -------
#include "Tesla/Core/Input.h"
#include "Tesla/Core/KeyCodes.h"
#include "Tesla/Core/MouseCodes.h"
#include "Tesla/Renderer/OrthographicCameraController.h"

#include "Tesla/ImGui/ImGuiLayer.h"

#include "Tesla/Scene/Scene.h"
#include "Tesla/Scene/Components.h"
#include "Tesla/Scene/Entity.h"

// ----- Rendering -------
#include "Tesla/Renderer/RenderCommand.h"
#include "Tesla/Renderer/Renderer.h"
#include "Tesla/Renderer/Renderer2D.h"

#include "Tesla/Renderer/Buffer.h"
#include "Tesla/Renderer/VertexArray.h"
#include "Tesla/Renderer/Shader.h"
#include "Tesla/Renderer/Framebuffer.h"
#include "Tesla/Renderer/Texture.h"

#include "Tesla/Renderer/OrthographicCamera.h"

// ----- Include pch header ------

#include "tlpch.h"