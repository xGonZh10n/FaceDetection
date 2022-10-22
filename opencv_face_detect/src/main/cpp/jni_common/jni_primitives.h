#ifndef JNI_PRIMITIVES_H
#define JNI_PRIMITIVES_H

// Modified by Lightweh on Nov 21, 2018

#include <jni.h>

#define CLASSNAME_VISION_DET_RET "com/lightweh/dlib/VisionDetRet"
#define CONSTSIG_VISION_DET_RET "()V"

#define CLASSNAME_FACE_DET "com/lightweh/dlib/FaceDet"

class JNI_VisionDetRet {
public:
    JNI_VisionDetRet(JNIEnv *env) {
        jclass detRetClass = env->FindClass(CLASSNAME_VISION_DET_RET);
        jID_left = env->GetFieldID(detRetClass, "mLeft", "I");
        jID_top = env->GetFieldID(detRetClass, "mTop", "I");
        jID_right = env->GetFieldID(detRetClass, "mRight", "I");
        jID_bottom = env->GetFieldID(detRetClass, "mBottom", "I");
    }

    void setRect(JNIEnv *env, jobject &jDetRet, const int &left, const int &top,
                 const int &right, const int &bottom) {
        env->SetIntField(jDetRet, jID_left, left);
        env->SetIntField(jDetRet, jID_top, top);
        env->SetIntField(jDetRet, jID_right, right);
        env->SetIntField(jDetRet, jID_bottom, bottom);
    }

    static jobject createJObject(JNIEnv *env) {
        jclass detRetClass = env->FindClass(CLASSNAME_VISION_DET_RET);
        jmethodID mid =
                env->GetMethodID(detRetClass, "<init>", CONSTSIG_VISION_DET_RET);
        return env->NewObject(detRetClass, mid);
    }

    static jobjectArray createJObjectArray(JNIEnv *env, const int &size) {
        jclass detRetClass = env->FindClass(CLASSNAME_VISION_DET_RET);
        return (jobjectArray) env->NewObjectArray(size, detRetClass, NULL);
    }

private:
    jfieldID jID_left;
    jfieldID jID_top;
    jfieldID jID_right;
    jfieldID jID_bottom;
};

#endif  // JNI_PRIMITIVES_H
