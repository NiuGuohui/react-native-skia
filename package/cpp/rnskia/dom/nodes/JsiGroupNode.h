
#pragma once

#include "JsiDomRenderNode.h"

namespace RNSkia {

static const char *GroupNodeName = "skGroup";

class JsiGroupNode : public JsiDomRenderNode {
public:
  JsiGroupNode(std::shared_ptr<RNSkPlatformContext> context,
               jsi::Runtime &runtime,
               const jsi::Value *arguments,
               size_t count) :
  JsiDomRenderNode(context, runtime, arguments, count) {}
  
  static const jsi::HostFunctionType
  createCtor(std::shared_ptr<RNSkPlatformContext> context) {
    return JSI_HOST_FUNCTION_LAMBDA {
      auto node = std::make_shared<JsiGroupNode>(context, runtime, arguments, count);
      return jsi::Object::createFromHostObject(runtime, std::move(node));
    };
  }
  
protected:
  void renderNode(std::shared_ptr<JsiBaseDrawingContext> context) override {
    for (auto &child: getChildren()) {
      auto node = std::static_pointer_cast<JsiDomRenderNode>(child);
      if (node != nullptr) {
        node->render(context);
      }
    }
  }
  
  // FIXME: Add to enum and sync with JS somehow?
  const char *getType() override { return GroupNodeName; }
  
private:
  SkRect _rect;
};

}
