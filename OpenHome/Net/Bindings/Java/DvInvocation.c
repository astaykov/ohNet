#include <jni.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "DvInvocation.h"
#include "OpenHome/Net/C/DvProvider.h"

#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationGetVersion
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationGetVersion
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	uint32_t version;
	aEnv = aEnv;
	aClass = aClass;

	DvInvocationGetVersion(invocation, &version);
	return (jint) version;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationGetAdapter
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationGetAdapter
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	TIpAddress adapter;
	aEnv = aEnv;
	aClass = aClass;
	
	DvInvocationGetAdapter(invocation, &adapter);
	return (jint) adapter;
}


/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationGetResourceUriPrefix
 * Signature: (J)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationGetResourceUriPrefix
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* uriPrefix;
    uint32_t len;
	aClass = aClass;
	
	DvInvocationGetResourceUriPrefix(invocation, &uriPrefix, &len);
	return (*aEnv)->NewStringUTF(aEnv, uriPrefix);
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationReadStart
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationReadStart
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	aEnv = aEnv;
	aClass = aClass;
	
	return (jint) DvInvocationReadStart(invocation);
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationReadInt
 * Signature: (JLjava/lang/String;)Lorg/openhome/net/device/DvInvocation/InvocationStatusInt;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationReadInt
  (JNIEnv *aEnv, jclass aObject, jlong aInvocation, jstring aName)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	int32_t value;
	int result;
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	aEnv = aEnv;

	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvInvocation$InvocationStatusInt");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvInvocation$InvocationStatusInt\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvInvocation;II)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvInvocation$InvocationStatusInt\n");
        return NULL;
	}
	result = DvInvocationReadInt(invocation, name, &value);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, value, result);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationReadUint
 * Signature: (JLjava/lang/String;)Lorg/openhome/net/device/DvInvocation/InvocationStatusUint;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationReadUint
  (JNIEnv *aEnv, jclass aObject, jlong aInvocation, jstring aName)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	uint32_t value;
	int result;
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	aEnv = aEnv;

	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvInvocation$InvocationStatusUint");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvInvocation$InvocationStatusUint\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvInvocation;JI)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvInvocation$InvocationStatusUint\n");
        return NULL;
	}
	result = DvInvocationReadUint(invocation, name, &value);
	// Need to cast value to a jlong as Java constructor expects a long,
	// otherwise it will corrupt the value of "result".
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, (jlong)value, result);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationReadBool
 * Signature: (JLjava/lang/String;)Lorg/openhome/net/device/DvInvocation/InvocationStatusBool;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationReadBool
  (JNIEnv *aEnv, jclass aObject, jlong aInvocation, jstring aName)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	uint32_t value;
	int result;
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	aEnv = aEnv;

	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvInvocation$InvocationStatusBool");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvInvocation$InvocationStatusBool\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvInvocation;II)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvInvocation$InvocationStatusBool\n");
        return NULL;
	}
	result = DvInvocationReadBool(invocation, name, &value);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, value, result);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationReadString
 * Signature: (JLjava/lang/String;)Lorg/openhome/net/device/DvInvocation/InvocationStatusString;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationReadString
  (JNIEnv *aEnv, jclass aObject, jlong aInvocation, jstring aName)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	char* value;
	jobject valueJava;
	int result;
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	aEnv = aEnv;

	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvInvocation$InvocationStatusString");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvInvocation$InvocationStatusString\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvInvocation;Ljava/lang/String;I)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvInvocation$InvocationStatusString\n");
        return NULL;
	}
	result = DvInvocationReadString(invocation, name, &value);
	valueJava = (*aEnv)->NewStringUTF(aEnv, value);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, valueJava, result);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationReadBinary
 * Signature: (JLjava/lang/String;)Lorg/openhome/net/device/DvInvocation/InvocationStatusBinary;
 */
JNIEXPORT jobject JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationReadBinary
  (JNIEnv *aEnv, jclass aObject, jlong aInvocation, jstring aName)
{
	jclass statusClass;
	jmethodID cid;
	jobject status;
	uint8_t* value;
	uint32_t len;
	jbyteArray valueJava;
	int result;
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	aEnv = aEnv;
	
	statusClass = (*aEnv)->FindClass(aEnv, "org/openhome/net/device/DvInvocation$InvocationStatusBinary");
	if (statusClass == NULL)
	{
		printf("Unable to find class org/openhome/net/device/DvInvocation$InvocationStatusBinary\n");
		return NULL;
	}
	cid = (*aEnv)->GetMethodID(aEnv, statusClass, "<init>", "(Lorg/openhome/net/device/DvInvocation;[BI)V");
	if (cid == NULL) {
		printf("Unable to find constructor for class org/openhome/net/device/DvInvocation$InvocationStatusBinary\n");
        return NULL;
	}
	result = DvInvocationReadBinary(invocation, name, &value, &len);
	valueJava = (*aEnv)->NewByteArray(aEnv, len);
	(*aEnv)->SetByteArrayRegion(aEnv, valueJava, 0, len, (jbyte *) value);
	status = (*aEnv)->NewObject(aEnv, statusClass, cid, aObject, valueJava, result);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	(*aEnv)->DeleteLocalRef(aEnv, statusClass);
	
	return status;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationReadEnd
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationReadEnd
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	aEnv = aEnv;
	aClass = aClass;
	
	return DvInvocationReadEnd(invocation);
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationReportError
 * Signature: (JJLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationReportError
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jlong aCode, jstring aDescription)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	uint32_t code = (uint32_t) aCode;
	const char* description = (*aEnv)->GetStringUTFChars(aEnv, aDescription, NULL);
	int32_t result;
	aClass = aClass;
	
	result = DvInvocationReportError(invocation, code, description);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aDescription, description);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteStart
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteStart
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	aEnv = aEnv;
	aClass = aClass;
	
	return DvInvocationWriteStart(invocation);
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteInt
 * Signature: (JLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteInt
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jstring aName, jint aValue)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	int32_t result;
	aClass = aClass;

	result = DvInvocationWriteInt(invocation, name, aValue);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteUint
 * Signature: (JLjava/lang/String;J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteUint
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jstring aName, jlong aValue)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	uint32_t value = (uint32_t) aValue;
	int32_t result;
	aClass = aClass;
	
	result = DvInvocationWriteUint(invocation, name, value);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteBool
 * Signature: (JLjava/lang/String;I)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteBool
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jstring aName, jint aValue)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	int32_t result;
	aClass = aClass;
	
	result = DvInvocationWriteBool(invocation, name, aValue);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteStringStart
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteStringStart
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jstring aName)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	int32_t result;
	aClass = aClass;
	
	result = DvInvocationWriteStringStart(invocation, name);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteString
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteString
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jstring aValue)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* value = (*aEnv)->GetStringUTFChars(aEnv, aValue, NULL);
	int32_t result;
	aClass = aClass;
	
	result = DvInvocationWriteString(invocation, value);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aValue, value);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteStringEnd
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteStringEnd
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jstring aName)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	int32_t result;
	aClass = aClass;
	
	result = DvInvocationWriteStringEnd(invocation, name);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteBinaryStart
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteBinaryStart
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jstring aName)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	int32_t result;
	aClass = aClass;
	
	result = DvInvocationWriteBinaryStart(invocation, name);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteBinary
 * Signature: (J[BI)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteBinary
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jbyteArray aData, jint aLen)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	uint8_t *data = (uint8_t*)malloc(sizeof(uint8_t)*aLen);
	int32_t result;
	aClass = aClass;
	
	(*aEnv)->GetByteArrayRegion(aEnv, aData, 0, aLen, (jbyte *)data);
	result = DvInvocationWriteBinary(invocation, data, aLen);
	
	free(data); // Do we want to do this or does the stack use this reference?
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteBinaryEnd
 * Signature: (JLjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteBinaryEnd
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation, jstring aName)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	const char* name = (*aEnv)->GetStringUTFChars(aEnv, aName, NULL);
	int32_t result;
	aClass = aClass;
	
	result = DvInvocationWriteBinaryEnd(invocation, name);
	(*aEnv)->ReleaseStringUTFChars(aEnv, aName, name);
	
	return result;
}

/*
 * Class:     org_openhome_net_device_DvInvocation
 * Method:    DvInvocationWriteEnd
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_org_openhome_net_device_DvInvocation_DvInvocationWriteEnd
  (JNIEnv *aEnv, jclass aClass, jlong aInvocation)
{
	DvInvocationC invocation = (DvInvocationC) (size_t)aInvocation;
	aEnv = aEnv;
	aClass = aClass;
	
	return DvInvocationWriteEnd(invocation);
}

#ifdef __cplusplus
}
#endif
