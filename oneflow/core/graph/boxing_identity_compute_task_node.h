/*
Copyright 2020 The OneFlow Authors. All rights reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#ifndef ONEFLOW_CORE_GRAPH_BOXING_IDENTITY_COMPUTE_TASK_NODE_H_
#define ONEFLOW_CORE_GRAPH_BOXING_IDENTITY_COMPUTE_TASK_NODE_H_

#include "oneflow/core/graph/compute_task_node.h"

namespace oneflow {

class BoxingIdentityCompTaskNode : public CompTaskNode {
 public:
  OF_DISALLOW_COPY_AND_MOVE(BoxingIdentityCompTaskNode);
  BoxingIdentityCompTaskNode() = default;
  ~BoxingIdentityCompTaskNode() override = default;

  void Init(const CompTaskNode* src_node, const LogicalBlobId& lbi);
  TaskType GetTaskType() const override { return TaskType::kBoxingIdentity; }

 private:
  void BuildExecGphAndRegst() override;
  void ProduceAllRegstsAndBindEdges() override;
  void ConsumeAllRegsts() final;
  void InferProducedDataRegstTimeShape() final;

  LogicalBlobId lbi_;
};

}  // namespace oneflow

#endif  // ONEFLOW_CORE_GRAPH_BOXING_IDENTITY_COMPUTE_TASK_NODE_H_
