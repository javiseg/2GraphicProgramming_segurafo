#include <EDK3/ref_ptr.h>
#include <EDK3/texture.h>

#include <EDK3/dev/opengl.h>


namespace JSF {

	class JSFTexture : public EDK3::Texture {

	public:

		void set_data(const Format f, 
			const EDK3::Type t, const void* data, 
			unsigned int mipmap_LOD = 0) override;
		
		void bind(unsigned int utext) const override;

		unsigned int internal_id() const override;
		void set_mag_filter(Filter f) override;
		void set_min_filter(Filter f) override;
		void generateMipmaps() const override;
		void set_wrap_s(Wrap c) override;
		void set_wrap_t(Wrap c) override;
		void set_wrap_r(Wrap c) override;

		void initTexture(Type t, Format internal_format, 
			unsigned int width, unsigned int height = 1, 
			unsigned int depth = 1);

		GLenum ConvertType(Type t) const;
		
		GLint ConvertWrap(Wrap c) const;
		
		GLenum ConvertFormat(Format t) const;

		
	private:
		
		JSFTexture(const JSFTexture&);
		JSFTexture& operator=(const JSFTexture&);

		friend class EDK3::ref_ptr<EDK3::Texture>;


		GLuint text_id_;
	
	protected:
		JSFTexture();
		virtual ~JSFTexture();



	};
}
