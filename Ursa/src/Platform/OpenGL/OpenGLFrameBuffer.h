#pragma once
#include "Ursa/Renderer/FrameBuffer.h"

namespace Ursa {
	class OpenGLFrameBuffer : public FrameBuffer {
	public:
		OpenGLFrameBuffer(const FrameBufferSpecification& spec);
		virtual ~OpenGLFrameBuffer();

		void Invalidate();
		virtual void Bind() override;
		virtual void Unbind() override;
		virtual void Resize(uint32_t width, uint32_t height) override;
		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
		virtual uint32_t GetDepthAttachmentRendererID() const override { return m_DepthAttachment; }
		virtual const FrameBufferSpecification& GetSpecification() const override { return m_Specification; }

	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment = 0;
		uint32_t m_DepthAttachment = 0;
		uint32_t m_IDAttachment = 0;
		FrameBufferSpecification m_Specification;
	};
}