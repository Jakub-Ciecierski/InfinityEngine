#include "Particle.h"

static std::vector<unsigned short> indices;

Particle::Particle() {
	X = Y = Z = 0;
	ScaleX = ScaleY = ScaleZ = 0.2f;

	initVertices();
	initColor();
}

Particle::Particle(float x, float y, float z) {
	X = x;
	Y = y;
	Z = z;
	ScaleX = ScaleY = ScaleZ = 0.2f;

	initVertices();
	initColor();
}

Particle::Particle(float x, float y, float z, GLuint texture,
		GLuint textureID) {
	X = x;
	Y = y;
	Z = z;
	ScaleX = ScaleY = ScaleZ = 1.0f;

	this->Texture = texture;
	this->TextureID = textureID;

	initVertices();
	initTexture();
	initIndices();
}

void Particle::init() {
	initVertices();
	//initColor();
	initTexture();
}

void Particle::initVertices() {
	static const GLfloat g_vertex_buffer_data[] = { -1.0f };

	/***** Vertex Buffer *******/
	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &vertexbuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
			g_vertex_buffer_data, GL_STATIC_DRAW);
}

void Particle::initColor() {
	float r = 1.0f;
	float g = 1.0f;
	float b = 0.50f;

	static const GLfloat g_color_buffer_data[] = { r, g, b, };

	/***** Color Buffer *******/
	// Generate 1 buffer, put the resulting identifier in colorbuffer
	glGenBuffers(1, &colorbuffer);
	// The following commands will talk about our 'colorbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data),
			g_color_buffer_data, GL_STATIC_DRAW);
}

void Particle::initTexture() {
	// Two UV coordinatesfor each vertex. They were created withe Blender.
	static const GLfloat g_uv_buffer_data[] = { 0.000059f, 1.0f - 0.000004f, };

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data,
			GL_STATIC_DRAW);
}

void Particle::initIndices() {
	if (indices.empty()) {
		fprintf(stderr, "initIndicies()\n");
		indices.push_back(0);
	}
	/***** Indices *******/
	// Generate a buffer for the indices
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			indices.size() * sizeof(unsigned short), &indices[0],
			GL_STATIC_DRAW);
}

void Particle::initPosition(){
	// The VBO containing the positions and sizes of the particles
	GLuint particles_position_buffer;
	glGenBuffers(1, &particles_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, particles_position_buffer);
	// Initialize with empty (NULL) buffer : it will be updated later, each frame.
	glBufferData(GL_ARRAY_BUFFER, MaxParticles * 4 * sizeof(GLfloat), NULL, GL_STREAM_DRAW);
}

glm::mat4 Particle::GetModelMatrix() {
	glm::mat4 ScalingMatrix = glm::scale(glm::mat4(),
			glm::vec3(this->ScaleX, this->ScaleY, this->ScaleZ));

	glm::mat4 TranslateMatrix = glm::translate(glm::mat4(),
			glm::vec3(this->X, this->Y, this->Z));

	glm::mat4 Model = TranslateMatrix * ScalingMatrix;

	return Model;
}

void Particle::Render() {
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*) 0            // array buffer offset
			);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glVertexAttribPointer(1, // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
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
	glDrawArrays(GL_TRIANGLES, 0, 1); // Starting from vertex 0; 3 vertices total -> 1 triangle

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Particle::RenderTexture() {
	// Bind our texture in Texture Unit 0
	glActiveTexture (GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "textureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*) 0            // array buffer offset
			);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
			);
	//fprintf(stderr, "Render() before glDrawArrays\n");
	// Draw the cube !
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
	//fprintf(stderr, "Render() after glDrawArrays\n");
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void Particle::RenderTextureIndices() {
	// Bind our texture in Texture Unit 0
	glActiveTexture (GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "textureSampler" sampler to user Texture Unit 0
	glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*) 0            // array buffer offset
			);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                                // size : U+V => 2
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*) 0                          // array buffer offset
			);

	// Index buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	// Draw the triangles !
	glDrawElements(GL_TRIANGLES,      // mode
			indices.size(),    // count
			GL_UNSIGNED_SHORT,   // type
			(void*) 0           // element array buffer offset
			);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}