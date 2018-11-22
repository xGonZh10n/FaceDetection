/*
 *  Created on: Oct 20, 2015
 *      Author: Tzutalin
 *
 *  Copyright (c) 2015 Tzutalin. All rights reserved.
 */
// Modified by Gaurav on Feb 23, 2018
// Modified by Lightweh on Nov 21, 2018

#include <jni.h>
#include <android/bitmap.h>
#include <jni_common/jni_bitmap2mat.h>
#include <jni_common/jni_primitives.h>
#include <face_detector.h>

using namespace cv;

JNI_VisionDetRet *g_pJNI_VisionDetRet;

JavaVM *g_javaVM = NULL;

JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    g_javaVM = vm;
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    g_pJNI_VisionDetRet = new JNI_VisionDetRet(env);

    return JNI_VERSION_1_6;
}

void JNI_OnUnload(JavaVM *vm, void *reserved) {

    g_javaVM = NULL;

    delete g_pJNI_VisionDetRet;
}


namespace {

#define JAVA_NULL 0
    using DetPtr = FaceDetector *;

    class JNI_FaceDet {
    public:
        JNI_FaceDet(JNIEnv *env) {
            jclass clazz = env->FindClass(CLASSNAME_FACE_DET);
            mNativeContext = env->GetFieldID(clazz, "mNativeFaceDetContext", "J");
            env->DeleteLocalRef(clazz);
        }

        DetPtr getDetectorPtrFromJava(JNIEnv *env, jobject thiz) {
            DetPtr const p = (DetPtr) env->GetLongField(thiz, mNativeContext);
            return p;
        }

        void setDetectorPtrToJava(JNIEnv *env, jobject thiz, jlong ptr) {
            env->SetLongField(thiz, mNativeContext, ptr);
        }

        jfieldID mNativeContext;
    };

    // Protect getting/setting and creating/deleting pointer between java/native
    std::mutex gLock;

    std::shared_ptr<JNI_FaceDet> getJNI_FaceDet(JNIEnv *env) {
        static std::once_flag sOnceInitflag;
        static std::shared_ptr<JNI_FaceDet> sJNI_FaceDet;
        std::call_once(sOnceInitflag, [env]() {
            sJNI_FaceDet = std::make_shared<JNI_FaceDet>(env);
        });
        return sJNI_FaceDet;
    }

    DetPtr const getDetPtr(JNIEnv *env, jobject thiz) {
        std::lock_guard<std::mutex> lock(gLock);
        return getJNI_FaceDet(env)->getDetectorPtrFromJava(env, thiz);
    }

    // The function to set a pointer to java and delete it if newPtr is empty
    void setDetPtr(JNIEnv *env, jobject thiz, DetPtr newPtr) {
        std::lock_guard<std::mutex> lock(gLock);
        DetPtr oldPtr = getJNI_FaceDet(env)->getDetectorPtrFromJava(env, thiz);
        if (oldPtr != JAVA_NULL) {
            delete oldPtr;
        }

        getJNI_FaceDet(env)->setDetectorPtrToJava(env, thiz, (jlong) newPtr);
    }

}  // end unnamespace

#ifdef __cplusplus
extern "C" {
#endif

#define DLIB_FACE_JNI_METHOD(METHOD_NAME) Java_com_lightweh_dlib_FaceDet_##METHOD_NAME

void JNIEXPORT
DLIB_FACE_JNI_METHOD(jniNativeClassInit)(JNIEnv *env, jclass _this) {}


jobjectArray getRecResult(JNIEnv *env, DetPtr faceDetector, const int &size) {
    jobjectArray jDetRetArray = JNI_VisionDetRet::createJObjectArray(env, size);
    for (int i = 0; i < size; i++) {
        jobject jDetRet = JNI_VisionDetRet::createJObject(env);
        env->SetObjectArrayElement(jDetRetArray, i, jDetRet);
        dlib::rectangle rect = faceDetector->getDetResultRects()[i];

        g_pJNI_VisionDetRet->setRect(env, jDetRet, rect.left(), rect.top(),
                                     rect.right(), rect.bottom());
    }
    return jDetRetArray;
}

JNIEXPORT jobjectArray JNICALL
DLIB_FACE_JNI_METHOD(jniBitmapDet)(JNIEnv *env, jobject thiz, jobject bitmap) {
    cv::Mat rgbaMat;
    cv::Mat bgrMat;
    jniutils::ConvertBitmapToRGBAMat(env, bitmap, rgbaMat, true);
    cv::cvtColor(rgbaMat, bgrMat, cv::COLOR_RGBA2BGR);
    DetPtr mDetPtr = getDetPtr(env, thiz);
    jint size = mDetPtr->Detect(bgrMat);
    return getRecResult(env, mDetPtr, size);
}

jint JNIEXPORT JNICALL
DLIB_FACE_JNI_METHOD(jniInit)(JNIEnv *env, jobject thiz) {
    DetPtr mDetPtr = new FaceDetector();
    setDetPtr(env, thiz, mDetPtr);
    return JNI_OK;
}


jint JNIEXPORT JNICALL
DLIB_FACE_JNI_METHOD(jniDeInit)(JNIEnv *env, jobject thiz) {
    setDetPtr(env, thiz, JAVA_NULL);
    return JNI_OK;
}

#ifdef __cplusplus
}
#endif
