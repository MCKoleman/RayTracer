#include "mainHelper.h"
using namespace glm;

// Actual raytracing calculation
// -----------------------------
glm::vec3 RaytracePixel(Scene* scene, Ray viewRay, unsigned int depth)
{
    // Intersect ray with scene
    // ------------------------
    Hit hit = scene->Intersect(viewRay, NEAR_CLIP_DIST, FAR_CLIP_DIST);

    // Compute illumination at visible point
    // -------------------------------------
    // n = hit.normal
    // v = viewRay.dir
    // l = light.dir - hit.pos
    // h = normalize(v + l)
    // L = La + Ld + Ls
    // L = ka*Ia + I*(kd*max(0, n.l) + ks*max(0, n.h)^p) + km

    if (hit.dist >= 0.0f && hit.model != nullptr) {
        // Calculate all common values once
        vec3 l = normalize(scene->light->dir - hit.pos);
        vec3 h = normalize(viewRay.dir + scene->light->dir);
        vec3 n = hit.normal;
        vec3 ka = hit.model->mat.ka;
        vec3 kd = hit.model->mat.kd;
        vec3 ks = hit.model->mat.ks;
        vec3 km = hit.model->mat.km;
        vec3 ia = scene->light->ia;
        int p = hit.model->mat.p;
        float I = scene->light->intensity;
        float nl = dot(n, l);
        float nh = dot(n, h);

        // Calculate mirror
        // ----------------
        vec3 result = vec3(0, 0, 0);
        if (hit.model->mat.matType == MatType::Mirror && depth < hit.model->mat.maxR && scene->options.enableMirrors) {
            // Recursively raytrace reflections until the maximum depth is reached
            result += RaytracePixel(scene, Ray(hit.pos, viewRay.dir - 2*dot(viewRay.dir, hit.normal)*hit.normal), depth + 1);
        }

        // Calculate shadows
        // -----------------
        if (scene->options.enableShadows) {
            Ray shadowRay = Ray(hit.pos, scene->light->dir);
            Hit shadowHit = scene->Intersect(shadowRay, NEAR_CLIP_DIST, FAR_CLIP_DIST);

            if(shadowHit.dist > 0.0f && hit.model != nullptr) {
                return result;
            }
        }

        // Return result
        // -------------

        // Add ambient
        if (scene->options.enableAmbient) {
            result += vec3(ka.r * ia.r, ka.g * ia.g, ka.b * ia.b);
        }

        // Add diffuse
        if (scene->options.enableDiffuse) {
            float diff = I * max(0.0f, nl);
            result += vec3(kd.r * diff, kd.g * diff, kd.b * diff);
        }

        // Add specular
        if (scene->options.enableSpecular) {
            float spec = I * (float)pow(max(0.0f, nh), p);
            result += vec3(ks.r * spec, ks.g * spec, ks.b * spec);
        }

        // Return combined result of all shading on this pixel
        return result;
    }
    // Background
    else {
        return scene->bgColor;
    }
}

// Main raytracing logic
// ---------------------
void RaytraceScene(Scene* scene)
{
    unsigned char image[WIDTH * HEIGHT * 3];

    // Main Ray Tracing loop
    // ---------------------
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            // Find index
            int idx = (i * WIDTH + j) * 3;

            // Compute viewing ray
            // -------------------
            Ray viewRay = scene->GetRay(i, j, WIDTH, HEIGHT);
            vec3 resultColor = RaytracePixel(scene, viewRay, 0);

            // Put result into image
            // ---------------------
            image[idx] = clamp((int)resultColor.r, 0, 255);
            image[idx + 1] = clamp((int)resultColor.g, 0, 255);
            image[idx + 2] = clamp((int)resultColor.b, 0, 255);
        }
    }

    // Draw image onto screen
    unsigned char* data = &image[0];
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
}

// Initializes the given scene (static definition)
Scene* InitScene()
{
    Scene* scene = new Scene(
        new Camera(                     // __________________Camera________
            vec3(2.8f, 2.6f, -2.8f),    // Position
            vec3(-1.0f, -0.7f, 1.0f),   // LookAt
            vec3(0, 0, 1),              // Up
            true,                       // Orthographic
            110.0f,                     // FOV
            vec2(1,1)),                 // Aspect
        new Light(                      // __________________Light_________
            vec3(-0.5, 2, -2),          // Position
            vec3(0, 1, -1),             // Direction
            vec3(1.0f, 1.0f, 1.0f),     // Ambient intensity
            3.0f),                      // Intensity
        vec3(25, 25, 25),               // Background color
        Options(                        //___________________Options_______
            true,                       // Mirrors
            true,                       // Shadows
            true,                       // Diffuse
            true,                       // Ambient
            true)                       // Specular
    );
    /**/
    scene->AddModel(
        new Sphere(
            vec3(-0.7f, 0.4f, 0.7f),
            0.4f,
            Blinn(
                glm::vec3(255, 0, 0),               // Diffuse
                glm::vec3(255, 255, 255),           // Specular
                glm::vec3(50, 10, 10),              // Ambient
                10000))                             // Phong exponent
    );

    scene->AddModel(
        new Sphere(
            vec3(0.45f, 0.2f, 0.8f),
            0.2f,
            Lambert(
                glm::vec3(0, 0, 255),               // Diffuse
                glm::vec3(10, 10, 50)))             // Ambient
    );
    /**/
    scene->AddModel(
        new Tetrahedron(
            vec3(-0.2f, 0.25f, -0.2f),
            0.4f,
            Blinn(
                glm::vec3(255, 215, 0),             // Diffuse
                glm::vec3(255, 255, 255),           // Specular
                glm::vec3(60, 50, 0),               // Ambient
                10000))                             // Phong exponent
    );

    /**/
    scene->AddModel(
        new Plane(
            glm::vec3(0, 0, 0),
            3.0f,
            3.0f,
            Mirror(
                glm::vec3(70, 70, 70),              // Diffuse
                glm::vec3(255, 255, 255),           // Specular
                glm::vec3(70, 70, 70),              // Ambient
                glm::vec3(1.0f, 1.0f, 1.0f),        // Mirror coefficient                
                10,                                 // Phong exponent
                1))                                 // Max recursion runs
    );
    /**/

    return scene;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly.
// returns whether a significant key was pressed this frame
// ---------------------------------------------------------------------------------------------------------
bool processInput(GLFWwindow* window, Scene* scene)
{
    // Close
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
        return true;
    }
    // Move forward
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(MOVE_MOD, 0, 0));
        return true;
    }
    // Move back
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(-MOVE_MOD, 0, 0));
        return true;
    }
    // Move right
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(0, 0, MOVE_MOD));
        return true;
    }
    // Move left
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(0, 0, -MOVE_MOD));
        return true;
    }
    // Move up
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(0, MOVE_MOD, 0));
        return true;
    }
    // Move down
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(0, -MOVE_MOD, 0));
        return true;
    }
    // Look up
    else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        scene->RotateCamera(glm::vec3(MOVE_MOD, 0, 0));
        return true;
    }
    // Look down
    else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        scene->RotateCamera(glm::vec3(-MOVE_MOD, 0, 0));
        return true;
    }
    // Look right
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        scene->RotateCamera(glm::vec3(0, MOVE_MOD, 0));
        return true;
    }
    // Look left
    else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        scene->RotateCamera(glm::vec3(0, -MOVE_MOD, 0));
        return true;
    }
    // Toggle perspective
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        scene->ToggleOrth();
        std::cout << "View status toggled. Is now [" << (scene->IsOrth() ? "orthographic" : "perspective") << "]" << std::endl;
        return true;
    }
    // Toggle mirrors
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        scene->options.ToggleMirrors();
        std::cout << "Mirrors toggled. Is now [" << (scene->options.enableMirrors ? "On" : "Off") << "]" << std::endl;
        return true;
    }
    // Toggle shadows
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        scene->options.ToggleShadows();
        std::cout << "Shadows toggled. Is now [" << (scene->options.enableShadows ? "On" : "Off") << "]" << std::endl;
        return true;
    }
    // Toggle ambient
    else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
        scene->options.ToggleAmbient();
        std::cout << "Ambient toggled. Is now [" << (scene->options.enableAmbient ? "On" : "Off") << "]" << std::endl;
        return true;
    }
    // Toggle diffuse
    else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        scene->options.ToggleDiffuse();
        std::cout << "Diffuse toggled. Is now [" << (scene->options.enableDiffuse ? "On" : "Off") << "]" << std::endl;
        return true;
    }
    // Toggle specular
    else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        scene->options.ToggleSpecular();
        std::cout << "Specular toggled. Is now [" << (scene->options.enableSpecular ? "On" : "Off") << "]" << std::endl;
        return true;
    }
    // Refresh
    else if(glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
    {
        return true;
    }

    // Default to returning false
    return false;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}