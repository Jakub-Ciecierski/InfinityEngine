#include "Renderer.h"

const int windowWidth = 1024;
const int windowHeight = 768;

/*********************/
/***** VARIABLES *****/
/*********************/

glm::mat4 Projection;
glm::mat4 View;
glm::mat4 Model;
glm::mat4 MVP;

GLuint programID;
GLuint MatrixID;

GLuint Texture;
GLuint TextureID;

Triangle* triangle;
Cube* cube;
Sphere* sphere;
Sphere* sphere1;
Camera* camera;

Star*** galaxies;

//  The number of frames
int frameCount = 0;
//  Number of frames per second
float fps = 0;

//  currentTime - previousTime is the time elapsed
//  between every call of the Idle function
int currentTime = 0, previousTime = 0;


/*********************/
/***** FUNCtIONS *****/
/*********************/

void render(void);
void keyboard(unsigned char c, int x, int y);
void specialKeys(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMove(int x, int y);
void calculateFPS();
void RenderString(float x, float y, void *font, const unsigned char* string);

void RenderString(float x, float y, void *font, const unsigned char* string)
{
    //char *c;

    glRasterPos2f(x, y);

    glutBitmapString(font, string);
}

void render(void)
{
    glUseProgram(programID);

    camera->Update();
    calculateFPS();

    //system("cls");
    //printf("FPS: %lf\n", fps);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
 
    //MVP = camera->ProjectionMatrix * camera->ViewMatrix * sphere->GetModelMatrix();
    //glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    //sphere->Render();
     
    //galaxyCollisionInit(galaxies, GALAXY_COUNT, MAX_DISK_COUNT + MAX_BULGE_COUNT);    

    for (int i = 0; i < GALAXY_COUNT; i++)
    {
        for (int j = 0; j < (MAX_DISK_COUNT + MAX_BULGE_COUNT); j++)
        {
            Star* star = galaxies[i][j];
            
            MVP = camera->ProjectionMatrix * camera->ViewMatrix * star->GetSphere()->GetModelMatrix();
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
            star->GetSphere()->RenderTexture();
        }
    }

    glutSwapBuffers();

    glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y)
{

}

void specialKeys(int key, int x, int y)
{
    switch (key){
    case GLUT_KEY_LEFT:
        camera->position -= camera->right * camera->speed;
        break;
    case GLUT_KEY_RIGHT:
        camera->position += camera->right * camera->speed;
        break;
    case GLUT_KEY_UP:
        camera->position += camera->direction * camera->speed;
        break;
    case GLUT_KEY_DOWN:
        camera->position -= camera->direction * camera->speed;
        break;
    }
}

void mouse(int button, int state, int x, int y)
{
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {

        // when the button is released
        if (state == GLUT_UP) {
            //angle += deltaAngle;
            camera->xOrigin = -1;
            camera->yOrigin = -1;
        }
        else  {// state = GLUT_DOWN
            camera->xOrigin = x;
            camera->yOrigin = y;
        }
    }
}

void mouseMove(int x, int y)
{
    // this will only be true when the left button is down
    if (camera->xOrigin >= 0 && camera->yOrigin >= 0) {

        camera->horizontalAngle += (x - camera->xOrigin) * camera->mouseSpeed;
        camera->verticalAngle += (y - camera->yOrigin) * camera->mouseSpeed;

        camera->xOrigin = x;
        camera->yOrigin = y;
    }
}

void calculateFPS()
{
    //  Increase frame count
    frameCount++;

    //  Get the number of milliseconds since glutInit called 
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
    int timeInterval = currentTime - previousTime;

    if (timeInterval > 1000)
    {
        //  calculate the number of frames per second
        fps = frameCount / (timeInterval / 1000.0f);

        //  Set time
        previousTime = currentTime;

        //  Reset frame count
        frameCount = 0;
    }
}

int GFXInit(int argc, char** argv)
{
	glutInit(&argc, argv);

    initWindow();

    initEvents();

    initProgram();

    initSampleObjects();

    galaxies = gllParse(argv[1], Texture, TextureID);

    glutMainLoop();

    delete(galaxies);
    
    return EXIT_SUCCESS;
}

int initWindow()
{
	// GLUT Display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Galaxy Collision");

	// GLEW init
	glewExperimental = true; // Needed in core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

    // Black screen
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	return 0;
}

int initEvents()
{
    // Glut function poitners
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMove);

    return 0;
}

int initProgram()
{
    // VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    fprintf(stderr, "Current WD: %s\n", get_current_dir_name());

    // Load shaders
    //programID = LoadShaders("src/gfx/shaders/VertexShader.vert", "src/gfx/shaders/FragmentShader.frag");
    programID = LoadShaders("src/gfx/shaders/TextureVertexShader.vert", "src/gfx/shaders/TextureFragmentShader.frag");

    // Get a handle for our "MVP" uniform.
    MatrixID = glGetUniformLocation(programID, "MVP");

    // Load the texture using any two methods
	Texture = LoadBMP("resources/uvtemplate.bmp");
	//GLuint Texture = loadDDS("uvtemplate.DDS");

	// Get a handle for our "myTextureSampler" uniform
	TextureID  = glGetUniformLocation(programID, "textureSampler");

	fprintf(stderr, "ProgramID: %d, Texture: %d, TextureID: %d\n", programID, Texture, TextureID);

	return 0;
}

int initSampleObjects()
{
    // Objects
    //sphere = new Sphere(0, 0, 0, 0.002f);
    sphere = new Sphere(0, 0, 0);
    //sphere = new Sphere(0.5f, 0.5f, 0.5f, 0.002f);
    cube = new Cube();
    camera = new Camera(0.0f, 0.0f, 50.0f);

    return 0;
}
