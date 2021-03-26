//
// Copyright 2020 Eugene Gershnik
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://github.com/gershnik/android-cmdline-jni/blob/main/LICENSE
//

#include <iostream>


#if defined(__ANDROID__)

#include <dlfcn.h>
#include <jni.h>

extern "C"
{
    typedef int JNI_CreateJavaVM_t(void *, void *, void *);

    __attribute__((visibility("default"))) void AddSpecialSignalHandlerFn() 
    { }
}

static auto load_art() -> std::pair<JavaVM *, JNIEnv *>
{
    JavaVMOption opt[] = {
        { "-Djava.library.path=/data/local/tmp", nullptr },
        { "-verbose:jni", nullptr }
    };

    JavaVMInitArgs args = {
        JNI_VERSION_1_6,
        std::size(opt),
        opt,
        JNI_FALSE
    };

    void * libart = dlopen("libart.so", RTLD_NOW);
    if (!libart) 
    {
        std::cerr << dlerror() << std::endl;
        abort();
    }

    auto JNI_CreateJavaVM = (JNI_CreateJavaVM_t *)dlsym(libart, "JNI_CreateJavaVM");
    if (!JNI_CreateJavaVM)
    {
        std::cerr << "No JNI_CreateJavaVM: " << dlerror() << std::endl;
        abort();
    }

    std::pair<JavaVM *, JNIEnv *> ret;
    int res = JNI_CreateJavaVM(&ret.first, &ret.second, &args);
    if (res != 0)
    {
        std::cerr << "Failed to create VM: " << res << std::endl;
        abort();
    }
    return ret;
}

#endif

int main() {
    #if defined(__ANDROID__)

        auto [vm, env] = load_art();
        
        jclass systemCls = env->FindClass("java/lang/System");
        jfieldID outField = env->GetStaticFieldID(systemCls, "out", "Ljava/io/PrintStream;");

        jclass printStreamCls = env->FindClass("java/io/PrintStream");
        jmethodID printMethod = env->GetMethodID(printStreamCls, "print", "(Ljava/lang/String;)V");
        
        
        jobject outObj = env->GetStaticObjectField(systemCls, outField);
        const char16_t text[] = u"Hello, World from Java!\n";
        jstring jtext = env->NewString((const jchar *)text, std::size(text) - 1);
        env->CallVoidMethod(outObj, printMethod, jtext);

    #else
        std::cout << "Hello, World!\n";
    #endif
}
