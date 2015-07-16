#include "Sphere.h"

Sphere::Sphere()
{
    X = Y = Z = 0;
    ScaleX = ScaleY = ScaleZ = 0.2f;

    initVertices();
	initColor();
}

Sphere::Sphere(float x, float y, float z)
{
    X = x; Y = y; Z = z;
    ScaleX = ScaleY = ScaleZ = 0.2f;

    initVertices();
    initColor();
}

Sphere::Sphere(float x, float y, float z, GLuint texture, GLuint textureID)
{
    X = x; Y = y; Z = z;
    ScaleX = ScaleY = ScaleZ = 0.2f;

    this->Texture = texture;
    this->TextureID = textureID;

    initVertices();
    initTexture();
}

Sphere::Sphere(float x, float y, float z, float width)
{
    X = x; Y = y; Z = z;

    Model = glm::mat4(1.0f);
    Model = glm::translate(Model, glm::vec3(X, Y, Z));

    static const GLfloat g_vertex_buffer_data[] = {
        0.0f, 0.0f, 0.0f,
        width, 0.0f, 0.0f,
        width, width, 0.0f,
        0.0f, width, 0.0f,
        0.0f, 0.0f, width,
        width, 0.0f, width,
        width, width, width,
        0.0f, width, width
    };

    // One color for each vertex. They were generated randomly.
    static const GLfloat g_color_buffer_data[] = {
        0.583f, 0.771f, 0.014f,
        0.609f, 0.115f, 0.436f,
        0.327f, 0.483f, 0.844f,
        0.822f, 0.569f, 0.201f,
        0.435f, 0.602f, 0.223f,
        0.310f, 0.747f, 0.185f,
        0.597f, 0.770f, 0.761f,
        0.559f, 0.436f, 0.730f
    };

    static const std::vector<unsigned short> indices;/* = {
        0, 1, 2,
        0, 2, 3,
        1, 5, 2,
        5, 6, 2,
        6, 5, 4,
        6, 4, 7,
        4, 0, 3,
        4, 3, 7,
        7, 3, 2,
        2, 6, 7,
        1, 0, 4,
        1, 4, 5 };*/

    /***** Vertex Buffer *******/
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    /***** Color Buffer *******/
    // Generate 1 buffer, put the resulting identifier in colorbuffer
    glGenBuffers(1, &colorbuffer);
    // The following commands will talk about our 'colorbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

    /***** VBO *******/
    // Generate a buffer for the indices
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
}

void Sphere::init()
{
	initVertices();
	//initColor();
	initTexture();
}

void Sphere::initVertices()
{
	static const GLfloat g_vertex_buffer_data[] = {
	        -1.0f, -1.0f, -1.0f, // triangle 1 : begin
	        -1.0f, -1.0f, 1.0f,
	        -1.0f, 1.0f, 1.0f, // triangle 1 : end
	        1.0f, 1.0f, -1.0f, // triangle 2 : begin
	        -1.0f, -1.0f, -1.0f,
	        -1.0f, 1.0f, -1.0f, // triangle 2 : end
	        1.0f, -1.0f, 1.0f,
	        -1.0f, -1.0f, -1.0f,
	        1.0f, -1.0f, -1.0f,
	        1.0f, 1.0f, -1.0f,
	        1.0f, -1.0f, -1.0f,
	        -1.0f, -1.0f, -1.0f,
	        -1.0f, -1.0f, -1.0f,
	        -1.0f, 1.0f, 1.0f,
	        -1.0f, 1.0f, -1.0f,
	        1.0f, -1.0f, 1.0f,
	        -1.0f, -1.0f, 1.0f,
	        -1.0f, -1.0f, -1.0f,
	        -1.0f, 1.0f, 1.0f,
	        -1.0f, -1.0f, 1.0f,
	        1.0f, -1.0f, 1.0f,
	        1.0f, 1.0f, 1.0f,
	        1.0f, -1.0f, -1.0f,
	        1.0f, 1.0f, -1.0f,
	        1.0f, -1.0f, -1.0f,
	        1.0f, 1.0f, 1.0f,
	        1.0f, -1.0f, 1.0f,
	        1.0f, 1.0f, 1.0f,
	        1.0f, 1.0f, -1.0f,
	        -1.0f, 1.0f, -1.0f,
	        1.0f, 1.0f, 1.0f,
	        -1.0f, 1.0f, -1.0f,
	        -1.0f, 1.0f, 1.0f,
	        1.0f, 1.0f, 1.0f,
	        -1.0f, 1.0f, 1.0f,
	        1.0f, -1.0f, 1.0f
	    };

    /***** Vertex Buffer *******/
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Sphere::initColor()
{
    float r = 1.0f; 
    float g = 1.0f;
    float b = 0.50f;

    static const GLfloat g_color_buffer_data[] = {
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b,
        r, g, b
    };

    /***** Color Buffer *******/
    // Generate 1 buffer, put the resulting identifier in colorbuffer
    glGenBuffers(1, &colorbuffer);
    // The following commands will talk about our 'colorbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
}

void Sphere::initTexture()
{
    // Two UV coordinatesfor each vertex. They were created withe Blender.
     static const GLfloat g_uv_buffer_data[] = {
             0.000059f, 1.0f-0.000004f,
             0.000103f, 1.0f-0.336048f,
             0.335973f, 1.0f-0.335903f,
             1.000023f, 1.0f-0.000013f,
             0.667979f, 1.0f-0.335851f,
             0.999958f, 1.0f-0.336064f,
             0.667979f, 1.0f-0.335851f,
             0.336024f, 1.0f-0.671877f,
             0.667969f, 1.0f-0.671889f,
             1.000023f, 1.0f-0.000013f,
             0.668104f, 1.0f-0.000013f,
             0.667979f, 1.0f-0.335851f,
             0.000059f, 1.0f-0.000004f,
             0.335973f, 1.0f-0.335903f,
             0.336098f, 1.0f-0.000071f,
             0.667979f, 1.0f-0.335851f,
             0.335973f, 1.0f-0.335903f,
             0.336024f, 1.0f-0.671877f,
             1.000004f, 1.0f-0.671847f,
             0.999958f, 1.0f-0.336064f,
             0.667979f, 1.0f-0.335851f,
             0.668104f, 1.0f-0.000013f,
             0.335973f, 1.0f-0.335903f,
             0.667979f, 1.0f-0.335851f,
             0.335973f, 1.0f-0.335903f,
             0.668104f, 1.0f-0.000013f,
             0.336098f, 1.0f-0.000071f,
             0.000103f, 1.0f-0.336048f,
             0.000004f, 1.0f-0.671870f,
             0.336024f, 1.0f-0.671877f,
             0.000103f, 1.0f-0.336048f,
             0.336024f, 1.0f-0.671877f,
             0.335973f, 1.0f-0.335903f,
             0.667969f, 1.0f-0.671889f,
             1.000004f, 1.0f-0.671847f,
             0.667979f, 1.0f-0.335851f
     };

     glGenBuffers(1, &uvbuffer);
     glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
     glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

glm::mat4 Sphere::GetModelMatrix()
{
    glm::mat4 ScalingMatrix = glm::scale(glm::mat4(), glm::vec3(this->ScaleX, this->ScaleY, this->ScaleZ));
    
    glm::mat4 TranslateMAtrix = glm::translate(glm::mat4(), glm::vec3(this->X, this->Y, this->Z));
    
    glm::mat4 Model = TranslateMAtrix * ScalingMatrix;

    return Model;
}

void Sphere::Render()
{
    // 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
        );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        3,                                // size
        GL_FLOAT,                         // type
        GL_FALSE,                         // normalized?
        0,                                // stride
        (void*)0                          // array buffer offset
        );

    /*
    // Index buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    // Draw the triangles !
    glDrawElements(
        GL_TRIANGLES,      // mode
        VBOSize,    // count
        GL_UNSIGNED_INT,   // type
        (void*)0           // element array buffer offset
        );
    */

    // Draw the cube !
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}


void Sphere::RenderTexture()
{
    // Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "textureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

    // Draw the cube !
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
