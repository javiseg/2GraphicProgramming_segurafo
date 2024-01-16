
#include "EDK3/dev/buffer.h"
#include "EDK3/dev/opengl.h"
#include "EDK3/ref_ptr.h"

namespace JSF {

	class JSFBuffer : public EDK3::dev::Buffer {

	public:
		virtual void init(unsigned int size) override;

		virtual void bind(const EDK3::dev::Buffer::Target t) const override;
		virtual unsigned int size() const override;
		
		virtual void uploadData(const void* data, unsigned int size, unsigned int offset = 0) override;
		virtual void release() override;

	protected:
		JSFBuffer();
		virtual ~JSFBuffer();

	private:
		GLuint buffer_id_;
		unsigned int size_;
		friend class EDK3::ref_ptr<EDK3::dev::Buffer>;
	};
}


