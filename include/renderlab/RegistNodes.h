#pragma once

#include "renderlab/Node.h"
#include "renderlab/ReflectPropTypes.h"

#include <blueprint/Pin.h>

#include <painting0/Color.h>

namespace rlab
{

void nodes_regist_rttr();

namespace node
{

#define GRP_DEFINE_NODE(name, preview, prop) \
class name : public Node                     \
{                                            \
public:                                      \
	name()                                   \
		: Node(#name, preview)               \
	{                                        \
		InitPins(#name);                     \
	}                                        \
                                             \
	prop                                     \
	RTTR_ENABLE(Node)                        \
};

#define GRP_NODE_PROP

GRP_DEFINE_NODE(Clear, true, \
    ClearType  type;         \
    pt0::Color color;        \
)
GRP_DEFINE_NODE(Viewport, true, \
    int x = 0;                  \
    int y = 0;                  \
    int w = 0;                  \
    int h = 0;                  \
)
GRP_DEFINE_NODE(Texture, true,                                                                 \
    virtual void PreviewDraw(const rg::NodePtr& node, const sm::Matrix2D& mat) const override; \
    std::string filepath;                                                                      \
    rlab::TextureType type = rlab::TextureType::Tex2D;                                           \
    int width = 0;                                                                             \
    int height = 0;                                                                            \
    rlab::TextureFormat format = rlab::TextureFormat::RGBA8;                                     \
)
GRP_DEFINE_NODE(RenderTarget, true, GRP_NODE_PROP)
GRP_DEFINE_NODE(Shader, false, \
    std::string vert;          \
    std::string frag;          \
)
GRP_DEFINE_NODE(Bind, false, \
    int channel = 0;         \
)
GRP_DEFINE_NODE(Unbind, false, GRP_NODE_PROP)
GRP_DEFINE_NODE(DrawCube, false, GRP_NODE_PROP)

class OutputToScreen : public Node
{
public:
    OutputToScreen()
        : Node("OutputToScreen", false)
    {
        InitPins({
			{ bp::PIN_ANY_VAR, "prev" }
		},{
		});
    }

    RTTR_ENABLE(Node)

}; // OutputToScreen

}

}