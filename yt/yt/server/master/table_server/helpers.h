#pragma once

#include <yt/yt/server/master/cell_master/bootstrap.h>

#include <yt/yt/server/master/table_server/table_node.h>

namespace NYT::NTableServer {

////////////////////////////////////////////////////////////////////////////////

//! Return the stage stored in the table node if it is set and the per-cluster default if it is null.
TString GetEffectiveQueueAgentStage(
    NCellMaster::TBootstrap* bootstrap,
    const NTableServer::TTableNode* table);

//! For use with EInternedAttributeKey::[Queue/Consumer][Status/Partitions].
TFuture<NYson::TYsonString> GetQueueAgentAttributeAsync(
    NCellMaster::TBootstrap* bootstrap,
    const NTableServer::TTableNode* table,
    const NYPath::TYPath& path,
    NYTree::TInternedAttributeKey key);

////////////////////////////////////////////////////////////////////////////////

} // namespace NYT::NTableServer
