/*!
\brief The Swapchain class. The Swapchain is the object wrapping
the on-screen rendering Framebuffer images (aka front/backbuffers)
\file PVRVk/SwapchainVk.h
\author PowerVR by Imagination, Developer Technology Team
\copyright Copyright (c) Imagination Technologies Limited.
*/

#pragma once
#include "PVRVk/DeviceVk.h"
#include "PVRVk/ImageVk.h"
namespace pvrvk {
/// <summary>Contains swapchain create informations</summary>
struct SwapchainCreateInfo
{
public:
	pvrvk::SwapchainCreateFlagsKHR flags; //!< Bitmask of pvrvk::SwapchainCreateFlagBitsKHR indicating parameters of swapchain creation.
	Surface surface; //!< The surface that the swapchain will present images to.
	uint32_t minImageCount; //!< The minimum number of presentable images that the application needs. The platform will either create the swapchain with at least that many images,
							//!< or will fail to create the swapchain
	pvrvk::Format imageFormat; //!< pvrvk::Format that is valid for swapchains on the specified surface.
	pvrvk::ColorSpaceKHR imageColorSpace; //!<  pvrvk::ColorSpaceKHR that is valid for swapchains on the specified surface.
	Extent2D imageExtent; //!< Size (in pixels) of the swapchain. Behavior is platform-dependent when the image extent does not match the surface’s currentExtent as returned by
						  //!< PysicalDevice::getSurfaceCapabilities
	uint32_t imageArrayLayers; //!< Number of views in a multiview/stereo surface. For non-stereoscopic-3D applications, this value is 1
	pvrvk::ImageUsageFlags imageUsage; //!< Bitmask of pvrvk::ImageUsageFlagBits, indicating how the application will use the swapchain’s presentable images
	pvrvk::SharingMode imageSharingMode; //!< Sharing mode used for the images of the swapchain.
	uint32_t numQueueFamilyIndex; //!< Number of queue families having access to the images of the swapchain in case imageSharingMode is VKSharingMode::e_CONCURRENT
	const uint32_t* queueFamilyIndices; //!< Array of queue family indices having access to the images of the swapchain in case imageSharingMode is VKSharingMode::e_CONCURRENT
	pvrvk::SurfaceTransformFlagsKHR preTransform; //!< Bitmask of pvrvk::SurfaceTransformFlagBitsKHR, describing the transform, relative to the presentation engine’s natural
												  //!< orientation, applied to the image content prior to presentation
	pvrvk::CompositeAlphaFlagsKHR compositeAlpha; //!< Bitmask of pvrvk::CompositeAlphaFlagBitsKHR indicating the alpha compositing mode to use when this surface is composited
												  //!< together with other surfaces on certain window systems
	pvrvk::PresentModeKHR presentMode; //!< Presentation mode the swapchain will use. A swapchain’s present mode determines how incoming present requests will be processed and queued internally
	bool clipped; //!< indicates whether the Vulkan implementation is allowed to discard rendering operations that affect regions of the surface which are not visible
	Swapchain oldSwapchain; //!< If not null handle, specifies the swapchain that will be replaced by the new swapchain being created. The new swapchain will be a descendant of
							//!< oldSwapchain. Further, any descendants of the new swapchain will also be descendants of oldSwapchain

	/// <summary>Constructor. Default intialised</summary>
	SwapchainCreateInfo()
		: flags(pvrvk::SwapchainCreateFlagsKHR(0)), minImageCount(0), imageFormat(pvrvk::Format::e_UNDEFINED), imageColorSpace(pvrvk::ColorSpaceKHR::e_PASS_THROUGH_EXT),
		  imageExtent(Extent2D()), imageArrayLayers(0), imageUsage(pvrvk::ImageUsageFlags::e_COLOR_ATTACHMENT_BIT), imageSharingMode(pvrvk::SharingMode::e_EXCLUSIVE),
		  numQueueFamilyIndex(0), preTransform(pvrvk::SurfaceTransformFlagsKHR::e_IDENTITY_BIT_KHR), compositeAlpha(pvrvk::CompositeAlphaFlagsKHR::e_OPAQUE_BIT_KHR),
		  presentMode(pvrvk::PresentModeKHR::e_FIFO_KHR), clipped(true)
	{}
};

namespace impl {
/// <summary>The Swapchain is the object wrapping the on - screen rendering Framebuffer images
/// (aka front/backbuffers)</summary>
class Swapchain_ : public DeviceObjectHandle<VkSwapchainKHR>, public DeviceObjectDebugMarker<Swapchain_>
{
public:
	DECLARE_NO_COPY_SEMANTICS(Swapchain_)

	/// <summary>Acquire next image. The acquired swapchain index can be retrieved by calling getSwapchainIndex.
	///   Note: The presenation engine may still be consuming the swapchain image, therefore the calle must synchronise it before using it. </summary>
	/// <param name="timeOut">indicates how long the function waits, in nanoseconds, if no image is available.</param>
	/// <param name="signalSemaphore"> is null semaphore or a semaphore to signal</param>
	/// <param name="signalFence">is a null fence or fence to signal</param>
	/// <returns>Return true if image was acquired, false if timed out or suboptimal.</returns>
	bool acquireNextImage(uint64_t timeOut, Semaphore signalSemaphore, Fence signalFence);

	/// <summary>Acquire next image. The acquired swapchain index can be retrieved by calling getSwapchainIndex.
	///   Note: The presenation engine may still be consuming the swapchain image, therefore the calle must synchronise it before using it. </summary>
	/// <param name="timeOut">indicates how long the function waits, in nanoseconds, if no image is available.</param>
	/// <param name="signalSemaphore"> is null semaphore or a semaphore to signal</param>
	/// <returns>Return true if image was acquired, false if timed out or suboptimal.</returns>
	bool acquireNextImage(uint64_t timeOut, Semaphore signalSemaphore = Semaphore());

	/// <summary>Get swapchain length</summary>
	/// <returns>uint</returns>32_t
	uint32_t getSwapchainLength() const
	{
		return _swapChainLength;
	}

	/// <summary>Get the acquired swapchain index. Note: The presenation engine may still be consuming
	///   the swapchain image, therefore the calle must synchronise it before using it.  swapchain index</summary>
	/// <returns></returns>
	const uint32_t& getSwapchainIndex() const
	{
		return _swapchainId;
	}

	/// <summary>Get swapchain image view</summary>
	/// <param name="swapchain">swapchain index</param>
	/// <returns>ImageView</returns>
	ImageView getImageView(uint32_t swapchain) const
	{
		debug_assertion(swapchain < FrameworkCaps::MaxSwapChains, "Index out of bound");
		return _colorImageViews[swapchain];
	}

	/// <summary>Get swapchain image</summary>
	/// <param name="swapchain">swapchain index</param>
	/// <returns>Image</returns>
	Image getImage(uint32_t swapchain) const
	{
		return getImageView(swapchain)->getImage();
	}

	/// <summary>Get dimension</summary>
	/// <returns>Extent</returns>
	Extent2D getDimension() const
	{
		return Extent2D(_createInfo.imageExtent.getWidth(), _createInfo.imageExtent.getHeight());
	}

	/// <summary>Gets whether the swapchain images are clipped</summary>
	/// <returns>True if the swapchain images are clipped</returns>
	bool isClipped() const
	{
		return _createInfo.clipped;
	}

	/// <summary>Gets the pvrvk::CompositeAlphaFlagsKHR of the swapchain images</summary>
	/// <returns>The pvrvk::CompositeAlphaFlagsKHR for the swapchain image</returns>
	pvrvk::CompositeAlphaFlagsKHR getCompositeAlphaFlags() const
	{
		return _createInfo.compositeAlpha;
	}

	/// <summary>Gets the number of array layers of the swapchain images</summary>
	/// <returns>The number of array layers of the swapchain images</returns>
	uint32_t getNumArrayLayers() const
	{
		return _createInfo.imageArrayLayers;
	}

	/// <summary>Get swapchain image format</summary>
	/// <returns>pvrvk::Format</returns>
	pvrvk::Format getImageFormat() const
	{
		return _createInfo.imageFormat;
	}

	/// <summary>Gets the color space of the swapchain images</summary>
	/// <returns>The color space of the swapchain images</returns>
	pvrvk::ColorSpaceKHR getColorSpace() const
	{
		return _createInfo.imageColorSpace;
	}

	/// <summary>Gets the surface transform flags of the swapchain images</summary>
	/// <returns>The surface transform flags of the swapchain images</returns>
	pvrvk::SurfaceTransformFlagsKHR getTransformFlags() const
	{
		return _createInfo.preTransform;
	}

	/// <summary>Gets the image sharing mode of the swapchain images</summary>
	/// <returns>The image sharing mode of the swapchain images</returns>
	pvrvk::SharingMode getSharingMode() const
	{
		return _createInfo.imageSharingMode;
	}

	/// <summary>Gets the presentation mode of the swapchain images</summary>
	/// <returns>The presentation mode of the swapchain images</returns>
	pvrvk::PresentModeKHR getPresentationMode() const
	{
		return _createInfo.presentMode;
	}

	/// <summary>Gets the number of queue families which can make use of the swapchain images</summary>
	/// <returns>The number of queue families which can make use of the swapchain images</returns>
	uint32_t getNumQueueFamilyIndices() const
	{
		return _createInfo.numQueueFamilyIndex;
	}

	/// <summary>Gets the queue family indicies for the queues which can make use of the swapchain images</summary>
	/// <returns>The queue family indicies for the queues which can make use of the swapchain images</returns>
	std::vector<uint32_t> getQueueFamilyIndices() const
	{
		std::vector<uint32_t> indices;
		for (uint32_t i = 0; i < _createInfo.numQueueFamilyIndex; i++)
		{
			indices.push_back(_createInfo.queueFamilyIndices[i]);
		}
		return indices;
	}

	/// <summary>Gets the swapchain image usage flags</summary>
	/// <returns>The swapchain image usage</returns>
	pvrvk::ImageUsageFlags getUsage() const
	{
		return _createInfo.imageUsage;
	}

	/// <summary>Returns whether the swapchain supports the specified image usage flag bits</summary>
	/// <param name="imageUsage">The pvrvk::ImageUsageFlags bits to check for support</param>
	/// <returns>True if the swapchain supports the specified image usage</returns>
	bool supportsUsage(const pvrvk::ImageUsageFlags& imageUsage) const
	{
		if (static_cast<uint32_t>(getUsage() & imageUsage) != 0)
		{
			return true;
		}
		return false;
	}

private:
	friend class ::pvrvk::impl::Device_;
	template<typename>
	friend struct ::pvrvk::RefCountEntryIntrusive;
	Swapchain_(DeviceWeakPtr device, Surface surface, const SwapchainCreateInfo& createInfo);

	~Swapchain_();

	uint32_t _swapchainId;
	uint32_t _swapChainLength;
	ImageView _colorImageViews[static_cast<uint32_t>(FrameworkCaps::MaxSwapChains)];
	Surface _surface;
	pvrvk::SwapchainCreateInfo _createInfo;
};
} // namespace impl
} // namespace pvrvk
