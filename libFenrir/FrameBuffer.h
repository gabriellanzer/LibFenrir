#include <iostream>
#include <gl\glew.h>
#include <gl\GL.h>

#pragma once
using namespace std;
enum AttachmentType
{
	Color_Attachment = 0x00,
	Depth_Attachment = 0x01,
	Stencil_Attachment = 0x02
};

class FrameBuffer
{
public:
	FrameBuffer();
	FrameBuffer(GLuint index);
	~FrameBuffer();

	void Attach(AttachmentType type, GLuint index, GLuint layout = 0, bool isRenderBuffer = false);

	void Bind();
	void Unbind();
	void Reset();

	GLuint getFBO();

private:
	GLuint FBO;
	GLuint attachmentsUsed = 0;
	GLuint numAttachments = 0;
	GLint maxAttachments = 0;
};