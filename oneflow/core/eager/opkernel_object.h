#ifndef ONEFLOW_CORE_EAGER_OPKERNEL_OBJECT_H_
#define ONEFLOW_CORE_EAGER_OPKERNEL_OBJECT_H_

#include "oneflow/core/vm/object.h"
#include "oneflow/core/operator/operator.h"
#include "oneflow/core/kernel/kernel.h"

namespace oneflow {
namespace eager {

class OpKernelObject : public vm::Object {
 public:
  OpKernelObject(const OpKernelObject&) = delete;
  OpKernelObject(OpKernelObject&&) = delete;
  OpKernelObject(const std::shared_ptr<const JobDesc>& job_desc, const OperatorConf& op_conf)
      : job_desc_(job_desc),
        op_(ConstructOp(op_conf, job_desc.get())),
        kernel_(nullptr),
        is_kernel_initiated_(false) {}
  ~OpKernelObject() override = default;

  const Operator& op() const { return *op_; }
  const Kernel& kernel(DeviceCtx* device_ctx);

  void InferAndNewUninitiatedKernel(
      const std::function<BlobDesc*(const std::string&)>& BlobDesc4BnInOp);

 private:
  void InferBlobDescs(const std::function<BlobDesc*(const std::string&)>& BlobDesc4BnInOp,
                      const ParallelContext* parallel_ctx);
  void NewUninitiatedKernel(const std::function<BlobDesc*(const std::string&)>& BlobDesc4BnInOp,
                            const ParallelContext* parallel_ctx);

  std::shared_ptr<const JobDesc> job_desc_;
  std::shared_ptr<Operator> op_;
  std::unique_ptr<OpContext> op_ctx_;
  KernelConf kernel_conf_;
  std::unique_ptr<Kernel> kernel_;
  bool is_kernel_initiated_;
};

}  // namespace eager
}  // namespace oneflow

#endif  // ONEFLOW_CORE_EAGER_OPKERNEL_OBJECT_H_