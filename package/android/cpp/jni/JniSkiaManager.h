#pragma once

#include <ReactCommon/CallInvokerHolder.h>
#include <fbjni/fbjni.h>
#include <jsi/jsi.h>
#include <map>
#include <memory>
#include <string>

#include "JniPlatformContext.h"
#include "JniSkiaDrawView.h"
#include "RNSkManager.h"

namespace RNSkia {

using namespace facebook;

using TSelf =
    jni::local_ref<jni::HybridClass<RNSkia::JniSkiaManager>::jhybriddata>;

using JSCallInvokerHolder =
    jni::alias_ref<facebook::react::CallInvokerHolder::javaobject>;

using JavaPlatformContext = jni::alias_ref<JniPlatformContext::javaobject>;

class JniSkiaManager : public jni::HybridClass<JniSkiaManager> {
   public:
    static auto constexpr kJavaDescriptor = "Lcom/shopify/reactnative/skia/SkiaManager;";
    static auto constexpr TAG = "ReactNativeSkia";

    static TSelf initHybrid(
        jni::alias_ref<jhybridobject> jThis,
        jlong jsContext,
        JSCallInvokerHolder jsCallInvokerHolder,
        JavaPlatformContext platformContext);

    static void registerNatives();

    JniSkiaManager() {}

    explicit JniSkiaManager(
        jni::alias_ref<JniSkiaManager::jhybridobject> jThis,
        jsi::Runtime *runtime,
        std::shared_ptr<facebook::react::CallInvoker> jsCallInvoker,
        std::shared_ptr<JniPlatformContext> platformContext)
        : _javaPart(jni::make_global(jThis)),
          _jsRuntime(runtime),
          _jsCallInvoker(jsCallInvoker),
          _context(platformContext) {}

    void registerSkiaView(int viewTag, JniSkiaDrawView *skiaView);
    void unregisterSkiaView(int viewTag);

   private:
    friend HybridBase;

    std::shared_ptr<RNSkManager> _rnSkManager;

    jni::global_ref<JniSkiaManager::javaobject> _javaPart;

    jsi::Runtime *_jsRuntime;
    std::shared_ptr<facebook::react::CallInvoker> _jsCallInvoker;
    std::shared_ptr<JniPlatformContext> _context;

    void initializeRuntime();
    void installJSIBindings();
};

} // namespace RNSkia