#include "renderlab/RenderGraph.h"
#include "renderlab/RegistNodes.h"
#include "renderlab/Node.h"
#include "renderlab/PinType.h"

#include <blueprint/Node.h>
#include <blueprint/Pin.h>
#include <blueprint/Connecting.h>

#include <unirender/typedef.h>
#include <rendergraph/node/Clear.h>
#include <rendergraph/node/Viewport.h>
#include <rendergraph/node/Texture.h>
#include <rendergraph/node/Shader.h>
#include <rendergraph/node/Bind.h>
#include <rendergraph/node/value_nodes.h>
#include <rendergraph/node/math_nodes.h>
#include <rendergraph/node/Cull.h>
#include <facade/ImageLoader.h>

namespace rlab
{

rg::NodePtr RenderGraph::CreateGraphNode(const bp::Node& node)
{
    auto type = node.get_type();
    auto src_type = type.get_name().to_string();
    std::string dst_type;
    auto find_sg = src_type.find("rlab::");
    if (find_sg != std::string::npos) {
        dst_type = "rg::" + src_type.substr(find_sg + strlen("rlab::"));
    }
    if (dst_type.empty()) {
        return nullptr;
    }

	rttr::type t = rttr::type::get_by_name(dst_type);
	if (!t.is_valid()) {
		return nullptr;
	}
	assert(t.is_valid());
	rttr::variant var = t.create();
	assert(var.is_valid());

    rg::NodePtr dst = var.get_value<std::shared_ptr<rg::Node>>();
	assert(dst);

    if (type == rttr::type::get<node::Clear>())
    {
        auto& src = static_cast<const node::Clear&>(node);
        auto clear = std::static_pointer_cast<rg::node::Clear>(dst);

        uint32_t type = 0;
        if (src.type.type & ClearType::CLEAR_COLOR) {
            type |= rg::node::Clear::CLEAR_COLOR;
        }
        if (src.type.type & ClearType::CLEAR_DEPTH) {
            type |= rg::node::Clear::CLEAR_DEPTH;
        }
        if (src.type.type & ClearType::CLEAR_STENCIL) {
            type |= rg::node::Clear::CLEAR_STENCIL;
        }
        clear->SetClearType(type);

        clear->SetColor(src.color);
    }
    else if (type == rttr::type::get<node::Viewport>())
    {
        auto& src = static_cast<const node::Viewport&>(node);
        auto vp = std::static_pointer_cast<rg::node::Viewport>(dst);
        vp->SetParams(src.x, src.y, src.w, src.h);
    }
    else if (type == rttr::type::get<node::Texture>())
    {
        auto& src = static_cast<const node::Texture&>(node);
        auto tex = std::static_pointer_cast<rg::node::Texture>(dst);

        tex->SetFilepath(src.filepath);

        int type = 0;
        switch (src.type)
        {
        case TextureType::Tex2D:
            type = ur::TEXTURE_2D;
            break;
        case TextureType::TexCube:
            type = ur::TEXTURE_CUBE;
            break;
        }

        int format = 0;
        switch (src.format)
        {
        case TextureFormat::RGBA8:
            format = ur::TEXTURE_RGBA8;
            break;
        case TextureFormat::RGBA4:
            format = ur::TEXTURE_RGBA4;
            break;
        case TextureFormat::RGB:
            format = ur::TEXTURE_RGB;
            break;
        case TextureFormat::RGB565:
            format = ur::TEXTURE_RGB565;
            break;
        case TextureFormat::A8:
            format = ur::TEXTURE_A8;
            break;
        }

        tex->SetParams(type, src.width, src.height, format);

        // todo
        facade::ImageLoader loader(src.filepath);
        loader.Load();
        tex->SetTexID(loader.GetID());
    }
    else if (type == rttr::type::get<node::Shader>())
    {
        auto& src = static_cast<const node::Shader&>(node);
        std::static_pointer_cast<rg::node::Shader>(dst)->SetCodes(src.GetVert(), src.GetFrag());
    }
    else if (type == rttr::type::get<node::Bind>())
    {
        auto& src = static_cast<const node::Bind&>(node);
        std::static_pointer_cast<rg::node::Bind>(dst)->SetChannel(src.channel);
    }
    // value
    else if (type == rttr::type::get<node::Vector1>())
    {
        auto& src = static_cast<const node::Vector1&>(node);
        std::static_pointer_cast<rg::node::Vector1>(dst)->SetValue(src.val);
    }
    else if (type == rttr::type::get<node::Vector2>())
    {
        auto& src = static_cast<const node::Vector2&>(node);
        std::static_pointer_cast<rg::node::Vector2>(dst)->SetValue(src.val);
    }
    else if (type == rttr::type::get<node::Vector3>())
    {
        auto& src = static_cast<const node::Vector3&>(node);
        std::static_pointer_cast<rg::node::Vector3>(dst)->SetValue(src.val);
    }
    else if (type == rttr::type::get<node::Vector4>())
    {
        auto& src = static_cast<const node::Vector4&>(node);
        std::static_pointer_cast<rg::node::Vector4>(dst)->SetValue(src.val);
    }
    else if (type == rttr::type::get<node::Matrix2>())
    {
        auto& src = static_cast<const node::Matrix2&>(node);
        std::static_pointer_cast<rg::node::Matrix2>(dst)->SetValue(src.val);
    }
    else if (type == rttr::type::get<node::Matrix3>())
    {
        auto& src = static_cast<const node::Matrix3&>(node);
        std::static_pointer_cast<rg::node::Matrix3>(dst)->SetValue(src.val);
    }
    else if (type == rttr::type::get<node::Matrix4>())
    {
        auto& src = static_cast<const node::Matrix4&>(node);
        std::static_pointer_cast<rg::node::Matrix4>(dst)->SetValue(src.val);
    }
    // math
    else if (type == rttr::type::get<node::PerspectiveMat>())
    {
        auto& src = static_cast<const node::PerspectiveMat&>(node);
        auto pm = std::static_pointer_cast<rg::node::PerspectiveMat>(dst);
        pm->fovy   = src.fovy;
        pm->aspect = src.aspect;
        pm->znear  = src.znear;
        pm->zfar   = src.zfar;
    }
    else if (type == rttr::type::get<node::OrthoMat>())
    {
        auto& src = static_cast<const node::OrthoMat&>(node);
        auto om = std::static_pointer_cast<rg::node::OrthoMat>(dst);
        om->left   = src.left;
        om->right  = src.right;
        om->bottom = src.bottom;
        om->top    = src.top;
        om->znear  = src.znear;
        om->zfar   = src.zfar;
    }
    else if (type == rttr::type::get<node::LookAtMat>())
    {
        auto& src = static_cast<const node::LookAtMat&>(node);
        auto lm = std::static_pointer_cast<rg::node::LookAtMat>(dst);
        lm->eye    = src.eye;
        lm->center = src.center;
        lm->up     = src.up;
    }
    // state
    else if (type == rttr::type::get<node::Cull>())
    {
        auto& src = static_cast<const node::Cull&>(node);
        auto cull = std::static_pointer_cast<rg::node::Cull>(dst);
        switch (src.type)
        {
        case CullType::Off:
            cull->SetCullType(rg::node::Cull::CullType::Off);
            break;
        case CullType::Back:
            cull->SetCullType(rg::node::Cull::CullType::Back);
            break;
        case CullType::Front:
            cull->SetCullType(rg::node::Cull::CullType::Front);
            break;
        }
    }

    // connect
    for (int i = 0, n = node.GetAllInput().size(); i < n; ++i)
    {
        auto& imports = dst->GetImports();
        if (node.IsExtensibleInputPorts() && i >= static_cast<int>(imports.size())) {
            continue;
        }
        rg::Node::PortAddr from_port;
        if (!CreateFromNode(node, i, from_port) ||
            from_port.node.expired()) {
            continue;
        }
        rg::make_connecting(from_port, { dst, i });
    }

    m_cached_nodes.push_back(dst);

    return dst;
}

bool RenderGraph::CreateFromNode(const bp::Node& node, int input_idx, rg::Node::PortAddr& from_port)
{
    auto& to_port = node.GetAllInput()[input_idx];
    auto& conns = to_port->GetConnecting();
    if (conns.empty()) {
        return false;
    }
    assert(conns.size() == 1);
    auto& bp_from_port = conns[0]->GetFrom();
    assert(bp_from_port);

    from_port.node = CreateGraphNode(bp_from_port->GetParent());
    from_port.idx  = bp_from_port->GetPosIdx();
    return true;
}

}