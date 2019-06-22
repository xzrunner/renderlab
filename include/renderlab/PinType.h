#pragma once

namespace rlab
{

enum PinType
{
    PIN_TEXTURE = 1000,
    PIN_RENDERTARGET,
    PIN_MODEL,

    PIN_BOOL,
    PIN_VECTOR1,
    PIN_VECTOR2,
    PIN_VECTOR3,
    PIN_VECTOR4,
    PIN_MATRIX2,
    PIN_MATRIX3,
    PIN_MATRIX4,
    PIN_SAMPLER2D,
    PIN_SAMPLE_CUBE,

    PIN_VECTOR3_ARRAY,
    PIN_VECTOR4_ARRAY,
};

}