#include "JSFBuffer.h"
#include "EDK3/dev/gpumanager.h"

JSF::JSFBuffer::JSFBuffer()
{
	buffer_id_ = -1;
	size_ = 0;
}

JSF::JSFBuffer::~JSFBuffer()
{
	if (buffer_id_ != -1) {

		glDeleteBuffers(1, &buffer_id_);

	}
}

void JSF::JSFBuffer::init(unsigned int size)
{
	size_ = size;
	
	glGenBuffers(1, &buffer_id_);

	bind(kTarget_Vertex_Data);
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_STATIC_DRAW);
}

void JSF::JSFBuffer::bind(const Target t) const
{
	switch (t)
	{
		case kTarget_Vertex_Data:
				glBindBuffer(GL_ARRAY_BUFFER, buffer_id_); 
			break;
		case kTarget_Elements:
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_id_); 
			break;
		default: 
			break;
	}
}

unsigned int JSF::JSFBuffer::size() const
{
	return size_;
}

void JSF::JSFBuffer::uploadData(const void* data, unsigned int size, unsigned int offset)
{
	bind(kTarget_Vertex_Data);

	glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

void JSF::JSFBuffer::release()
{
	if (-1 != buffer_id_) {
		glDeleteBuffers(1, &buffer_id_);
	}
}
