#include "VKWindowEngine.hpp"
#include "Logger.hpp"
#include <vulkan/vk_enum_string_helper.h>

static VkPhysicalDevice g_PhysicalDevice = VK_NULL_HANDLE;
static VkDevice g_Device = VK_NULL_HANDLE;
static uint32_t g_QueueFamily = (uint32_t)-1;
static VkQueue g_Queue = VK_NULL_HANDLE;
static VkDebugReportCallbackEXT g_DebugReport = VK_NULL_HANDLE;
static VkPipelineCache g_PipelineCache = VK_NULL_HANDLE;
static VkDescriptorPool g_DescriptorPool = VK_NULL_HANDLE;

static int g_MinImageCount = 2;
static bool g_SwapChainRebuild = false;

CVKWindowEngine::CVKWindowEngine()
    : m_vkInstance(VK_NULL_HANDLE)
    , m_vkAllocator(NULL)
    , m_imguiMainWindowData()
    , m_glfwWindow(nullptr)
{
    LOG_INFO("Create VKWindowEngine");
}

CVKWindowEngine::~CVKWindowEngine()
{
    LOG_INFO("Close VKWindowEngine");
}

auto CVKWindowEngine::CreateWindow() -> GLFWwindow*
{
    LOG_INFO("CreateWindow");
    // Setup GLFW window
    glfwSetErrorCallback(glfwErrorCallback);
    if (!glfwInit()) {
        throw "glfwInit Error";
    }

    // Create window
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    m_glfwWindow = glfwCreateWindow(1800, 1200, "VKWindowEngine", NULL, NULL);
    if (m_glfwWindow == nullptr) {
        return m_glfwWindow;
    }

    // Setup Vulkan
    if (!glfwVulkanSupported()) {
        throw "GLFW: Vulkan Not Supported";
    }

    // Extensios
    uint32_t extensions_count = 0;
    const char** extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
    SetupVulkan(extensions, extensions_count);

    // Create Window Surface
    VkSurfaceKHR surface;
    VkResult err = glfwCreateWindowSurface(m_vkInstance, m_glfwWindow, m_vkAllocator, &surface);
    vkCheckResult(err);

    // Create Framebuffers
    int w { 0 };
    int h { 0 };
    glfwGetFramebufferSize(m_glfwWindow, &w, &h);
    ImGui_ImplVulkanH_Window* wd = &m_imguiMainWindowData;
    vkSetupWindow(wd, surface, w, h);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForVulkan(m_glfwWindow, true);
    ImGui_ImplVulkan_InitInfo init_info = {};
    init_info.Instance = m_vkInstance;
    init_info.PhysicalDevice = g_PhysicalDevice;
    init_info.Device = g_Device;
    init_info.QueueFamily = g_QueueFamily;
    init_info.Queue = g_Queue;
    init_info.PipelineCache = g_PipelineCache;
    init_info.DescriptorPool = g_DescriptorPool;
    init_info.Subpass = 0;
    init_info.MinImageCount = g_MinImageCount;
    init_info.ImageCount = wd->ImageCount;
    init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
    init_info.Allocator = m_vkAllocator;
    init_info.CheckVkResultFn = vkCheckResult;
    ImGui_ImplVulkan_Init(&init_info, wd->RenderPass);

    // Load Fonts
    constexpr float fontSize = 17.0F;
    // TODO(dlorenz) add dynamic path
    io.Fonts->AddFontFromFileTTF("C:\\Users\\dalo\\Desktop\\GitPriv\\AlbikarEngine\\AlbikarEditor\\assets\\fonts\\opensans\\OpenSans-Bold.ttf", fontSize);
    io.FontDefault = io.Fonts->AddFontFromFileTTF("C:\\Users\\dalo\\Desktop\\GitPriv\\AlbikarEngine\\AlbikarEditor\\assets\\fonts\\opensans\\OpenSans-Regular.ttf", fontSize);

    // Upload Fonts
    {
        // Use any command queue
        VkCommandPool command_pool = wd->Frames[wd->FrameIndex].CommandPool;
        VkCommandBuffer command_buffer = wd->Frames[wd->FrameIndex].CommandBuffer;

        err = vkResetCommandPool(g_Device, command_pool, 0);
        vkCheckResult(err);
        VkCommandBufferBeginInfo begin_info = {};
        begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        begin_info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(command_buffer, &begin_info);
        vkCheckResult(err);

        ImGui_ImplVulkan_CreateFontsTexture(command_buffer);

        VkSubmitInfo end_info = {};
        end_info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        end_info.commandBufferCount = 1;
        end_info.pCommandBuffers = &command_buffer;
        err = vkEndCommandBuffer(command_buffer);
        vkCheckResult(err);
        err = vkQueueSubmit(g_Queue, 1, &end_info, VK_NULL_HANDLE);
        vkCheckResult(err);

        err = vkDeviceWaitIdle(g_Device);
        vkCheckResult(err);
        ImGui_ImplVulkan_DestroyFontUploadObjects();
    }

    return m_glfwWindow;
}

auto CVKWindowEngine::IsWindowsClosed() -> bool
{
    return !glfwWindowShouldClose(m_glfwWindow);
}

auto CVKWindowEngine::NewFrame() -> bool
{
    glfwPollEvents();

    // Resize swap chain?
    if (g_SwapChainRebuild) {
        LOG_WARN("Resize Frame buffer");
        int width { 0 };
        int height { 0 };
        glfwGetFramebufferSize(m_glfwWindow, &width, &height);
        if (width > 0 && height > 0) {
            ImGui_ImplVulkan_SetMinImageCount(g_MinImageCount);
            ImGui_ImplVulkanH_CreateOrResizeWindow(m_vkInstance, g_PhysicalDevice, g_Device, &m_imguiMainWindowData, g_QueueFamily, m_vkAllocator, width, height, g_MinImageCount);
            m_imguiMainWindowData.FrameIndex = 0;
            g_SwapChainRebuild = false;
        }
    }

    // Start the Dear ImGui frame
    ImGui_ImplVulkan_NewFrame();
    ImGui_ImplGlfw_NewFrame();

    return true;
}

auto CVKWindowEngine::Render(ImDrawData* imguiDrawData) -> bool
{
    ImVec4 clear_color(0.45f, 0.55f, 0.60f, 1.00f);
    if (imguiDrawData == nullptr)
        return false;
    const bool is_minimized = (imguiDrawData->DisplaySize.x <= 0.0f || imguiDrawData->DisplaySize.y <= 0.0f);
    if (!is_minimized) {
        m_imguiMainWindowData.ClearValue.color.float32[0] = clear_color.x * clear_color.w;
        m_imguiMainWindowData.ClearValue.color.float32[1] = clear_color.y * clear_color.w;
        m_imguiMainWindowData.ClearValue.color.float32[2] = clear_color.z * clear_color.w;
        m_imguiMainWindowData.ClearValue.color.float32[3] = clear_color.w;
        FrameRender(imguiDrawData);
        FramePresent();
    }

    return true;
}

auto CVKWindowEngine::Cleanup() -> bool
{
    VkResult err = vkDeviceWaitIdle(g_Device);
    vkCheckResult(err);
    ImGui_ImplVulkan_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    ImGui_ImplVulkanH_DestroyWindow(m_vkInstance, g_Device, &m_imguiMainWindowData, m_vkAllocator);
    vkDestroyDescriptorPool(g_Device, g_DescriptorPool, m_vkAllocator);

#ifdef IMGUI_VULKAN_DEBUG_REPORT
    // Remove the debug report callback
    auto vkDestroyDebugReportCallbackEXT = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(m_vkInstance, "vkDestroyDebugReportCallbackEXT");
    vkDestroyDebugReportCallbackEXT(m_vkInstance, g_DebugReport, m_vkAllocator);
#endif // IMGUI_VULKAN_DEBUG_REPORT

    vkDestroyDevice(g_Device, m_vkAllocator);
    vkDestroyInstance(m_vkInstance, m_vkAllocator);

    glfwDestroyWindow(m_glfwWindow);
    glfwTerminate();
    return true;
}

auto CVKWindowEngine::SetupVulkan(const char** extensions, unsigned int extensions_count) -> void
{
    VkResult err;

    // Create Vulkan Instance
    {
        VkInstanceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        create_info.enabledExtensionCount = extensions_count;
        create_info.ppEnabledExtensionNames = extensions;
        for (auto i = 0u; i < extensions_count; i++) {
            LOG_INFO("Extension(", i + 1, "/", extensions_count, "): ", std::string(extensions[i]));
        }
#ifdef IMGUI_VULKAN_DEBUG_REPORT
        // Enabling validation layers
        const char* layers[] = { "VK_LAYER_KHRONOS_validation" };
        create_info.enabledLayerCount = 1;
        create_info.ppEnabledLayerNames = layers;

        // Enable debug report extension (we need additional storage, so we duplicate the user array to add our new extension to it)
        const char** extensions_ext = (const char**)malloc(sizeof(const char*) * (extensions_count + 1));
        memcpy(extensions_ext, extensions, extensions_count * sizeof(const char*));
        extensions_ext[extensions_count] = "VK_EXT_debug_report";
        create_info.enabledExtensionCount = extensions_count + 1;
        create_info.ppEnabledExtensionNames = extensions_ext;

        // Create Vulkan Instance
        err = vkCreateInstance(&create_info, g_Allocator, &g_Instance);
        vkCheckResult(err);
        free(extensions_ext);

        // Get the function pointer (required for any extensions)
        auto vkCreateDebugReportCallbackEXT = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(g_Instance, "vkCreateDebugReportCallbackEXT");
        IM_ASSERT(vkCreateDebugReportCallbackEXT != NULL);

        // Setup the debug report callback
        VkDebugReportCallbackCreateInfoEXT debug_report_ci = {};
        debug_report_ci.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
        debug_report_ci.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
        debug_report_ci.pfnCallback = debug_report;
        debug_report_ci.pUserData = NULL;
        err = vkCreateDebugReportCallbackEXT(g_Instance, &debug_report_ci, g_Allocator, &g_DebugReport);
        vkCheckResult(err);
#else
        // Create Vulkan Instance without any debug feature
        err = vkCreateInstance(&create_info, m_vkAllocator, &m_vkInstance);
        vkCheckResult(err);
        IM_UNUSED(g_DebugReport);
#endif
    }

    // Select GPU
    {
        uint32_t gpu_count;
        err = vkEnumeratePhysicalDevices(m_vkInstance, &gpu_count, NULL);
        vkCheckResult(err);
        IM_ASSERT(gpu_count > 0);

        VkPhysicalDevice* gpus = (VkPhysicalDevice*)malloc(sizeof(VkPhysicalDevice) * gpu_count);
        err = vkEnumeratePhysicalDevices(m_vkInstance, &gpu_count, gpus);
        vkCheckResult(err);

        // If a number >1 of GPUs got reported, find discrete GPU if present, or use first one available. This covers
        // most common cases (multi-gpu/integrated+dedicated graphics). Handling more complicated setups (multiple
        // dedicated GPUs) is out of scope of this sample.
        int use_gpu = 0;
        LOG_INFO("Number of GPUs: ", gpu_count);
        for (int i = 0; i < (int)gpu_count; i++) {
            VkPhysicalDeviceProperties properties;
            vkGetPhysicalDeviceProperties(gpus[i], &properties);
            if (properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
                use_gpu = i;
                break;
            }
        }

        g_PhysicalDevice = gpus[use_gpu];
        free(gpus);
    }

    // Select graphics queue family
    {
        uint32_t count;
        vkGetPhysicalDeviceQueueFamilyProperties(g_PhysicalDevice, &count, NULL);
        VkQueueFamilyProperties* queues = (VkQueueFamilyProperties*)malloc(sizeof(VkQueueFamilyProperties) * count);
        vkGetPhysicalDeviceQueueFamilyProperties(g_PhysicalDevice, &count, queues);
        for (uint32_t i = 0; i < count; i++)
            if (queues[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                g_QueueFamily = i;
                break;
            }
        free(queues);
        IM_ASSERT(g_QueueFamily != (uint32_t)-1);
    }

    // Create Logical Device (with 1 queue)
    {
        int device_extension_count = 1;
        const char* device_extensions[] = { "VK_KHR_swapchain" };
        const float queue_priority[] = { 1.0F };
        VkDeviceQueueCreateInfo queue_info[1] = {};
        queue_info[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queue_info[0].queueFamilyIndex = g_QueueFamily;
        queue_info[0].queueCount = 1;
        queue_info[0].pQueuePriorities = queue_priority;
        VkDeviceCreateInfo create_info = {};
        create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        create_info.queueCreateInfoCount = sizeof(queue_info) / sizeof(queue_info[0]);
        create_info.pQueueCreateInfos = queue_info;
        create_info.enabledExtensionCount = device_extension_count;
        create_info.ppEnabledExtensionNames = device_extensions;
        err = vkCreateDevice(g_PhysicalDevice, &create_info, m_vkAllocator, &g_Device);
        vkCheckResult(err);
        vkGetDeviceQueue(g_Device, g_QueueFamily, 0, &g_Queue);
    }

    // Create Descriptor Pool
    {
        VkDescriptorPoolSize pool_sizes[] = {
            { VK_DESCRIPTOR_TYPE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
            { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000 },
            { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
            { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000 }
        };
        VkDescriptorPoolCreateInfo pool_info = {};
        pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
        pool_info.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT;
        pool_info.maxSets = 1000 * IM_ARRAYSIZE(pool_sizes);
        pool_info.poolSizeCount = (uint32_t)IM_ARRAYSIZE(pool_sizes);
        pool_info.pPoolSizes = pool_sizes;
        err = vkCreateDescriptorPool(g_Device, &pool_info, m_vkAllocator, &g_DescriptorPool);
        vkCheckResult(err);
    }
}

auto CVKWindowEngine::FrameRender(ImDrawData* imguiDrawData) -> void
{
    VkResult err;

    VkSemaphore image_acquired_semaphore = m_imguiMainWindowData.FrameSemaphores[m_imguiMainWindowData.SemaphoreIndex].ImageAcquiredSemaphore;
    VkSemaphore render_complete_semaphore = m_imguiMainWindowData.FrameSemaphores[m_imguiMainWindowData.SemaphoreIndex].RenderCompleteSemaphore;
    err = vkAcquireNextImageKHR(g_Device, m_imguiMainWindowData.Swapchain, UINT64_MAX, image_acquired_semaphore, VK_NULL_HANDLE, &m_imguiMainWindowData.FrameIndex);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
        g_SwapChainRebuild = true;
        return;
    }
    vkCheckResult(err);

    ImGui_ImplVulkanH_Frame* fd = &m_imguiMainWindowData.Frames[m_imguiMainWindowData.FrameIndex];
    {
        err = vkWaitForFences(g_Device, 1, &fd->Fence, VK_TRUE, UINT64_MAX); // wait indefinitely instead of periodically checking
        vkCheckResult(err);

        err = vkResetFences(g_Device, 1, &fd->Fence);
        vkCheckResult(err);
    }
    {
        err = vkResetCommandPool(g_Device, fd->CommandPool, 0);
        vkCheckResult(err);
        VkCommandBufferBeginInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        info.flags |= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
        err = vkBeginCommandBuffer(fd->CommandBuffer, &info);
        vkCheckResult(err);
    }
    {
        VkRenderPassBeginInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
        info.renderPass = m_imguiMainWindowData.RenderPass;
        info.framebuffer = fd->Framebuffer;
        info.renderArea.extent.width = m_imguiMainWindowData.Width;
        info.renderArea.extent.height = m_imguiMainWindowData.Height;
        info.clearValueCount = 1;
        info.pClearValues = &m_imguiMainWindowData.ClearValue;
        vkCmdBeginRenderPass(fd->CommandBuffer, &info, VK_SUBPASS_CONTENTS_INLINE);
    }

    // Record dear imgui primitives into command buffer
    ImGui_ImplVulkan_RenderDrawData(imguiDrawData, fd->CommandBuffer);

    // Submit command buffer
    vkCmdEndRenderPass(fd->CommandBuffer);
    {
        VkPipelineStageFlags wait_stage = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
        VkSubmitInfo info = {};
        info.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        info.waitSemaphoreCount = 1;
        info.pWaitSemaphores = &image_acquired_semaphore;
        info.pWaitDstStageMask = &wait_stage;
        info.commandBufferCount = 1;
        info.pCommandBuffers = &fd->CommandBuffer;
        info.signalSemaphoreCount = 1;
        info.pSignalSemaphores = &render_complete_semaphore;

        err = vkEndCommandBuffer(fd->CommandBuffer);
        vkCheckResult(err);
        err = vkQueueSubmit(g_Queue, 1, &info, fd->Fence);
        vkCheckResult(err);
    }
}
auto CVKWindowEngine::FramePresent() -> void
{
    if (g_SwapChainRebuild)
        return;
    VkSemaphore render_complete_semaphore = m_imguiMainWindowData.FrameSemaphores[m_imguiMainWindowData.SemaphoreIndex].RenderCompleteSemaphore;
    VkPresentInfoKHR info = {};
    info.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    info.waitSemaphoreCount = 1;
    info.pWaitSemaphores = &render_complete_semaphore;
    info.swapchainCount = 1;
    info.pSwapchains = &m_imguiMainWindowData.Swapchain;
    info.pImageIndices = &m_imguiMainWindowData.FrameIndex;
    VkResult err = vkQueuePresentKHR(g_Queue, &info);
    if (err == VK_ERROR_OUT_OF_DATE_KHR || err == VK_SUBOPTIMAL_KHR) {
        g_SwapChainRebuild = true;
        return;
    }
    vkCheckResult(err);
    m_imguiMainWindowData.SemaphoreIndex = (m_imguiMainWindowData.SemaphoreIndex + 1) % m_imguiMainWindowData.ImageCount; // Now we can use the next set of semaphores
}

auto CVKWindowEngine::vkSetupWindow(ImGui_ImplVulkanH_Window* wd, VkSurfaceKHR surface, int width, int height) -> void
{
    wd->Surface = surface;

    // Check for WSI support
    VkBool32 res;
    vkGetPhysicalDeviceSurfaceSupportKHR(g_PhysicalDevice, g_QueueFamily, wd->Surface, &res);
    if (res != VK_TRUE) {
        LOG_ERROR("Error no WSI support on physical device 0");
        throw "Error no WSI support on physical device 0";
    }

    // Select Surface Format
    const VkFormat requestSurfaceImageFormat[] = { VK_FORMAT_B8G8R8A8_UNORM, VK_FORMAT_R8G8B8A8_UNORM, VK_FORMAT_B8G8R8_UNORM, VK_FORMAT_R8G8B8_UNORM };
    const VkColorSpaceKHR requestSurfaceColorSpace = VK_COLORSPACE_SRGB_NONLINEAR_KHR;
    wd->SurfaceFormat = ImGui_ImplVulkanH_SelectSurfaceFormat(g_PhysicalDevice, wd->Surface, requestSurfaceImageFormat, (size_t)IM_ARRAYSIZE(requestSurfaceImageFormat), requestSurfaceColorSpace);

    // Select Present Mode
#ifdef IMGUI_UNLIMITED_FRAME_RATE
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_MAILBOX_KHR, VK_PRESENT_MODE_IMMEDIATE_KHR, VK_PRESENT_MODE_FIFO_KHR };
#else
    VkPresentModeKHR present_modes[] = { VK_PRESENT_MODE_FIFO_KHR };
#endif
    wd->PresentMode = ImGui_ImplVulkanH_SelectPresentMode(g_PhysicalDevice, wd->Surface, &present_modes[0], IM_ARRAYSIZE(present_modes));
    LOG_INFO("[vulkan] Selected PresentMode = ", wd->PresentMode);

    // Create SwapChain, RenderPass, Framebuffer, etc.
    IM_ASSERT(g_MinImageCount >= 2);
    ImGui_ImplVulkanH_CreateOrResizeWindow(m_vkInstance, g_PhysicalDevice, g_Device, wd, g_QueueFamily, m_vkAllocator, width, height, g_MinImageCount);
}

auto CVKWindowEngine::vkCheckResult(VkResult err) -> void
{
    if (err == 0)
        return;
    LOG_ERROR("VKWindowEngine Vulakn Error: VkResult = ", string_VkResult(err));
    if (err < 0)
        throw string_VkResult(err);
}

auto CVKWindowEngine::glfwErrorCallback(int error, const char* description) -> void
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}