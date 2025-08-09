#include "Renderer.h"
//-----------------------------------------------------
#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE
//-----------------------------------------------------
class VertexBuffer;
class VertexBufferLayout;
//-----------------------------------------------------
GLFWwindow* window; //pointer to data location for window
//-----------------------------------------------------
#define GLAD_GL_IMPLEMENTATION
#define GLFW_INCLUDE_NONE
//-----------------------------------------------------
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
//-----------------------------------------------------
double runtime = glfwGetTime();
//-----------------------------------------------------
static void print(std::string text) {
	std::cout << text << std::endl;
}
//-----------------------------------------------------
void error_callback(int error, const char* description) // function for errors
{
	fprintf(stderr, "Error: %s\n", description);
}
//-----------------------------------------------------
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) //function for keys, will be expanded
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, int(GLFW_TRUE));
}
//-----------------------------------------------------
void processInput(GLFWwindow* window, Camera& camera) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) camera.ProcessKeyboard(FORWARD, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) camera.ProcessKeyboard(BACKWARD, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) camera.ProcessKeyboard(LEFT, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) camera.ProcessKeyboard(RIGHT, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) camera.ProcessKeyboard(UP, camera.deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) camera.ProcessKeyboard(DOWN, camera.deltaTime);
}
//-----------------------------------------------------
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
//-----------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
	static Camera* cam = nullptr;
	if (!cam) cam = &camera; // store pointer first time

	if (cam->firstMouse) {
		cam->lastX = (float)xpos;
		cam->lastY = (float)ypos;
		cam->firstMouse = false;
	}

	float xoffset = (float)xpos - cam->lastX;
	float yoffset = cam->lastY - (float)ypos; // reversed Y

	cam->lastX = (float)xpos;
	cam->lastY = (float)ypos;

	cam->ProcessMouseMovement(xoffset, yoffset);
}
//defining openGL name spaces inorder for them to support the program

int main() {

	glfwSetErrorCallback(error_callback); //if an error occurs the program detects it, this has to be set up first to debug
	std::cout << "Hi" << std::endl;
	glfwInit();//initialise glfw
	if (!glfwInit())//checks if glfw has been initilised
	{
		std::cout << "GLFW FAILED" << std::endl; //If glfw hasn't been initilised, it prints "glfw failed" to command line
		// Initialization failed
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //max 3rd opengl type
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //min 3rd opengl subtype
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // mac needs core profile to run, as open gl is cross platform

	window = glfwCreateWindow(1280, 720, "Graphics Engine", NULL, NULL); // create a 500 x 500 window named graphics engine in the variable window
	glfwMakeContextCurrent(window); //make the current context of all actions on windows happen to the wind
	glfwSetWindowShouldClose(window, GLFW_FALSE); // set the window to not close immediately

	if (!window) { //if the window closes
		glfwTerminate(); //end glfw
		return -1;
	}
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glewInit();//initialise glew
	if (glewInit() != GLEW_OK)//checks if glew has been initilised
	{
		std::cout << "GLEW FAILED" << std::endl;//If glew hasn't been initilised, it prints "glew failed" to command line
		// Initialization failed
	}

	//data
	float positions[20] = { //position data array of floats
		 -0.5f, -0.5f, 0, 0.0f, 0.0f,//0
		  0.5f, -0.5f, 0, 1.0f, 0.0f,//1
		  0.5f,  0.5f, 0, 1.0f, 1.0f,//2
		 -0.5f,  0.5f, 0, 0.0f, 1.0f //3

	};
	unsigned int indices[6]{ // index of the order that they are drawn in counter clock wise order
		0, 1, 2,
		2, 3, 0,
	};
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	VertexBuffer vb;
	vb.VertexBufferAssign(positions, sizeof(positions)); //<----------------------------------------------//Vertex Buffer Call//---------------------
	VertexArray va;
	Layout layout;
	layout.Push<float>(3);
	layout.Push<float>(2);

	vb.Bind();
	va.AddArrayBuffer(layout);
	IndexBuffer ib(indices, sizeof(indices) / sizeof(unsigned int)); //<----------------------------------------------//Index Buffer Call//------

	glm::mat4 proj = glm::ortho(-1.0f,1.0f,-1.0f,1.0f,-1.0f,1.0f);


	Shader shader("basicShader.shader");
	shader.Bind();
	float b = 0.0f;
	float r = 0.0f;
	float g = 0.0f;
	float incrementb = 0.01f;
	float incrementr = 0.03f;
	float incrementg = 0.05f;
	shader.SetUniform4f("u_Color", b, r, g, 1.0f);
	shader.SetUniformMat4f("u_MVP", proj);


	Texture texture("Grass_Block_Sides.png");
	texture.Bind();

	shader.SetUniform1i("u_Texture", 0);

	glfwSetKeyCallback(window, key_callback); // every cycle it checks for the keys function
	Renderer renderer;



	while (!glfwWindowShouldClose(window)) {
		double currentFrame = glfwGetTime();
		camera.deltaTime = currentFrame - camera.lastFrame;
		camera.lastFrame = currentFrame;

		processInput(window, camera);

		//std::cout <<  << std::endl;
		std::cout << "Hi 2" << std::endl;//a simple output test of the loop, prints Hi 2 every loop
		renderer.Clear();
		int width, height;
		glfwGetFramebufferSize(window, &width, &height); //gets the size in the form of pointers to the 2 int's data locations
		glViewport(0, 0, width, height); //getting the view port of the window

		// Example model matrix (for positioning your object)
		glm::mat4 model = glm::mat4(1.0f);

		// Build MVP and send to shader
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = camera.GetProjectionMatrix((float)SCR_WIDTH / SCR_HEIGHT);
		glm::mat4 mvp = projection * view * model;
		shader.SetUniformMat4f("u_MVP", mvp);

		renderer.Draw(va, ib, shader);

		shader.SetUniform4f("u_Color", b, r, g, 1.0f);

		if (b > 1.0f)// if the value of r gets to large increment down
			incrementb = -0.05f;
		else if (b < 0.0f)// if the value of r gets to small increment up
			incrementb = 0.05f;
		b += incrementb; //incrementation

		if (r > 1.0f)// if the value of r gets to large increment down
			incrementr = -0.05f;
		else if (r < 0.0f)// if the value of r gets to small increment up
			incrementr = 0.05f;
		r += incrementr; //incrementation

		if (g > 1.0f)// if the value of r gets to large increment down
			incrementg = -0.05f;
		else if (g < 0.0f)// if the value of r gets to small increment up
			incrementg = 0.05f;
		g += incrementg; //incrementation

		glfwSwapInterval(1);// may need to be changed as the screen doesnt render as fast as the calculations occur 
		// so the calculations would be wasted
		glfwSwapBuffers(window);// changing the buffers to iterate the image on the screen as it cycles
		glfwPollEvents(); // this checks if anything happened every cycle
		// glfwWaitEvents does something similar but instead only goes when an event occurs which can be more memory efficent
		// is more complex and unlikely to give any notable improvement in this game as there is contant mocvement and thus constant buffer swapping
	}

	glfwDestroyWindow(window); //at the end of the program destroy the window
	if (!window) {
		glfwTerminate(); //now because we just destroyed the window glfw is terminated
		return -1;
	}
}
