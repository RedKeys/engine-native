/****************************************************************************
Copyright (c) 2020 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "GLES2Std.h"

#include "GLES2Commands.h"
#include "GLES2PipelineLayout.h"
#include "GLES2PipelineState.h"
#include "GLES2RenderPass.h"
#include "GLES2Shader.h"

namespace cc {
namespace gfx {

const GLenum GLES2Primitives[] = {
    GL_POINTS,
    GL_LINES,
    GL_LINE_STRIP,
    GL_LINE_LOOP,
    GL_NONE,
    GL_NONE,
    GL_NONE,
    GL_TRIANGLES,
    GL_TRIANGLE_STRIP,
    GL_TRIANGLE_FAN,
    GL_NONE,
    GL_NONE,
    GL_NONE,
    GL_NONE,
};

GLES2PipelineState::GLES2PipelineState(Device *device)
: PipelineState(device) {
}

GLES2PipelineState::~GLES2PipelineState() {
}

bool GLES2PipelineState::initialize(const PipelineStateInfo &info) {

    _primitive = info.primitive;
    _shader = info.shader;
    _inputState = info.inputState;
    _rasterizerState = info.rasterizerState;
    _depthStencilState = info.depthStencilState;
    _blendState = info.blendState;
    _dynamicStates = info.dynamicStates;
    _renderPass = info.renderPass;
    _pipelineLayout = info.pipelineLayout;

    _gpuPipelineState = CC_NEW(GLES2GPUPipelineState);
    _gpuPipelineState->glPrimitive = GLES2Primitives[(int)_primitive];
    _gpuPipelineState->gpuShader = ((GLES2Shader *)_shader)->gpuShader();
    _gpuPipelineState->rs = _rasterizerState;
    _gpuPipelineState->dss = _depthStencilState;
    _gpuPipelineState->bs = _blendState;
    _gpuPipelineState->gpuRenderPass = ((GLES2RenderPass *)_renderPass)->gpuRenderPass();
    _gpuPipelineState->gpuPipelineLayout = ((GLES2PipelineLayout *)_pipelineLayout)->gpuPipelineLayout();

    for (uint i = 0; i < 31; i++) {
        if ((uint)_dynamicStates & (1 << i)) {
            _gpuPipelineState->dynamicStates.push_back((DynamicStateFlagBit)(1 << i));
        }
    }

    return true;
}

void GLES2PipelineState::destroy() {
    if (_gpuPipelineState) {
        CC_DELETE(_gpuPipelineState);
        _gpuPipelineState = nullptr;
    }
}

} // namespace gfx
} // namespace cc
