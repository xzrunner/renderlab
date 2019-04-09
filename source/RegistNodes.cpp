#include "renderlab/RegistNodes.h"
#include "renderlab/PinType.h"

#include <ee0/ReflectPropTypes.h>
#include <blueprint/NodeHelper.h>

#include <node2/RenderSystem.h>
#include <painting2/RenderSystem.h>
#include <rendergraph/node/Texture.h>
#include <rendergraph/node/Shader.h>
#include <js/RTTR.h>

#define REGIST_NODE_RTTI(name, prop)                            \
	rttr::registration::class_<rlab::node::name>("rlab::"#name) \
		.constructor<>()                                        \
		prop                                                    \
	;

#define PROP
#define REGIST_NODE_RTTI_DEFAULT(name) REGIST_NODE_RTTI(name, PROP)

RTTR_REGISTRATION
{

REGIST_NODE_RTTI(Clear,                                            \
.property("type", &rlab::node::Clear::type)                        \
(                                                                  \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Type"))  \
)                                                                  \
.property("color", &rlab::node::Clear::color)                      \
(                                                                  \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Color")) \
)                                                                  \
)

REGIST_NODE_RTTI(Viewport,                                          \
.property("x", &rlab::node::Viewport::x)                            \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("X"))      \
)                                                                   \
.property("y", &rlab::node::Viewport::y)                            \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Y"))      \
)                                                                   \
.property("w", &rlab::node::Viewport::w)                            \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Width"))  \
)                                                                   \
.property("h", &rlab::node::Viewport::h)                            \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Height")) \
)                                                                   \
)

REGIST_NODE_RTTI(Texture,                                              \
.property("filepath", &rlab::node::Texture::filepath)                  \
(                                                                      \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Filepath")), \
    rttr::metadata(js::RTTR::FilePathTag(), true),                     \
    rttr::metadata(ee0::PropOpenFileTag(), ee0::PropOpenFile("*.png")) \
)                                                                      \
.property("type", &rlab::node::Texture::type)                          \
(                                                                      \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Type"))      \
)                                                                      \
.property("width", &rlab::node::Texture::width)                        \
(                                                                      \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Width"))     \
)                                                                      \
.property("height", &rlab::node::Texture::height)                      \
(                                                                      \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Height"))    \
)                                                                      \
.property("format", &rlab::node::Texture::format)                      \
(                                                                      \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Format"))    \
)                                                                      \
)

REGIST_NODE_RTTI_DEFAULT(RenderTarget)

REGIST_NODE_RTTI(Shader,                                                      \
.property("vert", &rlab::node::Shader::GetVert, &rlab::node::Shader::SetVert) \
(                                                                             \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Vert")),            \
    rttr::metadata(ee0::PropLongStringTag(), true)                            \
)                                                                             \
.property("frag", &rlab::node::Shader::GetFrag, &rlab::node::Shader::SetFrag) \
(                                                                             \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Frag")),            \
    rttr::metadata(ee0::PropLongStringTag(), true)                            \
)                                                                             \
)

REGIST_NODE_RTTI(Bind,                                               \
.property("channel", &rlab::node::Bind::channel)                     \
(                                                                    \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Channel")) \
)                                                                    \
)

REGIST_NODE_RTTI_DEFAULT(Unbind)
REGIST_NODE_RTTI_DEFAULT(DrawCube)

REGIST_NODE_RTTI_DEFAULT(OutputToScreen)

// value
REGIST_NODE_RTTI(Vector1,                                        \
.property("val", &rlab::node::Vector1::val)                      \
(                                                                \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Val")) \
)                                                                \
)
REGIST_NODE_RTTI(Vector2,                                        \
.property("val", &rlab::node::Vector2::val)                      \
(                                                                \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Val")) \
)                                                                \
)
REGIST_NODE_RTTI(Vector3,                                        \
.property("val", &rlab::node::Vector3::val)                      \
(                                                                \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Val")) \
)                                                                \
)
REGIST_NODE_RTTI(Vector4,                                        \
.property("val", &rlab::node::Vector4::val)                      \
(                                                                \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Val")) \
)                                                                \
)
REGIST_NODE_RTTI(Matrix2,                                        \
.property("val", &rlab::node::Matrix2::val)                      \
(                                                                \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Val")) \
)                                                                \
)
REGIST_NODE_RTTI(Matrix3,                                        \
.property("val", &rlab::node::Matrix3::val)                      \
(                                                                \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Val")) \
)                                                                \
)
REGIST_NODE_RTTI(Matrix4,                                        \
.property("val", &rlab::node::Matrix4::val)                      \
(                                                                \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Val")) \
)                                                                \
)
// math
REGIST_NODE_RTTI_DEFAULT(Add)
REGIST_NODE_RTTI_DEFAULT(Mul)
REGIST_NODE_RTTI(PerspectiveMat,                                    \
.property("fovy", &rlab::node::PerspectiveMat::fovy)                \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Fovy"))   \
)                                                                   \
.property("aspect", &rlab::node::PerspectiveMat::aspect)            \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Aspect")) \
)                                                                   \
.property("znear", &rlab::node::PerspectiveMat::znear)              \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("ZNear"))  \
)                                                                   \
.property("zfar", &rlab::node::PerspectiveMat::zfar)                \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("ZFar"))   \
)                                                                   \
)
REGIST_NODE_RTTI(OrthoMat,                                          \
.property("left", &rlab::node::OrthoMat::left)                      \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Left"))   \
)                                                                   \
.property("right", &rlab::node::OrthoMat::right)                    \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Right"))  \
)                                                                   \
.property("bottom", &rlab::node::OrthoMat::bottom)                  \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Bottom")) \
)                                                                   \
.property("top", &rlab::node::OrthoMat::top)                        \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Top"))    \
)                                                                   \
.property("znear", &rlab::node::OrthoMat::znear)                    \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("ZNear"))  \
)                                                                   \
.property("zfar", &rlab::node::OrthoMat::zfar)                      \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("ZFar"))   \
)                                                                   \
)
REGIST_NODE_RTTI(LookAtMat,                                         \
.property("eye", &rlab::node::LookAtMat::eye)                       \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Eye"))    \
)                                                                   \
.property("center", &rlab::node::LookAtMat::center)                 \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Center")) \
)                                                                   \
.property("up", &rlab::node::LookAtMat::up)                         \
(                                                                   \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Up"))     \
)                                                                   \
)
// input
REGIST_NODE_RTTI_DEFAULT(CamProjMat)
REGIST_NODE_RTTI_DEFAULT(CamViewMat)
REGIST_NODE_RTTI_DEFAULT(CameraPosition)
REGIST_NODE_RTTI_DEFAULT(LightPosition)

// state
REGIST_NODE_RTTI(Cull,                                            \
.property("type", &rlab::node::Cull::type)                        \
(                                                                 \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Cull")) \
)                                                                 \
)

}

namespace rlab
{

void nodes_regist_rttr()
{
}

namespace node
{

//////////////////////////////////////////////////////////////////////////
// class Texture
//////////////////////////////////////////////////////////////////////////

void Texture::PreviewDraw(const rg::NodePtr& node, const sm::Matrix2D& mat) const
{
    if (!node) {
        return;
    }

    assert(node->get_type() == rttr::type::get<rg::node::Texture>());
    auto tex = std::static_pointer_cast<rg::node::Texture>(node);
    pt2::RenderSystem::DrawTexture(width, height, tex->GetTexID(), sm::rect(1, 1), mat);
}

//////////////////////////////////////////////////////////////////////////
// class Shader
//////////////////////////////////////////////////////////////////////////

void Shader::SetVert(const std::string& vert)
{
    if (m_vert == vert) {
        return;
    }

    m_vert = vert;

    std::vector<Node::PinDesc> uniforms;
    GetCodeUniforms(m_vert, uniforms);
    if (uniforms != m_vert_uniforms) {
        m_vert_uniforms = uniforms;
        InitInputsFromUniforms();
    }
}

void Shader::SetFrag(const std::string& frag)
{
    if (m_frag == frag) {
        return;
    }

    m_frag = frag;

    std::vector<Node::PinDesc> uniforms;
    GetCodeUniforms(m_frag, uniforms);
    if (uniforms != m_frag_uniforms) {
        m_frag_uniforms = uniforms;
        InitInputsFromUniforms();
    }
}

void Shader::InitInputsFromUniforms()
{
    std::vector<Node::PinDesc> uniforms = m_vert_uniforms;
    std::copy(m_frag_uniforms.begin(), m_frag_uniforms.end(), std::back_inserter(uniforms));

    bool same = true;
    if (uniforms.size() == m_all_input.size() - 1) {
        for (int i = 0, n = uniforms.size(); i < n; ++i) {
            if (uniforms[i].type != m_all_input[1 + i]->GetOldType() ||
                uniforms[i].name != m_all_input[1 + i]->GetName()) {
                same = false;
                break;
            }
        }
    } else {
        same = false;
    }

    if (same) {
        return;
    }

    for (int i = 1, n = m_all_input.size(); i < n; ++i) {
        for (auto& c : m_all_input[i]->GetConnecting()) {
            bp::disconnect(c);
        }
    }
    m_all_input.erase(m_all_input.begin() + 1, m_all_input.end());

    for (auto& desc : uniforms) {
        auto pin = std::make_shared<bp::Pin>(true, m_all_input.size(), desc.type, desc.name, *this);
        m_all_input.push_back(pin);
    }
    Layout();

    SetSizeChanged(true);
}

void Shader::GetCodeUniforms(const std::string& code, std::vector<Node::PinDesc>& uniforms)
{
    std::vector<rg::Variable> rg_unifs;
    rg::node::Shader::GetCodeUniforms(code, rg_unifs);
    for (auto& u : rg_unifs)
    {
        Node::PinDesc desc;
        desc.name = u.name;
        switch (u.type)
        {
        case rg::VariableType::Vector1:
            desc.type = PIN_VECTOR1;
            break;
        case rg::VariableType::Vector2:
            desc.type = PIN_VECTOR2;
            break;
        case rg::VariableType::Vector3:
            desc.type = PIN_VECTOR3;
            break;
        case rg::VariableType::Vector4:
            desc.type = PIN_VECTOR4;
            break;
        case rg::VariableType::Matrix2:
            desc.type = PIN_MATRIX2;
            break;
        case rg::VariableType::Matrix3:
            desc.type = PIN_MATRIX3;
            break;
        case rg::VariableType::Matrix4:
            desc.type = PIN_MATRIX4;
            break;
        case rg::VariableType::Sampler2D:
            desc.type = PIN_SAMPLER2D;
            break;
        default:
            assert(0);
        }
        uniforms.push_back(desc);
    }
}

}
}