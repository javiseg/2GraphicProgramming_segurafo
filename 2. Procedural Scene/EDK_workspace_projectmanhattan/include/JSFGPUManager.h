#include "EDK3/dev/gpumanager.h"
#include "EDK3/dev/opengl.h"

namespace JSF {

	class JSFGPUManager : public EDK3::dev::GPUManager {
	
	public:
		JSFGPUManager();
		virtual ~JSFGPUManager();
		virtual void newShader(EDK3::ref_ptr<EDK3::dev::Shader>* output) override;
		virtual void newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output) override;
		virtual void newProgram(EDK3::ref_ptr<EDK3::dev::Program>* output) override;
		GLenum ConvertEDK3Type(EDK3::Type element_type);
		unsigned GetSize(EDK3::Type t);
		void enableCullFaces(const FaceType f)override;
		void disableCullFaces() override;
		void changeColorMask(const bool red, const bool green, const bool blue, const bool alpha) override;
		virtual void enableVertexAttribute(
			const EDK3::dev::Buffer* buffer,
			const unsigned int attribute_index,
			const EDK3::Type type,
			const bool normalized = false,
			const unsigned int offset = 0,
			const unsigned int stride = 0) override;
		
		void changeDepthMask(bool enable);
		virtual void disableVertexAttribute(const unsigned int attrib_index) override;
		/*virtual void drawElements(
			const DrawMode mode,
			unsigned int count,
			const EDK3::dev::Buffer* buffer,
			const EDK3::Type element_type = EDK3::Type::T_USHORT,
			const unsigned int offset = 0) const override;*/
		void enableDepthTest(const CompareFunc f);
		void disableDepthTest() override;
		void enableScissor(int x, int y, unsigned int width, unsigned int height) override;
		void disableScissor()override;
		void enableBlend(BlendParam source, BlendParam destination, BlendOp operation, const float ConstantColor[4])override;
		void disableBlend();
	};
}