#pragma once

#include "public.h"
#include "ephemeral_node_factory.h"

#include <yt/yt/core/yson/consumer.h>


namespace NYT::NYson {

////////////////////////////////////////////////////////////////////////////////

template <class T>
TYsonString ConvertToYsonString(const T& value);

template <class T>
TYsonString ConvertToYsonString(const T& value, EYsonFormat format);

template <class T>
TYsonString ConvertToYsonString(const T& value, EYsonFormat format, int indent);

template <class T>
TYsonString ConvertToYsonStringNestingLimited(const T& value, int nestingLevelLimit);

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NYSon

namespace NYT::NYTree {

////////////////////////////////////////////////////////////////////////////////

template <class T>
NYson::TYsonProducer ConvertToProducer(T&& value);

template <class T>
INodePtr ConvertToNode(
    const T& value,
    INodeFactory* factory = GetEphemeralNodeFactory());

template <class T>
IAttributeDictionaryPtr ConvertToAttributes(const T& value);

template <class TTo>
TTo ConvertTo(const INodePtr& node);

template <class TTo, class TFrom>
TTo ConvertTo(const TFrom& value);

template <class T>
T ConstructYTreeConvertableObject();

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NYTree

#define CONVERT_INL_H_
#include "convert-inl.h"
#undef CONVERT_INL_H_
