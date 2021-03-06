/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_openhome_net_core_PropertyString */

#ifndef _Included_org_openhome_net_core_PropertyString
#define _Included_org_openhome_net_core_PropertyString
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertyCreateStringCp
 * Signature: (Ljava/lang/String;Lorg/openhome/net/controlpoint/IPropertyChangeListener;)Lorg/openhome/net/core/Property/PropertyInitialised;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertyCreateStringCp
  (JNIEnv *, jobject, jstring, jobject);

/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertyCreateStringDv
 * Signature: (J)J
 */
JNIEXPORT jlong JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertyCreateStringDv
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertyValueString
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertyValueString
  (JNIEnv *, jclass, jlong);

/*
 * Class:     org_openhome_net_core_PropertyString
 * Method:    ServicePropertySetValueString
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_core_PropertyString_ServicePropertySetValueString
  (JNIEnv *, jclass, jlong, jstring);

#ifdef __cplusplus
}
#endif
#endif
