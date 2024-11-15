
#include <jni.h>
#include "sodium.h"

#ifdef __cplusplus
extern "C"
{
#endif

  /* *****************************************************************************
   * Sodium-specific functions
   * *****************************************************************************
   */
  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_sodium_1init(JNIEnv *jenv, jclass jcls)
  {
    int result;
    result = (int)sodium_init();
    return (jint)result;
  }

  JNIEXPORT jstring JNICALL Java_org_libsodium_jni_SodiumJNI_sodium_1version_1string(JNIEnv *jenv, jclass jcls)
  {
    char *result = (char *)sodium_version_string();
    return (*jenv)->NewStringUTF(jenv, (const char *)result);
  }

  /* *****************************************************************************
   * Random data generation
   * *****************************************************************************
   */

  JNIEXPORT jlong JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1random(JNIEnv *jenv, jclass jcls)
  {
    uint32_t result;
    result = (uint32_t)randombytes_random();
    return (jlong)result;
  }

  JNIEXPORT jlong JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1uniform(JNIEnv *jenv, jclass jcls, jlong j_upper_bound)
  {
    uint32_t result;
    result = (uint32_t)randombytes_uniform((uint32_t)j_upper_bound);
    return (jlong)result;
  }

  JNIEXPORT void JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1buf(JNIEnv *jenv, jclass jcls, jbyteArray j_buf, jint j_size)
  {
    unsigned char *buf = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_buf, 0);
    randombytes_buf(buf, (unsigned long long)j_size);
    (*jenv)->ReleaseByteArrayElements(jenv, j_buf, (jbyte *)buf, 0);
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1close(JNIEnv *jenv, jclass jcls)
  {
    int result = (int)randombytes_close();
    return (jint)result;
  }

  JNIEXPORT void JNICALL Java_org_libsodium_jni_SodiumJNI_randombytes_1stir(JNIEnv *jenv, jclass jcls)
  {
    randombytes_stir();
  }

  /* *****************************************************************************
   * Secret-key cryptography - authenticated encryption
   * *****************************************************************************
   */
  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1keybytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_secretbox_KEYBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1noncebytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_secretbox_NONCEBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1macbytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_secretbox_MACBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1easy(JNIEnv *jenv, jclass jcls, jbyteArray j_c, jbyteArray j_m, jlong j_mlen, jbyteArray j_n, jbyteArray j_k)
  {
    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *n = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_n, 0);
    unsigned char *k = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_k, 0);
    int result = crypto_secretbox_easy(c, m, (unsigned long long)j_mlen, n, k);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *)n, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *)k, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1secretbox_1open_1easy(JNIEnv *jenv, jclass jcls, jbyteArray j_m, jbyteArray j_c, jlong j_clen, jbyteArray j_n, jbyteArray j_k)
  {
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *n = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_n, 0);
    unsigned char *k = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_k, 0);
    int result = crypto_secretbox_open_easy(m, c, (unsigned long long)j_clen, n, k);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *)n, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *)k, 0);
    return (jint)result;
  }

  /* *****************************************************************************
   * Secret-key cryptography - authentication
   * *****************************************************************************
   */
  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1auth_1bytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_auth_BYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1auth_1keybytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_auth_KEYBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1auth(JNIEnv *jenv, jclass jcls, jbyteArray j_out, jbyteArray j_in, jlong j_inlen, jbyteArray j_k)
  {
    unsigned char *out = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_out, 0);
    unsigned char *in = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_in, 0);
    unsigned char *k = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_k, 0);

    int result = crypto_auth(out, in, (unsigned long long)j_inlen, k);

    (*jenv)->ReleaseByteArrayElements(jenv, j_out, (jbyte *)out, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_in, (jbyte *)in, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *)k, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1auth_1verify(JNIEnv *jenv, jclass jcls, jbyteArray j_h, jbyteArray j_in, jlong j_inlen, jbyteArray j_k)
  {
    unsigned char *h = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_h, 0);
    unsigned char *in = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_in, 0);
    unsigned char *k = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_k, 0);

    int result = crypto_auth_verify(h, in, (unsigned long long)j_inlen, k);

    (*jenv)->ReleaseByteArrayElements(jenv, j_h, (jbyte *)h, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_in, (jbyte *)in, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *)k, 0);

    return (jint)result;
  }

  /* *****************************************************************************
   * Public-key cryptography - authenticated encryption
   * *****************************************************************************
   */
  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1publickeybytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_box_PUBLICKEYBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1secretkeybytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_box_SECRETKEYBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1noncebytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_box_NONCEBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1macbytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_box_MACBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1zerobytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_box_ZEROBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1sealbytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_box_SEALBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1keypair(JNIEnv *jenv, jclass jcls, jbyteArray j_pk, jbyteArray j_sk)
  {
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    int result = (int)crypto_box_keypair(pk, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1easy(JNIEnv *jenv, jclass jcls, jbyteArray j_c, jbyteArray j_m, jlong j_mlen, jbyteArray j_n, jbyteArray j_pk, jbyteArray j_sk)
  {
    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *n = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_n, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    int result = crypto_box_easy(c, m, (unsigned long long)j_mlen, n, pk, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *)n, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1open_1easy(JNIEnv *jenv, jclass jcls, jbyteArray j_m, jbyteArray j_c, jlong j_clen, jbyteArray j_n, jbyteArray j_pk, jbyteArray j_sk)
  {
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *n = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_n, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    int result = crypto_box_open_easy(m, c, (unsigned long long)j_clen, n, pk, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *)n, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1beforenm(JNIEnv *jenv, jclass jcls, jbyteArray j_s, jbyteArray j_pk, jbyteArray j_sk)
  {
    unsigned char *s = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_s, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    int result = crypto_box_beforenm(s, pk, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_s, (jbyte *)s, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1easy_1afternm(JNIEnv *jenv, jclass jcls, jbyteArray j_c, jbyteArray j_m, jlong j_mlen, jbyteArray j_n, jbyteArray j_k)
  {
    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *n = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_n, 0);
    unsigned char *k = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_k, 0);
    int result = crypto_box_easy_afternm(c, m, (unsigned long long)j_mlen, n, k);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *)n, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *)k, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1open_1easy_1afternm(JNIEnv *jenv, jclass jcls, jbyteArray j_m, jbyteArray j_c, jlong j_clen, jbyteArray j_n, jbyteArray j_k)
  {
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *n = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_n, 0);
    unsigned char *k = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_k, 0);
    int result = crypto_box_open_easy_afternm(m, c, (unsigned long long)j_clen, n, k);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *)n, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *)k, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1seal(JNIEnv *jenv, jclass jcls, jbyteArray j_c, jbyteArray j_m, jlong j_mlen, jbyteArray j_pk)
  {
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    int result = crypto_box_seal(c, m, (unsigned long long)j_mlen, pk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1box_1seal_1open(JNIEnv *jenv, jclass jcls, jbyteArray j_m, jbyteArray j_c, jlong j_clen, jbyteArray j_pk, jbyteArray j_sk)
  {
    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    int result = crypto_box_seal_open(m, c, (unsigned long long)j_clen, pk, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  /* *****************************************************************************
   * Generic hashing - The generichash* API
   * *****************************************************************************
   */
  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash(JNIEnv *jenv, jclass jcls, jbyteArray j_out, jlong j_olong, jbyteArray j_in, jlong j_ilen, jbyteArray j_key, jint j_klen)
  {
    unsigned char *in = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_in, 0);
    unsigned char *key = j_key != NULL ? (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_key, 0) : NULL;
    ;
    unsigned char *out = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_out, 0);

    int result = crypto_generichash(out, (unsigned long long)j_olong, in, (unsigned long long)j_ilen, key, (unsigned long long)j_klen);

    (*jenv)->ReleaseByteArrayElements(jenv, j_in, (jbyte *)in, 0);
    key != NULL ? (*jenv)->ReleaseByteArrayElements(jenv, j_key, (jbyte *)key, 0) : NULL;
    (*jenv)->ReleaseByteArrayElements(jenv, j_out, (jbyte *)out, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1bytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_generichash_BYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1bytes_1min(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_generichash_BYTES_MIN;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1bytes_1max(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_generichash_BYTES_MAX;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1keybytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_generichash_KEYBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1keybytes_1min(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_generichash_KEYBYTES_MIN;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1keybytes_1max(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_generichash_KEYBYTES_MAX;
  }

  JNIEXPORT jstring JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1primitive(JNIEnv *jenv, jclass jcls)
  {
    return (jstring)crypto_generichash_PRIMITIVE;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1init(JNIEnv *jenv, jclass jcls, jbyteArray j_state, jbyteArray j_key, jlong j_klen, jint j_olen)
  {
    unsigned char *state = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_state, 0);
    unsigned char *key = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_key, 0);

    int result = crypto_generichash_init(state, key, (unsigned long long)j_klen, (unsigned long long)j_olen);

    (*jenv)->ReleaseByteArrayElements(jenv, j_state, (jbyte *)state, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_key, (jbyte *)key, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1update(JNIEnv *jenv, jclass jcls, jbyteArray j_state, jbyteArray j_in, jlong j_ilen)
  {
    unsigned char *state = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_state, 0);
    unsigned char *in = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_in, 0);

    int result = crypto_generichash_update(state, in, (unsigned long long)j_ilen);

    (*jenv)->ReleaseByteArrayElements(jenv, j_state, (jbyte *)state, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_in, (jbyte *)in, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1generichash_1final(JNIEnv *jenv, jclass jcls, jbyteArray j_state, jbyteArray j_out, jlong j_olen)
  {
    unsigned char *state = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_state, 0);
    unsigned char *out = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_out, 0);

    int result = crypto_generichash_final(state, out, (unsigned long long)j_olen);

    (*jenv)->ReleaseByteArrayElements(jenv, j_state, (jbyte *)state, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_out, (jbyte *)out, 0);
    return (jint)result;
  }

  /* *****************************************************************************
   * Password hashing - The pwhash* API
   * *****************************************************************************
   */
  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash(JNIEnv *jenv, jclass jcls, jbyteArray j_out, jlong j_olong, jbyteArray j_p, jlong j_plen, jbyteArray j_salt, jlong j_opslimit, jlong jmemlimit, jint j_algo)
  {
    const char *password = (const char *)(*jenv)->GetByteArrayElements(jenv, j_p, 0);
    unsigned char *salt = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_salt, 0);
    unsigned char *out = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_out, 0);

    int result = crypto_pwhash(out, (unsigned long long)j_olong, password, (unsigned long long)j_plen, salt, (unsigned long long)j_opslimit, (unsigned long long)jmemlimit, (unsigned int)j_algo);

    (*jenv)->ReleaseByteArrayElements(jenv, j_p, (jbyte *)password, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_salt, (jbyte *)salt, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_out, (jbyte *)out, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1salt_1bytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_SALTBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1opslimit_1moderate(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_OPSLIMIT_MODERATE;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1opslimit_1min(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_OPSLIMIT_MIN;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1opslimit_1max(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_OPSLIMIT_MAX;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1memlimit_1moderate(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_MEMLIMIT_MODERATE;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1memlimit_1min(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_MEMLIMIT_MIN;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1memlimit_1max(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_MEMLIMIT_MAX;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1algo_1default(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_ALG_DEFAULT;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1algo_1argon2i13(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_ALG_ARGON2I13;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1pwhash_1algo_1argon2id13(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_pwhash_ALG_ARGON2ID13;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1scalarmult_1base(JNIEnv *jenv, jclass jcls, jbyteArray j_q, jbyteArray j_n)
  {
    unsigned char *q = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_q, 0);
    unsigned char *n = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_n, 0);
    int result = (int)crypto_scalarmult_base(q, n);
    (*jenv)->ReleaseByteArrayElements(jenv, j_q, (jbyte *)q, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_n, (jbyte *)n, 0);
    return (jint)result;
  }

  /* *****************************************************************************
   * Public-key cryptography - signatures
   * *****************************************************************************
   */

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1secretkeybytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_sign_SECRETKEYBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1publickeybytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_sign_PUBLICKEYBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1seedbytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_sign_SEEDBYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1bytes(JNIEnv *jenv, jclass jcls)
  {
    return (jint)crypto_sign_BYTES;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign(JNIEnv *jenv, jclass jcls, jbyteArray j_msig, jbyteArray j_msg, jint j_msg_len, jbyteArray j_sk)
  {
    unsigned char *msig = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_msig, 0);
    unsigned char *msg = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_msg, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    int result = crypto_sign(msig, NULL, msg, j_msg_len, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_msig, (jbyte *)msig, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_msg, (jbyte *)msg, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1detached(JNIEnv *jenv, jclass jcls, jbyteArray j_sig, jbyteArray j_msg, jint j_msg_len, jbyteArray j_sk)
  {
    unsigned char *sig = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sig, 0);
    unsigned char *msg = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_msg, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    int result = crypto_sign_detached(sig, NULL, msg, j_msg_len, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sig, (jbyte *)sig, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_msg, (jbyte *)msg, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1verify_1detached(JNIEnv *jenv, jclass jcls, jbyteArray j_sig, jbyteArray j_msg, jlong j_msg_len, jbyteArray j_pk)
  {
    unsigned char *sig = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sig, 0);
    unsigned char *msg = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_msg, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    int result = crypto_sign_verify_detached(sig, msg, (unsigned long long)j_msg_len, pk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sig, (jbyte *)sig, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_msg, (jbyte *)msg, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1keypair(JNIEnv *jenv, jclass jcls, jbyteArray j_pk, jbyteArray j_sk)
  {
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    int result = crypto_sign_keypair(pk, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1seed_1keypair(JNIEnv *jenv, jclass jcls, jbyteArray j_pk, jbyteArray j_sk, jbyteArray j_seed)
  {
    unsigned char *seed = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_seed, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    int result = crypto_sign_seed_keypair(pk, sk, seed);
    (*jenv)->ReleaseByteArrayElements(jenv, j_seed, (jbyte *)seed, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1ed25519_1sk_1to_1seed(JNIEnv *jenv, jclass jcls, jbyteArray j_seed, jbyteArray j_sk)
  {
    unsigned char *seed = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_seed, 0);
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    int result = crypto_sign_ed25519_sk_to_seed(seed, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_seed, (jbyte *)seed, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1ed25519_1pk_1to_1curve25519(JNIEnv *jenv, jclass jcls, jbyteArray j_curve, jbyteArray j_ed)
  {
    unsigned char *curve = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_curve, 0);
    unsigned char *ed = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_ed, 0);
    int result = crypto_sign_ed25519_pk_to_curve25519(curve, ed);
    (*jenv)->ReleaseByteArrayElements(jenv, j_curve, (jbyte *)curve, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_ed, (jbyte *)ed, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1ed25519_1sk_1to_1curve25519(JNIEnv *jenv, jclass jcls, jbyteArray j_curve, jbyteArray j_ed)
  {
    unsigned char *curve = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_curve, 0);
    unsigned char *ed = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_ed, 0);
    int result = crypto_sign_ed25519_sk_to_curve25519(curve, ed);
    (*jenv)->ReleaseByteArrayElements(jenv, j_curve, (jbyte *)curve, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_ed, (jbyte *)ed, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1sign_1ed25519_1sk_1to_1pk(JNIEnv *jenv, jclass jcls, jbyteArray j_sk, jbyteArray j_pk)
  {
    unsigned char *sk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_sk, 0);
    unsigned char *pk = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_pk, 0);
    int result = crypto_sign_ed25519_sk_to_pk(pk, sk);
    (*jenv)->ReleaseByteArrayElements(jenv, j_sk, (jbyte *)sk, 0);
    (*jenv)->ReleaseByteArrayElements(jenv, j_pk, (jbyte *)pk, 0);
    return (jint)result;
  }

  // use only for copying values, returning values here from crypto won't work
  unsigned char *as_unsigned_char_array(JNIEnv *jenv, jbyteArray array)
  {
    if (array == NULL)
    {
      return NULL;
    }
    int len = (*jenv)->GetArrayLength(jenv, array);
    unsigned char *buf = malloc(len);
    (*jenv)->GetByteArrayRegion(jenv, array, 0, len, (jbyte *)(buf));
    return buf;
  }

  JNIEXPORT jint JNICALL Java_org_libsodium_jni_SodiumJNI_crypto_1aead_1xchacha20poly1305_1ietf_1encrypt(JNIEnv *jenv,
                                                                                                         jclass clazz,
                                                                                                         jbyteArray j_c,
                                                                                                         jintArray j_clen,
                                                                                                         jbyteArray j_m,
                                                                                                         jint j_mlen,
                                                                                                         jbyteArray j_ad,
                                                                                                         jint j_adlen,
                                                                                                         jbyteArray j_nsec,
                                                                                                         jbyteArray j_npub,
                                                                                                         jbyteArray j_k)
  {

    unsigned char *c = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_c, 0);
    unsigned char *m = as_unsigned_char_array(jenv, j_m);
    unsigned char *npub = as_unsigned_char_array(jenv, j_npub);
    unsigned char *ad = as_unsigned_char_array(jenv, j_ad);
    unsigned char *nsec = as_unsigned_char_array(jenv, j_nsec);
    unsigned char *k = as_unsigned_char_array(jenv, j_k);

    int result = crypto_aead_xchacha20poly1305_ietf_encrypt(c, j_clen, m, j_mlen, ad, j_adlen, nsec, npub, k);
    (*jenv)->ReleaseByteArrayElements(jenv, j_c, (jbyte *)c, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_crypto_1aead_1xchacha20poly1305_1ietf_1decrypt(JNIEnv *jenv,
                                                                                  jclass clazz,
                                                                                  jbyteArray j_m,
                                                                                  jintArray j_mlen_p,
                                                                                  jbyteArray j_nsec,
                                                                                  jbyteArray j_c,
                                                                                  jint j_clen,
                                                                                  jbyteArray j_ad,
                                                                                  jint j_adlen,
                                                                                  jbyteArray j_npub,
                                                                                  jbyteArray j_k)
  {
    unsigned char *c = as_unsigned_char_array(jenv, j_c);
    unsigned char *m = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_m, 0);
    unsigned char *npub = as_unsigned_char_array(jenv, j_npub);
    unsigned char *ad = as_unsigned_char_array(jenv, j_ad);
    unsigned char *nsec = as_unsigned_char_array(jenv, j_nsec);
    unsigned char *k = as_unsigned_char_array(jenv, j_k);

    int result = crypto_aead_xchacha20poly1305_ietf_decrypt(m, j_mlen_p, nsec, c, j_clen, ad, j_adlen, npub, k);
    (*jenv)->ReleaseByteArrayElements(jenv, j_m, (jbyte *)m, 0);
    return (jint)result;
  }

  JNIEXPORT jchar JNICALL
  Java_org_libsodium_jni_SodiumJNI_crypto_1aead_1xchacha20poly1305_1ietf_1keygen(JNIEnv *jenv,
                                                                                 jclass clazz,
                                                                                 jbyteArray j_k)
  {
    unsigned char *k = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_k, 0);
    crypto_aead_xchacha20poly1305_ietf_keygen(k);
    (*jenv)->ReleaseByteArrayElements(jenv, j_k, (jbyte *)k, 0);
    return k;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_crypto_1aead_1chacha20poly1305_1IETF_1ABYTES(JNIEnv *env,
                                                                                jclass clazz)
  {
    return (jint)crypto_aead_chacha20poly1305_IETF_ABYTES;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_crypto_1aead_1xchacha20poly1305_1IETF_1KEYBYTES(JNIEnv *env,
                                                                                   jclass clazz)
  {
    return (jint)crypto_aead_xchacha20poly1305_IETF_KEYBYTES;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_crypto_1aead_1xchacha20poly1305_1IETF_1NPUBBYTES(JNIEnv *env,
                                                                                    jclass clazz)
  {
    return (jint)crypto_aead_xchacha20poly1305_IETF_NPUBBYTES;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_crypto_1aead_1xchacha20poly1305_1IETF_1NSECBYTES(JNIEnv *env,
                                                                                    jclass clazz)
  {
    return (jint)crypto_aead_xchacha20poly1305_IETF_NSECBYTES;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_base64_1variant_1ORIGINAL(JNIEnv *env, jclass clazz)
  {
    return (jint)sodium_base64_VARIANT_ORIGINAL;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_base64_1variant_1VARIANT_1ORIGINAL_1NO_1PADDING(JNIEnv *env,
                                                                                   jclass clazz)
  {
    return (jint)sodium_base64_VARIANT_ORIGINAL_NO_PADDING;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_base64_1variant_1VARIANT_1URLSAFE(JNIEnv *env, jclass clazz)
  {
    return (jint)sodium_base64_VARIANT_URLSAFE;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_base64_1variant_1VARIANT_1URLSAFE_1NO_1PADDING(JNIEnv *env,
                                                                                  jclass clazz)
  {
    return (jint)sodium_base64_VARIANT_URLSAFE_NO_PADDING;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_sodium_1base642bin(JNIEnv *jenv, jclass clazz, jbyteArray j_bin,
                                                      jint j_bin_maxlen, jbyteArray j_b64, jint j_b64_len,
                                                      jbyteArray j_ignore, jintArray j_bin_len,
                                                      jbyteArray j_b64_end, jint j_variant)
  {
    unsigned char *bin = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_bin, 0);
    jint *len = (*jenv)->GetIntArrayElements(jenv, j_bin_len, 0);
    unsigned char *b64 = as_unsigned_char_array(jenv, j_b64);
    unsigned char *ignore = as_unsigned_char_array(jenv, j_ignore);
    void *memory = malloc(sizeof(int));
    int *ptr = (int *)memory;

    int result = sodium_base642bin(bin, j_bin_maxlen, b64, j_b64_len, ignore,
                                   ptr, j_b64_end, j_variant);
    (*jenv)->ReleaseByteArrayElements(jenv, j_bin, (jbyte *)bin, 0);
    len[0] = *ptr;
    (*jenv)->ReleaseIntArrayElements(jenv, j_bin_len, len, 0);
    free(memory);
    return (jint)result;
  }

  JNIEXPORT jchar JNICALL
  Java_org_libsodium_jni_SodiumJNI_sodium_1bin2hex(JNIEnv *jenv, jclass clazz, jbyteArray j_hex,
                                                   jint j_hex_maxlen, jbyteArray j_bin, jint j_bin_len)
  {
    unsigned char *hex = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_hex, 0);
    unsigned char *bin = as_unsigned_char_array(jenv, j_bin);

    int result = sodium_bin2hex(hex, j_hex_maxlen, bin, j_bin_len);
    (*jenv)->ReleaseByteArrayElements(jenv, j_hex, (jbyte *)hex, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_sodium_1hex2bin(JNIEnv *jenv, jclass clazz, jbyteArray j_bin,
                                                   jint j_bin_maxlen, jbyteArray j_hex, jint j_hex_len,
                                                   jbyteArray j_ignore, jintArray j_bin_len,
                                                   jbyteArray j_hex_end)
  {
    unsigned char *bin = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_bin, 0);
    jint *len = (*jenv)->GetIntArrayElements(jenv, j_bin_len, 0);
    unsigned char *hex = as_unsigned_char_array(jenv, j_hex);
    unsigned char *ignore = as_unsigned_char_array(jenv, j_ignore);
    void *memory = malloc(sizeof(int));
    int *ptr = (int *)memory;

    int result = sodium_hex2bin(bin, j_bin_maxlen, hex, j_hex_len, ignore, ptr, j_hex_end);
    (*jenv)->ReleaseByteArrayElements(jenv, j_bin, (jbyte *)bin, 0);
    len[0] = *ptr;
    (*jenv)->ReleaseIntArrayElements(jenv, j_bin_len, len, 0);
    free(memory);
    return (jint)result;
  }

  JNIEXPORT jchar JNICALL
  Java_org_libsodium_jni_SodiumJNI_sodium_1bin2base64(JNIEnv *jenv, jclass clazz, jbyteArray j_b64,
                                                      jint j_b64_maxlen, jbyteArray j_bin, jint j_bin_len,
                                                      jint j_variant)
  {
    unsigned char *b64 = (unsigned char *)(*jenv)->GetByteArrayElements(jenv, j_b64, 0);
    unsigned char *bin = as_unsigned_char_array(jenv, j_bin);

    int result = sodium_bin2base64(b64, j_b64_maxlen, bin, j_bin_len, j_variant);
    (*jenv)->ReleaseByteArrayElements(jenv, j_b64, (jbyte *)b64, 0);
    return (jint)result;
  }

  JNIEXPORT jint JNICALL
  Java_org_libsodium_jni_SodiumJNI_sodium_1base64_1encoded_1len(JNIEnv *jenv, jclass clazz,
                                                                jint j_bin_len, jint j_variant)
  {
    return (jint)sodium_base64_encoded_len(j_bin_len, j_variant);
  }

#ifdef __cplusplus
}
#endif
