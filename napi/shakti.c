#include <node_api.h>
#include <dlfcn.h>

// from r.h
typedef unsigned char C, *S, *K;
typedef int I;
typedef long long J;
typedef unsigned long long V;
#define wj (J)0x7fffffffffffffff
#define A(x)  ({V v=(V)(x),w=wj&v;w&&w<1L<<52?v>>48:KF;})
#define NK(x) ((I*)x)[-1]
#define xn  NK(x)
#define xi (I)(J)x
#define KC 1
#define KI 7
#define KJ 8
#define KF 14
#define KS 15
#define KE 0x8005
#define QQ(x) (KE==A(x))
// imports from k.so
K (*ex)(K);
K (*kp)(S);
K (*pn)(S,I);
K (*vx)(K);
S (*se)(I e);
void (*init)(void);

// some local shorthands for lazy developers
#define napi_iferr(a,x) if((a)){napi_throw_error(env,NULL,(x));}
#define napi_nok(x) napi_iferr(status != napi_ok,(x))

// evaluate k statement in local environment
napi_value shakti_k(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  C buf[256];size_t n;
  napi_value argv[1];
  K x;
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  napi_nok("Failed to parse arguments");
  status = napi_get_value_string_utf8(env, argv[0], buf, sizeof(buf), &n);
  napi_nok("Invalid number was passed as argument");
  napi_value res;
  x = ex(pn(buf, n));
  napi_iferr(QQ(x), se(15&xi));
  x = vx(x);
  status = napi_create_string_utf8(env, x, xn, &res);
  napi_nok("Unable to create return value");
  return res;
}

napi_value Init(napi_env env, napi_value exports) {
  void *dll;
  napi_status status;
  napi_value fn;
  char s[300];

  status = napi_create_function(env, NULL, 0, shakti_k, NULL, &fn);
  napi_nok("Unable to wrap native function");
  status = napi_set_named_property(env, exports, "k", fn);
  napi_nok("Unable to populate exports");
  
  dll = dlopen("k.so", RTLD_LAZY);
  napi_iferr(dll == NULL, dlerror());
  kp = dlsym(dll, "kp");
  pn = dlsym(dll, "pn");
  ex = dlsym(dll, "ex");
  vx = dlsym(dll, "vx");
  se = dlsym(dll, "se");
  init = dlsym(dll, "init");
  init();
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
