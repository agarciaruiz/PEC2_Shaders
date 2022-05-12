#ifndef ARRAYBUFFERS_H
#define ARRAYBUFFERS_H

#include <glad/glad.h>

class ArrayBuffers {
private:
	unsigned int vao;
	unsigned int vbo;

	void initialiseBuffer(float vertices[]) {
		vao = createVertexArray(vertices);
	}

	void bindArray(unsigned int vertexArray) {
		glBindVertexArray(vertexArray);
	}

	void bindTexture(unsigned int texture) {
		glBindTexture(GL_TEXTURE_2D, texture);
	}

	unsigned int createVertexArray(float vertices[]) {
		unsigned int vao, vbo;
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		return vao;
	}

public:
	ArrayBuffers(float vertices[]) {
		initialiseBuffer(vertices);
	}

	void bindVertexArray() {
		bindArray(vao);
	}

	void bindVertexTexture(unsigned int texture) {
		bindTexture(texture);
	}

	void enableVertexAttrib(unsigned int index, unsigned int size, unsigned int stride, unsigned int position) {
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)position);
	}

	void cleanUp() {
		glDeleteVertexArrays(1, &vao);
		glDeleteBuffers(1, &vbo);
	}
};
#endif