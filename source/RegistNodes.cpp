#include "renderlab/RegistNodes.h"
#include "renderlab/node/PassEnd.h"
#include "renderlab/node/Shader.h"
#include "renderlab/node/CustomFunction.h"
#include "renderlab/node/OutputToScreen.h"
#include "renderlab/node/Preview.h"
#include "renderlab/node/SubGraph.h"

#include <ee0/ReflectPropTypes.h>

#include <rendergraph/VariableType.h>
#include <js/RTTR.h>

#define REGIST_NODE_RTTI(type, name, prop)                                \
	rttr::registration::class_<renderlab::node::type>("renderlab::"#name) \
		.constructor<>()                                                  \
		prop                                                              \
	;

#define PROP
#define REGIST_NODE_RTTI_DEFAULT(type, name) REGIST_NODE_RTTI(type, name, PROP)

RTTR_REGISTRATION
{

// base

rttr::registration::class_<renderlab::Node>("renderlab::node")
.property("name", &renderlab::Node::GetName, &renderlab::Node::SetName)
(
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Name"))
)
;

#define EXE_FILEPATH "renderlab/node_rttr_gen.h"
#define SKIP_FILE_NODE
#include "renderlab/node_regist_cfg.h"
#undef SKIP_FILE_NODE
#undef EXE_FILEPATH

// resource
REGIST_NODE_RTTI(VertexArray, vertex_array,                               \
.property("vertices_data", &renderlab::node::VertexArray::vertices_data)  \
(                                                                         \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("VerticesData")) \
)                                                                         \
.property("indices_data", &renderlab::node::VertexArray::indices_data)    \
(                                                                         \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("IndicesData"))  \
)                                                                         \
.property("position", &renderlab::node::VertexArray::position)            \
(                                                                         \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Position"))     \
)                                                                         \
.property("normal", &renderlab::node::VertexArray::normal)                \
(                                                                         \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Normal"))       \
)                                                                         \
.property("texture", &renderlab::node::VertexArray::texture)              \
(                                                                         \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Texture"))      \
)                                                                         \
)
REGIST_NODE_RTTI(Model, model,                                         \
.property("filepath", &renderlab::node::Model::filepath)               \
(                                                                      \
    rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Filepath")), \
    rttr::metadata(js::RTTR::FilePathTag(), true),                     \
    rttr::metadata(ee0::PropOpenFileTag(), ee0::PropOpenFile("*.*"))   \
)                                                                      \
)

// renderlab
REGIST_NODE_RTTI_DEFAULT(Preview, preview)
REGIST_NODE_RTTI(Shader, shader,                                                                     \
.property("vert", &renderlab::node::Shader::GetVert, &renderlab::node::Shader::SetVert)              \
(                                                                                                    \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Vert")),                                   \
    rttr::metadata(ee0::PropEditCodeTag(), true)                                                     \
)                                                                                                    \
.property("tess_ctrl", &renderlab::node::Shader::GetTessCtrl, &renderlab::node::Shader::SetTessCtrl) \
(                                                                                                    \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("TessCtrl")),                               \
    rttr::metadata(ee0::PropEditCodeTag(), true)                                                     \
)                                                                                                    \
.property("tess_eval", &renderlab::node::Shader::GetTessEval, &renderlab::node::Shader::SetTessEval) \
(                                                                                                    \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("TessEval")),                               \
    rttr::metadata(ee0::PropEditCodeTag(), true)                                                     \
)                                                                                                    \
.property("frag", &renderlab::node::Shader::GetFrag, &renderlab::node::Shader::SetFrag)              \
(                                                                                                    \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Frag")),                                   \
    rttr::metadata(ee0::PropEditCodeTag(), true)                                                     \
)                                                                                                    \
.property("compute", &renderlab::node::Shader::GetCompute, &renderlab::node::Shader::SetCompute)     \
(                                                                                                    \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Compute")),                                \
    rttr::metadata(ee0::PropEditCodeTag(), true)                                                     \
)                                                                                                    \
.property("lang", &renderlab::node::Shader::GetLanguage, &renderlab::node::Shader::SetLanguage)      \
(                                                                                                    \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Lang"))                                    \
)                                                                                                    \
)

// value
REGIST_NODE_RTTI(String, string,                                                        \
.property("val", &renderlab::node::String::val)                                         \
(                                                                                       \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Value")),                     \
    rttr::metadata(ee0::PropEditCodeTag(), true)                                        \
)                                                                                       \
.property("type", &renderlab::node::String::type)                                       \
(                                                                                       \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Type"))                       \
)                                                                                       \
)

// control
REGIST_NODE_RTTI_DEFAULT(OutputToScreen, output_to_screen)
REGIST_NODE_RTTI(PassEnd, pass_end,                                                             \
.property("pass_end", &renderlab::node::PassEnd::GetOrder, &renderlab::node::PassEnd::SetOrder) \
(                                                                                               \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Order"))                              \
)
)

// utility
REGIST_NODE_RTTI(CustomFunction, custom_function,                                                       \
.property("code", &renderlab::node::CustomFunction::GetCode, &renderlab::node::CustomFunction::SetCode) \
(                                                                                                       \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Code")),                                      \
    rttr::metadata(ee0::PropLongStringTag(), true)                                                      \
)
)

REGIST_NODE_RTTI(SubGraph, sub_graph,                                                                   \
.property("filepath", &renderlab::node::SubGraph::GetFilepath, &renderlab::node::SubGraph::SetFilepath) \
(                                                                                                       \
    rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Filepath")),                                  \
    rttr::metadata(js::RTTR::FilePathTag(), true),                                                      \
    rttr::metadata(ee0::PropOpenFileTag(), ee0::PropOpenFile("*.json"))                                 \
)
)

// pipeline
REGIST_NODE_RTTI(SeparableSSS, separable_sss,                         \
.property("nsamples", &renderlab::node::SeparableSSS::nsamples)       \
(                                                                     \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("nSamples")) \
)                                                                     \
.property("strength", &renderlab::node::SeparableSSS::strength)       \
(                                                                     \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Strength")) \
)                                                                     \
.property("falloff", &renderlab::node::SeparableSSS::falloff)         \
(                                                                     \
	rttr::metadata(ee0::UIMetaInfoTag(), ee0::UIMetaInfo("Falloff"))  \
)                                                                     \
)
REGIST_NODE_RTTI_DEFAULT(GlobalIllumination, gi)

}

namespace renderlab
{

void nodes_regist_rttr()
{
}

}