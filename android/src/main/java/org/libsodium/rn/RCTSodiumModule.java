package org.libsodium.rn;

/**
 * Created by Lyubomir Ivanov on 21/09/16.
 */

import java.util.Arrays;
import java.util.Map;
import java.util.HashMap;
import android.util.Base64;
import android.util.Log;

import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.bridge.WritableNativeMap;
import com.facebook.react.common.MapBuilder;
import com.facebook.react.common.StandardCharsets;

import org.libsodium.jni.Sodium;

public class RCTSodiumModule extends ReactContextBaseJavaModule {

  static final String ESODIUM = "ESODIUM";
  static final String ERR_BAD_KEY = "BAD_KEY";
  static final String ERR_BAD_MAC = "BAD_MAC";
  static final String ERR_BAD_MSG = "BAD_MSG";
  static final String ERR_BAD_NONCE = "BAD_NONCE";
  static final String ERR_BAD_SEED = "BAD_SEED";
  static final String ERR_BAD_SIG = "BAD_SIG";
  static final String ERR_FAILURE = "FAILURE";

  public RCTSodiumModule(ReactApplicationContext reactContext) {
    super(reactContext);
    Sodium.loadLibrary();
  }

  @Override
  public String getName() {
    return "Sodium";
  }

  @Override
  public Map<String, Object> getConstants() {
    final Map<String, Object> constants = new HashMap<>();
    constants.put("crypto_secretbox_KEYBYTES", Sodium.crypto_secretbox_keybytes());
    constants.put("crypto_secretbox_NONCEBYTES", Sodium.crypto_secretbox_noncebytes());
    constants.put("crypto_secretbox_MACBYTES", Sodium.crypto_secretbox_macbytes());
    constants.put("crypto_auth_KEYBYTES", Sodium.crypto_auth_keybytes());
    constants.put("crypto_auth_BYTES", Sodium.crypto_auth_bytes());
    constants.put("crypto_box_PUBLICKEYBYTES", Sodium.crypto_box_publickeybytes());
    constants.put("crypto_box_SECRETKEYBYTES", Sodium.crypto_box_secretkeybytes());
    constants.put("crypto_box_NONCEBYTES", Sodium.crypto_box_noncebytes());
    constants.put("crypto_box_MACBYTES", Sodium.crypto_box_macbytes());
    constants.put("crypto_box_ZEROBYTES", Sodium.crypto_box_zerobytes());
    constants.put("crypto_box_SEALBYTES", Sodium.crypto_box_sealbytes());
    constants.put("crypto_sign_PUBLICKEYBYTES", Sodium.crypto_sign_publickeybytes());
    constants.put("crypto_sign_SECRETKEYBYTES", Sodium.crypto_sign_secretkeybytes());
    constants.put("crypto_sign_SEEDBYTES", Sodium.crypto_sign_seedbytes());
    constants.put("crypto_sign_BYTES", Sodium.crypto_sign_bytes());
    constants.put("crypto_generichash_BYTES", Sodium.crypto_generichash_bytes());
    constants.put("crypto_generichash_BYTES_MIN", Sodium.crypto_generichash_bytes_min());
    constants.put("crypto_generichash_BYTES_MAX", Sodium.crypto_generichash_bytes_max());
    constants.put("crypto_generichash_KEYBYTES", Sodium.crypto_generichash_keybytes());
    constants.put("crypto_generichash_KEYBYTES_MIN", Sodium.crypto_generichash_keybytes_min());
    constants.put("crypto_generichash_KEYBYTES_MAX", Sodium.crypto_generichash_keybytes_max());
    constants.put("crypto_pwhash_SALTBYTES", Sodium.crypto_pwhash_salt_bytes());
    constants.put("crypto_pwhash_OPSLIMIT_MODERATE", Sodium.crypto_pwhash_opslimit_moderate());
    constants.put("crypto_pwhash_OPSLIMIT_MIN", Sodium.crypto_pwhash_opslimit_min());
    constants.put("crypto_pwhash_OPSLIMIT_MAX", Sodium.crypto_pwhash_opslimit_max());
    constants.put("crypto_pwhash_MEMLIMIT_MODERATE", Sodium.crypto_pwhash_memlimit_moderate());
    constants.put("crypto_pwhash_MEMLIMIT_MIN", Sodium.crypto_pwhash_memlimit_min());
    constants.put("crypto_pwhash_MEMLIMIT_MAX", Sodium.crypto_pwhash_memlimit_max());
    constants.put("crypto_pwhash_ALG_DEFAULT", Sodium.crypto_pwhash_algo_default());
    constants.put("crypto_pwhash_ALG_ARGON2I13", Sodium.crypto_pwhash_algo_argon2i13());
    constants.put("crypto_pwhash_ALG_ARGON2ID13", Sodium.crypto_pwhash_algo_argon2id13());
    constants.put("crypto_aead_xchacha20poly1305_IETF_ABYTES", Sodium.crypto_aead_chacha20poly1305_IETF_ABYTES());
    constants.put("crypto_aead_xchacha20poly1305_IETF_KEYBYTES", Sodium.crypto_aead_xchacha20poly1305_IETF_KEYBYTES());
    constants.put("crypto_aead_xchacha20poly1305_IETF_NPUBBYTES", Sodium.crypto_aead_xchacha20poly1305_IETF_NPUBBYTES());
    constants.put("crypto_aead_xchacha20poly1305_IETF_NSECBYTES", Sodium.crypto_aead_xchacha20poly1305_IETF_NSECBYTES());
    constants.put("base64_variant_ORIGINAL", Sodium.base64_variant_ORIGINAL());
    constants.put("base64_variant_VARIANT_ORIGINAL_NO_PADDING", Sodium.base64_variant_VARIANT_ORIGINAL_NO_PADDING());
    constants.put("base64_variant_VARIANT_URLSAFE", Sodium.base64_variant_VARIANT_URLSAFE());
    constants.put("base64_variant_VARIANT_URLSAFE_NO_PADDING", Sodium.base64_variant_VARIANT_URLSAFE_NO_PADDING());

    return constants;
  }

  // ***************************************************************************
  // * Sodium-specific functions
  // ***************************************************************************
  @ReactMethod
  public void sodium_version_string(final Promise p) {
    p.resolve(Sodium.sodium_version_string());
  }

  // ***************************************************************************
  // * Random data generation
  // ***************************************************************************
  @ReactMethod
  public void randombytes_random(final Promise p) {
    // RN0.34: Long can't be passed through the bridge (int and double only)
    p.resolve(Long.valueOf(Sodium.randombytes_random()).doubleValue());
  }

  @ReactMethod
  public void randombytes_uniform(Double upper_bound, final Promise p) {
    // RN0.34: Long can't be passed through the bridge (int and double only)
    p.resolve(Long.valueOf(Sodium.randombytes_uniform(upper_bound.longValue())).doubleValue());
  }

  @ReactMethod
  public void randombytes_buf(int size, final Promise p) {
    try {
      byte[] buf = new byte[size];
      Sodium.randombytes_buf(buf, size);
      p.resolve(this.binToHex(buf));
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void randombytes_close(final Promise p) {
    int result = Sodium.randombytes_close();
    if (result == 0) p.resolve(0); else p.reject(ESODIUM,ERR_FAILURE);
  }

  @ReactMethod
  public void randombytes_stir(final Promise p) {
    Sodium.randombytes_stir();
    p.resolve(0);
  }


  // ***************************************************************************
  // * Secret-key cryptography - authenticated encryption
  // ***************************************************************************
  @ReactMethod
  public void crypto_secretbox_easy(final String m, final String n, final String k, final Promise p) {
    try {
      byte[] mb = Base64.decode(m, Base64.NO_WRAP);
      byte[] nb = Base64.decode(n, Base64.NO_WRAP);
      byte[] kb = Base64.decode(k, Base64.NO_WRAP);
      if (kb.length != Sodium.crypto_secretbox_keybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (nb.length != Sodium.crypto_secretbox_noncebytes())
        p.reject(ESODIUM,ERR_BAD_NONCE);
      else {
        byte[] cb = new byte[mb.length + Sodium.crypto_secretbox_macbytes()];
        int result = Sodium.crypto_secretbox_easy(cb, mb, mb.length, nb, kb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(cb,Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_secretbox_open_easy(final String c, final String n, final String k, final Promise p) {
    try {
      byte[] cb = Base64.decode(c, Base64.NO_WRAP);
      byte[] nb = Base64.decode(n, Base64.NO_WRAP);
      byte[] kb = Base64.decode(k, Base64.NO_WRAP);
      if (kb.length != Sodium.crypto_secretbox_keybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (nb.length != Sodium.crypto_box_noncebytes())
        p.reject(ESODIUM,ERR_BAD_NONCE);
      else if (cb.length <=  Sodium.crypto_box_macbytes())
        p.reject(ESODIUM,ERR_BAD_MSG);
      else {
        byte[] mb = new byte[cb.length - Sodium.crypto_box_macbytes()];
        int result = Sodium.crypto_secretbox_open_easy(mb, cb, cb.length, nb, kb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(mb,Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  // ***************************************************************************
  // * Secret-key cryptography - authentication
  // ***************************************************************************
  @ReactMethod
  public void crypto_auth(String in, String k, final Promise p){
    try {
      byte[] out = new byte[Sodium.crypto_auth_bytes()];
      byte[] inb = Base64.decode(in, Base64.NO_WRAP);
      byte[] kb = Base64.decode(k, Base64.NO_WRAP);
      if (kb.length != Sodium.crypto_auth_keybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else {
        int result = Sodium.crypto_auth(out, inb, inb.length, kb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(out,Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_auth_verify(String h, String in, String k, final Promise p){
    try {
      byte[] inb = Base64.decode(in, Base64.NO_WRAP);
      byte[] hb = Base64.decode(h, Base64.NO_WRAP);
      byte[] kb = Base64.decode(k, Base64.NO_WRAP);
      if (kb.length != Sodium.crypto_auth_keybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (hb.length != Sodium.crypto_auth_bytes())
        p.reject(ESODIUM,ERR_BAD_MAC);
      else {
        int result = Sodium.crypto_auth_verify(hb, inb, inb.length, kb);
        p.resolve(result);
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  // ***************************************************************************
  // * Public-key cryptography - XChaCha20-Poly1305 encryption
  // ***************************************************************************

  @ReactMethod
  public void crypto_aead_xchacha20poly1305_ietf_keygen(final Promise p) {
    byte[] k = new byte[Sodium.crypto_aead_xchacha20poly1305_IETF_KEYBYTES()];
    Sodium.crypto_aead_xchacha20poly1305_ietf_keygen(k);
    String s = Base64.encodeToString(k, Base64.NO_WRAP);
    p.resolve(s);
  }

  @ReactMethod
  public void crypto_aead_xchacha20poly1305_ietf_encrypt(final String message, final String public_nonce, final String key, final String additionalData, final Promise p) {
    try {
      byte[] m = message.getBytes(StandardCharsets.UTF_8);
      byte[] npub = this.hexToBin(public_nonce);
      byte[] k = this.hexToBin(key);

      if (m.length <= 0)
        p.reject(ESODIUM,ERR_FAILURE);
      else if (npub.length != Sodium.crypto_aead_xchacha20poly1305_IETF_NPUBBYTES())
        p.reject(ESODIUM,ERR_BAD_NONCE);
      else if (k.length != Sodium.crypto_aead_xchacha20poly1305_IETF_KEYBYTES())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else {
        byte[] ad = additionalData != null ? additionalData.getBytes(StandardCharsets.UTF_8) : null;
        int adlen = additionalData != null ? ad.length : 0;
        byte[] c = new byte[m.length + Sodium.crypto_aead_chacha20poly1305_IETF_ABYTES()];
        int result = Sodium.crypto_aead_xchacha20poly1305_ietf_encrypt(c, null, m, m.length, ad, adlen, null, npub, k);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(this.binToBase64(c, Sodium.base64_variant_ORIGINAL()));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_aead_xchacha20poly1305_ietf_decrypt(final String cipherText, final String public_nonce, final String key, final String additionalData, final Promise p) {
    try {
      byte[] c = this.base64ToBin(cipherText, Sodium.base64_variant_ORIGINAL());
      byte[] npub = this.hexToBin(public_nonce);
      byte[] k = this.hexToBin(key);
      if (c == null || c.length <= 0)
        p.reject(ESODIUM,ERR_FAILURE);
      else if (npub.length != Sodium.crypto_aead_xchacha20poly1305_IETF_NPUBBYTES())
        p.reject(ESODIUM,ERR_BAD_NONCE);
      else if (k.length != Sodium.crypto_aead_xchacha20poly1305_IETF_KEYBYTES())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else {
        byte[] ad = additionalData != null ? additionalData.getBytes(StandardCharsets.UTF_8) : null;
        int adlen = additionalData != null ? ad.length : 0;
        int[] decrypted_len = new int[1];
        byte[] decrypted = new byte[c.length - Sodium.crypto_aead_chacha20poly1305_IETF_ABYTES()];

        int result = Sodium.crypto_aead_xchacha20poly1305_ietf_decrypt(decrypted, decrypted_len, null, c, c.length, ad, adlen, npub, k);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(new String(decrypted, StandardCharsets.UTF_8));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  // ***************************************************************************
  // * Public-key cryptography - authenticated encryption
  // ***************************************************************************
  @ReactMethod
  public void crypto_box_keypair(final Promise p){
    try {
      byte[] pk = new byte[Sodium.crypto_box_publickeybytes()];
      byte[] sk = new byte[Sodium.crypto_box_secretkeybytes()];

      if (Sodium.crypto_box_keypair(pk, sk) != 0)
        p.reject(ESODIUM,ERR_FAILURE);
      else {
        WritableNativeMap result = new WritableNativeMap();
        result.putString("pk",Base64.encodeToString(pk,Base64.NO_WRAP));
        result.putString("sk",Base64.encodeToString(sk,Base64.NO_WRAP));
        p.resolve(result);
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_box_easy(final String m, final String n, final String pk, final String sk, final Promise p) {
    try {
      byte[] mb = Base64.decode(m, Base64.NO_WRAP);
      byte[] nb = Base64.decode(n, Base64.NO_WRAP);
      byte[] pkb = Base64.decode(pk, Base64.NO_WRAP);
      byte[] skb = Base64.decode(sk, Base64.NO_WRAP);
      if (pkb.length != Sodium.crypto_box_publickeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (skb.length != Sodium.crypto_box_secretkeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (nb.length != Sodium.crypto_box_noncebytes())
        p.reject(ESODIUM,ERR_BAD_NONCE);
      else {
        byte[] cb = new byte[mb.length + Sodium.crypto_box_macbytes()];
        int result = Sodium.crypto_box_easy(cb, mb, mb.length, nb, pkb, skb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(cb,Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_box_easy_afternm(final String m, final String n, final String k, final Promise p) {
    try {
      byte[] mb = Base64.decode(m, Base64.NO_WRAP);
      byte[] nb = Base64.decode(n, Base64.NO_WRAP);
      byte[] kb = Base64.decode(k, Base64.NO_WRAP);
      if (kb.length != Sodium.crypto_box_secretkeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (nb.length != Sodium.crypto_box_noncebytes())
        p.reject(ESODIUM,ERR_BAD_NONCE);
      else {
        byte[] cb = new byte[mb.length + Sodium.crypto_box_macbytes()];
        int result = Sodium.crypto_box_easy_afternm(cb, mb, mb.length, nb, kb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(cb,Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_box_open_easy(final String c, final String n, final String pk, final String sk, final Promise p) {
    try {
      byte[] cb = Base64.decode(c, Base64.NO_WRAP);
      byte[] nb = Base64.decode(n, Base64.NO_WRAP);
      byte[] pkb = Base64.decode(pk, Base64.NO_WRAP);
      byte[] skb = Base64.decode(sk, Base64.NO_WRAP);
      if (pkb.length != Sodium.crypto_box_publickeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (skb.length != Sodium.crypto_box_secretkeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (nb.length != Sodium.crypto_box_noncebytes())
        p.reject(ESODIUM,ERR_BAD_NONCE);
      else if (cb.length < Sodium.crypto_box_macbytes())
        p.reject(ESODIUM,ERR_BAD_MSG);
      else {
        byte[] mb = new byte[cb.length - Sodium.crypto_box_macbytes()];
        int result = Sodium.crypto_box_open_easy(mb, cb, cb.length, nb, pkb, skb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(mb,Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_box_open_easy_afternm(final String c, final String n, final String k, final Promise p) {
    try {
      byte[] cb = Base64.decode(c, Base64.NO_WRAP);
      byte[] nb = Base64.decode(n, Base64.NO_WRAP);
      byte[] kb = Base64.decode(k, Base64.NO_WRAP);
      if (kb.length != Sodium.crypto_box_secretkeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (nb.length != Sodium.crypto_box_noncebytes())
        p.reject(ESODIUM,ERR_BAD_NONCE);
      else if (cb.length < Sodium.crypto_box_macbytes())
        p.reject(ESODIUM,ERR_BAD_MSG);
      else {
        byte[] mb = new byte[cb.length - Sodium.crypto_box_macbytes()];
        int result = Sodium.crypto_box_open_easy_afternm(mb, cb, cb.length, nb, kb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(mb,Base64.NO_WRAP));
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_box_beforenm(final String pk, final String sk, final Promise p) {
    try {
      byte[] pkb = Base64.decode(pk, Base64.NO_WRAP);
      byte[] skb = Base64.decode(sk, Base64.NO_WRAP);
      if (pkb.length != Sodium.crypto_box_publickeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (skb.length != Sodium.crypto_box_secretkeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else {
        byte[] s = new byte[Sodium.crypto_box_secretkeybytes()];
        int result = Sodium.crypto_box_beforenm(s, pkb, skb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(s,Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_generichash(final Integer outlen, final String data, final String key, final Promise p) {
    try {
      byte[] keyb = key != null ? Base64.decode(key, Base64.NO_WRAP): null;
      int keylen = key != null ? keyb.length : 0;
      byte[] datab = Base64.decode(data, Base64.NO_WRAP);
      byte[] out = new byte[outlen];

      int result = Sodium.crypto_generichash(out, out.length, datab, datab.length, keyb, keylen);
      if (result != 0)
        p.reject(ESODIUM,ERR_FAILURE);
      else
        p.resolve(Base64.encodeToString(out, Base64.NO_WRAP));
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_pwhash(final Integer keylen, final String password, final String salt, final Integer opslimit, final Integer memlimit, final Integer algo , final Promise p) {
    try {
      byte[] saltb = this.hexToBin(salt);
      byte[] passwordb = password.getBytes(StandardCharsets.UTF_8);
      byte[] out = new byte[keylen];

      int result = Sodium.crypto_pwhash(out, out.length, passwordb, passwordb.length, saltb, opslimit, memlimit, algo);
      if (result != 0)
        p.reject(ESODIUM,ERR_FAILURE);
      else
        p.resolve(this.binToHex(out));
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_box_seal(final String m, final String pk, final Promise p) {
    try {
      byte[] pkb = Base64.decode(pk, Base64.NO_WRAP);
      byte[] mb = Base64.decode(m, Base64.NO_WRAP);
      if (pkb.length != Sodium.crypto_box_publickeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else {
        byte[] c = new byte[Sodium.crypto_box_sealbytes() + mb.length];
        int result = Sodium.crypto_box_seal(c, mb, mb.length, pkb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(c, Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_box_seal_open(final String c, final String pk, final String sk, final Promise p) {
    try {
      byte[] pkb = Base64.decode(pk, Base64.NO_WRAP);
      byte[] skb = Base64.decode(sk, Base64.NO_WRAP);
      byte[] cb = Base64.decode(c, Base64.NO_WRAP);
      if (pkb.length != Sodium.crypto_box_publickeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else if (skb.length != Sodium.crypto_box_secretkeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else {
        byte[] m = new byte[cb.length - Sodium.crypto_box_sealbytes()];
        int result = Sodium.crypto_box_seal_open(m, cb, cb.length, pkb, skb);
        if (result != 0)
          p.reject(ESODIUM,ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(m, Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  @ReactMethod
  public void crypto_scalarmult_base(final String n, final Promise p) {
    try {
      byte[] nb = Base64.decode(n, Base64.NO_WRAP);
      if (nb.length != Sodium.crypto_box_secretkeybytes())
        p.reject(ESODIUM,ERR_BAD_KEY);
      else {
        byte[] q = new byte[Sodium.crypto_box_publickeybytes()];
        int result = Sodium.crypto_scalarmult_base(q, nb);
        if (result != 0)
          p.reject(ESODIUM,ERR_BAD_KEY);
        else
          p.resolve(Base64.encodeToString(q,Base64.NO_WRAP));
      }
    }
    catch (Throwable t) {
      p.reject(ESODIUM,ERR_FAILURE,t);
    }
  }

  // ***************************************************************************
  // * Public-key cryptography - signatures
  // ***************************************************************************
  @ReactMethod
  public void crypto_sign(final String msg, final String sk, final Promise p) {
    try {
      byte[] msgb = Base64.decode(msg, Base64.NO_WRAP);
      byte[] skb  = Base64.decode(sk, Base64.NO_WRAP);
      if (skb.length != Sodium.crypto_sign_secretkeybytes()){
        p.reject(ESODIUM,ERR_BAD_KEY);
      }
      else {
        byte[] msig = new byte[Sodium.crypto_sign_bytes() + msgb.length];
        int result = Sodium.crypto_sign(msig, msgb, msgb.length, skb);
        if (result != 0)
          p.reject(ESODIUM, ERR_FAILURE);
        else {
          p.resolve(Base64.encodeToString(msig, Base64.NO_WRAP));
        }
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }
  
  @ReactMethod
  public void crypto_sign_detached(final String msg, final String sk, final Promise p) {
    try {
      byte[] msgb = Base64.decode(msg, Base64.NO_WRAP);
      byte[] skb  = Base64.decode(sk, Base64.NO_WRAP);
      if (skb.length != Sodium.crypto_sign_secretkeybytes()){
        p.reject(ESODIUM,ERR_BAD_KEY);
      }
      else {
        byte[] sig = new byte[Sodium.crypto_sign_bytes()];
        int result = Sodium.crypto_sign_detached(sig, msgb, msgb.length, skb);
        if (result != 0)
          p.reject(ESODIUM, ERR_FAILURE);
        else {
          p.resolve(Base64.encodeToString(sig, Base64.NO_WRAP));
        }
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }

  @ReactMethod
  public void crypto_sign_verify_detached(final String sig, final String msg, final String pk, final Promise p) {
    try {
      byte[] sigb = Base64.decode(sig, Base64.NO_WRAP);
      byte[] msgb = Base64.decode(msg, Base64.NO_WRAP);
      byte[] pkb  = Base64.decode(pk, Base64.NO_WRAP);
      if (pkb.length != Sodium.crypto_sign_publickeybytes()){
        p.reject(ESODIUM,ERR_BAD_KEY);
      }
      if (sigb.length != Sodium.crypto_sign_bytes()){
        p.reject(ESODIUM,ERR_BAD_SIG);
      }
      else {
        int result = Sodium.crypto_sign_verify_detached(sigb, msgb, msgb.length, pkb);
        if (result != 0)
          p.reject(ESODIUM, ERR_FAILURE);
        else
          p.resolve(true);
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }

  @ReactMethod
  public void crypto_sign_keypair(final Promise p) {
    try {
      byte[] pk = new byte[Sodium.crypto_sign_publickeybytes()];
      byte[] sk = new byte[Sodium.crypto_sign_secretkeybytes()];

      int result = Sodium.crypto_sign_keypair(pk, sk);
      if (result != 0)
        p.reject(ESODIUM, ERR_FAILURE);
      else {
        WritableNativeMap map = new WritableNativeMap();
        map.putString("pk",Base64.encodeToString(pk,Base64.NO_WRAP));
        map.putString("sk",Base64.encodeToString(sk,Base64.NO_WRAP));
        p.resolve(map);
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }

  @ReactMethod
  public void crypto_sign_seed_keypair(final String seed, final Promise p) {
    try {
      byte[] seedb = Base64.decode(seed, Base64.NO_WRAP);
      byte[] pk = new byte[Sodium.crypto_sign_publickeybytes()];
      byte[] sk = new byte[Sodium.crypto_sign_secretkeybytes()];

      if (seedb.length != Sodium.crypto_sign_seedbytes()) {
        p.reject(ESODIUM,ERR_BAD_SEED);
      }
      else {
        int result = Sodium.crypto_sign_seed_keypair(pk, sk, seedb);
        if (result != 0)
          p.reject(ESODIUM, ERR_FAILURE);
        else {
          WritableNativeMap map = new WritableNativeMap();
          map.putString("pk",Base64.encodeToString(pk,Base64.NO_WRAP));
          map.putString("sk",Base64.encodeToString(sk,Base64.NO_WRAP));
          p.resolve(map);
        }
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }

  @ReactMethod
  public void crypto_sign_ed25519_sk_to_seed(final String sk, final Promise p) {
    try {
      byte[] skb = Base64.decode(sk, Base64.NO_WRAP);
      if(skb.length != Sodium.crypto_sign_secretkeybytes()){
        p.reject(ESODIUM,ERR_BAD_KEY);
      }
      else {
        byte[] seed = new byte[Sodium.crypto_box_secretkeybytes()];
        int result = Sodium.crypto_sign_ed25519_sk_to_seed(seed, skb);
        if (result != 0)
          p.reject(ESODIUM, ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(seed, Base64.NO_WRAP));
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }

  @ReactMethod
  public void crypto_sign_ed25519_pk_to_curve25519(final String pk, final Promise p) {
    try {
      byte[] pkb = Base64.decode(pk, Base64.NO_WRAP);
      if(pkb.length != Sodium.crypto_sign_publickeybytes()){
        p.reject(ESODIUM,ERR_BAD_KEY);
      }
      else {
        byte[] curve_pk = new byte[Sodium.crypto_sign_publickeybytes()];
        int result = Sodium.crypto_sign_ed25519_pk_to_curve25519(curve_pk, pkb);
        if (result != 0)
          p.reject(ESODIUM, ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(curve_pk, Base64.NO_WRAP));
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }

  @ReactMethod
  public void crypto_sign_ed25519_sk_to_curve25519(final String sk, final Promise p) {
    try {
      byte[] skb = Base64.decode(sk, Base64.NO_WRAP);
      if(skb.length != Sodium.crypto_sign_secretkeybytes()){
        p.reject(ESODIUM,ERR_BAD_KEY);
      }
      else {
        byte[] curve_sk = new byte[Sodium.crypto_box_secretkeybytes()];
        int result = Sodium.crypto_sign_ed25519_sk_to_curve25519(curve_sk, skb);
        if (result != 0)
          p.reject(ESODIUM, ERR_FAILURE);
        else
          p.resolve(Base64.encodeToString(curve_sk, Base64.NO_WRAP));
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }

  @ReactMethod
  public void crypto_sign_ed25519_sk_to_pk(final String sk, final Promise p) {
    try {
      byte[] skb = Base64.decode(sk, Base64.NO_WRAP);
      if(skb.length != Sodium.crypto_sign_secretkeybytes()){
        p.reject(ESODIUM,ERR_BAD_KEY);
      }
      else {
        byte[] pk = new byte[Sodium.crypto_sign_publickeybytes()];
        int result = Sodium.crypto_sign_ed25519_sk_to_pk(skb, pk);
        if (result != 0) {
          p.reject(ESODIUM, ERR_FAILURE);
        }
        else {
          p.resolve(Base64.encodeToString(pk, Base64.NO_WRAP));
        }
      }
    }
    catch(Throwable t) {
      p.reject(ESODIUM, ERR_FAILURE, t);
    }
  }

  // ***************************************************************************
  // * Utils
  // ***************************************************************************

  @ReactMethod
  public void to_base64(final String message, final int variant, final Promise p) {
    byte[] m = message.getBytes(StandardCharsets.UTF_8);
    String result = this.binToBase64(m, variant);
    if (result == null) {
      p.reject(ESODIUM,ERR_FAILURE);
    } else {
      p.resolve(result);
    }
  }

  @ReactMethod
  public void from_base64(final String cipher, final int variant, final Promise p) {
    byte[] result = this.base64ToBin(cipher, variant);
    if (result == null) {
      p.reject(ESODIUM,ERR_FAILURE);
    } else {
      p.resolve(new String(result, StandardCharsets.UTF_8));
    }
  }

  @ReactMethod
  public void to_hex(final String message, final Promise p) {
    byte[] m = message.getBytes(StandardCharsets.UTF_8);
    String result = this.binToHex(m);
    if (result == null) {
      p.reject(ESODIUM,ERR_FAILURE);
    } else {
      p.resolve(result);
    }
  }

  @ReactMethod
  public void from_hex(final String cipher, final Promise p) {
    byte[] result = this.hexToBin(cipher);
    if (result == null) {
      p.reject(ESODIUM,ERR_FAILURE);
    } else {
      p.resolve(new String(result, StandardCharsets.UTF_8));
    }
  }

  private String binToBase64(final byte[] data, final int variant) {
    try {
      if (data.length <= 0 || variant == 0)
        return null;
      else {
        int encoded_len = Sodium.sodium_base64_encoded_len(data.length, variant);
        byte[] encoded = new byte[encoded_len];
        Sodium.sodium_bin2base64(encoded, encoded_len, data, data.length, variant);
        String result = new String(encoded, StandardCharsets.UTF_8);
        return result.substring(0, result.length() - 1); // remove /0 byte
      }
    }
    catch (Throwable t) {
      return null;
    }
  }

  private byte[] base64ToBin(String cipher, final int variant) {
    try {
      byte[] c = cipher.getBytes(StandardCharsets.UTF_8);

      if (c.length <= 0 || variant == 0)
        return null;

      else {
        int blen = c.length;
        byte[] decoded = new byte[blen];
        int[] decoded_len = new int[1];
        int result = Sodium.sodium_base642bin(decoded, blen, c, c.length, null, decoded_len, null, variant);
        if (result != 0)
          return null;
        else
          return Arrays.copyOfRange(decoded, 0, decoded_len[0]);
      }
    }
    catch (Throwable t) {
      return null;
    }
  }

  private String binToHex(final byte[] data) {
    try {
      if (data.length <= 0)
        return null;

      else {
        int encoded_len = data.length * 2 + 1;
        byte[] encoded = new byte[encoded_len];
        Sodium.sodium_bin2hex(encoded, encoded_len, data, data.length);
        String result = new String(encoded, StandardCharsets.UTF_8);
        return result.substring(0, result.length() - 1); // remove /0 byte
      }
    } catch (Throwable t) {
      return null;
    }
  }

  private byte[] hexToBin(String cipher) {
    try {
      byte[] c = cipher.getBytes(StandardCharsets.UTF_8);

      if (c.length <= 0)
        return null;

      else {
        int blen = c.length;
        byte[] decoded = new byte[blen];
        int[] decoded_len = new int[1];
        int result = Sodium.sodium_hex2bin(decoded, blen, c, c.length, null, decoded_len, null);
        if (result != 0)
          return null;
        else
          return Arrays.copyOfRange(decoded, 0, decoded_len[0]);
      }
    } catch (Throwable t) {
      return null;
    }
  }
}
