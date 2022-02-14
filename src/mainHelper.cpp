#include "mainHelper.h"
using namespace glm;

// Main raytracing logic
// ---------------------
void Raytrace(Scene* scene)
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
            if (i * j < 50) {
                //std::cout << "[" << viewRay.dir.x << "," << viewRay.dir.y << "," << viewRay.dir.z << "]; [";
                //std::cout << viewRay.pos.x << "," << viewRay.pos.y << "," << viewRay.pos.z << "]" << std::endl;
            }

            // Intersect ray with scene
            // ------------------------
            Hit hit = scene->Intersect(viewRay, NEAR_CLIP_DIST, FAR_CLIP_DIST);
            if (i * j < 50) {
                //std::cout << "Hit: [" << hit.pos << "]; [" << hit.loc.x << "," << hit.loc.y << "," << hit.loc.z << "]; [";
                //std::cout << hit.model << "]" << std::endl;
            }

            // Compute illumination at visible point
            // -------------------------------------
            // n = hit.normal
            // v = viewRay.dir
            // l = light.dir - hit.pos
            // h = normalize(v + l)
            // L = La + Ld + Ls
            // L = ka*Ia + I*(kd*max(0, n.l) + ks*max(0, n.h)^p)

            if (hit.dist >= 0.0f && hit.model != nullptr) {
                // Calculate all common values once
                vec3 l = normalize(scene->light->dir - hit.pos);
                vec3 h = normalize(viewRay.dir + l);
                vec3 n = hit.normal;
                vec3 ka = hit.model->mat.ka;
                vec3 kd = hit.model->mat.kd;
                vec3 ks = hit.model->mat.ks;
                vec3 ia = scene->light->ia;
                int p = 10;
                float I = scene->light->intensity;
                float nl = dot(n, l);
                float nh = dot(n, h);

                // Put result into image
                // ---------------------
                image[idx] = clamp((int)(ka.r * ia.r + I * (kd.r * max(0.0f, nl) + ks.r * pow(max(0.0f, nh), p))), 0, 255);
                image[idx + 1] = clamp((int)(ka.g * ia.g + I * (kd.g * max(0.0f, nl) + ks.g * pow(max(0.0f, nh), p))), 0, 255);
                image[idx + 2] = clamp((int)(ka.b * ia.b + I * (kd.b * max(0.0f, nl) + ks.b * pow(max(0.0f, nh), p))), 0, 255);
            }
            else {
                image[idx] = (int)scene->bgColor.r;
                image[idx + 1] = (int)scene->bgColor.g;
                image[idx + 2] = (int)scene->bgColor.b;
            }
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
            vec3(-0.5, -2, 1.5),        // Position
            vec3(0, 1, -1),             // LookAt
            vec3(0, 0, 1),              // Up
            true,                       // Orthographic
            90.0f,                      // FOV
            vec2(2,2)),                 // Aspect
        new Light(                      // __________________Light_________
            vec3(-0.5, 2, 2),              // Position
            vec3(0, -1, -1),            // Direction
            vec3(1.0f, 1.0f, 1.0f),     // Ambient intensity
            3.0f),                      // Intensity
        vec3(225, 225, 225)             // Background color
    );
    /**/
    scene->AddModel(
        new Sphere(
            vec3(-0.3f, 0.0f, 0.0f),
            0.5f,
            Lambert(
                glm::vec3(255, 0, 0),               // Diffuse
                glm::vec3(50, 0, 0)))               // Ambient
    );

    scene->AddModel(
        new Sphere(
            vec3(0.4f, 0.0f, 0.0f),
            0.2f,
            Blinn(
                glm::vec3(0, 0, 255),               // Diffuse
                glm::vec3(255, 255, 255),           // Specular
                glm::vec3(10, 10, 50),              // Ambient
                10000))                             // Phong exponent
    );
    /**/
    scene->AddModel(
        new Tetrahedron(
            vec3(0.5f, 0.1f, 0.7f),
            0.2f,
            Lambert(
                glm::vec3(255, 215, 0),             // Diffuse
                glm::vec3(60, 50, 0)))              // Ambient
    );

    /**/
    scene->AddModel(
        new Plane(
            vec3(0.0f, 0.0f, -0.5f),
            2.0f,
            2.0f,
            Mirror(
                glm::vec3(150, 150, 150),           // Diffuse
                glm::vec3(22, 22, 22),              // Specular
                glm::vec3(70, 70, 70),              // Ambient
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
    // Move right
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(MOVE_MOD, 0, 0));
        return true;
    }
    // Move left
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(-MOVE_MOD, 0, 0));
        return true;
    }
    // Move forward
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(0, MOVE_MOD, 0));
        return true;
    }
    // Move back
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(0, -MOVE_MOD, 0));
        return true;
    }
    // Move up
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(0, 0, MOVE_MOD));
        return true;
    }
    // Move down
    else if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
    {
        scene->MoveCamera(glm::vec3(0, 0, -MOVE_MOD));
        return true;
    }
    // Toggle perspective
    else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        scene->ToggleOrth();
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