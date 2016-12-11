#include "FrameBuffer.h"
#include "GLError.h"

FrameBuffer::FrameBuffer()
{
	glGenFramebuffers(1, &FBO);
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttachments);
}

FrameBuffer::FrameBuffer(GLuint FBO)
{
	this->FBO = FBO;
	glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS, &maxAttachments);
}

FrameBuffer::~FrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &FBO);
}

void FrameBuffer::Attach(AttachmentType type, GLuint index, GLuint layout, bool isRenderBuffer)
{
	if (layout < 0 || layout >(maxAttachments - 1))
	{
		cout << "Maximum number of attachments is " << maxAttachments << "!\nYou are trying to use layout " << layout << "!" << endl;
		_ASSERT(false);
	}

	//Bind this FrameBuffer as current one!
	glBindFramebuffer(GL_FRAMEBUFFER, FBO);

	//Do different attaching opperations depending on Attachment type!
	switch (type)
	{
	case Color_Attachment:
	{
		//Bind Texture ID with given Color Attachment
		if (isRenderBuffer)
		{
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + layout, GL_RENDERBUFFER, index);
		}
		else
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + layout, GL_TEXTURE_2D, index, 0);
		}

		//Check if attachment was already in use
		if (!((attachmentsUsed >> layout + 2) & 0x01))
		{
			numAttachments++;
		}

		//Register attachment as used
		attachmentsUsed |= (0x01 << layout + 2);
	}
	break;
	case Depth_Attachment:
	{
		if (isRenderBuffer)
		{
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, index);
		}
		else
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, index, 0);
		}

		//Register attachment as used
		attachmentsUsed |= (0x01);
	}
	break;
	case Stencil_Attachment:
		//TODO
		break;
	case (Depth_Attachment | Stencil_Attachment):
		//TODO
		break;
	default:
		cout << "FrameBuffer attachment of type " << type << " doesn't exists!" << endl;
		_ASSERT(false);
		break;
	}

	//Check whether or not FrameBuffer is okay with GPU capabilities
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		cout << "FrameBuffer error! Status: " << status << endl;
		_ASSERT(false);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Bind()
{
	if (numAttachments > 0)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, FBO);

		// Set the list of draw buffers.
		GLenum *DrawBuffers = new GLenum[numAttachments];
		int cont = 0;

		//For each color attachment
		for (GLuint i = 0; i < sizeof(GLuint) * 8 - 2; i++)
		{
			if ((attachmentsUsed >> i + 2) & 0x01)
			{
				//--Debug--//
				//cout << "Color Attachment " << i << " linked to draw buffer layout " << cont << endl;
				//---------//
				DrawBuffers[cont] = GL_COLOR_ATTACHMENT0 + i;
				cont++;
			}
		}

		//Debug glDrawBuffers
		//check_gl_error();
		glDrawBuffers(numAttachments, DrawBuffers);
		//check_gl_error();

		//Check whether or not FrameBuffer is okay with GPU capabilities
		GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
		if (status != GL_FRAMEBUFFER_COMPLETE)
		{
			cout << "FrameBuffer error! Status: " << status << endl;
			_ASSERT(false);
		}

		//No errors occured! Return normally!
		return;
	}

	cout << "FrameBuffer cannot be used if there is no attachments!" << endl;
	_ASSERT(false);
}

void FrameBuffer::Unbind()
{
	glDrawBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBuffer::Reset()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	attachmentsUsed = 0;
	numAttachments = 0;
}

GLuint FrameBuffer::getFBO()
{
	return FBO;
}