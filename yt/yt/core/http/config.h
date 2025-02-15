#pragma once

#include "public.h"

#include <yt/yt/core/net/public.h>

#include <yt/yt/core/ytree/yson_struct.h>

namespace NYT::NHttp {

////////////////////////////////////////////////////////////////////////////////

class THttpIOConfig
    : public NYTree::TYsonStruct
{
public:
    int ReadBufferSize;

    TDuration ConnectionIdleTimeout;

    TDuration HeaderReadTimeout;
    TDuration BodyReadIdleTimeout;

    TDuration WriteIdleTimeout;

    REGISTER_YSON_STRUCT(THttpIOConfig);

    static void Register(TRegistrar registrar);
};

DEFINE_REFCOUNTED_TYPE(THttpIOConfig);

////////////////////////////////////////////////////////////////////////////////

class TServerConfig
    : public THttpIOConfig
{
public:
    //! If zero then the port is chosen automatically.
    int Port;

    //! Limit for number of open TCP connections.
    int MaxSimultaneousConnections;
    int MaxBacklogSize;

    int BindRetryCount;
    TDuration BindRetryBackoff;

    bool EnableKeepAlive;

    bool CancelFiberOnConnectionClose;

    //! Disables Nagle's algorithm.
    bool NoDelay;

    //! This field is not accessible from config.
    bool IsHttps = false;

    //! Used for thread naming.
    //! CamelCase identifiers are preferred.
    //! This field is not accessible from config.
    TString ServerName = "Http";

    REGISTER_YSON_STRUCT(TServerConfig);

    static void Register(TRegistrar registrar);
};

DEFINE_REFCOUNTED_TYPE(TServerConfig);

////////////////////////////////////////////////////////////////////////////////

class TClientConfig
    : public THttpIOConfig
{
public:
    int MaxIdleConnections;
    NNet::TDialerConfigPtr Dialer;

    REGISTER_YSON_STRUCT(TClientConfig);

    static void Register(TRegistrar registrar);
};

DEFINE_REFCOUNTED_TYPE(TClientConfig);

////////////////////////////////////////////////////////////////////////////////

class TCorsConfig
    : public NYTree::TYsonStruct
{
public:
    bool DisableCorsCheck;
    std::vector<TString> HostAllowList;
    std::vector<TString> HostSuffixAllowList;

    REGISTER_YSON_STRUCT(TCorsConfig);

    static void Register(TRegistrar registrar);
};

DEFINE_REFCOUNTED_TYPE(TCorsConfig);

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NHttp
