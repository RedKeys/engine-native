#include "VKStd.h"

#include "VKCommands.h"
#include "VKTexture.h"
#include "VKTextureView.h"

NS_CC_BEGIN

CCVKTextureView::CCVKTextureView(GFXDevice *device)
: GFXTextureView(device) {
}

CCVKTextureView::~CCVKTextureView() {
}

bool CCVKTextureView::initialize(const GFXTextureViewInfo &info) {
    _texture = info.texture;
    _type = info.type;
    _format = info.format;
    _baseLevel = info.baseLevel;
    _levelCount = info.levelCount;
    _baseLayer = info.baseLayer;
    _layerCount = info.layerCount;
    if (_texture == nullptr) {
        CC_LOG_ERROR("CCVKTextureView: texture should not be nullptr.");
        _status = GFXStatus::FAILED;
        return false;
    }
    _gpuTexView = CC_NEW(CCVKGPUTextureView);
    _gpuTexView->gpuTexture = static_cast<CCVKTexture *>(_texture)->gpuTexture();
    _gpuTexView->type = _type;
    _gpuTexView->format = _format;
    _gpuTexView->baseLevel = info.baseLevel;
    _gpuTexView->levelCount = info.levelCount;

    CCVKCmdFuncCreateTextureView((CCVKDevice *)_device, _gpuTexView);

    _status = GFXStatus::SUCCESS;

    return true;
}

void CCVKTextureView::destroy() {
    if (_gpuTexView) {
        CCVKCmdFuncDestroyTextureView((CCVKDevice *)_device, _gpuTexView);
        CC_DELETE(_gpuTexView);
        _gpuTexView = nullptr;
    }
    _texture = nullptr;
    _status = GFXStatus::UNREADY;
}

NS_CC_END